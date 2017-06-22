//TH-Header
//*****************************************************************************************
// Copyright (c) 2000 Michael Kurz
// All rights reserved.
// If you want to use this source in your applications conatct: <MichaelKurz@gmx.at>
//
// $FileName    : CodeMax.h
// $ProjectName : VDF implementation of the CodeMax Edit Control header file.
// $Author      : Michael Kurz <MichaelKurz@gmx.at>
// $Created     : 01-25-2001 @ 19:00
//
// Contents:
//      Codemax Edit
//
// $Rev History
//      MK 01.04.2001 11:00 Overwrite Absolute_GUIOrigin to popup SelectionList relativ to the
//                          Cursor Position in the CodeMax.
//
//*****************************************************************************************
//TH-RevisionStart
// 17.05.2001 21:31  Absolute_gui_Origin is overwritten    Mk     SERVER
//                   to allow popup objects to pos
//                   relativ to cursor position
// 17.05.2001 21:33  Use a constant CMAX_DLL_NAME instead  Mk     SERVER
//                   of direct CMAX20.DLL for an easy DLL
//                   Name change
// 16.01.2003 21:49  CodeSense add-on implementation                        Ad
//TH-RevisionEnd

Use DFAllent
Use mStrConv.pkg
Use mPointer.pkg

Define CMAX_DLL_NAME FOR THCS23.DLL
//Define CMAX_DLL_NAME For DFEDIT21.DLL


Define NM_SETFOCUS              FOR -7
Define NM_KILLFOCUS             FOR -8

#IFNDEF Get_CreateWindowEx
  External_Function CreateWindowEx     'CreateWindowExA'      User32.dll  Dword e Pointer c Pointer v Dword w Dword x Dword y Dword wi Dword he Handle hP Handle hm Handle hi Pointer cs Returns Handle
#ENDIF
External_Function GetObject          'GetObjectA'           Gdi32.dll   Handle hGdi Integer iSize Pointer pBuff Returns Integer
#IFNDEF Get_CreateFontIndirect
  External_Function CreateFontIndirect 'CreateFontIndirectA'  Gdi32.dll   Pointer pLogfont Returns Integer
#ENDIF
External_Function LockWindowUpdate   'LockWindowUpdate'     USer32.dll  Handle hwnd Returns Integer
#IFNDEF Get_RedrawWindow
  External_Function RedrawWindow       'RedrawWindow'         User32.dll  Handle hwnd Pointer pRect Handle hUpdReg Integer iFlags Returns Integer
#ENDIF
External_Function ReplyMessage       'ReplyMessage'         User32.dll  Integer iResult Returns Integer
External_Function GetFocus           'GetFocus'             User32.dll  Returns Integer

    // File Dropping from e.g WindowsExplorer.
Define WM_DROPFILES              FOR |CI$0233
External_Function DragAcceptFiles    'DragAcceptFiles'      Shell32.dll Handle hwnd Integer iFlag Returns Integer
External_Function DragQueryFile      'DragQueryFile'        Shell32.dll Handle hDrop Integer iFileIndex Pointer pFileBuff Integer iBuffSize Returns Integer
External_Function DragFinish         'DragFinish'           Shell32.dll Handle hDrop Returns Integer

    // CodeTip Support external Function
External_Function CT_DestroyWindow   'DestroyWindow'        User32.dll  Handle hWnd Returns Integer


Define RDW_INVALIDATE          FOR |CI$0001
Define RDW_INTERNALPAINT       FOR |CI$0002
Define RDW_ERASE               FOR |CI$0004

Define RDW_VALIDATE            FOR |CI$0008
Define RDW_NOINTERNALPAINT     FOR |CI$0010
Define RDW_NOERASE             FOR |CI$0020

Define RDW_NOCHILDREN          FOR |CI$0040
Define RDW_ALLCHILDREN         FOR |CI$0080

Define RDW_UPDATENOW           FOR |CI$0100
Define RDW_ERASENOW            FOR |CI$0200

Define RDW_FRAME               FOR |CI$0400
Define RDW_NOFRAME             FOR |CI$0800


Define COLORREF FOR Dword




    // Is a command that allows to put a string into a structure
    // Usage: PUT_POINTER sName  pName  "String..."  to sBuff at TYPE.FIELD
#COMMAND PUT_POINTER R R R "TO" R "AT" R
    Local_Buffer !1 !2
    Move !3 to !1
    GetAddress Of !1    to !2
    Put !2  to !5 at !7 !8
#ENDCOMMAND


    // Windows Standard type: fuer WM_Notify
TYPE NMHDR
    Field NMHDR.hwndFrom             as Handle    //TYPE: HWND
    Field NMHDR.idFrom               as Integer   //TYPE: UINT
    Field NMHDR.code                 as Integer   //TYPE: UINT
END_TYPE

Define LF_FACESIZE          FOR 32
Define CODEMAXWNDCLASS      FOR "CodeSense" //"CodeMax"

/////////////////////////////////////////////////////////////
//
// Constants
//
//

// maximum size (TCHARs) of text to find or replace
Define CM_MAX_FINDREPL_TEXT          FOR 100
// maximum MRU size in find and find/replace dialogs
Define CM_FIND_REPLACE_MRU_MAX       FOR 10
// required buffer size for pszMRUList argument CMSetFindReplaceMRUList() and CMGetFindReplaceMRUList()
Define CM_FIND_REPLACE_MRU_BUFF_SIZE FOR ( ( CM_MAX_FINDREPL_TEXT + 1 ) * CM_FIND_REPLACE_MRU_MAX )
// maximum number of keystroke macros supported by CodeMax
Define CM_MAX_MACROS                 FOR 10
// maximum size of command string returned in pszBuff param of CMGetCommandString() if bDescription is FALSE
Define CM_MAX_CMD_STRING             FOR 50
// maximum size of command string returned in pszBuff param of CMGetCommandString() if bDescription is TRUE
Define CM_MAX_CMD_DESCRIPTION        FOR 100
// maximum size of a language name set with CMRegisterLanguage
Define CM_MAX_LANGUAGE_NAME          FOR 30
// maximum tab size (characters)
Define CM_MAX_TABSIZE                FOR 100
// minimum tab size (characters)
Define CM_MIN_TABSIZE                FOR 2
// left margin width (pixels)
Define CM_CXLEFTMARGIN               FOR 24
// SVN // maximum CodeList tooltip text length
Define CM_MAX_CODELIST_TIP			 FOR 128

/////////////////////////////////////////////////////////////
//
// CMM_SETLINESTYLE style bits
//
//
Define CML_OWNERDRAW      FOR |CI$1      // Parent window should receive CMN_DRAWLINE notifications
Define CML_NOTIFY_DEL     FOR |CI$2      // Parent window should receive CMN_DELETELINE notifications


