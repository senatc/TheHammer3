//TH-Header
//*****************************************************************************************
// Copyright (c)  2003 Bernhard Ponemayr
// All rights reserved.
//
// $FileName    : C:\VDF7\Projects\hammer\Pkg\cFolderTabs.h
// $ProjectName : The Hammer Entwicklung
// $Author      : Bernhard Ponemayr
// $Created     : 08.03.2003  01:27
//
// Contents: Header file for cFolderTabs class, a tabs class just like the
//           Worksheet selector in M$ Excel
//
//*****************************************************************************************
//TH-RevisionStart
// 08.03.2003 01:28  Inital Revision                       BP     APBP
//TH-RevisionEnd


// Some defines needed for GDI functions
Define DT_TOP              For |CI$00000000
Define DT_LEFT             For |CI$00000000
Define DT_CENTER           For |CI$00000001
Define DT_RIGHT            For |CI$00000002
Define DT_VCENTER          For |CI$00000004
Define DT_BOTTOM           For |CI$00000008
Define DT_WORDBREAK        For |CI$00000010
Define DT_SINGLELINE       For |CI$00000020
Define DT_EXPANDTABS       For |CI$00000040
Define DT_TABSTOP          For |CI$00000080
Define DT_NOCLIP           For |CI$00000100
Define DT_EXTERNALLEADING  For |CI$00000200
Define DT_CALCRECT         For |CI$00000400
Define DT_NOPREFIX         For |CI$00000800
Define DT_INTERNAL         For |CI$00001000

Define DT_EDITCONTROL      For |CI$00002000
Define DT_PATH_ELLIPSIS    For |CI$00004000
Define DT_END_ELLIPSIS     For |CI$00008000
Define DT_MODIFYSTRING     For |CI$00010000
Define DT_RTLREADING       For |CI$00020000
Define DT_WORD_ELLIPSIS    For |CI$00040000

Define DEFAULT_GUI_FONT    For 17

Define RDW_INVALIDATE          For |CI$0001
Define RDW_INTERNALPAINT       For |CI$0002
Define RDW_ERASE               For |CI$0004

Define RDW_VALIDATE            For |CI$0008
Define RDW_NOINTERNALPAINT     For |CI$0010
Define RDW_NOERASE             For |CI$0020

Define RDW_NOCHILDREN          For |CI$0040
Define RDW_ALLCHILDREN         For |CI$0080

Define RDW_UPDATENOW           For |CI$0100
Define RDW_ERASENOW            For |CI$0200

Define RDW_FRAME               For |CI$0400
Define RDW_NOFRAME             For |CI$0800

Define HS_HORIZONTAL           For 0       //* ----- */
Define HS_VERTICAL             For 1       //* ||||| */
Define HS_FDIAGONAL            For 2       //* \\\\\ */
Define HS_BDIAGONAL            For 3       //* ///// */
Define HS_CROSS                For 4       //* +++++ */
Define HS_DIAGCROSS            For 5       //* xxxxx */

Define SRCCOPY             For |CI$00CC0020 //* dest = source                   */
Define SRCPAINT            For |CI$00EE0086 //* dest = source Or dest           */
Define SRCAND              For |CI$008800C6 //* dest = source And dest          */
Define SRCINVERT           For |CI$00660046 //* dest = source XOR dest          */
Define SRCERASE            For |CI$00440328 //* dest = source And (Not dest )   */
Define NOTSRCCOPY          For |CI$00330008 //* dest = (Not source)             */
Define NOTSRCERASE         For |CI$001100A6 //* dest = (Not src) And (Not dest) */
Define MERGECOPY           For |CI$00C000CA //* dest = (source And pattern)     */
Define MERGEPAINT          For |CI$00BB0226 //* dest = (Not source) Or dest     */
Define PATCOPY             For |CI$00F00021 //* dest = pattern                  */
Define PATPAINT            For |CI$00FB0A09 //* dest = DPSnoo                   */
Define PATINVERT           For |CI$005A0049 //* dest = pattern XOR dest         */
Define DSTINVERT           For |CI$00550009 //* dest = (Not dest)               */
Define BLACKNESS           For |CI$00000042 //* dest = BLACK                    */
Define WHITENESS           For |CI$00FF0062 //* dest = WHITE                    */

Define COLOR_HOTLIGHT      For 26

// Defines and Structures needed for TrackMouseEvent
Define WM_MOUSELEAVE           For |CI$02A3
Define WM_MOUSEHOVER           For |CI$02A1
Define WM_MOUSEWHEEL           For |CI$020A

Define TME_HOVER               For |CI$00000001
Define TME_LEAVE               For |CI$00000002

