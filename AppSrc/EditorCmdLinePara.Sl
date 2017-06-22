//TH-Header
//*****************************************************************************************
// Copyright (c)  2002 Michael Kurz
// All rights reserved.
// If you want to use this source in your applications contact: <MichaelKurz@gmx.at>
//
// $FileName    : EditorCmdLinePara.SL
// $ProjectName : The Hammer
// $Author      : Michael Kurz
// $Created     : 06.02.2002  00:25
//
// Contents:
//
//*****************************************************************************************
//TH-RevisionStart
//TH-RevisionEnd

// Project Object Structure
//   oCommandLineParameter is a dbModalPanel
//     oOK_bn is a Button
//     oCancel_bn is a Button
//     Form1 is a Form

// Register all objects
Register_Object Form1
Register_Object oCancel_bn
Register_Object oCommandLineParameter
Register_Object oOK_bn



//Use cCD_Popup.pkg


Use DFAllEnt.pkg



Cd_Popup_Object oCommandLineParameter Is a dbModalPanel

    #IF (!@ >= 140)
    Set pbSizeToClientArea to False
    #ENDIF
    Set locate_mode  To CENTER_ON_SCREEN
    Set Border_Style To Border_Dialog
    Set Label To "Command Line Parameters"
    Set Size To 59 297
    Set Location To 4 4




    Object oCmdLine Is a Form
        Set Size To 13 278
        Set Location To 5 5
        On_Key kEnter   Send DoOk
        On_Key KCANCEL  Send DoCancel
    End_Object    // Form1

    Object oOK_bn Is a Button
        Set Label To "Ok"
        Set Location To 25 178

        Procedure OnClick
            Send DoOk
        End_Procedure
        On_Key kEnter   Send DoOk
        On_Key KCANCEL  Send DoCancel

    End_Object    // oOK_bn

    Object oCancel_bn Is a Button
        Set Label To "Cancel"
        Set Location To 25 233

        Procedure OnClick
            Send DoCancel
        End_Procedure
        On_Key kEnter   Send DoOk
        On_Key KCANCEL  Send DoCancel

    End_Object    // oCancel_bn


    Procedure popup_group
        Forward Send popup_group
        Set Value Of (oCmdLine(Self)) Item 0 To (StringP1(Self))
        Set StringP1 To ""
    End_Procedure
    Procedure DoOk
        Set StringP1    To (Value(oCmdLine(Self),0))
        Send Close_Panel
    End_Procedure
    Procedure DoCancel
        Set StringP1    To "#ERR"
        Send Close_Panel
    End_Procedure

Cd_End_Object    // oCommandLineParameter


Function GetCommandLineParameter String sInit Returns String
    Set StringP1 Of (oCommandLineParameter(Self)) To (Trim(sInit))
    Send Popup   To (oCommandLineParameter(Self))
    Function_Return (StringP1(oCommandLineParameter(Self)))
End_Function