/////////////////////////////////////////////////////////////
//
// Messages
//
//
Define CMM_SETLANGUAGE                FOR ( WM_USER + 1600 )
Define CMM_GETLANGUAGE                FOR ( WM_USER + 1601 )
Define CMM_ENABLECOLORSYNTAX          FOR ( WM_USER + 1610 )
Define CMM_ISCOLORSYNTAXENABLED       FOR ( WM_USER + 1620 )
Define CMM_SETCOLORS                  FOR ( WM_USER + 1630 )
Define CMM_GETCOLORS                  FOR ( WM_USER + 1640 )
Define CMM_ENABLEWHITESPACEDISPLAY    FOR ( WM_USER + 1800 )
Define CMM_ISWHITESPACEDISPLAYENABLED FOR ( WM_USER + 1810 )
Define CMM_ENABLETABEXPAND            FOR ( WM_USER + 1811 )
Define CMM_ISTABEXPANDENABLED         FOR ( WM_USER + 1812 )
Define CMM_ENABLESMOOTHSCROLLING      FOR ( WM_USER + 1820 )
Define CMM_SETTABSIZE                 FOR ( WM_USER + 1821 )
Define CMM_GETTABSIZE                 FOR ( WM_USER + 1822 )
Define CMM_ISSMOOTHSCROLLINGENABLED   FOR ( WM_USER + 1830 )
Define CMM_SETREADONLY                FOR ( WM_USER + 1840 )
Define CMM_ISREADONLY                 FOR ( WM_USER + 1850 )
Define CMM_ENABLELINETOOLTIPS         FOR ( WM_USER + 1860 )
Define CMM_ISLINETOOLTIPSENABLED      FOR ( WM_USER + 1870 )
Define CMM_ENABLELEFTMARGIN           FOR ( WM_USER + 1880 )
Define CMM_ISLEFTMARGINENABLED        FOR ( WM_USER + 1890 )
Define CMM_ENABLECOLUMNSEL            FOR ( WM_USER + 1891 )
Define CMM_ISCOLUMNSELENABLED         FOR ( WM_USER + 1892 )
Define CMM_ENABLEDRAGDROP             FOR ( WM_USER + 1893 )
Define CMM_ISDRAGDROPENABLED          FOR ( WM_USER + 1894 )
Define CMM_ENABLEOVERTYPE             FOR ( WM_USER + 1900 )
Define CMM_ISOVERTYPEENABLED          FOR ( WM_USER + 1910 )
Define CMM_ENABLECASESENSITIVE        FOR ( WM_USER + 1920 )
Define CMM_ISCASESENSITIVEENABLED     FOR ( WM_USER + 1930 )
Define CMM_ENABLEPRESERVECASE         FOR ( WM_USER + 1931 )
Define CMM_ISPRESERVECASEENABLED      FOR ( WM_USER + 1932 )
Define CMM_ENABLEWHOLEWORD            FOR ( WM_USER + 1940 )
Define CMM_ISWHOLEWORDENABLED         FOR ( WM_USER + 1950 )
Define CMM_SETTOPINDEX                FOR ( WM_USER + 1960 )
Define CMM_GETTOPINDEX                FOR ( WM_USER + 1970 )
Define CMM_GETVISIBLELINECOUNT        FOR ( WM_USER + 1980 )
Define CMM_HITTEST                    FOR ( WM_USER + 1990 )
Define CMM_OPENFILE                   FOR ( WM_USER + 2300 )
Define CMM_SAVEFILE                   FOR ( WM_USER + 2310 )
Define CMM_INSERTFILE                 FOR ( WM_USER + 2320 )
Define CMM_INSERTTEXT                 FOR ( WM_USER + 2330 )
Define CMM_SETTEXT                    FOR ( WM_USER + 2335 )
Define CMM_REPLACETEXT                FOR ( WM_USER + 2340 )
Define CMM_GETTEXTLENGTH              FOR ( WM_USER + 2350 )
Define CMM_GETTEXT                    FOR ( WM_USER + 2360 )
Define CMM_GETLINECOUNT               FOR ( WM_USER + 2365 )
Define CMM_GETLINE                    FOR ( WM_USER + 2370 )
Define CMM_GETLINELENGTH              FOR ( WM_USER + 2380 )
Define CMM_GETWORD                    FOR ( WM_USER + 2381 )
Define CMM_GETWORDLENGTH              FOR ( WM_USER + 2382 )
Define CMM_ADDTEXT                    FOR ( WM_USER + 2390 )
Define CMM_DELETELINE                 FOR ( WM_USER + 2400 )
Define CMM_INSERTLINE                 FOR ( WM_USER + 2410 )
Define CMM_GETSEL                     FOR ( WM_USER + 2420 )
Define CMM_GETSELFROMPOINT            FOR ( WM_USER + 2425 )
Define CMM_SETSEL                     FOR ( WM_USER + 2430 )
Define CMM_SELECTLINE                 FOR ( WM_USER + 2435 )
Define CMM_DELETESEL                  FOR ( WM_USER + 2440 )
Define CMM_REPLACESEL                 FOR ( WM_USER + 2450 )
Define CMM_ISMODIFIED                 FOR ( WM_USER + 2460 )
Define CMM_SETMODIFIED                FOR ( WM_USER + 2461 )
Define CMM_ENABLECRLF                 FOR ( WM_USER + 2470 )
Define CMM_ISCRLFENABLED              FOR ( WM_USER + 2480 )
Define CMM_SETFONTOWNERSHIP           FOR ( WM_USER + 2485 )
Define CMM_GETFONTOWNERSHIP           FOR ( WM_USER + 2486 )
Define CMM_EXECUTECMD                 FOR ( WM_USER + 2700 )
Define CMM_SETSPLITTERPOS             FOR ( WM_USER + 2900 )
Define CMM_GETSPLITTERPOS             FOR ( WM_USER + 2901 )
Define CMM_SETAUTOINDENTMODE          FOR ( WM_USER + 3100 )
Define CMM_GETAUTOINDENTMODE          FOR ( WM_USER + 3110 )
Define CMM_CANUNDO                    FOR ( WM_USER + 3300 )
Define CMM_CANREDO                    FOR ( WM_USER + 3310 )
Define CMM_CANCUT                     FOR ( WM_USER + 3320 )
Define CMM_CANCOPY                    FOR ( WM_USER + 3330 )
Define CMM_CANPASTE                   FOR ( WM_USER + 3340 )
Define CMM_REDO                       FOR ( WM_USER + 3350 )
Define CMM_CLEARUNDOBUFFER            FOR ( WM_USER + 3351 )
Define CMM_UNDO                       FOR ( WM_USER + 3360 )
Define CMM_CUT                        FOR ( WM_USER + 3370 )
Define CMM_COPY                       FOR ( WM_USER + 3380 )
Define CMM_PASTE                      FOR ( WM_USER + 3390 )
Define CMM_SETUNDOLIMIT               FOR ( WM_USER + 3400 )
Define CMM_GETUNDOLIMIT               FOR ( WM_USER + 3410 )
Define CMM_GETVIEWCOUNT               FOR ( WM_USER + 3600 )
Define CMM_GETCURRENTVIEW             FOR ( WM_USER + 3610 )
Define CMM_SHOWSCROLLBAR              FOR ( WM_USER + 3700 )
Define CMM_HASSCROLLBAR               FOR ( WM_USER + 3710 )
Define CMM_ENABLESPLITTER             FOR ( WM_USER + 3720 )
Define CMM_ISSPLITTERENABLED          FOR ( WM_USER + 3730 )
Define CMM_ISRECORDINGMACRO           FOR ( WM_USER + 3731 )
Define CMM_ISPLAYINGMACRO             FOR ( WM_USER + 3732 )
Define CMM_ENABLEGLOBALPROPS          FOR ( WM_USER + 3740 )
Define CMM_ISGLOBALPROPSENABLED       FOR ( WM_USER + 3741 )
Define CMM_SETDLGPARENT               FOR ( WM_USER + 3750 )

// 2.0
Define CMM_ENABLESELBOUNDS            FOR ( WM_USER + 3760 )
Define CMM_ISSELBOUNDSENABLED         FOR ( WM_USER + 3770 )
Define CMM_SETFONTSTYLES              FOR ( WM_USER + 3780 )
Define CMM_GETFONTSTYLES              FOR ( WM_USER + 3790 )
Define CMM_ENABLEREGEXP               FOR ( WM_USER + 3800 )
Define CMM_ISREGEXPENABLED            FOR ( WM_USER + 3810 )
Define CMM_SETITEMDATA                FOR ( WM_USER + 3820 )
Define CMM_GETITEMDATA                FOR ( WM_USER + 3830 )
Define CMM_SETLINESTYLE               FOR ( WM_USER + 3840 )
Define CMM_GETLINESTYLE               FOR ( WM_USER + 3850 )
Define CMM_SETBOOKMARK                FOR ( WM_USER + 3860 )
Define CMM_GETBOOKMARK                FOR ( WM_USER + 3870 )
Define CMM_SETALLBOOKMARKS            FOR ( WM_USER + 3880 )
Define CMM_GETALLBOOKMARKS            FOR ( WM_USER + 3890 )
Define CMM_SETLINENUMBERING           FOR ( WM_USER + 3900 )
Define CMM_GETLINENUMBERING           FOR ( WM_USER + 3910 )
Define CMM_POSFROMCHAR                FOR ( WM_USER + 3920 )
Define CMM_ENABLEHIDESEL              FOR ( WM_USER + 3930 )
Define CMM_ISHIDESELENABLED           FOR ( WM_USER + 3940 )
Define CMM_SETHIGHLIGHTEDLINE         FOR ( WM_USER + 3950 )
Define CMM_GETHIGHLIGHTEDLINE         FOR ( WM_USER + 3960 )
Define CMM_ENABLENORMALIZECASE        FOR ( WM_USER + 3970 )
Define CMM_ISNORMALIZECASEENABLED     FOR ( WM_USER + 3980 )
Define CMM_SETDIVIDER                 FOR ( WM_USER + 3990 )
Define CMM_GETDIVIDER                 FOR ( WM_USER + 4000 )
Define CMM_ENABLEOVERTYPECARET        FOR ( WM_USER + 4010 )
Define CMM_ISOVERTYPECARETENABLED     FOR ( WM_USER + 4020 )
Define CMM_SETFINDTEXT                FOR ( WM_USER + 4030 )
Define CMM_GETFINDTEXT                FOR ( WM_USER + 4040 )
Define CMM_SETREPLACETEXT             FOR ( WM_USER + 4050 )
Define CMM_GETREPLACETEXT             FOR ( WM_USER + 4060 )
Define CMM_SETIMAGELIST               FOR ( WM_USER + 4070 )
Define CMM_GETIMAGELIST               FOR ( WM_USER + 4080 )
Define CMM_SETMARGINIMAGES            FOR ( WM_USER + 4090 )
Define CMM_GETMARGINIMAGES            FOR ( WM_USER + 4100 )
Define CMM_ABOUTBOX                   FOR ( WM_USER + 4110 )
Define CMM_PRINT                      FOR ( WM_USER + 4120 )
Define CMM_SETCARETPOS                FOR ( WM_USER + 4130 )
Define CMM_VIEWCOLTOBUFFERCOL         FOR ( WM_USER + 4140 )
Define CMM_BUFFERCOLTOVIEWCOL         FOR ( WM_USER + 4150 )

// 2.1
Define CMM_SETBORDERSTYLE             FOR ( WM_USER + 4160 )
Define CMM_GETBORDERSTYLE             FOR ( WM_USER + 4170 )
// SVN
Define CMM_SETCURRENTVIEW             FOR ( WM_USER + 4180 )

