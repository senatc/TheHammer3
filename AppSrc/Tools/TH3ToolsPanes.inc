// TH3ToolPanes.inc
// Created by Sergey V Natarov (senatc@postman.ru) on 09/03/2017 @ 11:40
//

Use Flexml.pkg
Use Tools\TH3Workspace.pkg
Use Tools\cDatabaseTreeView.pkg
Use Tools\cWorkspaceTreeView.pkg
Use Tools\cOutputDialog.pkg
Use Tools\TH3WorkspaceConfigure.dg
Use cToolsPalette.pkg

Struct tDFCompileOutput
    String  sFile
    Integer iLine
End_Struct

Struct tDFClassList
  String  sClassName
  String  sImage
  String  sPackage
  String  sLibraryID
End_Struct

Struct tDFClassGroup
    String          sName
    tDFClassList[]  ltDFClassList
End_Struct

Object oToolPane is a Container3d
    Set Size to 50 100
    Set Location to 9 9
    Set Border_Style to Border_None
    Object oToolsDialog is a TabDialog
        Set Size to 204 181
        Set Location to 1 1
        Set Rotate_Mode to RM_Rotate
        Set peAnchors to anAll
        Set peTabStyle to tsFlatButtons
        Set peTabPosition to tpBottom
        Set TabWidth_Mode to twRaggedRight //twFixedWidth
        Set pbFlatSeparators to True
        //
        Object oAppImageList is a cImageList32
            Set piMaxImages to 3
            Procedure OnCreate // add the images
                Integer iImage
                Get AddImage 'Palette16.ico' to iImage
                Get AddImage 'Database16.ico' clFuchsia to iImage
                Get AddImage 'THSource16.ico' to iImage
                Get AddImage 'Folders16.ico' to iImage
            End_Procedure
        End_Object
        Set phoImageList to (oAppImageList(Self))
        //
        Object oTP_Workspace is a TabPage
            Set piImageIndex to 3
            Set Tab_ToolTip_Value to 'Workspace'
            Set Label to "Workspace" //"W"
            //
            Object oWorkspaceCommandBar     is a cCJCommandBarSystem
            
                Object oWorkspaceToolBar    is a cCJToolbar
                    Set psTitle             to "Manage Workspace"
                    Set pbCloseable         to False
                    Set pbCustomizable      to False
                    Set pbEnableDocking     to False
                    Set pbGripper           to False
                    
                    Object oAddFolderMenuItem is a cCJMenuItem
                        Set psCaption   to "Add Folder"
                        Set psToolTip   to "Add Folder"
                        Set psImage     to "THAddFolder16.ico"
                        Procedure OnExecute Variant vCommandBarControl
                            Send mAddFolder
                        End_Procedure
                    End_Object
                    
                    Object oRemoveFolderMenuItem is a cCJMenuItem
                        Set pbControlBeginGroup to True
                        Set psCaption   to "Remove Folder"
                        Set psToolTip   to "Remove Folder"
                        Set psImage     to "THRemoveFolder16.ico"
                        Set pbActiveUpdate to True
                        Procedure OnExecute Variant vCommandBarControl
                            Send mRemoveElement
                        End_Procedure
                        Function IsEnabled Returns Boolean
                            Boolean bEnabled
                            Get CanRemoveElement of (oFilesTree(Self)) to bEnabled
                            Function_Return bEnabled
                        End_Function
                    End_Object
                    
                    Object oCollapseFolderMenuItem is a cCJMenuItem
                        Set pbControlBeginGroup to True
                        Set psCaption   to "Collapse"
                        Set psToolTip   to "Collapse Workspace Tree"
                        Set psImage     to "Collapse16.ico"
                        Procedure OnExecute Variant vCommandBarControl
                            Send CollapseFilesTree
                        End_Procedure
                    End_Object
                    
                    Object oExpandFolderMenuItem is a cCJMenuItem
                        Set pbControlBeginGroup to True
                        Set psCaption   to "Expand"
                        Set psToolTip   to "Expand Workspace Tree"
                        Set psImage     to "Expand16.ico"
                        Procedure OnExecute Variant vCommandBarControl
                            Send ExpandFilesTree
                        End_Procedure
                    End_Object

                    Object oShowPathMenuItem is a cCJMenuItem
                        Set pbControlBeginGroup to True
                        Set psCaption   to "Paths"
                        Set psToolTip   to "Show File Path"
                        Set psImage     to "Tooltip16.ico"
                        Set pbChecked   to True
                        Procedure OnExecute Variant vCommandBarControl
                            Send ToggleInfoTips
                        End_Procedure
                        Function IsChecked Returns Boolean
                            Boolean bOn
                            Get WorkspacePathTip to bOn
                            Function_Return bOn
                        End_Function
                    End_Object
                    
                    Object oConfigMenuItem is a cCJMenuItem
                        Set pbControlBeginGroup to True
                        Set psCaption   to "Configure"
                        Set psToolTip   to "Configure Project Workspace"
                        Set psImage     to "Configure16.ico"
                        Procedure OnExecute Variant vCommandBarControl
                            Send Popup                  to oTH3WorkspaceConfigure
                            Send LoadWorkspaceStructure to oFilesTree
                        End_Procedure
                    End_Object
                    
                End_Object
                    
            End_Object
            //
            Object oListFolders is an OpenDirDialog
                Set Dialog_Caption to "Select Source Directory"
            End_Object
            //
            Procedure mAddFolder
                Integer iOK
                String sFolder
                Get Show_Dialog of oListFolders to iOK
                If (iOK) Begin
                    Get Dir_Name of oListFolders to sFolder
                    Move sFolder to gtTHWorkspace.saFolders[SizeOfArray(gtTHWorkspace.saFolders)]
                    Send THDoWriteWorkspace gtTHWorkspace.sFullName
                    Send LoadWorkspaceStructure to oFilesTree
                End
            End_Procedure
            //
            Procedure mRemoveElement
                Integer iOK
                Handle  hItem
                Integer iData iFolder iFolders iCount
                String[] saFileName saFolders
                String  sFolder
                Get psFileName      of oFilesTree       to saFileName
                Get CurrentTreeItem of oFilesTree       to hItem
                Get ItemData        of oFilesTree hItem to iData
                Get YesNo_Box ("Confirm you wish remove\n\n"*saFileName[iData]*"\n\nfrom The Hammer project?") ;
                               "Confirmation" MBR_No    to iOK
                If (iOK=MBR_Yes) Begin
                    Send mRemoveFolder to oFilesTree saFileName[iData]
                    Send THDoWriteWorkspace gtTHWorkspace.sFullName
                    Send LoadWorkspaceStructure to oFilesTree
                End
            End_Procedure
            //
            Object oFilesTree is a cWorkspaceTreeView
                Set Size to 176 180
                Set Location to 24 0
                Procedure End_Construct_Object
                    Forward Send End_Construct_Object
                    Get Object_Id to ghoWorkspaceFilesTree
                End_Procedure
            End_Object // oFilesTree
            Object oFilter is a Form
                Set Size to 11 196
                Set Location to 14 0
                Set peAnchors to anTopLeftRight
                Set Color to gtColorer[EC_TEXT].iBackC
                On_Key Key_Down_Arrow Send GotoTree
                Procedure GotoTree
                    Send Activate to oFilesTree
                End_Procedure
                Procedure OnChange
                    Send UpdateTree
                End_Procedure
            End_Object
            Procedure UpdateTree
                String sFilter
                Get Value of oFilter to sFilter
                Send SearchFiles to oFilesTree sFilter
                Set Color of oFilter to gtColorer[EC_TEXT].iBackC
                If (sFilter<>"") Set Color of oFilter to (RGB(255,200,200))
            End_Procedure
            Procedure ExpandFilesTree
                Handle hItem
                Get RootItem of oFilesTree to hItem
                Send DoExpandAll to oFilesTree
                Send DoMakeItemFirstVisible to oFilesTree hItem
                Set piCollapsed of oFilesTree to False
            End_Procedure
            Procedure CollapseFilesTree
                Handle hItem
                Get RootItem of oFilesTree to hItem
                Send DoCollapseAll to oFilesTree hItem
                Send DoExpandItem to oFilesTree hItem
                Set piCollapsed of oFilesTree to True
            End_Procedure
            Procedure ToggleInfoTips
                Set pbEnableInfoTips of oFilesTree to (not(pbEnableInfoTips(oFilesTree(Self))))
            End_Procedure
            Function WorkspacePathTip Returns Integer
                Function_Return (pbEnableInfoTips(oFilesTree(Self)))
            End_Function
        End_Object // oTP_Workspace
        //
        Object oTP_Database is a TabPage
            Set piImageIndex to 1
            Set Tab_ToolTip_Value to 'Database'
            Set Label to "Data" //"D"
    
            Object oTablesTree is a cDatabaseTreeView
                Set Size to 166 180
                Set Location to 11 0
            End_Object // oParserTree

            Object oSortBy is a CheckBox
                Set Size to 10 50
                Set Location to 178 1
                Set Label to "Sort by Name"
                Set peAnchors to anBottomLeft
                Procedure OnChange
                    Send UpdateTree
                End_Procedure
            End_Object
            Object oFilter is a Form
                Set Size to 11 196
                Set Location to 1 0
                Set Color to gtColorer[EC_TEXT].iBackC
                Set peAnchors to anTopLeftRight
                Procedure OnChange
                    Send UpdateTree
                End_Procedure
            End_Object
            Procedure UpdateTree
                Boolean bChecked
                String sFilter
                Get Checked_State of oSortBy to bChecked
                Get Value of oFilter to sFilter
                Set Color of oFilter to gtColorer[EC_TEXT].iBackC
                If (sFilter<>"") Set Color of oFilter to (RGB(255,200,200))
                Send LoadTablesList to oTablesTree bChecked sFilter
            End_Procedure

        End_Object // TP_Database

        Object oTP_Palette is a TabPage
            Set piImageIndex to 0
            Set Tab_ToolTip_Value to 'Palette'
            Set Label to "Palette"
            
            Object oPalette is a cToolsPalette
                Set Size        to 200 200
                Set Location    to -1 -1

                Function ButtonTemplate Integer iData Returns String
                    String sOpenPath sVdfConfig sTemplate sObject sClass sName sPkg
                    String[] saClassList saPackageList
                    Get psClassList     to saClassList
                    Get psPackageList   to saPackageList
                    //
                    Get psVdfRootDir   of ghoWorkSpaceHandlerEx to sVdfConfig
                    Move (sVdfConfig + "\Pkg\Config\;") to sVdfConfig
                    Get_Attribute DF_OPEN_PATH to sOpenPath
                    Set_Attribute DF_OPEN_PATH to (sVdfConfig+sOpenPath)
                    Direct_Input (saClassList[iData]+".dfo")
                    If (not(SeqEof)) Begin
                        Read_Block sTemplate 4096
                    End
                    Close_Input
                    Set_Attribute DF_OPEN_PATH to sOpenPath
                    //
                    Move (saClassList[iData]) to sClass
                    Move sClass to sObject
                    If (Left(sObject, 1)="c") Move (Right(sObject, Length(sClass)-1)) to sObject
                    Move ("o"+sObject) to sName
                    Move ("Object"*sName*"is a"*sClass) to sObject
                    If (sTemplate<>"") Begin
                        Move (Trim(sTemplate)) to sTemplate
                        If (Left(Uppercase(sTemplate), 6)="OBJECT") Begin
                            Move (Right(sTemplate, Length(sTemplate)-6)) to sTemplate
                            Move (sObject+sTemplate * "//"*sName) to sObject
                        End
                    End
                    Else Move (sObject + Character(13)+Character(10)+"End_Object //"*sName) to sObject
                    //
                    Move ("Use" * saPackageList[iData]+ Character(13)+Character(10)+sObject+ Character(13)+Character(10)) to sObject
                    Function_Return sObject
                End_Function
                
                Procedure OnClassSelect Integer iData
                    // In case you need something on Button click
                    // For example, show Class builder etc (if required)
                End_Procedure
                
                Procedure DoCreatePalette
                    Integer iPage iBtn iPgNo
                    String sLabel
                    Integer iGroup iGroups
                    Integer iClass iClasses iItem
                    tDFClassGroup[] ltDFClassGroups
                    String[] saClassList
                    String[] saPackageList
                    Handle   hoClient
                    //
                    Send Delete_Data
                    //
                    String sOpenPath sVdfConfig
                    Get psVdfRootDir   of ghoWorkSpaceHandlerEx to sVdfConfig
                    Move (sVdfConfig + "\Pkg\Config\;") to sVdfConfig
                    Get_Attribute DF_OPEN_PATH to sOpenPath
                    Set_Attribute DF_OPEN_PATH to (sVdfConfig+sOpenPath)
                    //
                    Get Client_Id to hoClient
                    Send LoadClassList of hoClient (&ltDFClassGroups)
                    //
                    Move (SizeOfArray(ltDFClassGroups)) to iGroups
                    For iGroup from 0 to (iGroups-1)
                        Move (SizeOfArray(ltDFClassGroups[iGroup].ltDFClassList)) to iClasses
                        If iClasses Begin
                            Get Create_Palette_Page ltDFClassGroups[iGroup].sName to iPage
                            For iClass from 0 to (iClasses-1)
                                Move (SizeOfArray(saClassList)) to iItem
                                Move ltDFClassGroups[iGroup].ltDFClassList[iClass].sClassName to saClassList[iItem]
                                Move ltDFClassGroups[iGroup].ltDFClassList[iClass].sPackage   to saPackageList[iItem]
                                Get Create_Palette_Button Msg_OnClassSelect ;
                                    ltDFClassGroups[iGroup].ltDFClassList[iClass].sClassName ;
                                    ltDFClassGroups[iGroup].ltDFClassList[iClass].sImage ;
                                        iItem to iBtn
                                Set Page_Button of iPage iClass to iBtn
                            Loop
                        End
                    Loop
                    //
                    Set psClassList to saClassList
                    Set psPackageList to saPackageList
                    Set_Attribute DF_OPEN_PATH to sOpenPath
                    Send UpdatePalette
                End_Procedure

                Procedure OnCreatePalette
                End_Procedure
                
                Procedure UpdatePalette
                    Integer iPage
                    Set Visible_State to False
                    Get Current_Page to iPage
                    Send Show_Page 0
                    Send Show_Page (Total_Pages(Self))
                    Send Show_Page iPage
                    Set Visible_State to True
                End_Procedure

                // Adjust cToolsPalette on Resize actions...
                Procedure Set GUISize Integer iY Integer iX
                    Forward Set GUISize to iY iX
                    Send UpdatePalette
                End_Procedure

            End_Object // oPalette

        End_Object