Type cfTRACKMOUSEEVENT
    Field cfTRACKMOUSEEVENT.cbSize          as DWORD     // (DWORD)
    Field cfTRACKMOUSEEVENT.dwFlags         as DWORD     // (DWORD)
    Field cfTRACKMOUSEEVENT.hwndTrack       as Handle    // (HWND)
    Field cfTRACKMOUSEEVENT.dwHoverTime     as DWORD     // (DWORD)
End_Type


// Defines and Structures needed for Tooltip
Define TTF_IDISHWND            For |CI$0001
Define TTF_CENTERTIP           For |CI$0002
Define TTF_RTLREADING          For |CI$0004
Define TTF_SUBCLASS            For |CI$0010
Define TTF_TRACK               For |CI$0020
Define TTF_ABSOLUTE            For |CI$0080
Define TTF_TRANSPARENT         For |CI$0100
Define TTF_DI_SETITEM          For |CI$8000       // valid only on the TTN_NEEDTEXT callback

Define TTM_ACTIVATE            For (WM_USER + 1)
Define TTM_ADDTOOL             For (WM_USER + 4)
Define TTM_TRACKACTIVATE       For (WM_USER + 17)
Define TTM_SETMAXTIPWIDTH      For (WM_USER + 24)
Define TTM_POP                 For (WM_USER + 28)
Define TTM_UPDATE              For (WM_USER + 29)

Define TTN_FIRST               For (-520)       // tooltips
Define TTN_LAST                For (-549)

Define TTN_GETDISPINFO         For (TTN_FIRST - 0)
Define TTN_SHOW                For (TTN_FIRST - 1)
Define TTN_POP                 For (TTN_FIRST - 2)

Define TTS_ALWAYSTIP           For |CI$01
Define TTS_NOPREFIX            For |CI$02

Type tTOOLINFO
    Field tTOOLINFO.cbSize as Integer
    Field tTOOLINFO.uFlags as Integer
    Field tTOOLINFO.hwnd as Handle
    Field tTOOLINFO.uID as Integer
    Field tTOOLINFO.rect as Char tRect_size
    Field tTOOLINFO.hInst as Handle
    Field tTOOLINFO.lpszText as Pointer
    Field tTOOLINFO.lParam as Integer
End_Type

Type tNmTTDispInfo
    Field tNmTTDispInfo.hdr.hwndFrom           as Handle
    Field tNmTTDispInfo.hdr.idFrom             as Integer
    Field tNmTTDispInfo.hdr.code               as Integer
    Field tNmTTDispInfo.lpszText               as Pointer
    Field tNmTTDispInfo.szText                 as Char 80
    Field tNmTTDispInfo.hinst                  as Handle
    Field tNmTTDispInfo.uFlags                 as Integer
    //Field tNmTTDispInfo.lParam                 as Integer
End_Type

#Replace clBgClr 14671839


Type TBITMAPBITS
    Field TBITMAPBITS.bmBits_1     as WORD    // (WORD)
    Field TBITMAPBITS.bmBits_2     as WORD    // (WORD)
    Field TBITMAPBITS.bmBits_3     as WORD    // (WORD)
    Field TBITMAPBITS.bmBits_4     as WORD    // (WORD)
End_Type

Define PATCOPY        For |CI$00F00021
Define PATINVERT      For |CI$005A0049
Define DSTINVERT      For |CI$00550009
Define BLACKNESS      For |CI$00000042
Define WHITENESS      For |CI$00FF0062

External_function CreateBitmapEf         "CreateBitmap"         GDI32.DLL Integer nW Integer nH Integer nPlanes Integer nBits Pointer pBits Returns Handle
External_function CreateBitmapIndirectEf "CreateBitmapIndirect" GDI32.DLL Pointer pBitmap Returns Handle
External_function CreatePatternBrushEf   "CreatePatternBrush"   GDI32.DLL Handle  hBitmap Returns Handle
External_function PatBltEf               "PatBlt"               GDI32.DLL Handle  hDC     Integer iX Integer iY Integer iW Integer iH DWord dwRop Returns Integer

Define fcolor For |CI$FFFF // clBtnFace = |CI$C8D0D4
Define scolor For |CI$0000