// Changed due to addition of CMM_SETCURRENTVIEW in CodeMax 2.1.0.14
//define CMM_GETCURRENTTOKEN            For ( WM_USER + 4180 )
Define CMM_GETCURRENTTOKEN            FOR ( WM_USER + 5000 )
Define CMM_UPDATECONTROLPOSITIONS     FOR ( WM_USER + 5010 )



// Extentions for Oem/Ansi support
Define CMM_ENABLEOEMCODE              FOR ( WM_USER + 4300 )
Define CMM_ISOEMCODEENABLED           FOR ( WM_USER + 4301 )

/////////////////////////////////////////////////////////////
//
// Notifications
//
//
Define CMN_CHANGE                    FOR 100      // buffer contents changed
Define CMN_HSCROLL                   FOR 110      // horizontal scrollbar pos changed
Define CMN_VSCROLL                   FOR  120      // vertical scrollbar pos changed
Define CMN_SELCHANGE                 FOR  130      // active selection has changed
Define CMN_VIEWCHANGE                FOR  140      // the user switched to a different splitter view
Define CMN_MODIFIEDCHANGE            FOR  150      // the modified state of the buffer has changed
Define CMN_SHOWPROPS                 FOR  160      // the user is about to show the props window
Define CMN_PROPSCHANGE               FOR  170      // the user changed properties via the props window
Define CMN_CREATE                    FOR  180      // the control has been created
Define CMN_DESTROY                   FOR  190      // the control is about to be destroyed

// 2.0
Define CMN_DRAWLINE                  FOR 200      // owner-draw functionality
Define CMN_DELETELINE                FOR 210      // line is about to be deleted
Define CMN_CMDFAILURE                FOR 220      // a keystroke command failed to successfully complete
Define CMN_REGISTEREDCMD             FOR 230      // a registered command has been invoked by the user
Define CMN_KEYDOWN                   FOR 240      // a key was pressed (WM_KEYDOWN)
Define CMN_KEYUP                     FOR 250      // a key was released (WM_KEYUP)
Define CMN_KEYPRESS                  FOR 260      // a key was pressed and released (WM_CHAR)
Define CMN_MOUSEDOWN                 FOR 270      // a mouse button was pressed (WM_xBUTTONDOWN)
Define CMN_MOUSEUP                   FOR 280      // a mouse button was released (WM_xBUTTONUP)
Define CMN_MOUSEMOVE                 FOR 290      // the mouse pointer was moved (WM_MOUSEMOVE)
Define CMN_OVERTYPECHANGE            FOR 300      // the overtype mode has changed

// 2.1
Define CMN_FINDWRAPPED               FOR 310      // a find operation wrapped to start/end of buffer

// SVN
Define CMN_CODELIST                  FOR 320      // user has activated CodeList control
Define CMN_CODELISTSELMADE           FOR 330      // user has selected an item in CodeList control
Define CMN_CODELISTCANCEL            FOR 340      // user cancelled CodeList control
Define CMN_CODELISTCHAR              FOR 350      // CodeList control received a WM_CHAR message
Define CMN_CODETIP                   FOR 360      // user has activated CodeTip control
Define CMN_CODETIPINITIALIZE         FOR 365      // application should initialize CodeTip control
Define CMN_CODETIPCANCEL             FOR 370      // user cancelled CodeTip control
Define CMN_CODETIPUPDATE             FOR 380      // the CodeTip control is about to be updated
Define CMN_CODELISTSELWORD           FOR 390      // the CodeList control is about to select new item
Define CMN_CODELISTSELCHANGE         FOR 400      // the CodeList selection has changed
Define CMN_CODELISTHOTTRACK          FOR 410      // the mouse hot-tracking selection has changed



/////////////////////////////////////////////////////////////
//
// Edit commands
//
//

