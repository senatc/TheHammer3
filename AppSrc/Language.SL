//TH-Header
//*****************************************************************************************
// Copyright (c)  2014  KURANT Project
// All rights reserved.
//
// $FileName    : Language.SL
// $ProjectName : The Hammer 2.0
// $Authors     : Wil van Antwerpen, Michael Kurz, Sergey V. Natarov, Bernhard Ponemayr
// $Created     : 01.25.2014  01:08
// $Type        : LGPL
//
// Contents: Edit and Create Languages
//
//*****************************************************************************************
//TH-RevisionStart
//TH-RevisionEnd




// Project Object Structure
//   oLanguage is a dbModalPanel
//     oLName is a ComboForm
//     oGroup1 is a Group
//       oStyle is a ComboForm
//       oCaseSensitiv is a CheckBox
//       oKeywords is a Form
//       oOperators is a Form
//       oSingLineComm is a Form
//       oMultiLineComm1 is a Form
//       oMultiLineComm2 is a Form
//       oScope1 is a Form
//       oScope2 is a Form
//       oStrDelim is a Form
//       oEscape is a Form
//       oTermination is a Form
//       oTagElementNames is a Form
//       oTagAttributeNames is a Form
//       oTagEntities is a Form
//     oSearch_bn is a Button
//     oCancel_bn is a Button

// Register all objects
Register_Object oCancel_bn
Register_Object oCaseSensitiv
Register_Object oEscape
Register_Object oGroup1
Register_Object oKeywords
Register_Object oLanguage
Register_Object oLName
Register_Object oMultiLineComm1
Register_Object oMultiLineComm2
Register_Object oOperators
Register_Object oScope1
Register_Object oScope2
Register_Object oSearch_bn
Register_Object oSingLineComm
Register_Object oStrDelim
Register_Object oStyle
Register_Object oTagAttributeNames
Register_Object oTagElementNames
Register_Object oTagEntities
Register_Object oTermination






CD_Popup_Object oLanguage is a dbModalPanel
    set Label to "Languages (Highlighting)"
    set Size to 281 501
    set Location to 4 5




    Object oLName is a ComboForm
        set Label to "Languagename:"
        set Size to 13 85
        set Location to 2 87
        set Form_Border to 0
        set Label_Col_Offset to 0
        set Label_Justification_Mode to jMode_Right

        // Combo_Fill_List is called when the list needs filling
        on_key key_F2 send SaveEntries
//        on_key kCancel send Close_Panel


        // notification of a selection change or edit change
        Procedure OnChange
            String sValue
            get Value to sValue
            set Object_Shadow_State of (oGroup1(Self)) to (sValue eq "")
        End_Procedure  // OnChange

        Property String psOldValue   Public ""

        Procedure Entering
            Forward send Entering
            set psOldValue  to (Value(Self,0))
        End_Procedure


    End_Object    // oLName

    Object oGroup1 is a Group
        set Size to 226 489
        set Location to 15 3
        Object oStyle is a ComboForm
            set Label to "Type:"
            set Size to 13 85
            set Location to 10 84
            set Form_Border to 0
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            // Combo_Fill_List is called when the list needs filling
            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel
            Procedure Combo_Fill_List
                // Fill the combo list with Send Combo_Add_Item
                send Combo_Add_Item "Procedural"
                send Combo_Add_Item "SGML"
            End_Procedure  // Combo_fill_list

            Function GetStyle returns Integer
                Integer iRet
                String  sValue
                get value to  sValue
                move (Combo_Item_Matching(Self,sValue)) to iRet
                if iRet lt 0 move 0                     to iRet
                Function_Return iRet
            End_Function

            Procedure SetStyle Integer iStyle
                set value to (Combo_Value(Self,iStyle))
            End_Procedure
            set Entry_State item 0 to False


            // notification of a selection change or edit change
            Procedure OnChange
                String  sValue
                Integer iFlag
                get Value                       to sValue
                move (sValue ne "Procedural")   to iFlag
                set Object_Shadow_State of (oTagElementNames(Self))     to iFlag
                set Object_Shadow_State of (oTagAttributeNames(Self))   to iFlag
                set Object_Shadow_State of (oTagEntities(Self))         to iFlag
            End_Procedure  // OnChange




            // notification that the list was closed
            //Procedure OnCloseUp
            //End_Procedure  // OnCloseUp

        End_Object    // oStyle

        Object oCaseSensitiv is a CheckBox
            set Label to "Casesensitiv"
            set Size to 10 56
            set Location to 28 84

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel
            Procedure OnChange
            End_Procedure  // OnChange

        End_Object    // oCaseSensitiv

        Object oKeywords is a Form
            set Label to "Keywords:"
            set Size to 13 400
            set Location to 40 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oKeywords

        Object oOperators is a Form
            set Label to "Operators:"
            set Size to 13 400
            set Location to 55 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oOperators

        Object oSingLineComm is a Form
            set Label to "Singel Line Comments:"
            set Size to 13 400
            set Location to 69 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oSingLineComm

        Object oMultiLineComm1 is a Form
            set Label to "Multi Line Comments 1:"
            set Size to 13 400
            set Location to 85 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oMultiLineComm1

        Object oMultiLineComm2 is a Form
            set Label to "Multi Line Comments 2:"
            set Size to 13 400
            set Location to 100 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oMultiLineComm2

        Object oScope1 is a Form
            set Label to "Scope Keywords 1:"
            set Size to 13 400
            set Location to 114 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oScope1

        Object oScope2 is a Form
            set Label to "Scope Keywords 2:"
            set Size to 13 400
            set Location to 130 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oScope2

        Object oStrDelim is a Form
            set Label to "String Delim.:"
            set Size to 13 400
            set Location to 145 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oStrDelim

        Object oEscape is a Form
            set Label to "Escapecharacter:"
            set Size to 13 38
            set Location to 160 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel
            set form_margin item 0 to 1

        End_Object    // oEscape

        Object oTermination is a Form
            set Label to "LineTerminationCharacter:"
            set Size to 13 38
            set Location to 159 216
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel
            set form_margin item 0 to 1

        End_Object    // oTermination

        Object oTagElementNames is a Form
            set Label to "TagElementNames:"
            set Size to 13 400
            set Location to 175 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oTagElementNames

        Object oTagAttributeNames is a Form
            set Label to "TagAttributeNames:"
            set Size to 13 400
            set Location to 189 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oTagAttributeNames

        Object oTagEntities is a Form
            set Label to "TagEntities:"
            set Size to 13 400
            set Location to 205 84
            set Label_Col_Offset to 0
            set Label_Justification_Mode to jMode_Right

            on_key key_F2 send SaveEntries
//            on_key kCancel send Close_Panel

        End_Object    // oTagEntities

        set Object_Shadow_State to True


    End_Object    // oGroup1

    Object oSearch_bn is a Button
        set Label to "Save"
        set Location to 249 441

        Procedure OnClick
            send SaveEntries
        End_Procedure
        on_key key_F2 send SaveEntries
//        on_key kCancel send Close_Panel

    End_Object    // oSearch_bn

    Object oCancel_bn is a Button
        set Label to "Close"
        set Location to 249 389

        Procedure OnClick
            send Close_Panel
        End_Procedure
        on_key key_F2 send SaveEntries
//        on_key kCancel send Close_Panel

    End_Object    // oCancel_bn



    Procedure SaveEntries
    End_Procedure


    Procedure LoadEntries Integer iC
    End_Procedure

    Procedure ClearEntries
    End_Procedure

CD_End_Object    // oLanguage