Function CreateDottedBrush Integer iColor Returns Handle
    Integer iRet
    Handle  hBrush hBmp
    String  sBmp sBits
    Pointer pBmp pBits

    ZeroType TBITMAPBITS To sBits
    // 1st row
    Put fcolor To sBits At TBITMAPBITS.bmBits_1
    Put scolor To sBits At TBITMAPBITS.bmBits_2
    // 2nd row
    Put scolor To sBits At TBITMAPBITS.bmBits_3
    Put fcolor To sBits At TBITMAPBITS.bmBits_4
    GetAddress Of sBits To pBits
    Move (CreateBitmapEf(2, 2, 2, 8, pBits)) To hBmp
    Move (CreatePatternBrushEf(hBmp))   To hBrush
    Move (DeleteObject(hBmp))           To iRet
    If (hBrush) Function_Return hBrush
    Function_Return 0
End_Function

// All DLL call's needed. Every function name has a "Ef" (=External Function)
// added at the end of the orginal name so we get no compiler problems if the
// function is already defined elsewhere
External_function MoveToExEf "MoveToEx" gdi32.dll Handle hDc dword iX dword iY Pointer pPoint Returns Integer
External_function CreatePolygonRgnEf "CreatePolygonRgn" gdi32.dll Pointer lppt Integer cPoints Integer fnFillMode Returns Integer
External_function FillRgnEf "FillRgn" gdi32.dll Handle hDc Handle hRgn Handle hBrush Returns Integer
External_function InflateRectEf "InflateRect" user32.dll Pointer pRect Integer dx Integer dY Returns Integer
External_function GetTextExtentPoint32Ef "GetTextExtentPoint32A" gdi32.dll Handle hDc Pointer pString Integer cbSize Pointer lpSize Returns Integer
External_function SetTextJustificationEf "SetTextJustification" gdi32.dll Handle hDC Integer nBreakExtra Integer nBreakCount Returns Integer
External_function SetTextCharacterExtraEf "SetTextCharacterExtra" gdi32.dll Handle hDC Integer nCharacterExtra Returns Integer
External_function LPToDpEf "LPtoDP" gdi32.dll Handle hDc Pointer pPoints Integer nCount Returns Integer
External_function RedrawWindowEf "RedrawWindow" User32.dll  Handle hwnd Pointer pRect Handle hUpdReg Integer iFlags Returns Integer
External_function PtInRegionEf "PtInRegion" gdi32.dll Handle hRegion Integer iX Integer iY Returns Integer
External_function PtInRectEf "PtInRect" user32.dll Pointer pRect Pointer pPoint Returns Integer
External_function GetRgnBoxEf "GetRgnBox" gdi32.dll Handle hRegion Pointer pRect Returns Integer
External_function PolylineToEf "PolylineTo" gdi32.dll Handle hDc Pointer lppt Integer cCount Returns Integer
External_function CreateHatchBrushEf "CreateHatchBrush" gdi32.dll Integer fnStyle Integer clrref Returns Handle
External_function GetSysColorBrushEf "GetSysColorBrush" user32.dll Integer nIndex Returns Handle
External_function OffsetRgnEf "OffsetRgn" gdi32.dll Handle hRgn Integer iX Integer iY Returns Integer
External_function OffsetRectEf "OffsetRect" user32.dll Pointer pRect Integer iX Integer iY Returns Integer
External_function GetCaptureEf "GetCapture" user32.dll Returns Handle
External_function CreateCompatibleDCEf "CreateCompatibleDC" gdi32.dll Handle hDc Returns Handle
External_function CreateCompatibleBitmapEf "CreateCompatibleBitmap" gdi32.dll Handle hDc Integer iWidth Integer iHeight Returns Handle
External_function BitBltEf "BitBlt" gdi32.dll Handle hDcDest Integer nXDest Integer nYDest Integer nWidth Integer nHeight Handle hDcSrc Integer nXSrc Integer nYSrc Integer dwRop Returns Integer
External_function DeleteDCEf "DeleteDC" gdi32.dll Handle hDc Returns Integer
External_function LoadImageEf "LoadImageA" user32.dll Handle hInst Pointer pPic Integer iTyp Integer iX Integer iY Integer iFlag Returns Integer
External_function FindWindowExEf "FindWindowExA" user32.dll Handle hParent Handle hChild Pointer pClass Pointer pName Returns Handle
External_function TrackMouseEventEf "TrackMouseEvent" User32.dll Pointer pMouse Returns Integer
External_function SetBkColorEf "SetBkColor" GDI32.dll Handle hDC DWORD crColor Returns DWord
External_function CreateWindowExEf "CreateWindowExA" user32.dll Integer dwSt Pointer lpClass Pointer lpName Integer dwStyle Integer iX Integer iY Integer iW Integer iH Handle hParent Handle hMenu Handle hInst Pointer lpParam Returns Handle
External_function DestroyWindowEf "DestroyWindow" user32.dll Handle hWnd Returns Integer