Define CMD_FIRST                       FOR 100
Define CMD_WORDUPPERCASE               FOR ( CMD_FIRST + 0 )
Define CMD_WORDTRANSPOSE               FOR ( CMD_FIRST + 1 )
Define CMD_WORDRIGHTEXTEND             FOR ( CMD_FIRST + 2 )
Define CMD_WORDRIGHT                   FOR ( CMD_FIRST + 3 )
Define CMD_WORDENDRIGHT                FOR ( CMD_FIRST + 4 )
Define CMD_WORDENDRIGHTEXTEND          FOR ( CMD_FIRST + 5 )
Define CMD_WORDLOWERCASE               FOR ( CMD_FIRST + 6 )
Define CMD_WORDLEFTEXTEND              FOR ( CMD_FIRST + 7 )
Define CMD_WORDLEFT                    FOR ( CMD_FIRST + 8 )
Define CMD_WORDENDLEFT                 FOR ( CMD_FIRST + 9 )
Define CMD_WORDENDLEFTEXTEND           FOR ( CMD_FIRST + 10 )
Define CMD_WORDDELETETOSTART           FOR ( CMD_FIRST + 11 )
Define CMD_WORDDELETETOEND             FOR ( CMD_FIRST + 12 )
Define CMD_WORDCAPITALIZE              FOR ( CMD_FIRST + 13 )
Define CMD_WINDOWSTART                 FOR ( CMD_FIRST + 14 )
Define CMD_WINDOWSCROLLUP              FOR ( CMD_FIRST + 15 )
Define CMD_WINDOWSCROLLTOTOP           FOR ( CMD_FIRST + 16 )
Define CMD_WINDOWSCROLLTOCENTER        FOR ( CMD_FIRST + 17 )
Define CMD_WINDOWSCROLLTOBOTTOM        FOR ( CMD_FIRST + 18 )
Define CMD_WINDOWSCROLLRIGHT           FOR ( CMD_FIRST + 19 )
Define CMD_WINDOWSCROLLLEFT            FOR ( CMD_FIRST + 20 )
Define CMD_WINDOWSCROLLDOWN            FOR ( CMD_FIRST + 21 )
Define CMD_WINDOWRIGHTEDGE             FOR ( CMD_FIRST + 22 )
Define CMD_WINDOWLEFTEDGE              FOR ( CMD_FIRST + 23 )
Define CMD_WINDOWEND                   FOR ( CMD_FIRST + 24 )
Define CMD_UPPERCASESELECTION          FOR ( CMD_FIRST + 25 )
Define CMD_UNTABIFYSELECTION           FOR ( CMD_FIRST + 26 )
Define CMD_UNINDENTSELECTION           FOR ( CMD_FIRST + 27 )
Define CMD_UNDOCHANGES                 FOR ( CMD_FIRST + 28 )
Define CMD_UNDO                        FOR ( CMD_FIRST + 29 )
Define CMD_TABIFYSELECTION             FOR ( CMD_FIRST + 30 )
Define CMD_SENTENCERIGHT               FOR ( CMD_FIRST + 31 )
Define CMD_SENTENCELEFT                FOR ( CMD_FIRST + 32 )
Define CMD_SENTENCECUT                 FOR ( CMD_FIRST + 33 )
Define CMD_SELECTSWAPANCHOR            FOR ( CMD_FIRST + 34 )
Define CMD_SELECTPARA                  FOR ( CMD_FIRST + 35 )
Define CMD_SELECTLINE                  FOR ( CMD_FIRST + 36 )
Define CMD_SELECTALL                   FOR ( CMD_FIRST + 37 )
Define CMD_REDOCHANGES                 FOR ( CMD_FIRST + 38 )
Define CMD_REDO                        FOR ( CMD_FIRST + 39 )
Define CMD_PASTE                       FOR ( CMD_FIRST + 40 )
Define CMD_PARAUP                      FOR ( CMD_FIRST + 41 )
Define CMD_PARADOWN                    FOR ( CMD_FIRST + 42 )
Define CMD_PAGEUPEXTEND                FOR ( CMD_FIRST + 43 )
Define CMD_PAGEUP                      FOR ( CMD_FIRST + 44 )
Define CMD_PAGEDOWNEXTEND              FOR ( CMD_FIRST + 45 )
Define CMD_PAGEDOWN                    FOR ( CMD_FIRST + 46 )
Define CMD_LOWERCASESELECTION          FOR ( CMD_FIRST + 47 )
Define CMD_LINEUPEXTEND                FOR ( CMD_FIRST + 48 )
Define CMD_LINEUP                      FOR ( CMD_FIRST + 49 )
Define CMD_LINETRANSPOSE               FOR ( CMD_FIRST + 50 )
Define CMD_LINESTART                   FOR ( CMD_FIRST + 51 )
Define CMD_LINEOPENBELOW               FOR ( CMD_FIRST + 52 )
Define CMD_LINEOPENABOVE               FOR ( CMD_FIRST + 53 )
Define CMD_LINEENDEXTEND               FOR ( CMD_FIRST + 54 )
Define CMD_LINEEND                     FOR ( CMD_FIRST + 55 )
Define CMD_LINEDOWNEXTEND              FOR ( CMD_FIRST + 56 )
Define CMD_LINEDOWN                    FOR ( CMD_FIRST + 57 )
Define CMD_LINEDELETETOSTART           FOR ( CMD_FIRST + 58 )
Define CMD_LINEDELETETOEND             FOR ( CMD_FIRST + 59 )
Define CMD_LINEDELETE                  FOR ( CMD_FIRST + 60 )
Define CMD_LINECUT                     FOR ( CMD_FIRST + 61 )
Define CMD_INDENTTOPREV                FOR ( CMD_FIRST + 62 )
Define CMD_INDENTSELECTION             FOR ( CMD_FIRST + 63 )
Define CMD_HOMEEXTEND                  FOR ( CMD_FIRST + 64 )
Define CMD_HOME                        FOR ( CMD_FIRST + 65 )
Define CMD_GOTOMATCHBRACE              FOR ( CMD_FIRST + 66 )
Define CMD_GOTOINDENTATION             FOR ( CMD_FIRST + 67 )
Define CMD_GOTOLINE                    FOR ( CMD_FIRST + 68 )
Define CMD_FINDREPLACE                 FOR ( CMD_FIRST + 69 )
Define CMD_REPLACE                     FOR ( CMD_FIRST + 70 )
Define CMD_REPLACEALLINBUFFER          FOR ( CMD_FIRST + 71 )
Define CMD_REPLACEALLINSELECTION       FOR ( CMD_FIRST + 72 )
Define CMD_FINDPREVWORD                FOR ( CMD_FIRST + 73 )
Define CMD_FINDPREV                    FOR ( CMD_FIRST + 74 )
Define CMD_FINDNEXTWORD                FOR ( CMD_FIRST + 75 )
Define CMD_FINDNEXT                    FOR ( CMD_FIRST + 76 )
Define CMD_FINDMARKALL                 FOR ( CMD_FIRST + 77 )
Define CMD_FIND                        FOR ( CMD_FIRST + 78 )
Define CMD_SETFINDTEXT                 FOR ( CMD_FIRST + 79 )
Define CMD_SETREPLACETEXT              FOR ( CMD_FIRST + 80 )
Define CMD_TOGGLEPRESERVECASE          FOR ( CMD_FIRST + 81 )
Define CMD_TOGGLEWHOLEWORD             FOR ( CMD_FIRST + 82 )
Define CMD_TOGGLECASESENSITIVE         FOR ( CMD_FIRST + 83 )
Define CMD_END                         FOR ( CMD_FIRST + 84 )
Define CMD_TOGGLEWHITESPACEDISPLAY     FOR ( CMD_FIRST + 85 )
Define CMD_TOGGLEOVERTYPE              FOR ( CMD_FIRST + 86 )
Define CMD_SETREPEATCOUNT              FOR ( CMD_FIRST + 87 )
Define CMD_DOCUMENTSTARTEXTEND         FOR ( CMD_FIRST + 88 )
Define CMD_DOCUMENTSTART               FOR ( CMD_FIRST + 89 )
Define CMD_DOCUMENTENDEXTEND           FOR ( CMD_FIRST + 90 )
Define CMD_DOCUMENTEND                 FOR ( CMD_FIRST + 91 )
Define CMD_DELETEHORIZONTALSPACE       FOR ( CMD_FIRST + 92 )
Define CMD_DELETEBLANKLINES            FOR ( CMD_FIRST + 93 )
Define CMD_DELETEBACK                  FOR ( CMD_FIRST + 94 )
Define CMD_DELETE                      FOR ( CMD_FIRST + 95 )
Define CMD_CUTSELECTION                FOR ( CMD_FIRST + 96 )
Define CMD_CUT                         FOR ( CMD_FIRST + 97 )
Define CMD_COPY                        FOR ( CMD_FIRST + 98 )
Define CMD_CHARTRANSPOSE               FOR ( CMD_FIRST + 99 )
Define CMD_CHARRIGHTEXTEND             FOR ( CMD_FIRST + 100 )
Define CMD_CHARRIGHT                   FOR ( CMD_FIRST + 101 )
Define CMD_CHARLEFTEXTEND              FOR ( CMD_FIRST + 102 )
Define CMD_CHARLEFT                    FOR ( CMD_FIRST + 103 )
Define CMD_BOOKMARKTOGGLE              FOR ( CMD_FIRST + 104 )
Define CMD_BOOKMARKPREV                FOR ( CMD_FIRST + 105 )
Define CMD_BOOKMARKNEXT                FOR ( CMD_FIRST + 106 )
Define CMD_BOOKMARKCLEARALL            FOR ( CMD_FIRST + 107 )
Define CMD_BOOKMARKJUMPTOFIRST         FOR ( CMD_FIRST + 108 )
Define CMD_BOOKMARKJUMPTOLAST          FOR ( CMD_FIRST + 109 )
Define CMD_APPENDNEXTCUT               FOR ( CMD_FIRST + 110 )
Define CMD_INSERTCHAR                  FOR ( CMD_FIRST + 111 )
Define CMD_NEWLINE                     FOR ( CMD_FIRST + 112 )
Define CMD_RECORDMACRO                 FOR ( CMD_FIRST + 113 )
Define CMD_PLAYMACRO1                  FOR ( CMD_FIRST + 114 )
Define CMD_PLAYMACRO2                  FOR ( CMD_FIRST + 115 )
Define CMD_PLAYMACRO3                  FOR ( CMD_FIRST + 116 )
Define CMD_PLAYMACRO4                  FOR ( CMD_FIRST + 117 )
Define CMD_PLAYMACRO5                  FOR ( CMD_FIRST + 118 )
Define CMD_PLAYMACRO6                  FOR ( CMD_FIRST + 119 )
Define CMD_PLAYMACRO7                  FOR ( CMD_FIRST + 120 )
Define CMD_PLAYMACRO8                  FOR ( CMD_FIRST + 121 )
Define CMD_PLAYMACRO9                  FOR ( CMD_FIRST + 122 )
Define CMD_PLAYMACRO10                 FOR ( CMD_FIRST + 123 )
Define CMD_PROPERTIES                  FOR ( CMD_FIRST + 124 )
Define CMD_BEGINUNDO                   FOR ( CMD_FIRST + 125 )
Define CMD_ENDUNDO                     FOR ( CMD_FIRST + 126 )
Define CMD_RESERVED3                   FOR ( CMD_FIRST + 127 )  // internal use only
// 2.0
Define CMD_TOGGLEREGEXP                FOR ( CMD_FIRST + 128 )
Define CMD_CLEARSELECTION              FOR ( CMD_FIRST + 129 )
Define CMD_REGEXPON                    FOR ( CMD_FIRST + 130 )
Define CMD_REGEXPOFF                   FOR ( CMD_FIRST + 131 )
Define CMD_WHOLEWORDON                 FOR ( CMD_FIRST + 132 )
Define CMD_WHOLEWORDOFF                FOR ( CMD_FIRST + 133 )
Define CMD_PRESERVECASEON              FOR ( CMD_FIRST + 134 )
Define CMD_PRESERVECASEOFF             FOR ( CMD_FIRST + 135 )
Define CMD_CASESENSITIVEON             FOR ( CMD_FIRST + 136 )
Define CMD_CASESENSITIVEOFF            FOR ( CMD_FIRST + 137 )
Define CMD_WHITESPACEDISPLAYON         FOR ( CMD_FIRST + 138 )
Define CMD_WHITESPACEDISPLAYOFF        FOR ( CMD_FIRST + 139 )
Define CMD_OVERTYPEON                  FOR ( CMD_FIRST + 140 )
Define CMD_OVERTYPEOFF                 FOR ( CMD_FIRST + 141 )
// SVN
//Define CMD_LAST                        For ( CMD_FIRST + 141 )
// 2.1
Define CMD_CODELIST                    FOR ( CMD_FIRST + 142 )
Define CMD_CODETIP                     FOR ( CMD_FIRST + 143 )
Define CMD_LAST                        FOR ( CMD_FIRST + 143 )

// all register commands must be at or higher than CMD_USER_BASE
Define CMD_USER_BASE                   FOR ( CMD_FIRST + 900 )

Define CMDERR_FAILURE     FOR 1     // general failure
Define CMDERR_INPUT       FOR 2     // bad input
Define CMDERR_SELECTION   FOR 3     // bad selection
Define CMDERR_NOTFOUND    FOR 4     // data not found
Define CMDERR_EMPTYBUF    FOR 5     // buffer is empty
Define CMDERR_READONLY    FOR 6     // buffer is read-only

////////////////////////////////////////////////////////////////////////////////////////
//
// Language Support for CMM_SETLANGUAGE, RegisterLanguage(), and UnregisterLanguage()
//
//

// stock languages
Define CMLANG_CPP         FOR "C/C++"
Define CMLANG_PASCAL      FOR "Pascal"
Define CMLANG_BASIC       FOR "Basic"
Define CMLANG_SQL         FOR "SQL"
Define CMLANG_JAVA        FOR "Java"
Define CMLANG_HTML        FOR "HTML"
Define CMLANG_XML         FOR "XML"

// language styles
Define CMLS_PROCEDURAL    FOR 0
Define CMLS_SGML          FOR 1


