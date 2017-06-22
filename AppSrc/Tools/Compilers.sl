
Object oCompilers_SL is a dbModalPanel
    Set pbSizeToClientArea to False
    Set Label to "Available Built-In Compilers"
    Set Size to 155 180
    Set Location to 4 4
    Set piMinSize to 155 180

    Object oSelList is a List
        Property Integer Invoking_Object_Id Public 0
        Set Size to 105 160
        Set Location to 5 5
        Set peAnchors to anAll
        Set piMinSize to 105 160

        Procedure AddLine String sTxt
            Send add_item msg_none sTxt
        End_Procedure

        Procedure Fill
            Integer iCompiler iCompilers
            String  sCreated
            Send Delete_Data
            Move (SizeOfArray(gtTHCompilers)-1) to iCompilers
            For iCompiler from 0 to iCompilers
                Move "" to sCreated
                If (gtTHCompilers[iCompiler].hoCompiler) Move " (Created)" to sCreated
                Send AddLine ("DataFlex" * gtTHCompilers[iCompiler].sVersion + sCreated)
            Loop
        End_Procedure  // Combo_fill_list

        Procedure Ok
            Send Close_Panel
        End_Procedure
        On_Key kEnter   Send Ok
        On_Key KCANCEL  Send Close_Panel
        Procedure mouse_click Integer iPara0
            Send Ok
        End_Procedure

    End_Object    // oSelList

    Procedure popup
        Set Invoking_Object_Id of (oSelList(Self))  to (Focus(Desktop))
        Send Fill to (oSelList(Self))
        Forward Send popup
    End_Procedure

    Object oCancel_bn is a Button
        Set Label to "Cancel"
        Set Location to 114 115
        Set peAnchors to anBottomRight
        Procedure OnClick
            Send Close_Panel
        End_Procedure
    End_Object    // oCancel_bn
End_Object    // LookUp