//        //
//        Object oTP_Code is a TabPage
//            Set piImageIndex to 2
//            Set Tab_ToolTip_Value  to 'Code'
//            Set Label to "C"
//            Object oTablesTree is a TreeView
//                Set Size to 166 180
//                Set Location to 11 0
//            End_Object // oParserTree
//        End_Object
        //
    End_Object // oToolsDialog

    Procedure RebuildPanes
        Boolean bChecked
        Get Checked_State of (oSortBy(oTP_Database(oToolsDialog(Self)))) to bChecked
        Send LoadWorkspaceStructure to (oFilesTree(oTP_Workspace(oToolsDialog(Self))))
        Send LoadTablesList to (oTablesTree(oTP_Database(oToolsDialog(Self)))) bChecked ""
        Send DoCreatePalette to (oPalette(oTP_Palette(oToolsDialog(Self))))
    End_Procedure
    
    Procedure ColorsLikeEdit
        Handle hTarget
        // Workspace Explorer
        Move (oFilter(oTP_Workspace(oToolsDialog(Self)))) to hTarget
        Set TextColor   of hTarget                  to gtColorer[EC_TEXT].iForeC
        Set Color      	of hTarget                  to gtColorer[EC_TEXT].iBackC
        Set TextColor   of ghoWorkspaceFilesTree    to gtColorer[EC_TEXT].iForeC
        Set Color      	of ghoWorkspaceFilesTree    to gtColorer[EC_TEXT].iBackC
        Set piTextColor of ghoWorkspaceFilesTree    to gtColorer[EC_TEXT].iForeC
        Set piBackColor of ghoWorkspaceFilesTree    to gtColorer[EC_TEXT].iBackC
        Set piLineColor of ghoWorkspaceFilesTree    to gtColorer[EC_TEXT].iForeC
        // Database Explorer
        Move (oFilter(oTP_Database(oToolsDialog(Self)))) to hTarget
        Set TextColor   of hTarget                  to gtColorer[EC_TEXT].iForeC
        Set Color      	of hTarget                  to gtColorer[EC_TEXT].iBackC
        Move (oTablesTree(oTP_Database(oToolsDialog(Self)))) to hTarget
        Set TextColor   of hTarget                  to gtColorer[EC_TEXT].iForeC
        Set Color      	of hTarget                  to gtColorer[EC_TEXT].iBackC
        Set piTextColor of hTarget                  to gtColorer[EC_TEXT].iForeC
        Set piBackColor of hTarget                  to gtColorer[EC_TEXT].iBackC
        Set piLineColor of hTarget                  to gtColorer[EC_TEXT].iForeC
    End_Procedure