TYPE CM_LANGUAGE
    Field CM_LANGUAGE.dwStyle                             as Dword    // One of the CMLS_ values DWORD
    Field CM_LANGUAGE.bIsCaseSensitive                    as Integer  // TRUE if keywords are case sensitive BOOL
    Field CM_LANGUAGE.pszKeywords                         as Pointer  // The keywords delimited by '\n' LPCTSTR
    Field CM_LANGUAGE.pszOperators                        as Pointer  // The operators delimited by '\n' LPCTSTR
    Field CM_LANGUAGE.pszSingleLineComments               as Pointer  // The single line comment tokens (e.g. "//") LPCTSTR
    Field CM_LANGUAGE.pszMultiLineComments1               as Pointer  // The multiline comment start tokens (e.g. "/*\n{\n(*") LPCTSTR
    Field CM_LANGUAGE.pszMultiLineComments2               as Pointer  // The multiline comment end tokens (e.g. "*/\n}\n*)") LPCTSTR
    Field CM_LANGUAGE.pszScopeKeywords1                   as Pointer  // The scoping start tokens (e.g. "{\nbegin") LPCTSTR
    Field CM_LANGUAGE.pszScopeKeywords2                   as Pointer  // The multiline comment end tokens (e.g. "}\nend") LPCTSTR
    Field CM_LANGUAGE.pszStringDelims                     as Pointer  // The string literal delimiters (e.g. "\"\n'") -- also includes character literals LPCTSTR
    Field CM_LANGUAGE.chEscape                            as Char 1   // The escape character TCHAR
    Field CM_LANGUAGE.chTerminator                        as Char 1   // The statement terminator char (usually ';') TCHAR
    Field CM_LANGUAGE.pszTagElementNames                  as Pointer  // Tag-based element names delimited by '\n' LPCTSTR
    Field CM_LANGUAGE.pszTagAttributeNames                as Pointer  // Tag-based attribute names delimited by '\n' LPCTSTR
    Field CM_LANGUAGE.pszTagEntities                      as Pointer  // Tag-based entities delimited by '\n' LPCTSTR
END_TYPE

// Color settings for CMM_GETCOLORS and CMM_SETCOLORS
//
// Note:  Use CLR_INVALID on background colors to specify transparent
//        (text) or appropriate control panel setting
TYPE CM_COLORS
    Field CM_COLORS.crWindow                            as COLORREF // window background color
    Field CM_COLORS.crLeftMargin                        as COLORREF // left margin background color
    Field CM_COLORS.crBookmark                          as COLORREF // bookmark foreground color
    Field CM_COLORS.crBookmarkBk                        as COLORREF // bookmark background color
    Field CM_COLORS.crText                              as COLORREF // plain text foreground color
    Field CM_COLORS.crTextBk                            as COLORREF // plain text background color
    Field CM_COLORS.crNumber                            as COLORREF // numeric literal foreground color
    Field CM_COLORS.crNumberBk                          as COLORREF // numeric literal background color
    Field CM_COLORS.crKeyword                           as COLORREF // keyword foreground color
    Field CM_COLORS.crKeywordBk                         as COLORREF // keyword background color
    Field CM_COLORS.crOperator                          as COLORREF // operator foreground color
    Field CM_COLORS.crOperatorBk                        as COLORREF // operator background color
    Field CM_COLORS.crScopeKeyword                      as COLORREF // scope keyword foreground color
    Field CM_COLORS.crScopeKeywordBk                    as COLORREF // scope keyword background color
    Field CM_COLORS.crComment                           as COLORREF // comment foreground color
    Field CM_COLORS.crCommentBk                         as COLORREF // comment background color
    Field CM_COLORS.crString                            as COLORREF // string foreground color
    Field CM_COLORS.crStringBk                          as COLORREF // string background color
    Field CM_COLORS.crTagText                           as COLORREF // plain tag text foreground color
    Field CM_COLORS.crTagTextBk                         as COLORREF // plain tag text background color
    Field CM_COLORS.crTagEntity                         as COLORREF // tag entity foreground color
    Field CM_COLORS.crTagEntityBk                       as COLORREF // tag entity background color
    Field CM_COLORS.crTagElementName                    as COLORREF // tag element name foreground color
    Field CM_COLORS.crTagElementNameBk                  as COLORREF // tag element name background color
    Field CM_COLORS.crTagAttributeName                  as COLORREF // tag attribute name foreground color
    Field CM_COLORS.crTagAttributeNameBk                as COLORREF // tag attribute name background color
    Field CM_COLORS.crLineNumber                        as COLORREF // line number foreground color
    Field CM_COLORS.crLineNumberBk                      as COLORREF // line number background color
    Field CM_COLORS.crHDividerLines                     as COLORREF // line number separate line color
    Field CM_COLORS.crVDividerLines                     as COLORREF // left margin separate line color
    Field CM_COLORS.crHighlightedLine                   as COLORREF // highlighted line color
END_TYPE


/////////////////////////////////////////////////////////////
//
// Font style settings for CMM_GETFONTSTYLES and CMM_SETFONTSTYLES
// each byte value is one of the CM_FONT_XXX values listed below
// this declaration
//
TYPE CM_FONTSTYLES
    Field CM_FONTSTYLES.byText                              as Char 1   // plain text font style BYTE
    Field CM_FONTSTYLES.byNumber                            as Char 1   // numeric literal font style BYTE
    Field CM_FONTSTYLES.byKeyword                           as Char 1   // keyword font style BYTE
    Field CM_FONTSTYLES.byOperator                          as Char 1   // operator font style BYTE
    Field CM_FONTSTYLES.byScopeKeyword                      as Char 1   // scope keyword font style BYTE
    Field CM_FONTSTYLES.byComment                           as Char 1   // comment font style BYTE
    Field CM_FONTSTYLES.byString                            as Char 1   // string font style BYTE
    Field CM_FONTSTYLES.byTagText                           as Char 1   // plain tag text font style BYTE
    Field CM_FONTSTYLES.byTagEntity                         as Char 1   // tag entity font style BYTE
    Field CM_FONTSTYLES.byTagElementName                    as Char 1   // tag element name font style BYTE
    Field CM_FONTSTYLES.byTagAttributeName                  as Char 1   // tag attribute name font style BYTE
    Field CM_FONTSTYLES.byLineNumber                        as Char 1   // line number font style BYTE
END_TYPE

/////////////////////////////////////////////////////////////
//
// Font style options used in CM_FONTSTYLES
//
//
Define CM_FONT_NORMAL     FOR 0   // normal weight
Define CM_FONT_BOLD       FOR 1   // bold weight
Define CM_FONT_ITALIC     FOR 2   // normal weight, italic
Define CM_FONT_BOLDITALIC FOR 3   // bold weight, italic
Define CM_FONT_UNDERLINE  FOR 4   // normal weight, underline

/////////////////////////////////////////////////////////////
//
// AutoIndent options
//
//
Define CM_INDENT_OFF        FOR  0    // auto-indent off -- new line begins at column 0
Define CM_INDENT_SCOPE      FOR  1    // new line begins at correct language scope indentation level
Define CM_INDENT_PREVLINE   FOR  2    // new line has identical indentation of previous line

/////////////////////////////////////////////////////////////
//
// Print option flags used with CMM_PRINT
//
//
Define CM_PRINT_PROMPTDLG    FOR |CI$000   // display the print common dialog
Define CM_PRINT_DEFAULTPRN   FOR |CI$001   // use default printer (no print dialog displayed)
Define CM_PRINT_HDC          FOR |CI$002   // use HDC provided
Define CM_PRINT_RICHFONTS    FOR |CI$004   // use bold, italics, underline, etc. when appropriate
Define CM_PRINT_COLOR        FOR |CI$008   // print in color
Define CM_PRINT_PAGENUMS     FOR |CI$010   // print 'page # of #' at the bottom of the page
Define CM_PRINT_DATETIME     FOR |CI$020   // print date and time at top of the page
Define CM_PRINT_BORDERTHIN   FOR |CI$040   // surround text with a thin border
Define CM_PRINT_BORDERTHICK  FOR |CI$080   // surround text with a thick border
Define CM_PRINT_BORDERDOUBLE FOR |CI$100   // surround text with two thin borders
Define CM_PRINT_SELECTION    FOR |CI$200   // print the selection rather than entire edit contents

/////////////////////////////////////////////////////////////
//
// Border option flags used with CMM_GETBORDERSTYLE and CMM_SETBORDERSTYLE.
// Note: this values may be or'd together to achieve different effects.
//
Define CM_BORDER_NONE        FOR |CI$0  // no border
Define CM_BORDER_THIN        FOR |CI$1  // 1-pixel border
Define CM_BORDER_CLIENT      FOR |CI$2  // client edge (WS_EX_CLIENTEDGE)
Define CM_BORDER_STATIC      FOR |CI$4  // static edge (WS_EX_STATICEDGE)
Define CM_BORDER_MODAL       FOR |CI$8  // modal edge (WS_EX_DLGMODALFRAME)
Define CM_BORDER_CORRAL      FOR (CM_BORDER_MODAL Ior CM_BORDER_CLIENT)


/////////////////////////////////////////////////////////////
//
// Text position indicators
//
//

TYPE CM_POSITION
    Field CM_POSITION.nLine                as Integer  // zero-based line number int
    Field CM_POSITION.nCol                 as Integer  // zero-based *buffer* column number int
END_TYPE

    // Erzeugt einen String und eine Pointer variable, wenn diese noch nicht definiert sind!
    // Fueltt mit Line und Col und holt die Addresse in the Pointer
