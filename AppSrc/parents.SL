//TH-Header
//*****************************************************************************************
// Copyright (c)  2014  KURANT Project
// All rights reserved.
//
// $FileName    : Parents.SL
// $ProjectName : The Hammer 2.0
// $Authors     : Wil van Antwerpen, Michael Kurz, Sergey V. Natarov
// $Created     : 01.25.2014  01:08
// $Type        : LGPL
//
// Contents: Parents List
//
//*****************************************************************************************
//TH-RevisionStart
//TH-RevisionEnd

// Project Object Structure
//   oPL is a dbModalPanel
//     Vdfcls_DD is a DataDictionary
//     oSelList is a dbList
//     oOK_bn is a Button
//     oCancel_bn is a Button
//     oSearch_bn is a Button
//     dbEdit1 is a dbEdit

// Register all objects
Register_Object dbEdit1
Register_Object oCancel_bn
Register_Object oOK_bn
Register_Object oPL
Register_Object oSearch_bn
Register_Object oSelList
Register_Object Vdfcls_DD





Use VDFCLS.DD


Object oPL is a dbModalPanel
    Set Label to "Parents List"
    Set Size to 241 245
    Set Location to 4 5


    Object Vdfcls_DD is a Vdfcls_DataDictionary
    End_Object    // Vdfcls_DD

    Set Main_DD to (Vdfcls_DD(self))
    Set Server to (Vdfcls_DD(self))


    Object oSelList is a dbList

        Set auto_export_state to false
        Set export_item_state to true
        Set auto_column_state to false
        Set export_column to 1

        Set Main_File to Vdfcls.File_Number
        Set Ordering to 1
        Set Size to 149 229
        Set Location to 5 6

        Begin_Row
            Entry_Item Vdfcls.Name
            Entry_Item Vdfcls.Code
        End_Row

        Set Form_Width    item 0 to 172
        Set Header_Label  item 0 to "Name"

        Set Form_Width    item 1 to 48
        Set Header_Label  item 1 to "Code"





    End_Object    // oSelList

    Object oOK_bn is a Button
        Set Label to "&OK"
        Set Location to 209 75

        Procedure OnClick
            Send OK To oSelList
        End_Procedure

    End_Object    // oOK_bn

    Object oCancel_bn is a Button
        Set Label to "&Cancel"
        Set Location to 209 129

        Procedure OnClick
            Send Cancel To oSelList
        End_Procedure

    End_Object    // oCancel_bn

    Object oSearch_bn is a Button
        Set Label to "&Search..."
        Set Location to 209 185

        Procedure OnClick
            Send Search To oSelList
        End_Procedure

    End_Object    // oSearch_bn

    Object dbEdit1 is a dbEdit

        Set Object_Shadow_State To True

        Entry_Item Vdfcls.Descr
        Set Size to 44 229
        Set Location to 160 6



    End_Object    // dbEdit1


    On_Key Key_Alt+Key_O Send KeyAction To oOk_bn
    On_Key Key_Alt+Key_C Send KeyAction To oCancel_bn
    On_Key Key_Alt+Key_S Send KeyAction To oSearch_bn

End_Object    // oPL