End_Object

Object oOutputPane is a Container3d
    Set Size to 50 100
    Set Location to 0 0
    Set Border_Style to Border_None
    //
    Object oOutputDialog is a cOutputDialog
        //
        Object oBuildPage is a TabPage
            Set piImageIndex to 0
            Set Tab_ToolTip_Value to 'Build'
            Set Label to "Build" //"W"
            //
            Object oMessages is a cObject
            End_Object
            //
            Object oCompilerInfo is a TreeView
                Property Handle phRoot 0
                Property String psLastWarning ""
                Property tDFCompileOutput[] ptDFCompileOutput
                Property String[] psErrors
                Set Size        to 200 200
                Set Location    to 0 0
                Set peAnchors   to anAll
                Set piBackColor to gtColorer[EC_TEXT].iBackC
                Set piTextColor to gtColorer[EC_TEXT].iForeC
                Set piLineColor to gtColorer[EC_TEXT].iForeC

                Object oImageList is a cImageList32
                    Set piMaxImages to 3
                    Procedure OnCreate // add the images
                        Integer iImage
                        Get AddBitmap 'Compile16.bmp' clFuchsia to iImage
                        Get AddBitmap 'Include16.bmp' clFuchsia to iImage
                        Get AddBitmap 'Warning16.bmp' clFuchsia to iImage
                        Get AddBitmap 'Error16.bmp'   clFuchsia to iImage
                        Get AddBitmap 'Stop16.bmp'    clFuchsia to iImage
                        Get AddBitmap 'Build16.bmp'   clFuchsia to iImage
                        Get AddBitmap 'Run16.bmp'     clFuchsia to iImage
                    End_Procedure
                End_Object
                Set ImageListObject to (oImageList(Self))

                Register_Object oEdit
                Procedure OnItemDblClick Handle hItem Boolean ByRef bCancel
                    Integer iData
                    String  sPathFile
                    Handle  hoClient hoEditor
                    tDFCompileOutput[] ltDFCompileOutput
                    //
                    Get Client_Id to hoClient
                    If (hItem<>0) Begin
                        Get ItemData hItem to iData
                        Get ptDFCompileOutput to ltDFCompileOutput
                        If (SizeOfArray(ltDFCompileOutput)) Begin
                            Get FileNameOnDisk ltDFCompileOutput[iData].sFile to sPathFile
                            Send CAOpenFile of hoClient sPathFile
                            Get FindViewByFileName of hoClient sPathFile to hoEditor
                            If (hoEditor) Begin
                                Send Activate to (oEdit(hoEditor))
                                If (ltDFCompileOutput[iData].iLine) Begin
                                    Send GotoLine to (oEdit(hoEditor)) (ltDFCompileOutput[iData].iLine-1)
                                    Get CM_SetHighlightedLine of (oEdit(hoEditor)) (ltDFCompileOutput[iData].iLine-1) to iData
                                End
                            End
                        End
                    End
                End_Procedure
                
                Procedure Delete_Data
                    tDFCompileOutput[] ltDFCompileOutput
                    String[] lasErrors
                    Send ClearAll
                    Set phRoot to 0
                    Set ptDFCompileOutput to ltDFCompileOutput
                    Set psLastWarning to ""
                    Set psErrors to lasErrors
                End_Procedure
                
                Procedure mStart String sLabel
                    Handle hRoot
                    Send Delete_Data
                    Get AddTreeItem sLabel 0 0 0 0 to hRoot
                    Set phRoot to hRoot
                End_Procedure
                
                Function LabelData String sLabel Returns Integer
                    tDFCompileOutput[] ltDFCompileOutput
                    String sTemp sLine sFile
                    Integer iItem
                    //
                    Get ptDFCompileOutput to ltDFCompileOutput
                    Move 0 to iItem
                    //
                    Move (Uppercase(Trim(sLabel))) to sLabel
                    If (sLabel contains "COMPILING PROGRAM:") Begin
                        Move (Left(sLabel, 19)) to sTemp
                        Move (Replace(sTemp, sLabel, "")) to sLabel
                        Move sLabel to sFile
                    End
                    If (sLabel contains "INCLUDING FILE:") Begin
                        Move (Left(sLabel, Pos('(', sLabel))) to sTemp
                        Move (Replace(sTemp, sLabel, "")) to sLabel
                        Move (Left(sLabel, Length(sLabel)-1)) to sLabel
                        If (sLabel contains ".PKD") Begin
                            Move (Replace(".PKD", sLabel, ".PKG")) to sLabel
                        End
                        Move sLabel to sFile
                    End
                    If (sLabel contains "ON LINE:") Begin
                        // Line
                        Move (Left(sLabel, Pos('ON LINE:', sLabel)+8)) to sTemp
                        Move (Trim(Replace(sTemp, sLabel, ""))) to sLabel
                        Move (Trim(Left(sLabel, Pos('(', sLabel)-1))) to sTemp
                        Move (Trim(Replace(sTemp, sLabel, ""))) to sLabel
                        Move sTemp to sLine
                        Move (Left(sLabel, Pos('OF FILE:', sLabel)+8)) to sTemp
                        Move (Trim(Replace(sTemp, sLabel, ""))) to sLabel
                        Move sLabel to sFile
                    End
                    If (sFile<>"") Begin
                        Move (SizeOfArray(ltDFCompileOutput)) to iItem
                        Move sFile to ltDFCompileOutput[iItem].sFile
                        Move sLine to ltDFCompileOutput[iItem].iLine
                    End
                    //
                    Set ptDFCompileOutput to ltDFCompileOutput
                    //
                    Function_Return iItem
                End_Function
                
                Procedure AddMessage String sLabel Integer iImg
                    Handle hRoot
                    Integer iData
                    String[] lasErrors
                    If (iImg<>2) Begin
                        Get phRoot to hRoot
                        Get psErrors to lasErrors
                        Get AddTreeItem sLabel hRoot 0 iImg iImg to hRoot
                        Get LabelData sLabel to iData
                        Set ItemData hRoot to iData
                        Send DoMakeItemFirstVisible hRoot
                        If (iImg=3) Begin
                            If (psLastWarning(Self)<>"") Begin
                                Get AddTreeItem (psLastWarning(Self)) hRoot 0 2 2 to hRoot
                                Set ItemData hRoot to iData
                            End
                            Move sLabel to lasErrors[SizeOfArray(lasErrors)]
                        End
                        Set psLastWarning to ""
                        Set psErrors to lasErrors
                    End
                    Else Set psLastWarning to sLabel
                End_Procedure
                
                Procedure mFinish String sLabel
                    Handle hRoot hItem
                    Integer iError iErrors iData
                    String[] lasErrors
                    Get psErrors to lasErrors
                    Get phRoot to hRoot
                    Get AddTreeItem sLabel hRoot 0 4 4 to hItem
                    Send DoMakeItemFirstVisible hItem
                    Move (SizeOfArray(lasErrors)) to iErrors
                    If iErrors Begin
                        Get AddTreeItem "---- Compiler Error Summary ----" hRoot 0 3 3 to hRoot
                        For iError from 0 to (iErrors-1)
                            Get LabelData lasErrors[iError] to iData
                            Get AddTreeItem lasErrors[iError] hRoot 0 3 3 to hItem
                            Set ItemData hItem to iData
                            Send DoMakeItemFirstVisible hItem
                            Send DoMakeItemFirstVisible hRoot
                        Loop
                    End
                End_Procedure
                
                Procedure End_Construct_Object
                    Forward Send End_Construct_Object
                    Get Object_Id to ghoCompilerInfo
                End_Procedure
            End_Object
        End_Object
    End_Object
    Object oErrors is an Array
        Object oTabFindObjects is an Array
        End_Object
        Object oTabPage1 is an Array
            Object oErrorList is an Array
            End_Object
        End_Object
    End_Object
    Procedure ColorsLikeEdit
        Handle hTarget hoPage hoTabDlg
        // Build Page
        Move (oCompilerInfo(oBuildPage(oOutputDialog(Self)))) to hTarget
        Set TextColor   of hTarget                  to gtColorer[EC_TEXT].iForeC
        Set Color      	of hTarget                  to gtColorer[EC_TEXT].iBackC
        Set piTextColor of hTarget                  to gtColorer[EC_TEXT].iForeC
        Set piBackColor of hTarget                  to gtColorer[EC_TEXT].iBackC
        Set piLineColor of hTarget                  to gtColorer[EC_TEXT].iForeC
        // Possible Search Result Pages
        Integer iPage iPages
        Move (oOutputDialog(Self)) to hoTabDlg
        Get Item_Count of hoTabDlg to iPages
        If (iPages>1) Begin
            For iPage from 1 to (iPages-1)
                Get tab_page_id of hoTabDlg item iPage to hoPage
                If hoPage Begin
                    Move (oMessages(hoPage)) to hoPage
                    Set piTextColor of hoPage to gtColorer[EC_TEXT].iForeC
                    Set piBackColor of hoPage to gtColorer[EC_TEXT].iBackC
                    Set piLineColor of hoPage to gtColorer[EC_TEXT].iForeC
                End
            Loop
        End
    End_Procedure