#COMMAND Local_CM_POSITION R R "LINE=" R "COL=" R
    DEFINE_STR_PTR !1 !2
    Zerotype CM_POSITION  to !1         // as a little insurance
    Put !4 to !1 at CM_POSITION.nLine   // Set Line
    Put !6 to !1 at CM_POSITION.nCol    // Set Column
    GetAddress Of !1 to !2
#ENDCOMMAND


    // Erzeugt einen String und eine Pointer variable, wenn diese noch nicht definiert sind!
    // Fueltt mit Line und Col und holt die Addresse in the Pointer

TYPE CM_RANGE
    Field CM_RANGE.posStart             as Char CM_POSITION_SIZE    // the anchor CM_POSITION
    Field CM_RANGE.posEnd               as Char CM_POSITION_SIZE    // the extension (if same as anchor, selection is empty) CM_POSITION
    Field CM_RANGE.bColumnSel           as Integer                  // TRUE if is a column selection, FALSE if paragragh selection BOOL
END_TYPE

#COMMAND Local_CM_RANGE R R "START=" R  R "END=" R R
    DEFINE_STR_PTR !1 !2
    Zerotype CM_RANGE   to !1

    Local_CM_POSITION sPosStart psPosStart LINE= !4 COL= !5   // Create a String with the StartPosition
    Local_CM_POSITION sPosEnd   psPosEnd   LINE= !7 COL= !8   // Create a String with the EndPosition

    PUT_STRING sPosStart to !1 AT CM_RANGE.posStart           // Set Start Position
    PUT_STRING sPosEnd   to !1 AT CM_RANGE.posEnd             // Set End Position

    GetAddress Of !1     to !2                                // Get the Address of the created Structure
#ENDCOMMAND


/////////////////////////////////////////////////////////////
//
// Hot key descriptor
//
//
TYPE CM_HOTKEY
    Field CM_HOTKEY.byModifiers1         as Integer //Char 1   // 1st keystroke's modifiers (combination of HOTKEYF_ALT, HOTKEYF_SHIFT, HOTKEYF_CONTROL) BYTE
    Field CM_HOTKEY.nVirtKey1            as Integer  // 1st keystroke's virtkey (e.g. Ctrl + 'A') UINT
    Field CM_HOTKEY.byModifiers2         as Integer //Char 1   // 2nd keystroke's modifiers (combination of HOTKEYF_ALT, HOTKEYF_SHIFT, HOTKEYF_CONTROL) BYTE
    Field CM_HOTKEY.nVirtKey2            as Integer  // 2nd keystroke's virtkey (e.g. Ctrl + 'A') UINT
END_TYPE

/////////////////////////////////////////////////////////////
//
// CMN_DRAWLINE notification data passed to parent window
//
//
TYPE CM_DRAWLINEDATA
    Field CM_DRAWLINEDATA.hdr                  as Char NMHDR_SIZE   // standard notification data NMHDR
    Field CM_DRAWLINEDATA.hDC                  as Pointer           // device context to draw with, clipped to current paint area HDC
    Field CM_DRAWLINEDATA.rcLine.Left          as Dword             // Expand the tRectStructure to ist elements.
    Field CM_DRAWLINEDATA.rcLine.top           as Dword
    Field CM_DRAWLINEDATA.rcLine.Right         as Dword
    Field CM_DRAWLINEDATA.rcLine.bottom        as Dword
    Field CM_DRAWLINEDATA.nLine                as Integer           // line number to draw int
    Field CM_DRAWLINEDATA.nLeftCol             as Integer           // leftmost visible col int
    Field CM_DRAWLINEDATA.nRightCol            as Integer           // rightmost visible col int
    Field CM_DRAWLINEDATA.lParam               as Pointer           // itemdata associated with the line (CMM_SETITEMDATA) LPARAM
    Field CM_DRAWLINEDATA.dwStyle              as Pointer           // line style bits (CML_XXX) DWORD
END_TYPE

/////////////////////////////////////////////////////////////
//
// CMN_DELETELINE notification data passed to parent window
//
//
TYPE CM_DELETELINEDATA
    Field CM_DELETELINEDATA.hdr                  as Char NMHDR_SIZE  // standard notification data NMHDR
    Field CM_DELETELINEDATA.nLine                as Integer          // line that is about to be deleted int
    Field CM_DELETELINEDATA.lParam               as Pointer          // itemdata associated with the line (CMM_SETITEMDATA) LPARAM
END_TYPE

/////////////////////////////////////////////////////////////
//
// CMN_CMDFAILURE notification data passed to parent window
//
//
TYPE CM_CMDFAILUREDATA
    Field CM_CMDFAILUREDATA.hdr                  as Char NMHDR_SIZE // standard notification data NMHDR
    Field CM_CMDFAILUREDATA.wCmd                 as WORD            // CMD_XXX command that failed WORD
    Field CM_CMDFAILUREDATA.dwErr                as Dword           // CMDERR_XXX failure code DWORD
END_TYPE


/////////////////////////////////////////////////////////////
//
// CMN_REGISTEREDCMD notification data passed to parent window
//
//
TYPE CM_REGISTEREDCMDDATA
    Field CM_REGISTEREDCMDDATA.hdr                  as Char NMHDR_SIZE  // standard notification data NMHDR
    Field CM_REGISTEREDCMDDATA.wCmd                 as WORD             // registered command to be executed WORD
END_TYPE
/////////////////////////////////////////////////////////////
//
// CMN_KEYDOWN, CMN_KEYUP, CMN_KEYPRESS notification
// data passed to parent window
//
//
Define CM_KEY_NOEXT      FOR |CI$0
Define CM_KEY_SHIFT      FOR |CI$1
Define CM_KEY_CTRL       FOR |CI$2
Define CM_KEY_ALT        FOR |CI$4
TYPE CM_KEYDATA
    Field CM_KEYDATA.hdr                  as Char NMHDR_SIZE    // standard notification data NMHDR
    Field CM_KEYDATA.nKeyCode             as Integer            // virtkey if CMN_KEYUP or CMN_KEYDOWN.  Ascii code if CMN_KEYPRESS int
    Field CM_KEYDATA.nKeyModifier         as Integer            // bitfield of: CM_KEY_SHIFT, CM_KEY_CTRL, and/or CM_KEY_ALT int
END_TYPE

    // Just converts the ID to the name.
Function CMKeymodifierIDToName Global Integer iModifier Returns String
    String sRet
    If (iModifier Iand CM_KEY_SHIFT) Append sRet (If(sRet Eq "","","+")) "Shift"
    If (iModifier Iand CM_KEY_CTRL)  Append sRet (If(sRet Eq "","","+")) "Ctrl"
    If (iModifier Iand CM_KEY_ALT)   Append sRet (If(sRet Eq "","","+")) "Alt"
    Function_Return sRet
End_Function

/////////////////////////////////////////////////////////////
//
// CMN_MOUSEDOWN, CMN_MOUSEUP, CMN_MOUSEPRESS notification
// data passed to parent window
//
//
Define CM_BTN_LEFT      FOR |CI$1
Define CM_BTN_RIGHT     FOR |CI$2
Define CM_BTN_MIDDLE    FOR |CI$4

TYPE CM_MOUSEDATA
    Field CM_MOUSEDATA.hdr                  as Char NMHDR_SIZE  // standard notification data NMHDR
    Field CM_MOUSEDATA.pt                   as Char tPOINT_SIZE // position of mouse (client coordinates) POINT
    Field CM_MOUSEDATA.nButton              as Integer  // bitfield of: CM_BTN_LEFT, CM_BTN_RIGHT, and/or CM_BTN_MIDDLE int
    Field CM_MOUSEDATA.nKeyModifier         as Integer  // bitfield of: CM_KEY_SHIFT, CM_KEY_CTRL, and/or CM_KEY_ALT int
END_TYPE

/////////////////////////////////////////////////////////////
//
// CMN_FINDWRAPPED notification data passed to parent window
//
//
TYPE CM_FINDWRAPPEDDATA
    Field CM_FINDWRAPPEDDATA.hdr                  as Char NMHDR_SIZE // standard notification data NMHDR
    Field CM_FINDWRAPPEDDATA.wCmd                 as WORD     // the command being executed WORD
    Field CM_FINDWRAPPEDDATA.bForward             as Integer  // TRUE if wrapped while searching forward, FALSE if searching backward BOOL
END_TYPE

// START - SVN
// -----------------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////
//
// CMN_CODELIST, CMN_CODELISTSELMADE, CMN_CODELISTCANCEL
// notification data passed to parent window
//
TYPE CM_CODELISTDATA
    Field CM_CODELISTDATA.hdr              as Char NMHDR_SIZE   // standard notification data (NMHDR)
    Field CM_CODELISTDATA.hListCtrl        as Handle   // handle to list view control window (HWND)
END_TYPE

/////////////////////////////////////////////////////////////
//
// CMN_CODELISTCHAR notification data passed to parent
// window
//

// BP Codelist support

TYPE CM_CODELISTKEYDATA
    Field CM_CODELISTKEYDATA.clData.hDr         as Char NMHDR_SIZE
    Field CM_CODELISTKEYDATA.clData.hListCtrl   as Handle
    Field CM_CODELISTKEYDATA.wChar              as Integer
    Field CM_CODELISTKEYDATA.lKeyData           as Integer
END_TYPE


