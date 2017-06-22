//TH-Header
//*****************************************************************************************
// Copyright (c)  2014  KURANT Project
// All rights reserved.
//
// $FileName    : Workspace.SL
// $ProjectName : The Hammer 2.0
// $Authors     : Wil van Antwerpen, Michael Kurz, Sergey V. Natarov
// $Created     : 01.25.2014  01:08
// $Type        : LGPL
//
// Contents: WorkSpace Selector
//
//*****************************************************************************************
//TH-RevisionStart
//TH-RevisionEnd

Use cWorkSpacePanel.pkg
Use WorkSpaceInfo.DG
Use vWin32fh.pkg
Use cWorkSpaceSortArray.pkg

Use cWorkspaceList.pkg
Use cLineControl.pkg

Cd_Popup_Object oWorkSpace is a cWorkspacePanel
    Set Label to "Select Workspace..."
    Set Location to 4 8
    Set Size to 240 230
    Set Border_Style to Border_Thick
    Set piMinSize to 240 230

    Object oVDFVersion                  is a ComboForm
        Set Label                       to "VDF &Version:"
        Set Size                        to 13 50
        Set Location                    to 4 50
        Set Form_Border                 to 0
        Set Label_Col_Offset            to 2
        Set Label_Justification_Mode    to jMode_Right
        Set entry_state item 0          to False
        Set combo_sort_state            to False // **WvA: 28-10-2004 Display VDF10 below VDF9
    
        On_Key kCancel Send Close_Panel
    
        Object oVDFVersionArray is a cWorkSpaceSortArray
            Set pbCheckRuntimeInstalled to True
        End_Object // oVDFVersionArray
    
        //
        // Enumerate the registry keys to get a list of all the installed VDF revisions.
        Procedure Combo_Fill_List
            Integer hoArray
            Integer iLoop
            String  sValue
            Move (oVdfVersionArray(Self)) to hoArray
            If (hoArray) Begin
                Send LoadArray of hoArray
                If (Item_Count(hoArray)=0) Begin
                    // There's a bug that sometimes the array doesn't get filled when calling it the first time.. calling it again
                    // fixes this.. no logical explanation at all.. but it works.
                    Send LoadArray of hoArray
                End
                Move 0 to iLoop
                While (iLoop<Item_count(hoArray))
                    Get VDFversion of hoArray item iLoop to sValue
                    Send Combo_Add_Item sValue
                    Increment iLoop
                Loop
            End
            //@ Set value Item 0 To (Combo_Value(Self,Combo_Item_Count(Self)-1))
            If (psVDFRegistryVersion(ghoEditorProperties)) Ne "" Begin
                Set value to (psVDFRegistryVersion(ghoEditorProperties))
            End
            Else Begin
                // 31.05.2005 RRS
                // See//@ Change by Raveen to eradicate the "file workspaces.ini could not be opened" error for uninstalled VDF versions.
                Set value item 0 to (Combo_Value(Self,Combo_Item_Count(Self)-1))
            End
        End_Procedure // Combo_Fill_List
    
        // Set the property pnVersion
        // Fill the workspace list
        Procedure onChange
            String  sCrntVersion
            String  sVer
            String  sSelectedTag
            Integer iCurrent
            Integer iCount
            Number nVer
            
            If (focus(Self) <> Self) Procedure_Return
            Get psVersion to sCrntVersion
            Get value to sVer
            Get piCurrentItem of oWorkspaceList to iCurrent
            Get WorkSpaceTag  of ghoWorkspaceHandlerEx iCurrent to sSelectedTag
            Set psVersion to sVer
            Send FillList to (oWorkspaceList(Self))
            Get StringVdfVersionToNum of ghoWorkspaceHandlerEx sVer to nVer
            If (nVer<120) Begin
                Set Enabled_State of (oBrowse_bn(Self)) to False
            End
            Else Begin
                Set Enabled_State of (oBrowse_bn(Self)) to True
            End
            Get Item_Count of (oWorkspaceList(Self)) to iCount
            If (iCount>0) Begin
                If (Enabled_State(oInfo_bn(Self))=False) Begin
                    Set Enabled_State of (oInfo_bn(Self))   to True
                    Set Enabled_State of (oSelect_bn(Self)) to True
                End
            End
            Else Begin
                Set Enabled_State of (oInfo_bn(Self)) to False
                Set Enabled_State of (oSelect_bn(Self)) to False
            End
        End_Procedure
    
        Procedure Previous
            Send Activate to (oClose_bn(Self))
        End_Procedure // Previous

    End_Object    // oVDFVersion

    Object oDisplay_fm is a ComboForm
        Set Size to 13 85
        Set Location to 4 140
        Set Form_Border to 0
        Set Label_Justification_Mode to jMode_Right
        Set Combo_Sort_State to False
        Set entry_state item 0 to False
        Set Label to "Display:"
        Set Label_Col_Offset to 2
        Set peAnchors to anTopLeftRight
        On_Key kCancel Send Close_Panel

        Define CS_WSDISP_DESCRIPTION for "Description"
        Define CS_WSDISP_KEY         for "Key"
        Define CS_WSDISP_BOTH        for "Both"

        Procedure Combo_Fill_List
            // Fill the combo list with Send Combo_Add_Item
            Send Combo_Add_Item CS_WSDISP_DESCRIPTION
            Send Combo_Add_Item CS_WSDISP_KEY
            Send Combo_Add_Item CS_WSDISP_BOTH
        End_Procedure  // Combo_fill_list

        // notification of a selection change or edit change
        Procedure OnChange
            String  sValue
            Integer iOldDisplayMode iNewDisplayMode
            
            If (focus(Self) <> Self) Procedure_Return
            Get pcDisplayWSList to iOldDisplayMode
            Get Value to sValue // the current selected item
            Case Begin
                Case (sValue = CS_WSDISP_DESCRIPTION)
                    Move ctWSDisplayDescription to iNewDisplayMode
                    Case Break
                Case (sValue = CS_WSDISP_KEY)
                    Move ctWSDisplayKey         to iNewDisplayMode
                    Case Break
                Case Else
                    Move ctWSDisplayBoth        to iNewDisplayMode
            Case End
            If (iOldDisplayMode <> iNewDisplayMode) Begin
                Set pcDisplayWSList to iNewDisplayMode
                Send FillList to (oWorkspaceList(Self))
            End
        End_Procedure  // OnChange

        Procedure Next
            Send activate to (oWorkspaceList(Self))
        End_Procedure

    End_Object    // oDisplay_fm

    Object oWorkspaceList is a cWorkspaceList
        Set Size to 190 220
        Set Location to 28 5
        Set peAnchors to anAll
        
        On_Key kCancel Send Close_Panel
        On_Key kEnter  Send Enter
        
        Procedure Enter
            Send Select
        End_Procedure
        
        Procedure Mouse_Click
            Send Enter
        End_Procedure
        
        // **WvA 27-6-2003 Added Dynamic Update State logic
        Procedure FillList
            String  sCur sVer
            Integer hKeyWrkSpc
            Number  nVer
            Integer bExists
            Integer iWrk iWorkspaceCount iDisplayMode
            String  sVDF sVDFRoot sWSName sWSPath sWStag sLine
            String  sMessage
            
            Get psVersion to sVer
            Get pcDisplayWSList to iDisplayMode
            // Clear the list control
            Send Delete_Data
            Get CurrentWorkspace sVer to sCur
            Send DoSetLabel sCur
            Send DoEnumerateWorkspaces to ghoWorkspaceHandlerEx sVer
            Get WorkspaceCount of ghoWorkspaceHandlerEx to iWorkspaceCount
            If iWorkSpaceCount Ge 0 Begin
                Set Dynamic_Update_State to False
                For iWrk from 0 to (iWorkSpaceCount - 1)
                    Get WorkSpaceName  of ghoWorkspaceHandlerEx item iWrk to sWSName
                    Get WorkSpaceTag   of ghoWorkspaceHandlerEx item iWrk to sWSTag
                    Get WorkSpacePath  of ghoWorkspaceHandlerEx item iWrk to sWSPath
                    If (Trim(sWSTag) = sCur) Begin
                        Set piCurrentItem to (Item_Count(Self))
                    End
                    Case Begin
                        Case (iDisplayMode = ctWSDisplayDescription)
                            Send Add_Item MSG_None sWSName
                            Case Break
                        Case (iDisplayMode = ctWSDisplayKey)
                            Send Add_Item MSG_None sWSTag
                            Case Break
                        Case Else
                            Send Add_Item MSG_None (sWSName+"   -   [ "+sWSTag+" ]")
                    Case End
                Loop
                Set Dynamic_Update_State to True
            End
            Set Current_Item to (piCurrentItem(Self))
        End_Procedure // FillList

    End_Object    // oWorkspaceList

    Object oLineControl1 is a cLineControl
        Set Size to 2 220
        Set Location to 22 5
        Set peAnchors to anTopLeftRight
    End_Object    // oLineControl1

    Object oInfo_bn is a Button
        Set Label to "&Info..."
        Set Location to 221 6
        Set peAnchors to anBottomRight
        On_Key kCancel Send Close_Panel
        Procedure OnClick
            Send Request_Info
        End_Procedure // OnClick
    End_Object    // oInfo_bn

    Object oBrowse_bn is a Button
        Set Label to "&Browse..."
        Set Location to 221 62
        Set peAnchors to anBottomRight
        Procedure OnClick
            Send Request_Browse
        End_Procedure // OnClick
    End_Object    // oBrowse_bn

    Object oSelect_bn is a Button
        Set Label to "&Select"
        Set Location to 221 118
        Set Default_State to True
        Set peAnchors to anBottomRight
        On_Key kCancel Send Close_Panel
        Procedure OnClick
            Send Select
        End_Procedure // OnClick
    End_Object    // oSelect_bn

    Object oClose_bn is a Button
        Set Label to "&Close"
        Set Location to 221 174
        Set peAnchors to anBottomRight
        On_Key kCancel Send Close_Panel
        Procedure OnClick
            Send Close_Panel
        End_Procedure // OnClick
    End_Object    // oClose_bn

    On_Key KEY_ALT+KEY_V Send Activate to oVDFVersion
    On_Key Key_Alt+Key_D Send Activate to oDisplay_fm
    On_Key Key_Alt+Key_I Send Request_Info //Activate To oInfo_bn
    On_Key Key_Alt+Key_S Send Activate to oSelect_bn
    On_Key Key_Alt+Key_C Send Activate to oClose_bn

    Procedure DoSetLabel String sWrkSpcTag
        String sLabel
        If (sWrkSpcTag<>"") Begin
            Move sWrkSpcTag to sLabel
            If (Pos(".sws",Lowercase(sLabel))<>0) Begin
                Get DeriveDescriptionFromStudioFile of ghoWorkspaceHandlerEx sLabel to sLabel
            End
            Move ("Select Workspace - ["+sLabel+"]") to sLabel
        End
        Else Move "Select Workspace..." to sLabel
        Set Label to sLabel
    End_Procedure // DoSetLabel

    Procedure Popup_Group
        String #ver
        Forward Send Popup_Group
        Get psVDFVersion of ghoWorkSpaceHandlerEx to #ver
        Set value of (oVDFVersion(Self)) to #ver
        Send Activate   to (oWorkspaceList(Self))
    End_Procedure

    //
    // Returns the currently selected workspace tag and
    // sets the psCurrentWorkspace property
    //
    Function CurrentWorkspace String sVer Returns String
        String sCur
        Get fsCurrentWorkspace of ghoWorkspaceHandlerEx sVer   to sCur
        Set psCurrentWorkSpace to sCur
        Function_Return sCur
    End_Function // CurrentWorkspace

    // Selects the Workspace passed in sWrkSpcTag
    //
    // - Updates the Current Workspace tag in the registry with what we selected (sWrkSpcTag)
    // - Sets our global VDFVersion property
    // - Updates all the Currentxxxxxxx properties in the workspace handler
    //     and changes the Open_Path
    // - Saves the Editor properties
    Procedure SelectCurrentWorkSpace String sWrkSpcTag
        String sKey sVer
        Get psVersion to sVer
        // Update the Current workspace TaG in the registry
        Send ChangeCurrentWorkspace of ghoWorkSpaceHandlerEx sWrkSpcTag sVer
        Set psVDFVersion      of ghoWorkSpaceHandlerEx   to sVer
        Send doLoadVDFVersionInfo to ghoWorkSpaceHandlerEx
        // Set the global VDF Version equal to our selection
        Set VDFVersion      of Desktop to sVer
        Send DoSetOpenPath  to ghoWorkSpaceHandlerEx sWrkSpcTag
        Send LoadNonEmbeddedDriverAutoLoginPrompt of ghoWorkSpaceHandlerEx
        Send SaveIni        to ghoEditorProperties // Save it here because the SmartDosBox needs the info.
    End_Procedure // SelectCurrentWorkSpace


      // Perform the actual selection
    Procedure Select
        Integer iChanged iOk
        Integer iCurrent
        String  sWrkSpc sDir
        String  sWSName sWSPath sVer
        Number  nVer
        
        Get pnVersion to nVer
        Get psVersion to sVer
        Move (Current_Item(oWorkspaceList(Self))) to iCurrent
        Get WorkspaceTag  of ghoWorkSpaceHandlerEx  item iCurrent to sWrkSpc
        Get WorkspaceName of ghoWorkSpaceHandlerEx  item iCurrent to sWSName
        Get WorkspacePath of ghoWorkSpaceHandlerEx  item iCurrent to sWSPath
        
        Set psBufferWsTag      of ghoWorkSpaceHandlerEx to sWrkSpc
        // psversion == psbuffervdfversion
        //Set psBufferVdfVersion Of ghoWorkSpaceHandlerEx To sVer
        Set psBufferWsName     of ghoWorkSpaceHandlerEx to sWSName
        Set psBufferHome       of ghoWorkSpaceHandlerEx to sWSPath
        
        // Changed to support Reopen of Files based on Workspace
        // 18.05.01 Bernhard
        Get RequestChangeWorkspace of desktop sWrkSpc to iChanged
        If iChanged Begin
            Send AddRecentWorkspace to ghoEditorProperties sWrkSpc sWSName sVer
            Send SaveIni            to ghoEditorProperties
            Send SelectCurrentWorkSpace sWrkSpc
            Get  CurrentAppSrcPath of ghoWorkSpaceHandlerEx to sDir
            Send SelectWorkingDirectory sDir
            // Added 17.05.01 Bernhard
            Send OnWorkSpaceChanged
        End
        Send Close_Panel
    End_Procedure  // Select

    Procedure WorkSpaceInfoCallBack Integer iObj
        String sVer sNewKey sWrkSpc sName sDir sPath sVal
        Integer iOk iCurrent
        String sWSName sWSPath
        Get psVersion to sVer
        Move (Current_Item(oWorkspaceList(Self))) to iCurrent
        Get WorkspaceTag    of ghoWorkSpaceHandlerEx  item iCurrent to sWrkSpc
        Get WorkspaceName   of ghoWorkSpaceHandlerEx  item iCurrent to sWSName
        Get WorkspacePath   of ghoWorkSpaceHandlerEx  item iCurrent to sWSPath
        Set psBufferWsTag      of ghoWorkSpaceHandlerEx to sWrkSpc
        Set psBufferWsName     of ghoWorkSpaceHandlerEx to sWSName
        Set psBufferHome       of ghoWorkSpaceHandlerEx to sWSPath
        
        Get DoReadApplicationWorkspace of ghoWorkSpaceHandlerEx sWrkSpc sVer sWSPath True to iOK
        If not (iOk) Error 350 "Failed to read the data for the Application's workspace"
    End_Procedure // WorkSpaceInfoCallBack

    // Popup the workspace info dialog
    Procedure Request_Info
        Send Popup to (oWorkSpaceInfo(Self))
    End_Procedure

    Procedure Request_Browse
        String  sFileTypes
        String  sCaptionText
        String  sInitFolder
        String  sFile
        String  sStudio
        String  sVdfRootDir
        Boolean bExists
    
        Move "Select a workspace to register" to sCaptionText
        Move "Workspaces files|*.sws;*.ws|Studio Workspace files|*.sws|All files|*.*" to sFileTypes
        Get LastWorkspaceFolder of ghoWorkSpaceHandlerEx to sInitFolder
    
        Get vSelect_File sFileTypes sCaptionText sInitFolder to sFile
        If (sFile<>"") Begin
            Get psVdfRootDir of ghoWorkSpaceHandlerEx to sVdfRootDir
            Move (sVdfRootDir+"Bin\Studio.exe") to sStudio
            Get vFilePathExists sStudio to bExists
            If (bExists) Begin
                Runprogram Wait (sStudio+' -x"'+sFile+'"')
                // refresh list after exiting the studio
                Send FillList to (oWorkspaceList(Self))
            End
            Else Begin
                Send Info_box "Unable to locate the Visual DataFlex Studio to register this workspace."
            End
        End
    End_Procedure // Request_Browse

Cd_End_Object    // oWorkSpace