End_Object

Procedure Add_Tool_Pane Handle hoCmdBars Handle hoTool String sTitle Integer iLocation Integer bVisible Integer ByRef lhoPane Integer iWidth Integer iHeight
    Variant vToolPane vCommandBars
    Handle  hoToolPane
    Handle  hWnd
    Get ComAddDialogBar     of hoCmdBars sTitle iLocation         to vToolPane
    Get Create              of hoCmdBars (RefClass(cCJDialogBar)) to hoToolPane
    //
    If (hoToolPane) Begin
        Set pvComObject     of hoToolPane   to vToolPane
        Get Window_Handle   of hoTool       to hWnd
        Set ComChildHandle  of hoToolPane   to hWnd
        Set ComVisible      of hoToolPane   to bVisible
        Send ComSetSize     of hoToolPane   iWidth iHeight
        Move hoToolPane     to lhoPane
    End
End_Procedure

Procedure mCreateToolPanes Handle hoCmdBars
    Send Add_Tool_Pane hoCmdBars oToolPane      "Tools"    xtpBarRight  (pbToolsPaneVisible(ghoEditorProperties))    (&ghoToolsPane)   250 500
    Send Add_Tool_Pane hoCmdBars oOutputPane    "Output"   xtpBarBottom (pbOutputPaneVisible(ghoEditorProperties))   (&ghoOutputPane)  500 150
End_Procedure