/////////////////////////////////////////////////////////////
//
// CMN_CODELISTSELWORD notification data passed to parent
// window
//
//typedef struct _CM_CODELISTSELWORDDATA
//{
//	CM_CODELISTDATA		clData;
//	int					iItem;		// list item about to be selected
//
//} CM_CODELISTSELWORDDATA, *LPCM_CODELISTSELWORDDATA;


/////////////////////////////////////////////////////////////
//
// CMN_CODELISTSELCHANGE notification data passed to parent
// window
//
//typedef struct _CM_CODELISTSELCHANGEDATA
//{
//	CM_CODELISTDATA		clData;
//	int					iItem;
//	LPTSTR				pszText;
//	TCHAR				szText[CM_MAX_CODELIST_TIP];
//	HINSTANCE			hInstance;
//
//} CM_CODELISTSELCHANGEDATA, *LPCM_CODELISTSELCHANGEDATA;


/////////////////////////////////////////////////////////////
//
// CMN_CODELISTHOTTRACK notification data passed to parent
// window
//
//typedef struct _CM_CODELISTHOTTRACKDATA
//{
//	CM_CODELISTDATA		clData;
//	int					iItem;		// index of the list item that is "hot"
//
//} CM_CODELISTHOTTRACKDATA, *LPCM_CODELISTHOTTRACKDATA;


/////////////////////////////////////////////////////////////
//
// CMN_CODETIPCANCEL, CMN_CODETIPINITIALIZE,
// CMN_CODETIPUPDATE notification data passed to parent
// window
//

// Structure used if nTipType is set to CM_TIPSTYLE_NORMAL
//typedef struct _CM_CODETIPDATA
//{
//	NMHDR	hdr;		// standard notification data
//	HWND	hToolTip;	// handle to tooltip window
//	UINT	nTipType;	// type of tooltip in use
//
//} CM_CODETIPDATA, *LPCM_CODETIPDATA;

TYPE CM_CODETIPDATA
    Field CM_CODETIPDATA.hdr             as Char NMHDR_SIZE // standard notification data (NMHDR)
    Field CM_CODETIPDATA.hToolTip        as Handle          // handle to tooltip window (HWND)
    Field CM_CODETIPDATA.nTipType        as Integer         // type of tooltip in use (UINT)
END_TYPE

// Structure used if nTipType is set to CM_TIPSTYLE_HIGHLIGHT
//typedef struct _CM_CODETIPHIGHLIGHTDATA
//{
//	CM_CODETIPDATA		ctData;
//	UINT				nHighlightStartPos;
//	UINT				nHighlightEndPos;
//
//} CM_CODETIPHIGHLIGHTDATA, *LPCM_CODETIPHIGHLIGHTDATA;

TYPE CM_CODETIPHIGHLIGHTDATA
    Field CM_CODETIPHIGHLIGHTDATA.ctData.hdr            as Char NMHDR_SIZE
    Field CM_CODETIPHIGHLIGHTDATA.ctDatah.ToolTip        as Handle
    Field CM_CODETIPHIGHLIGHTDATA.ctDatan.TipType        as Integer
    Field CM_CODETIPHIGHLIGHTDATA.nHighlightStartPos    as Integer   // (UINT)
    Field CM_CODETIPHIGHLIGHTDATA.nHighlightEndPos      as Integer   // (UINT)
END_TYPE

// structure used if nTipType is set to CM_TIPSTYLE_FUNCHIGHLIGHT
//typedef struct _CM_CODETIPFUNCHIGHLIGHTDATA
//{
//	CM_CODETIPDATA		ctData;
//	UINT				nArgument;
//} CM_CODETIPFUNCHIGHLIGHTDATA, *LPCM_CODETIPFUNCHIGHLIGHTDATA;

TYPE CM_CODETIPFUNCHIGHLIGHTDATA
    Field CM_CODETIPFUNCHIGHLIGHTDATA.ctData.hdr            as Char NMHDR_SIZE
    Field CM_CODETIPFUNCHIGHLIGHTDATA.ctData.hToolTip       as Handle
    Field CM_CODETIPFUNCHIGHLIGHTDATA.ctData.nTipType       as Integer
    Field CM_CODETIPFUNCHIGHLIGHTDATA.nArgument             as Integer  // (UINT)
END_TYPE

//
// structure used if nTipType is set to CM_TIPSTYLE_MULTIFUNC
//typedef struct _CM_CODETIPMULTIFUNCDATA
//{
//	CM_CODETIPFUNCHIGHLIGHTDATA		ctfData;
//	UINT							nFuncCount;
//	UINT							nCurrFunc;
//} CM_CODETIPMULTIFUNCDATA, *LPCM_CODETIPMULTIFUNCDATA;

TYPE CM_CODETIPMULTIFUNCDATA
    Field CM_CODETIPMULTIFUNCDATA.ctfData.ctData.hdr       as Char NMHDR_SIZE
    Field CM_CODETIPMULTIFUNCDATA.ctfData.ctData.hToolTip  as Handle
    Field CM_CODETIPMULTIFUNCDATA.ctfData.ctData.nTipType  as Integer
    Field CM_CODETIPMULTIFUNCDATA.ctfData.nArgument        as Integer  // (UINT)
    Field CM_CODETIPMULTIFUNCDATA.nFuncCount               as Integer   // (UINT)
    Field CM_CODETIPMULTIFUNCDATA.nCurrFunc                as Integer   // (UINT)
END_TYPE


/////////////////////////////////////////////////////////////
//
// Tooltip window styles specified as return value from
// CMN_CODETIP notifications
//
Define CM_TIPSTYLE_NONE				    FOR 0	// don't display a tooltip
Define CM_TIPSTYLE_NORMAL				FOR 1	// standard tooltip window
Define CM_TIPSTYLE_HIGHLIGHT			FOR 2	// tooltip with text highlighting
Define CM_TIPSTYLE_FUNCHIGHLIGHT		FOR 3	// tooltip with function highlighting
Define CM_TIPSTYLE_MULTIFUNC			FOR 4	// highlighting for multiple functions


Define C_TIPTYPE_UNDEFINED        for 0
Define C_TIPTYPE_EXPRESSION       for 1
Define C_TIPTYPE_FUNCTION         for 2
Define C_TIPTYPE_PROCEDURE        for 3

// -----------------------------------------------------------------------------------------
// END - SVN


/////////////////////////////////////////////////////////////
//
// data passed to CMM_SETLINENUMBERING
//
//
Define CM_BINARY            FOR 2
Define CM_OCTAL             FOR 8
Define CM_DECIMAL           FOR 10
Define CM_HEXADECIMAL       FOR 16

TYPE CM_LINENUMBERING
    Field CM_LINENUMBERING.bEnabled             as Integer  // TRUE to enable, FALSE to disable BOOL
    Field CM_LINENUMBERING.nStartAt             as Integer  // # of line at top of buffer (line 0) UINT
    Field CM_LINENUMBERING.dwStyle              as Dword    // CM_DECIMAL, CM_HEXADECIMAL, CM_OCTAL, or CM_BINARY DWORD
END_TYPE

#COMMAND Local_CM_LINENUMBERING R R R R R
    DEFINE_STR_PTR !1 !2
    Zerotype CM_LINENUMBERING  to !1            // as a little insurance
    Put !3 to !1 at CM_LINENUMBERING.bEnabled   // On/Off
    Put !4 to !1 at CM_LINENUMBERING.nStartAt   // Start with Nr
    Put !5 to !1 at CM_LINENUMBERING.dwStyle    // Start with Nr
    GetAddress Of !1 to !2
#ENDCOMMAND

/////////////////////////////////////////////////////////////
//
// Error codes
//
//
//typedef LRESULT CME_CODE;

Define CME_SUCCESS        FOR 1        // function or method completed successfully
Define CME_FAILURE        FOR 0        // function or method did not complete because of an error
Define CME_BADARGUMENT    FOR -1       // function or method did not complete because an invalid argument was passed in

/////////////////////////////////////////////////////////////
//
// CMM_HITTEST return codes
//
//

Define CM_NOWHERE        FOR 0        // Not over the CodeMax control
Define CM_HSPLITTER      FOR 1        // Over the horizontal splitter bar
Define CM_VSPLITTER      FOR 2        // Over the vertical splitter bar
Define CM_HVSPLITTER     FOR 3        // Over the intersection of the horizontal and vertical splitter bar
Define CM_EDITSPACE      FOR 4        // Over the buffer contents (code)
Define CM_HSCROLLBAR     FOR 5        // Over the horizontal scrollbar
Define CM_VSCROLLBAR     FOR 6        // Over the vertical scrollbar
Define CM_SIZEBOX        FOR 7        // Over the sizebox visible when both scrollbars are visible
Define CM_LEFTMARGIN     FOR 8        // Over the left margin area


/////////////////////////////////////////////////////////////
//
// CMM_GETCURRENTTOKEN return codes
//
//

