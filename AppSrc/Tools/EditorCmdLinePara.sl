//TH-Header
//*****************************************************************************************
// Copyright (c) 2002-2017 Michael Kurz
// All rights reserved.
// If you want to use this source in your applications contact: <MichaelKurz@gmx.at>
//
// $FileName    : EditorCmdLinePara.SL
// $ProjectName : The Hammer
// $Author      : Michael Kurz, Sergey Natarov
// $Created     : 06.02.2002  00:25
//
// Contents:
//
//*****************************************************************************************
//TH-RevisionStart
//TH-RevisionEnd

Use DFAllEnt.pkg

Cd_Popup_Object oCommandLineParameter is a dbModalPanel
    Set pbSizeToClientArea to False
    Set locate_mode  To CENTER_ON_SCREEN
    Set Label To "Command Line Parameters"
    Set Size to 70 300
    Set Location To 4 4
    Set peAnchors to anAll
    Set piMinSize to 70 300
    Set piMaxSize to 70 3000

    Object oCmdLine is a Form
        Set Size to 13 270
        Set Location to 10 10
        Set peAnchors to anTopLeftRight
        On_Key kEnter   Send DoOk
        On_Key KCANCEL  Send DoCancel
    End_Object    // Form1

    Object oOK_bn Is a Button
        Set Label To "Ok"
        Set Location to 27 175
        Set peAnchors to anBottomRight
        On_Key kEnter   Send DoOk
        On_Key KCANCEL  Send DoCancel
        Procedure OnClick
            Send DoOk
        End_Procedure
    End_Object    // oOK_bn

    Object oCancel_bn Is a Button
        Set Label To "Cancel"
        Set Location to 27 230
        Set peAnchors to anBottomRight
        On_Key kEnter   Send DoOk
        On_Key KCANCEL  Send DoCancel
        Procedure OnClick
            Send DoCancel
        End_Procedure
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