Define CM_TOKENTYPE_KEYWORD					FOR |CI$1 // 0x01
Define CM_TOKENTYPE_OPERATOR				FOR |CI$2 //0x02
Define CM_TOKENTYPE_STRING					FOR |CI$3 //0x03
Define CM_TOKENTYPE_SINGLELINECOMMENT		FOR |CI$4 //0x04
Define CM_TOKENTYPE_MULTILINECOMMENT		FOR |CI$5 //0x05
Define CM_TOKENTYPE_NUMBER					FOR |CI$6 //0x06
Define CM_TOKENTYPE_SCOPEBEGIN				FOR |CI$7 //0x07
Define CM_TOKENTYPE_SCOPEEND				FOR |CI$8 //0x08
Define CM_TOKENTYPE_TEXT					FOR |CI$FF //0xff
Define CM_TOKENTYPE_LAST                    FOR |CI$FFFFFFFF
Define CM_TOKENTYPE_UNKNOWN					FOR (CM_TOKENTYPE_LAST-1) //(DWORD)-1



/////////////////////////////////////////////////////////////
//
// Exported functions
//
//

Define CM_VERSION FOR |CI$02100

External_Function CMRegisterControl "CMRegisterControl" CMAX_DLL_NAME Dword dwVersion Returns Integer
External_Function CMUnregisterControl "CMUnregisterControl" CMAX_DLL_NAME Returns Integer
External_Function CMSetFindReplaceMRUList "CMSetFindReplaceMRUList" CMAX_DLL_NAME Pointer pszMRUList Integer bFind Returns Integer
External_Function CMGetFindReplaceMRUList "CMGetFindReplaceMRUList" CMAX_DLL_NAME Pointer pszMRUList Integer bFind Returns Integer
External_Function CMRegisterLanguage "CMRegisterLanguage" CMAX_DLL_NAME Pointer pszName Pointer pLang Returns Integer
External_Function CMUnregisterLanguage "CMUnregisterLanguage" CMAX_DLL_NAME Pointer pszName Returns Integer
External_Function CMGetHotKeysInt "CMGetHotKeys" CMAX_DLL_NAME Pointer  pBuff Returns Integer
Function CMGetHotkeys Global Returns String
    Integer iSize
    Move (CMGetHotkeysInt(0))           to iSize
    Local_BUFFER sBuff pBuff iSize
    Move (CMGetHotKeysInt(pBuff))       to iSize
    Move (ConvertBuffToAscii(sBuff))    to sBuff
    Function_Return sBuff
End_Function
External_Function CMSetHotKeysInt "CMSetHotKeys" CMAX_DLL_NAME Pointer pBuff Returns Integer
Function CMSetHotkeys Global String sBuff Returns Integer
    Integer iRet
    Move (ConvertAsciiToBuff(sBuff))    to sBuff
    Local_BUFFER sBuff pBuff
    Move (CMSetHotKeysInt(pBuff))       to iRet
    Function_Return iRet
End_Function
External_Function CMResetDefaultHotKeys "CMResetDefaultHotKeys" CMAX_DLL_NAME  Returns Integer
External_Function CMGetHotKeysForCmd "CMGetHotKeysForCmd" CMAX_DLL_NAME Integer wCmd Pointer pHotKeys  Returns Integer
Use mWinAPIGetKeyNameText.pkg   // Get a name for a virual keycode.

Function CMCommandToHotKeyStr Integer iCmd Returns String
    String sKey sExt sRet sHotkey
    Integer iRet iModifier1 iModifier2 iVirtKey1 iVirtKey2 iTmp
    Integer iCount iKeys
    Move (CMGetHotKeysForCmd(iCmd,0))   to iKeys                 // Get the Number of hotkeys assigned!
    If iKeys Eq 0 Function_Return ""                             // No hotkey assigned.
    Local_Buffer sHotKeys pHotKeys (CM_HOTKEY_SIZE*iKeys+10)     // Reserver the necc. amount of memory to get all Hotkeys assigned to the cmd.
    Move (CMGetHotKeysForCmd(iCmd,pHotKeys))   to iRet           // Gets the assigned hotkeys.

    FOR iCount From 0 to (iKeys-1)
        Move (Mid(sHotkeys,CM_HOTKEY_SIZE,(CM_HOTKEY_SIZE*iCount)+1))   to sHotkey

        // We are only interested in the 1st Hotkey up to now.
        Getbuff From sHotKey at CM_HOTKEY.byModifiers1 to iModifier1
        Getbuff From sHotKey at CM_HOTKEY.nVirtKey1    to iVirtKey1
        Move (CMKeymodifierIDToName(iModifier1))        to sExt
        If sExt Ne "" Append sExt "+"
        Move ""                                          to sKey
        If iVirtKey1 Eq VK_Down  Move "Down"             to sKey    // Do this extra becouse
        If iVirtKey1 Eq VK_Up    Move "Up"               to sKey    // the created description for
        If iVirtKey1 Eq VK_Left  Move "Left"             to sKey    // these keys is awful long. <g>
        If iVirtKey1 Eq VK_Right Move "Right"            to sKey
        If sKey Eq "" Move (WinAPIGetKeyNameText(iVirtKey1))  to sKey
        If sRet Ne "" Append sRet ","
        Append sRet sExt sKey
    End
    Function_Return (ToOem(sRet))
End_Function


    // Gets the keys assigned to a value.
    // LOW: Virt key
    //  HI: Modifier (Combination of CM_KEY_ALT,CM_KEY_CONTROL,CM_KEY_SHIFT)
Function CMGetKeyForCommand Integer iCmd Integer iNr Returns Integer
    String  sHotkey
    Integer iRet iModifier1 iVirtKey1 iKeys
    Move (CMGetHotKeysForCmd(iCmd,0))   to iKeys                 // Get the Number of hotkeys assigned!
    If iNr Lt 0 Function_Return iKeys                            // If item lt 0 returns the number of keys.
    If iKeys Eq 0 Function_Return 0                              // If not keys are assigned break.
        // Get the keyvalues...
    Local_Buffer sHotKeys pHotKeys (CM_HOTKEY_SIZE*iKeys+10)                        // Reserver the necc. amount of memory to get all Hotkeys assigned to the cmd.
    Move (CMGetHotKeysForCmd(iCmd,pHotKeys))                    to iRet         // Gets the assigned hotkeys.
    Move (Mid(sHotkeys,CM_HOTKEY_SIZE,(CM_HOTKEY_SIZE*iNr)+1))  to sHotkey      // Get the selected key.
    Getbuff From sHotKey at CM_HOTKEY.byModifiers1              to iModifier1   // Get the Ext key.
    Getbuff From sHotKey at CM_HOTKEY.nVirtKey1                 to iVirtKey1    // Get the VK key.
    Function_Return (MAKEWPARAM(iModifier1,iVirtkey1))
End_Function





External_Function CMRegisterHotKey "CMRegisterHotKey" CMAX_DLL_NAME Pointer pHotKey Integer wCmd   Returns Integer
External_Function CMUnregisterHotKey "CMUnregisterHotKey" CMAX_DLL_NAME Pointer pHotKey   Returns Integer
External_Function CMGetCommandString "CMGetCommandString" CMAX_DLL_NAME Integer wCmd Integer bDescription Pointer pszBuff Integer nBuffLen   Returns Integer
External_Function CMGetMacro "CMGetMacro" CMAX_DLL_NAME Integer nMacro Pointer pMacroBuff   Returns Integer
External_Function CMSetMacro "CMSetMacro" CMAX_DLL_NAME Integer nMacro Pointer pMacroBuff  Returns Integer

// 2.0
External_Function CMUnregisterAllLanguages "CMUnregisterAllLanguages" CMAX_DLL_NAME   Returns Integer
External_Function CMGetLanguageDef "CMGetLanguageDef" CMAX_DLL_NAME Pointer pszName Pointer pLang   Returns Integer
External_Function CMRegisterCommandInt "CMRegisterCommand" CMAX_DLL_NAME Integer wCmd Pointer pszName Pointer pszDesc   Returns Integer
Procedure CMRegisterCommand Global Integer iCmd String sName String sDesc
    Integer iRet
    Pointer pName pDesc
    Append sName (Character(0))
    Append sDesc (Character(0))
    GetAddress Of sName to pName
    GetAddress Of sDesc to pDesc
    Move (CMRegisterCommandInt(iCmd,pName,pDesc)) to iRet
    Procedure_Return iRet
End_Procedure

    // Allows to declare a USerdefined Command which can be accesed
    // in the codemax control.
#COMMAND CMDeclareCommand R R R R
    Define !1 FOR ( CMD_USER_BASE + !2 )
    Send CMRegisterCommand ( CMD_USER_BASE + !2 )  !3 !4
#ENDCOMMAND

    // Allows to declare a USerdefined Command which can be accesed
    // in the codemax control.


//EXTERN_C CME_CODE CMUnregisterCommand( WORD wCmd );
External_Function CMUnregisterCommand "CMUnregisterCommand" CMAX_DLL_NAME Integer wCmd   Returns Integer



///////////////////////////////////////////////////////////////////
//
// Message crackers for all CM_xxxx messages
//
//

#COMMAND Local_BUFFER_CPY R R R R
    Local_BUFFER !1 !2 !3_SIZE
    Move (CopyMemory(!2,!4,!3_SIZE))    to !2
#ENDCOMMAND

    // Possible values for piFindWrapMode
Define FindWrapMode_NoWrap      FOR 1
Define FindWrapMode_NoWrapMsg   FOR 2
Define FindWrapMode_WrapSilent  FOR 3
Define FindWrapMode_WrapAsk     FOR 4

Set_Argument_Size 200000
