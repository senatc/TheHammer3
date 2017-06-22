
Use DFAllent
Use mStrConv.pkg
Use mPointer.pkg


Define CS_CR   for (Character(13))
Define CS_CRLF For (Character(13)+character(10))
Define CS_LF   for (Character(10))


Define CMAX_DLL_NAME FOR SCILEXER.DLL


Define NM_SETFOCUS              FOR -7
Define NM_KILLFOCUS             FOR -8

Define WM_CONTEXTMENU           For |CI$007B // 0x007B
Define WM_RBUTTONUP             For |CI$0205 // 0x0205

#IFNDEF GET_CREATEWINDOWEX
  External_Function CreateWindowEx     'CreateWindowExA'      User32.dll  Dword e Pointer c Pointer v Dword w Dword x Dword y Dword wi Dword he Handle hP Handle hm Handle hi Pointer cs Returns Handle
#ENDIF
External_Function GetObject          'GetObjectA'           Gdi32.dll   Handle hGdi Integer iSize Pointer pBuff Returns Integer
#IFNDEF GET_CREATEFONTINDIRECT
  External_Function CreateFontIndirect 'CreateFontIndirectA'  Gdi32.dll   Pointer pLogfont Returns Integer
#ENDIF
External_Function LockWindowUpdate   'LockWindowUpdate'     USer32.dll  Handle hwnd Returns Integer
#IFNDEF GET_REDRAWWINDOW
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


//  Basic signed type used throughout interface
// typedef int Sci_Position;
Define Sci_Position for Integer

//  Unsigned variant used for ILexer::Lex and ILexer::Fold
// typedef unsigned int Sci_PositionU;
Define Sci_PositionU for UInteger

// In a future release the type Sci_PositionCR will be redefined to be 64-bits when Scintilla is built for 64-bits on all platforms.
//
// typedef long Sci_PositionCR;
Define Sci_PositionCR for UInteger


//
//  Struct Sci_NotifyHeader {
//  	/* Compatible with Windows NMHDR.
//  	 * hwndFrom is really an environment specific window handle or pointer
//  	 * but most clients of Scintilla.h do not have this type visible. */
//  	void *hwndFrom;
//  	uptr_t idFrom;
//  	unsigned int code;
//  };
Struct tSci_NotifyHeader
  Pointer  hwndFrom
  Pointer  idFrom
  UInteger uCode
End_Struct
//
//  Struct SCNotification {
//  	Sci_NotifyHeader nmhdr;
//  	Sci_Position position;
//  	/* SCN_STYLENEEDED, SCN_DOUBLECLICK, SCN_MODIFIED, SCN_MARGINCLICK, */
//  	/* SCN_NEEDSHOWN, SCN_DWELLSTART, SCN_DWELLEND, SCN_CALLTIPCLICK, */
//  	/* SCN_HOTSPOTCLICK, SCN_HOTSPOTDOUBLECLICK, SCN_HOTSPOTRELEASECLICK, */
//  	/* SCN_INDICATORCLICK, SCN_INDICATORRELEASE, */
//  	/* SCN_USERLISTSELECTION, SCN_AUTOCSELECTION */
//
//  	int ch;
//  	/* SCN_CHARADDED, SCN_KEY, SCN_AUTOCCOMPLETED, SCN_AUTOCSELECTION, */
//  	/* SCN_USERLISTSELECTION */
//  	int modifiers;
//  	/* SCN_KEY, SCN_DOUBLECLICK, SCN_HOTSPOTCLICK, SCN_HOTSPOTDOUBLECLICK, */
//  	/* SCN_HOTSPOTRELEASECLICK, SCN_INDICATORCLICK, SCN_INDICATORRELEASE, */
//
//  	int modificationType;	/* SCN_MODIFIED */
//  	const Char *text;
//  	/* SCN_MODIFIED, SCN_USERLISTSELECTION, SCN_AUTOCSELECTION, SCN_URIDROPPED */
//
//  	Sci_Position length;		/* SCN_MODIFIED */
//  	Sci_Position linesAdded;	/* SCN_MODIFIED */
//  	int message;	/* SCN_MACRORECORD */
//  	uptr_t wParam;	/* SCN_MACRORECORD */
//  	sptr_t lParam;	/* SCN_MACRORECORD */
//  	Sci_Position line;		/* SCN_MODIFIED */
//  	int foldLevelNow;	/* SCN_MODIFIED */
//  	int foldLevelPrev;	/* SCN_MODIFIED */
//  	int margin;		/* SCN_MARGINCLICK */
//  	int listType;	/* SCN_USERLISTSELECTION */
//  	int x;			/* SCN_DWELLSTART, SCN_DWELLEND */
//  	int y;		/* SCN_DWELLSTART, SCN_DWELLEND */
//  	int token;		/* SCN_MODIFIED with SC_MOD_CONTAINER */
//  	Sci_Position annotationLinesAdded;	/* SCN_MODIFIED with SC_MOD_CHANGEANNOTATION */
//  	int updated;	/* SCN_UPDATEUI */
//  	int listCompletionMethod;
//  	/* SCN_AUTOCSELECTION, SCN_AUTOCCOMPLETED, SCN_USERLISTSELECTION, */
//  };
Struct tSCNotification
  tSci_NotifyHeader nmhdr
  Sci_Position      position
  Integer           ch
  Integer           modifiers
  Integer           modificationType
  Address           Text
  Sci_Position      length
  Sci_Position      linesAdded
  Integer           message
  Pointer           wParam
  Pointer           lParam
  Sci_Position      line
  Integer           foldLevelNow
  Integer           foldLevelPrev
  Integer           margin
  Integer           listType
  Integer           x
  Integer           y
  Integer           token
  Sci_Position      annotationLinesAdded
  Integer           updated
  Integer           listCompletionMethod
End_Struct
//
//
//
//


//
//struct Sci_CharacterRange {
//    Sci_PositionCR cpMin;
//    Sci_PositionCR cpMax;
//};
Struct Sci_CharacterRange
  Sci_PositionCR cpMin
  Sci_PositionCR cpMax
End_Struct
//
//struct Sci_TextRange {
//    struct Sci_CharacterRange chrg;
//    char *lpstrText;
//};
Struct Sci_TextRange
  Sci_CharacterRange chrg
  Pointer lpstrText
End_Struct

//
//struct Sci_TextToFind {
//    struct Sci_CharacterRange chrg;     // range to search
//    const char *lpstrText;                // the search pattern (zero terminated)
//    struct Sci_CharacterRange chrgText; // returned as position of matching text
//};
Struct Sci_TextToFind
  Sci_CharacterRange chrg
  Pointer            pszText
  Sci_CharacterRange chrgText
End_Struct
//
//    // Windows Standard type: fuer WM_Notify
//TYPE NMHDR
//    Field NMHDR.hwndFrom             as Handle    //TYPE: HWND
//    Field NMHDR.idFrom               as Integer   //TYPE: UINT
//    Field NMHDR.code                 as Integer   //TYPE: UINT
//END_TYPE








Define LF_FACESIZE          FOR 32
Define CODEMAXWNDCLASS      FOR "Scintilla" //"CodeSense" //"CodeMax"

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
// Messages - CMM_xxxxxx
// As long as they are listed then they have not yet been migrated to scintilla
// If commented out then it means not in scintilla or it simply works so much different that I have not
// made up my mind on how-to implement or migrate.
//
Define CMM_SETLANGUAGE                FOR ( WM_USER + 1600 )
Define CMM_GETLANGUAGE                FOR ( WM_USER + 1601 )
//Define CMM_ENABLECOLORSYNTAX          FOR ( WM_USER + 1610 )
//Define CMM_ISCOLORSYNTAXENABLED       FOR ( WM_USER + 1620 )
//Define CMM_SETCOLORS                  FOR ( WM_USER + 1630 )
//Define CMM_GETCOLORS                  FOR ( WM_USER + 1640 )
Define CMM_ENABLEWHITESPACEDISPLAY    FOR ( WM_USER + 1800 )
Define CMM_ISWHITESPACEDISPLAYENABLED FOR ( WM_USER + 1810 )
Define CMM_ENABLETABEXPAND            FOR ( WM_USER + 1811 )
Define CMM_ISTABEXPANDENABLED         FOR ( WM_USER + 1812 )
//Define CMM_ENABLESMOOTHSCROLLING      FOR ( WM_USER + 1820 )
//Define CMM_ISSMOOTHSCROLLINGENABLED   FOR ( WM_USER + 1830 )
//Define CMM_ENABLELINETOOLTIPS         FOR ( WM_USER + 1860 )
//Define CMM_ISLINETOOLTIPSENABLED      FOR ( WM_USER + 1870 )
Define CMM_ENABLELEFTMARGIN           FOR ( WM_USER + 1880 )
Define CMM_ISLEFTMARGINENABLED        FOR ( WM_USER + 1890 )
Define CMM_ENABLECOLUMNSEL            FOR ( WM_USER + 1891 )
Define CMM_ISCOLUMNSELENABLED         FOR ( WM_USER + 1892 )
Define CMM_ENABLEDRAGDROP             FOR ( WM_USER + 1893 )
Define CMM_ISDRAGDROPENABLED          FOR ( WM_USER + 1894 )
//Define CMM_SETTOPINDEX                FOR ( WM_USER + 1960 )
//Define CMM_GETTOPINDEX                FOR ( WM_USER + 1970 )
Define CMM_GETVISIBLELINECOUNT        FOR ( WM_USER + 1980 )
Define CMM_HITTEST                    FOR ( WM_USER + 1990 )
Define CMM_INSERTFILE                 FOR ( WM_USER + 2320 )
Define CMM_INSERTTEXT                 FOR ( WM_USER + 2330 )
Define CMM_REPLACETEXT                FOR ( WM_USER + 2340 )
Define CMM_GETWORDLENGTH              FOR ( WM_USER + 2382 )
Define CMM_GETSEL                     FOR ( WM_USER + 2420 )
Define CMM_GETSELFROMPOINT            FOR ( WM_USER + 2425 )
Define CMM_SETSEL                     FOR ( WM_USER + 2430 )
Define CMM_DELETESEL                  FOR ( WM_USER + 2440 )
Define CMM_REPLACESEL                 FOR ( WM_USER + 2450 )
Define CMM_SETMODIFIED                FOR ( WM_USER + 2461 )
Define CMM_ENABLECRLF                 FOR ( WM_USER + 2470 )
Define CMM_ISCRLFENABLED              FOR ( WM_USER + 2480 )
//Define CMM_SETFONTOWNERSHIP           FOR ( WM_USER + 2485 )
//Define CMM_GETFONTOWNERSHIP           FOR ( WM_USER + 2486 )
Define CMM_EXECUTECMD                 FOR ( WM_USER + 2700 )
//Define CMM_SETSPLITTERPOS             FOR ( WM_USER + 2900 )
//Define CMM_GETSPLITTERPOS             FOR ( WM_USER + 2901 )
Define CMM_GETVIEWCOUNT               FOR ( WM_USER + 3600 )
Define CMM_GETCURRENTVIEW             FOR ( WM_USER + 3610 )
//Define CMM_ENABLESPLITTER             FOR ( WM_USER + 3720 )
//Define CMM_ISSPLITTERENABLED          FOR ( WM_USER + 3730 )
Define CMM_ISRECORDINGMACRO           FOR ( WM_USER + 3731 )
Define CMM_ISPLAYINGMACRO             FOR ( WM_USER + 3732 )
Define CMM_ENABLEGLOBALPROPS          FOR ( WM_USER + 3740 )
Define CMM_ISGLOBALPROPSENABLED       FOR ( WM_USER + 3741 )
Define CMM_SETDLGPARENT               FOR ( WM_USER + 3750 )

// 2.0
Define CMM_ENABLESELBOUNDS            FOR ( WM_USER + 3760 )
Define CMM_ISSELBOUNDSENABLED         FOR ( WM_USER + 3770 )
//Define CMM_SETFONTSTYLES              FOR ( WM_USER + 3780 )
//Define CMM_GETFONTSTYLES              FOR ( WM_USER + 3790 )
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
Define CMM_POSFROMCHAR                FOR ( WM_USER + 3920 )
Define CMM_ENABLEHIDESEL              FOR ( WM_USER + 3930 )
Define CMM_ISHIDESELENABLED           FOR ( WM_USER + 3940 )
Define CMM_ENABLENORMALIZECASE        FOR ( WM_USER + 3970 )
Define CMM_ISNORMALIZECASEENABLED     FOR ( WM_USER + 3980 )
Define CMM_SETDIVIDER                 FOR ( WM_USER + 3990 )
Define CMM_GETDIVIDER                 FOR ( WM_USER + 4000 )
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

Define CMM_GETCURRENTTOKEN            FOR ( WM_USER + 5000 )
Define CMM_UPDATECONTROLPOSITIONS     FOR ( WM_USER + 5010 )



// Extentions for Oem/Ansi support
Define CMM_ENABLEOEMCODE              FOR ( WM_USER + 4300 )
Define CMM_ISOEMCODEENABLED           FOR ( WM_USER + 4301 )

///////////////////////////////////////////////////////////////
////
//// Notifications
////
////
//Define CMN_CHANGE                    FOR 100      // buffer contents changed
//Define CMN_HSCROLL                   FOR 110      // horizontal scrollbar pos changed
//Define CMN_VSCROLL                   FOR  120      // vertical scrollbar pos changed
//Define CMN_SELCHANGE                 FOR  130      // active selection has changed
//Define CMN_VIEWCHANGE                FOR  140      // the user switched to a different splitter view
//Define CMN_MODIFIEDCHANGE            FOR  150      // the modified state of the buffer has changed
//Define CMN_SHOWPROPS                 FOR  160      // the user is about to show the props window
//Define CMN_PROPSCHANGE               FOR  170      // the user changed properties via the props window
//Define CMN_CREATE                    FOR  180      // the control has been created
//Define CMN_DESTROY                   FOR  190      // the control is about to be destroyed
//
//// 2.0
//Define CMN_DRAWLINE                  FOR 200      // owner-draw functionality
//Define CMN_DELETELINE                FOR 210      // line is about to be deleted
//Define CMN_CMDFAILURE                FOR 220      // a keystroke command failed to successfully complete
//Define CMN_REGISTEREDCMD             FOR 230      // a registered command has been invoked by the user
//Define CMN_KEYDOWN                   FOR 240      // a key was pressed (WM_KEYDOWN)
//Define CMN_KEYUP                     FOR 250      // a key was released (WM_KEYUP)
//Define CMN_KEYPRESS                  FOR 260      // a key was pressed and released (WM_CHAR)
//Define CMN_MOUSEDOWN                 FOR 270      // a mouse button was pressed (WM_xBUTTONDOWN)
//Define CMN_MOUSEUP                   FOR 280      // a mouse button was released (WM_xBUTTONUP)
//Define CMN_MOUSEMOVE                 FOR 290      // the mouse pointer was moved (WM_MOUSEMOVE)
//Define CMN_OVERTYPECHANGE            FOR 300      // the overtype mode has changed
//
//// 2.1
//Define CMN_FINDWRAPPED               FOR 310      // a find operation wrapped to start/end of buffer
//
//// SVN
//Define CMN_CODELIST                  FOR 320      // user has activated CodeList control
//Define CMN_CODELISTSELMADE           FOR 330      // user has selected an item in CodeList control
//Define CMN_CODELISTCANCEL            FOR 340      // user cancelled CodeList control
//Define CMN_CODELISTCHAR              FOR 350      // CodeList control received a WM_CHAR message
//Define CMN_CODETIP                   FOR 360      // user has activated CodeTip control
//Define CMN_CODETIPINITIALIZE         FOR 365      // application should initialize CodeTip control
//Define CMN_CODETIPCANCEL             FOR 370      // user cancelled CodeTip control
//Define CMN_CODETIPUPDATE             FOR 380      // the CodeTip control is about to be updated
//Define CMN_CODELISTSELWORD           FOR 390      // the CodeList control is about to select new item
//Define CMN_CODELISTSELCHANGE         FOR 400      // the CodeList selection has changed
//Define CMN_CODELISTHOTTRACK          FOR 410      // the mouse hot-tracking selection has changed
//


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

//// language styles
//Define CMLS_PROCEDURAL    FOR 0
//Define CMLS_SGML          FOR 1
//
//
//TYPE CM_LANGUAGE
//    Field CM_LANGUAGE.dwStyle                             as Dword    // One of the CMLS_ values DWORD
//    Field CM_LANGUAGE.bIsCaseSensitive                    as Integer  // TRUE if keywords are case sensitive BOOL
//    Field CM_LANGUAGE.pszKeywords                         as Pointer  // The keywords delimited by '\n' LPCTSTR
//    Field CM_LANGUAGE.pszOperators                        as Pointer  // The operators delimited by '\n' LPCTSTR
//    Field CM_LANGUAGE.pszSingleLineComments               as Pointer  // The single line comment tokens (e.g. "//") LPCTSTR
//    Field CM_LANGUAGE.pszMultiLineComments1               as Pointer  // The multiline comment start tokens (e.g. "/*\n{\n(*") LPCTSTR
//    Field CM_LANGUAGE.pszMultiLineComments2               as Pointer  // The multiline comment end tokens (e.g. "*/\n}\n*)") LPCTSTR
//    Field CM_LANGUAGE.pszScopeKeywords1                   as Pointer  // The scoping start tokens (e.g. "{\nbegin") LPCTSTR
//    Field CM_LANGUAGE.pszScopeKeywords2                   as Pointer  // The multiline comment end tokens (e.g. "}\nend") LPCTSTR
//    Field CM_LANGUAGE.pszStringDelims                     as Pointer  // The string literal delimiters (e.g. "\"\n'") -- also includes character literals LPCTSTR
//    Field CM_LANGUAGE.chEscape                            as Char 1   // The escape character TCHAR
//    Field CM_LANGUAGE.chTerminator                        as Char 1   // The statement terminator char (usually ';') TCHAR
//    Field CM_LANGUAGE.pszTagElementNames                  as Pointer  // Tag-based element names delimited by '\n' LPCTSTR
//    Field CM_LANGUAGE.pszTagAttributeNames                as Pointer  // Tag-based attribute names delimited by '\n' LPCTSTR
//    Field CM_LANGUAGE.pszTagEntities                      as Pointer  // Tag-based entities delimited by '\n' LPCTSTR
//END_TYPE
//
//// Color settings for CMM_GETCOLORS and CMM_SETCOLORS
////
//// Note:  Use CLR_INVALID on background colors to specify transparent
////        (text) or appropriate control panel setting
//TYPE CM_COLORS
//    Field CM_COLORS.crWindow                            as COLORREF // window background color
//    Field CM_COLORS.crLeftMargin                        as COLORREF // left margin background color
//    Field CM_COLORS.crBookmark                          as COLORREF // bookmark foreground color
//    Field CM_COLORS.crBookmarkBk                        as COLORREF // bookmark background color
//    Field CM_COLORS.crText                              as COLORREF // plain text foreground color
//    Field CM_COLORS.crTextBk                            as COLORREF // plain text background color
//    Field CM_COLORS.crNumber                            as COLORREF // numeric literal foreground color
//    Field CM_COLORS.crNumberBk                          as COLORREF // numeric literal background color
//    Field CM_COLORS.crKeyword                           as COLORREF // keyword foreground color
//    Field CM_COLORS.crKeywordBk                         as COLORREF // keyword background color
//    Field CM_COLORS.crOperator                          as COLORREF // operator foreground color
//    Field CM_COLORS.crOperatorBk                        as COLORREF // operator background color
//    Field CM_COLORS.crScopeKeyword                      as COLORREF // scope keyword foreground color
//    Field CM_COLORS.crScopeKeywordBk                    as COLORREF // scope keyword background color
//    Field CM_COLORS.crComment                           as COLORREF // comment foreground color
//    Field CM_COLORS.crCommentBk                         as COLORREF // comment background color
//    Field CM_COLORS.crString                            as COLORREF // string foreground color
//    Field CM_COLORS.crStringBk                          as COLORREF // string background color
//    Field CM_COLORS.crTagText                           as COLORREF // plain tag text foreground color
//    Field CM_COLORS.crTagTextBk                         as COLORREF // plain tag text background color
//    Field CM_COLORS.crTagEntity                         as COLORREF // tag entity foreground color
//    Field CM_COLORS.crTagEntityBk                       as COLORREF // tag entity background color
//    Field CM_COLORS.crTagElementName                    as COLORREF // tag element name foreground color
//    Field CM_COLORS.crTagElementNameBk                  as COLORREF // tag element name background color
//    Field CM_COLORS.crTagAttributeName                  as COLORREF // tag attribute name foreground color
//    Field CM_COLORS.crTagAttributeNameBk                as COLORREF // tag attribute name background color
//    Field CM_COLORS.crLineNumber                        as COLORREF // line number foreground color
//    Field CM_COLORS.crLineNumberBk                      as COLORREF // line number background color
//    Field CM_COLORS.crHDividerLines                     as COLORREF // line number separate line color
//    Field CM_COLORS.crVDividerLines                     as COLORREF // left margin separate line color
//    Field CM_COLORS.crHighlightedLine                   as COLORREF // highlighted line color
//END_TYPE
//
//
///////////////////////////////////////////////////////////////
////
//// Font style settings for CMM_GETFONTSTYLES and CMM_SETFONTSTYLES
//// each byte value is one of the CM_FONT_XXX values listed below
//// this declaration
////
//TYPE CM_FONTSTYLES
//    Field CM_FONTSTYLES.byText                              as Char 1   // plain text font style BYTE
//    Field CM_FONTSTYLES.byNumber                            as Char 1   // numeric literal font style BYTE
//    Field CM_FONTSTYLES.byKeyword                           as Char 1   // keyword font style BYTE
//    Field CM_FONTSTYLES.byOperator                          as Char 1   // operator font style BYTE
//    Field CM_FONTSTYLES.byScopeKeyword                      as Char 1   // scope keyword font style BYTE
//    Field CM_FONTSTYLES.byComment                           as Char 1   // comment font style BYTE
//    Field CM_FONTSTYLES.byString                            as Char 1   // string font style BYTE
//    Field CM_FONTSTYLES.byTagText                           as Char 1   // plain tag text font style BYTE
//    Field CM_FONTSTYLES.byTagEntity                         as Char 1   // tag entity font style BYTE
//    Field CM_FONTSTYLES.byTagElementName                    as Char 1   // tag element name font style BYTE
//    Field CM_FONTSTYLES.byTagAttributeName                  as Char 1   // tag attribute name font style BYTE
//    Field CM_FONTSTYLES.byLineNumber                        as Char 1   // line number font style BYTE
//END_TYPE
//
///////////////////////////////////////////////////////////////
////
//// Font style options used in CM_FONTSTYLES
////
////
//Define CM_FONT_NORMAL     FOR 0   // normal weight
//Define CM_FONT_BOLD       FOR 1   // bold weight
//Define CM_FONT_ITALIC     FOR 2   // normal weight, italic
//Define CM_FONT_BOLDITALIC FOR 3   // bold weight, italic
//Define CM_FONT_UNDERLINE  FOR 4   // normal weight, underline
//
///////////////////////////////////////////////////////////////
////
// AutoIndent options
//
//
Define CM_INDENT_OFF        for  0    // auto-indent off -- new line begins at column 0
Define CM_INDENT_SCOPE      for  1    // NOT SUPPORTED
Define CM_INDENT_PREVLINE   for  2    // new line has identical indentation of previous line
//
///////////////////////////////////////////////////////////////
////
//// Print option flags used with CMM_PRINT
////
////
//Define CM_PRINT_PROMPTDLG    FOR |CI$000   // display the print common dialog
//Define CM_PRINT_DEFAULTPRN   FOR |CI$001   // use default printer (no print dialog displayed)
//Define CM_PRINT_HDC          FOR |CI$002   // use HDC provided
//Define CM_PRINT_RICHFONTS    FOR |CI$004   // use bold, italics, underline, etc. when appropriate
//Define CM_PRINT_COLOR        FOR |CI$008   // print in color
//Define CM_PRINT_PAGENUMS     FOR |CI$010   // print 'page # of #' at the bottom of the page
//Define CM_PRINT_DATETIME     FOR |CI$020   // print date and time at top of the page
//Define CM_PRINT_BORDERTHIN   FOR |CI$040   // surround text with a thin border
//Define CM_PRINT_BORDERTHICK  FOR |CI$080   // surround text with a thick border
//Define CM_PRINT_BORDERDOUBLE FOR |CI$100   // surround text with two thin borders
//Define CM_PRINT_SELECTION    FOR |CI$200   // print the selection rather than entire edit contents
//
///////////////////////////////////////////////////////////////
////
//// Border option flags used with CMM_GETBORDERSTYLE and CMM_SETBORDERSTYLE.
//// Note: this values may be or'd together to achieve different effects.
////
//Define CM_BORDER_NONE        FOR |CI$0  // no border
//Define CM_BORDER_THIN        FOR |CI$1  // 1-pixel border
//Define CM_BORDER_CLIENT      FOR |CI$2  // client edge (WS_EX_CLIENTEDGE)
//Define CM_BORDER_STATIC      FOR |CI$4  // static edge (WS_EX_STATICEDGE)
//Define CM_BORDER_MODAL       FOR |CI$8  // modal edge (WS_EX_DLGMODALFRAME)
//Define CM_BORDER_CORRAL      FOR (CM_BORDER_MODAL Ior CM_BORDER_CLIENT)
//
//
///////////////////////////////////////////////////////////////
////
//// Text position indicators
////
////
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
//
//
//    // Erzeugt einen String und eine Pointer variable, wenn diese noch nicht definiert sind!
//    // Fueltt mit Line und Col und holt die Addresse in the Pointer
//
//TYPE CM_RANGE
//    Field CM_RANGE.posStart             as Char CM_POSITION_SIZE    // the anchor CM_POSITION
//    Field CM_RANGE.posEnd               as Char CM_POSITION_SIZE    // the extension (if same as anchor, selection is empty) CM_POSITION
//    Field CM_RANGE.bColumnSel           as Integer                  // TRUE if is a column selection, FALSE if paragragh selection BOOL
//END_TYPE
//
//#COMMAND Local_CM_RANGE R R "START=" R  R "END=" R R
//    DEFINE_STR_PTR !1 !2
//    Zerotype CM_RANGE   to !1
//
//    Local_CM_POSITION sPosStart psPosStart LINE= !4 COL= !5   // Create a String with the StartPosition
//    Local_CM_POSITION sPosEnd   psPosEnd   LINE= !7 COL= !8   // Create a String with the EndPosition
//
//    PUT_STRING sPosStart to !1 AT CM_RANGE.posStart           // Set Start Position
//    PUT_STRING sPosEnd   to !1 AT CM_RANGE.posEnd             // Set End Position
//
//    GetAddress Of !1     to !2                                // Get the Address of the created Structure
//#ENDCOMMAND


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

///////////////////////////////////////////////////////////////
////
//// CMN_DRAWLINE notification data passed to parent window
////
////
//TYPE CM_DRAWLINEDATA
//    Field CM_DRAWLINEDATA.hdr                  as Char NMHDR_SIZE   // standard notification data NMHDR
//    Field CM_DRAWLINEDATA.hDC                  as Pointer           // device context to draw with, clipped to current paint area HDC
//    Field CM_DRAWLINEDATA.rcLine.Left          as Dword             // Expand the tRectStructure to ist elements.
//    Field CM_DRAWLINEDATA.rcLine.top           as Dword
//    Field CM_DRAWLINEDATA.rcLine.Right         as Dword
//    Field CM_DRAWLINEDATA.rcLine.bottom        as Dword
//    Field CM_DRAWLINEDATA.nLine                as Integer           // line number to draw int
//    Field CM_DRAWLINEDATA.nLeftCol             as Integer           // leftmost visible col int
//    Field CM_DRAWLINEDATA.nRightCol            as Integer           // rightmost visible col int
//    Field CM_DRAWLINEDATA.lParam               as Pointer           // itemdata associated with the line (CMM_SETITEMDATA) LPARAM
//    Field CM_DRAWLINEDATA.dwStyle              as Pointer           // line style bits (CML_XXX) DWORD
//END_TYPE

///////////////////////////////////////////////////////////////
////
//// CMN_DELETELINE notification data passed to parent window
////
////
//TYPE CM_DELETELINEDATA
//    Field CM_DELETELINEDATA.hdr                  as Char NMHDR_SIZE  // standard notification data NMHDR
//    Field CM_DELETELINEDATA.nLine                as Integer          // line that is about to be deleted int
//    Field CM_DELETELINEDATA.lParam               as Pointer          // itemdata associated with the line (CMM_SETITEMDATA) LPARAM
//END_TYPE
//
///////////////////////////////////////////////////////////////
////
//// CMN_CMDFAILURE notification data passed to parent window
////
////
//TYPE CM_CMDFAILUREDATA
//    Field CM_CMDFAILUREDATA.hdr                  as Char NMHDR_SIZE // standard notification data NMHDR
//    Field CM_CMDFAILUREDATA.wCmd                 as WORD            // CMD_XXX command that failed WORD
//    Field CM_CMDFAILUREDATA.dwErr                as Dword           // CMDERR_XXX failure code DWORD
//END_TYPE


///////////////////////////////////////////////////////////////
////
//// CMN_REGISTEREDCMD notification data passed to parent window
////
////
//TYPE CM_REGISTEREDCMDDATA
//    Field CM_REGISTEREDCMDDATA.hdr                  as Char NMHDR_SIZE  // standard notification data NMHDR
//    Field CM_REGISTEREDCMDDATA.wCmd                 as WORD             // registered command to be executed WORD
//END_TYPE
///////////////////////////////////////////////////////////////
////
//// CMN_KEYDOWN, CMN_KEYUP, CMN_KEYPRESS notification
//// data passed to parent window
////
////
Define CM_KEY_NOEXT      FOR |CI$0
Define CM_KEY_SHIFT      FOR |CI$1
Define CM_KEY_CTRL       FOR |CI$2
Define CM_KEY_ALT        FOR |CI$4
//TYPE CM_KEYDATA
//    Field CM_KEYDATA.hdr                  as Char NMHDR_SIZE    // standard notification data NMHDR
//    Field CM_KEYDATA.nKeyCode             as Integer            // virtkey if CMN_KEYUP or CMN_KEYDOWN.  Ascii code if CMN_KEYPRESS int
//    Field CM_KEYDATA.nKeyModifier         as Integer            // bitfield of: CM_KEY_SHIFT, CM_KEY_CTRL, and/or CM_KEY_ALT int
//END_TYPE

    // Just converts the ID to the name.
Function CMKeymodifierIDToName Global Integer iModifier Returns String
    String sRet
    If (iModifier Iand CM_KEY_SHIFT) Append sRet (If(sRet Eq "","","+")) "Shift"
    If (iModifier Iand CM_KEY_CTRL)  Append sRet (If(sRet Eq "","","+")) "Ctrl"
    If (iModifier Iand CM_KEY_ALT)   Append sRet (If(sRet Eq "","","+")) "Alt"
    Function_Return sRet
End_Function

///////////////////////////////////////////////////////////////
////
//// CMN_MOUSEDOWN, CMN_MOUSEUP, CMN_MOUSEPRESS notification
//// data passed to parent window
////
////
//Define CM_BTN_LEFT      FOR |CI$1
//Define CM_BTN_RIGHT     FOR |CI$2
//Define CM_BTN_MIDDLE    FOR |CI$4
//
//TYPE CM_MOUSEDATA
//    Field CM_MOUSEDATA.hdr                  as Char NMHDR_SIZE  // standard notification data NMHDR
//    Field CM_MOUSEDATA.pt                   as Char tPOINT_SIZE // position of mouse (client coordinates) POINT
//    Field CM_MOUSEDATA.nButton              as Integer  // bitfield of: CM_BTN_LEFT, CM_BTN_RIGHT, and/or CM_BTN_MIDDLE int
//    Field CM_MOUSEDATA.nKeyModifier         as Integer  // bitfield of: CM_KEY_SHIFT, CM_KEY_CTRL, and/or CM_KEY_ALT int
//END_TYPE
//
///////////////////////////////////////////////////////////////
////
//// CMN_FINDWRAPPED notification data passed to parent window
////
////
//TYPE CM_FINDWRAPPEDDATA
//    Field CM_FINDWRAPPEDDATA.hdr                  as Char NMHDR_SIZE // standard notification data NMHDR
//    Field CM_FINDWRAPPEDDATA.wCmd                 as WORD     // the command being executed WORD
//    Field CM_FINDWRAPPEDDATA.bForward             as Integer  // TRUE if wrapped while searching forward, FALSE if searching backward BOOL
//END_TYPE

// START - SVN
// -----------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
////
//// CMN_CODELIST, CMN_CODELISTSELMADE, CMN_CODELISTCANCEL
//// notification data passed to parent window
////
//TYPE CM_CODELISTDATA
//    Field CM_CODELISTDATA.hdr              as Char NMHDR_SIZE   // standard notification data (NMHDR)
//    Field CM_CODELISTDATA.hListCtrl        as Handle   // handle to list view control window (HWND)
//END_TYPE
//
///////////////////////////////////////////////////////////////
////
//// CMN_CODELISTCHAR notification data passed to parent
//// window
////
//
//// BP Codelist support
//
//TYPE CM_CODELISTKEYDATA
//    Field CM_CODELISTKEYDATA.clData.hDr         as Char NMHDR_SIZE
//    Field CM_CODELISTKEYDATA.clData.hListCtrl   as Handle
//    Field CM_CODELISTKEYDATA.wChar              as Integer
//    Field CM_CODELISTKEYDATA.lKeyData           as Integer
//END_TYPE
//
//
///////////////////////////////////////////////////////////////
////
//// CMN_CODELISTSELWORD notification data passed to parent
//// window
////
////typedef struct _CM_CODELISTSELWORDDATA
////{
////	CM_CODELISTDATA		clData;
////	int					iItem;		// list item about to be selected
////
////} CM_CODELISTSELWORDDATA, *LPCM_CODELISTSELWORDDATA;
//
//
///////////////////////////////////////////////////////////////
////
//// CMN_CODELISTSELCHANGE notification data passed to parent
//// window
////
////typedef struct _CM_CODELISTSELCHANGEDATA
////{
////	CM_CODELISTDATA		clData;
////	int					iItem;
////	LPTSTR				pszText;
////	TCHAR				szText[CM_MAX_CODELIST_TIP];
////	HINSTANCE			hInstance;
////
////} CM_CODELISTSELCHANGEDATA, *LPCM_CODELISTSELCHANGEDATA;
//
//
///////////////////////////////////////////////////////////////
////
//// CMN_CODELISTHOTTRACK notification data passed to parent
//// window
////
////typedef struct _CM_CODELISTHOTTRACKDATA
////{
////	CM_CODELISTDATA		clData;
////	int					iItem;		// index of the list item that is "hot"
////
////} CM_CODELISTHOTTRACKDATA, *LPCM_CODELISTHOTTRACKDATA;
//
//
///////////////////////////////////////////////////////////////
////
//// CMN_CODETIPCANCEL, CMN_CODETIPINITIALIZE,
//// CMN_CODETIPUPDATE notification data passed to parent
//// window
////
//
//
//
///////////////////////////////////////////////////////////////
////
//// Tooltip window styles specified as return value from
//// CMN_CODETIP notifications
////
//Define CM_TIPSTYLE_NONE				    for 0	// don't display a tooltip
//Define CM_TIPSTYLE_NORMAL				  for 1	// standard tooltip window
//Define CM_TIPSTYLE_HIGHLIGHT			for 2	// tooltip with text highlighting
//Define CM_TIPSTYLE_FUNCHIGHLIGHT	for 3	// tooltip with function highlighting
//Define CM_TIPSTYLE_MULTIFUNC			for 4	// highlighting for multiple functions

Define C_TIPTYPE_UNDEFINED        for 0
Define C_TIPTYPE_EXPRESSION       for 1
Define C_TIPTYPE_FUNCTION         for 2
Define C_TIPTYPE_PROCEDURE        for 3
//
//
//// -----------------------------------------------------------------------------------------
//// END - SVN
//

/////////////////////////////////////////////////////////////
//
// data passed to CMM_SETLINENUMBERING
//
//
Define CM_BINARY            FOR 2  // not supported
Define CM_OCTAL             FOR 8  // not supported
Define CM_DECIMAL           FOR 10
Define CM_HEXADECIMAL       FOR 16 // not supported


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


// Note that the following defines come from the Scintilla.h file in the scintilla project
// These files are generated from the Scintilla.iface file, so we will have to compare that
// file every time!
Define INVALID_POSITION                        for -1
Define SCI_START                               for 2000
Define SCI_OPTIONAL_START                      for 3000
Define SCI_LEXER_START                         for 4000
Define SCI_ADDTEXT                             for 2001
Define SCI_ADDSTYLEDTEXT                       for 2002
Define SCI_INSERTTEXT                          for 2003
Define SCI_CHANGEINSERTION                     for 2672
Define SCI_CLEARALL                            for 2004
Define SCI_DELETERANGE                         for 2645
Define SCI_CLEARDOCUMENTSTYLE                  for 2005
Define SCI_GETLENGTH                           for 2006
Define SCI_GETCHARAT                           for 2007
Define SCI_GETCURRENTPOS                       for 2008
Define SCI_GETANCHOR                           for 2009
Define SCI_GETSTYLEAT                          for 2010
Define SCI_REDO                                for 2011
Define SCI_SETUNDOCOLLECTION                   for 2012
Define SCI_SELECTALL                           for 2013
Define SCI_SETSAVEPOINT                        for 2014
Define SCI_GETSTYLEDTEXT                       for 2015
Define SCI_CANREDO                             for 2016
Define SCI_MARKERLINEFROMHANDLE                for 2017
Define SCI_MARKERDELETEHANDLE                  for 2018
Define SCI_GETUNDOCOLLECTION                   for 2019
Define SCWS_INVISIBLE                          for 0
Define SCWS_VISIBLEALWAYS                      for 1
Define SCWS_VISIBLEAFTERINDENT                 for 2
Define SCWS_VISIBLEONLYININDENT                for 3
Define SCI_GETVIEWWS                           for 2020
Define SCI_SETVIEWWS                           for 2021
Define SCTD_LONGARROW                          for 0
Define SCTD_STRIKEOUT                          for 1
Define SCI_GETTABDRAWMODE                      for 2698
Define SCI_SETTABDRAWMODE                      for 2699
Define SCI_POSITIONFROMPOINT                   for 2022
Define SCI_POSITIONFROMPOINTCLOSE              for 2023
Define SCI_GOTOLINE                            for 2024
Define SCI_GOTOPOS                             for 2025
Define SCI_SETANCHOR                           for 2026
Define SCI_GETCURLINE                          for 2027
Define SCI_GETENDSTYLED                        for 2028
Define SC_EOL_CRLF                             for 0
Define SC_EOL_CR                               for 1
Define SC_EOL_LF                               for 2
Define SCI_CONVERTEOLS                         for 2029
Define SCI_GETEOLMODE                          for 2030
Define SCI_SETEOLMODE                          for 2031
Define SCI_STARTSTYLING                        for 2032
Define SCI_SETSTYLING                          for 2033
Define SCI_GETBUFFEREDDRAW                     for 2034
Define SCI_SETBUFFEREDDRAW                     for 2035
Define SCI_SETTABWIDTH                         for 2036
Define SCI_GETTABWIDTH                         for 2121
Define SCI_CLEARTABSTOPS                       for 2675
Define SCI_ADDTABSTOP                          for 2676
Define SCI_GETNEXTTABSTOP                      for 2677
Define SC_CP_UTF8                              for 65001
Define SCI_SETCODEPAGE                         for 2037
Define SC_IME_WINDOWED                         for 0
Define SC_IME_INLINE                           for 1
Define SCI_GETIMEINTERACTION                   for 2678
Define SCI_SETIMEINTERACTION                   for 2679
Define MARKER_MAX                              for 31
Define SC_MARK_CIRCLE                          for 0
Define SC_MARK_ROUNDRECT                       for 1
Define SC_MARK_ARROW                           for 2
Define SC_MARK_SMALLRECT                       for 3
Define SC_MARK_SHORTARROW                      for 4
Define SC_MARK_EMPTY                           for 5
Define SC_MARK_ARROWDOWN                       for 6
Define SC_MARK_MINUS                           for 7
Define SC_MARK_PLUS                            for 8
Define SC_MARK_VLINE                           for 9
Define SC_MARK_LCORNER                         for 10
Define SC_MARK_TCORNER                         for 11
Define SC_MARK_BOXPLUS                         for 12
Define SC_MARK_BOXPLUSCONNECTED                for 13
Define SC_MARK_BOXMINUS                        for 14
Define SC_MARK_BOXMINUSCONNECTED               for 15
Define SC_MARK_LCORNERCURVE                    for 16
Define SC_MARK_TCORNERCURVE                    for 17
Define SC_MARK_CIRCLEPLUS                      for 18
Define SC_MARK_CIRCLEPLUSCONNECTED             for 19
Define SC_MARK_CIRCLEMINUS                     for 20
Define SC_MARK_CIRCLEMINUSCONNECTED            for 21
Define SC_MARK_BACKGROUND                      for 22
Define SC_MARK_DOTDOTDOT                       for 23
Define SC_MARK_ARROWS                          for 24
Define SC_MARK_PIXMAP                          for 25
Define SC_MARK_FULLRECT                        for 26
Define SC_MARK_LEFTRECT                        for 27
Define SC_MARK_AVAILABLE                       for 28
Define SC_MARK_UNDERLINE                       for 29
Define SC_MARK_RGBAIMAGE                       for 30
Define SC_MARK_BOOKMARK                        for 31
Define SC_MARK_CHARACTER                       for 10000
Define SC_MARKNUM_LINEHIGHLIGHT                for 10
Define SC_MARKNUM_BOOKMARK                     for 11
Define SC_MARKNUM_CHANGEDLINE                  for 12
Define SC_MARKNUM_CHANGEDLINESAVED             for 13
Define SC_MARKNUM_FOLDEREND                    for 25
Define SC_MARKNUM_FOLDEROPENMID                for 26
Define SC_MARKNUM_FOLDERMIDTAIL                for 27
Define SC_MARKNUM_FOLDERTAIL                   for 28
Define SC_MARKNUM_FOLDERSUB                    for 29
Define SC_MARKNUM_FOLDER                       for 30
Define SC_MARKNUM_FOLDEROPEN                   for 31
Define SC_MASK_FOLDERS                         for |CI$FE000000 // 0xFE000000
Define SC_MASK_MARGIN                          for |CI$01000000 // 0x01000000 - allow symbol 24
Define SC_MASK_BOOKMARK                        for |CI$00000800 // 0x00000800 - allow symbol 11, start counting from right, each bit is 1, starting from symbol 0
Define SC_MASK_CHANGEDLINEUNSAVED              for |CI$00001000 // 0x00001000 - allow symbol 12 only
Define SC_MASK_CHANGEDLINE                     for |CI$00003000 // 0x00003000 - allow symbol 12 and 13
Define SCI_MARKERDEFINE                        for 2040
Define SCI_MARKERSETFORE                       for 2041
Define SCI_MARKERSETBACK                       for 2042
Define SCI_MARKERSETBACKSELECTED               for 2292
Define SCI_MARKERENABLEHIGHLIGHT               for 2293
Define SCI_MARKERADD                           for 2043
Define SCI_MARKERDELETE                        for 2044
Define SCI_MARKERDELETEALL                     for 2045
Define SCI_MARKERGET                           for 2046
Define SCI_MARKERNEXT                          for 2047
Define SCI_MARKERPREVIOUS                      for 2048
Define SCI_MARKERDEFINEPIXMAP                  for 2049
Define SCI_MARKERADDSET                        for 2466
Define SCI_MARKERSETALPHA                      for 2476
Define SC_MAX_MARGIN                           for 4
Define SC_MARGIN_SYMBOL                        for 0
Define SC_MARGIN_NUMBER                        for 1
Define SC_MARGIN_BACK                          for 2
Define SC_MARGIN_FORE                          for 3
Define SC_MARGIN_TEXT                          for 4
Define SC_MARGIN_RTEXT                         for 5
Define SC_MARGIN_COLOUR                        for 6
Define SCI_SETMARGINTYPEN                      for 2240
Define SCI_GETMARGINTYPEN                      for 2241
Define SCI_SETMARGINWIDTHN                     for 2242
Define SCI_GETMARGINWIDTHN                     for 2243
Define SCI_SETMARGINMASKN                      for 2244
Define SCI_GETMARGINMASKN                      for 2245
Define SCI_SETMARGINSENSITIVEN                 for 2246
Define SCI_GETMARGINSENSITIVEN                 for 2247
Define SCI_SETMARGINCURSORN                    for 2248
Define SCI_GETMARGINCURSORN                    for 2249
Define SCI_SETMARGINBACKN                      for 2250
Define SCI_GETMARGINBACKN                      for 2251
Define SCI_SETMARGINS                          for 2252
Define SCI_GETMARGINS                          for 2253
Define STYLE_DEFAULT                           for 32
Define STYLE_LINENUMBER                        for 33
Define STYLE_BRACELIGHT                        for 34
Define STYLE_BRACEBAD                          for 35
Define STYLE_CONTROLCHAR                       for 36
Define STYLE_INDENTGUIDE                       for 37
Define STYLE_CALLTIP                           for 38
Define STYLE_FOLDDISPLAYTEXT                   for 39
Define STYLE_AUTOCOMPLETE                      for 40
Define STYLE_LASTPREDEFINED                    for 40
Define STYLE_MAX                               for 255
Define SC_CHARSET_ANSI                         for 0
Define SC_CHARSET_DEFAULT                      for 1
Define SC_CHARSET_BALTIC                       for 186
Define SC_CHARSET_CHINESEBIG5                  for 136
Define SC_CHARSET_EASTEUROPE                   for 238
Define SC_CHARSET_GB2312                       for 134
Define SC_CHARSET_GREEK                        for 161
Define SC_CHARSET_HANGUL                       for 129
Define SC_CHARSET_MAC                          for 77
Define SC_CHARSET_OEM                          for 255
Define SC_CHARSET_RUSSIAN                      for 204
Define SC_CHARSET_OEM866                       for 866
Define SC_CHARSET_CYRILLIC                     for 1251
Define SC_CHARSET_SHIFTJIS                     for 128
Define SC_CHARSET_SYMBOL                       for 2
Define SC_CHARSET_TURKISH                      for 162
Define SC_CHARSET_JOHAB                        for 130
Define SC_CHARSET_HEBREW                       for 177
Define SC_CHARSET_ARABIC                       for 178
Define SC_CHARSET_VIETNAMESE                   for 163
Define SC_CHARSET_THAI                         for 222
Define SC_CHARSET_8859_15                      for 1000
Define SCI_STYLECLEARALL                       for 2050
Define SCI_STYLESETFORE                        for 2051
Define SCI_STYLESETBACK                        for 2052
Define SCI_STYLESETBOLD                        for 2053
Define SCI_STYLESETITALIC                      for 2054
Define SCI_STYLESETSIZE                        for 2055
Define SCI_STYLESETFONT                        for 2056
Define SCI_STYLESETEOLFILLED                   for 2057
Define SCI_STYLERESETDEFAULT                   for 2058
Define SCI_STYLESETUNDERLINE                   for 2059
Define SC_CASE_MIXED                           for 0
Define SC_CASE_UPPER                           for 1
Define SC_CASE_LOWER                           for 2
Define SC_CASE_CAMEL                           for 3
Define SCI_STYLEGETFORE                        for 2481
Define SCI_STYLEGETBACK                        for 2482
Define SCI_STYLEGETBOLD                        for 2483
Define SCI_STYLEGETITALIC                      for 2484
Define SCI_STYLEGETSIZE                        for 2485
Define SCI_STYLEGETFONT                        for 2486
Define SCI_STYLEGETEOLFILLED                   for 2487
Define SCI_STYLEGETUNDERLINE                   for 2488
Define SCI_STYLEGETCASE                        for 2489
Define SCI_STYLEGETCHARACTERSET                for 2490
Define SCI_STYLEGETVISIBLE                     for 2491
Define SCI_STYLEGETCHANGEABLE                  for 2492
Define SCI_STYLEGETHOTSPOT                     for 2493
Define SCI_STYLESETCASE                        for 2060
Define SC_FONT_SIZE_MULTIPLIER                 for 100
Define SCI_STYLESETSIZEFRACTIONAL              for 2061
Define SCI_STYLEGETSIZEFRACTIONAL              for 2062
Define SC_WEIGHT_NORMAL                        for 400
Define SC_WEIGHT_SEMIBOLD                      for 600
Define SC_WEIGHT_BOLD                          for 700
Define SCI_STYLESETWEIGHT                      for 2063
Define SCI_STYLEGETWEIGHT                      for 2064
Define SCI_STYLESETCHARACTERSET                for 2066
Define SCI_STYLESETHOTSPOT                     for 2409
Define SCI_SETSELFORE                          for 2067
Define SCI_SETSELBACK                          for 2068
Define SCI_GETSELALPHA                         for 2477
Define SCI_SETSELALPHA                         for 2478
Define SCI_GETSELEOLFILLED                     for 2479
Define SCI_SETSELEOLFILLED                     for 2480
Define SCI_SETCARETFORE                        for 2069
Define SCI_ASSIGNCMDKEY                        for 2070
Define SCI_CLEARCMDKEY                         for 2071
Define SCI_CLEARALLCMDKEYS                     for 2072
Define SCI_SETSTYLINGEX                        for 2073
Define SCI_STYLESETVISIBLE                     for 2074
Define SCI_GETCARETPERIOD                      for 2075
Define SCI_SETCARETPERIOD                      for 2076
Define SCI_SETWORDCHARS                        for 2077
Define SCI_GETWORDCHARS                        for 2646
Define SCI_BEGINUNDOACTION                     for 2078
Define SCI_ENDUNDOACTION                       for 2079
Define INDIC_PLAIN                             for 0
Define INDIC_SQUIGGLE                          for 1
Define INDIC_TT                                for 2
Define INDIC_DIAGONAL                          for 3
Define INDIC_STRIKE                            for 4
Define INDIC_HIDDEN                            for 5
Define INDIC_BOX                               for 6
Define INDIC_ROUNDBOX                          for 7
Define INDIC_STRAIGHTBOX                       for 8
Define INDIC_DASH                              for 9
Define INDIC_DOTS                              for 10
Define INDIC_SQUIGGLELOW                       for 11
Define INDIC_DOTBOX                            for 12
Define INDIC_SQUIGGLEPIXMAP                    for 13
Define INDIC_COMPOSITIONTHICK                  for 14
Define INDIC_COMPOSITIONTHIN                   for 15
Define INDIC_FULLBOX                           for 16
Define INDIC_TEXTFORE                          for 17
Define INDIC_POINT                             for 18
Define INDIC_POINTCHARACTER                    for 19
Define INDIC_IME                               for 32
Define INDIC_IME_MAX                           for 35
Define INDIC_MAX                               for 35
Define INDIC_CONTAINER                         for 8
Define INDIC0_MASK                             for |CI$20  // 0x20
Define INDIC1_MASK                             for |CI$40  // 0x40
Define INDIC2_MASK                             for |CI$80  // 0x80
Define INDICS_MASK                             for |CI$E0  // 0xE0
Define SCI_INDICSETSTYLE                       for 2080
Define SCI_INDICGETSTYLE                       for 2081
Define SCI_INDICSETFORE                        for 2082
Define SCI_INDICGETFORE                        for 2083
Define SCI_INDICSETUNDER                       for 2510
Define SCI_INDICGETUNDER                       for 2511
Define SCI_INDICSETHOVERSTYLE                  for 2680
Define SCI_INDICGETHOVERSTYLE                  for 2681
Define SCI_INDICSETHOVERFORE                   for 2682
Define SCI_INDICGETHOVERFORE                   for 2683
Define SC_INDICVALUEBIT                        for |CI$1000000  // 0x1000000
Define SC_INDICVALUEMASK                       for |CI$FFFFFF   // 0xFFFFFF
Define SC_INDICFLAG_VALUEFORE                  for 1
Define SCI_INDICSETFLAGS                       for 2684
Define SCI_INDICGETFLAGS                       for 2685
Define SCI_SETWHITESPACEFORE                   for 2084
Define SCI_SETWHITESPACEBACK                   for 2085
Define SCI_SETWHITESPACESIZE                   for 2086
Define SCI_GETWHITESPACESIZE                   for 2087
Define SCI_SETSTYLEBITS                        for 2090
Define SCI_GETSTYLEBITS                        for 2091
Define SCI_SETLINESTATE                        for 2092
Define SCI_GETLINESTATE                        for 2093
Define SCI_GETMAXLINESTATE                     for 2094
Define SCI_GETCARETLINEVISIBLE                 for 2095
Define SCI_SETCARETLINEVISIBLE                 for 2096
Define SCI_GETCARETLINEBACK                    for 2097
Define SCI_SETCARETLINEBACK                    for 2098
Define SCI_STYLESETCHANGEABLE                  for 2099
Define SCI_AUTOCSHOW                           for 2100
Define SCI_AUTOCCANCEL                         for 2101
Define SCI_AUTOCACTIVE                         for 2102
Define SCI_AUTOCPOSSTART                       for 2103
Define SCI_AUTOCCOMPLETE                       for 2104
Define SCI_AUTOCSTOPS                          for 2105
Define SCI_AUTOCSETSEPARATOR                   for 2106
Define SCI_AUTOCGETSEPARATOR                   for 2107
Define SCI_AUTOCSELECT                         for 2108
Define SCI_AUTOCSETCANCELATSTART               for 2110
Define SCI_AUTOCGETCANCELATSTART               for 2111
Define SCI_AUTOCSETFILLUPS                     for 2112
Define SCI_AUTOCSETCHOOSESINGLE                for 2113
Define SCI_AUTOCGETCHOOSESINGLE                for 2114
Define SCI_AUTOCSETIGNORECASE                  for 2115
Define SCI_AUTOCGETIGNORECASE                  for 2116
Define SCI_USERLISTSHOW                        for 2117
Define SCI_AUTOCSETAUTOHIDE                    for 2118
Define SCI_AUTOCGETAUTOHIDE                    for 2119
Define SCI_AUTOCUSESTYLE                       for 2120
Define SCI_AUTOCSETDROPRESTOFWORD              for 2270
Define SCI_AUTOCGETDROPRESTOFWORD              for 2271
Define SCI_REGISTERIMAGE                       for 2405
Define SCI_CLEARREGISTEREDIMAGES               for 2408
Define SCI_AUTOCGETTYPESEPARATOR               for 2285
Define SCI_AUTOCSETTYPESEPARATOR               for 2286
Define SCI_AUTOCSETMAXWIDTH                    for 2208
Define SCI_AUTOCGETMAXWIDTH                    for 2209
Define SCI_AUTOCSETMAXHEIGHT                   for 2210
Define SCI_AUTOCGETMAXHEIGHT                   for 2211
Define SCI_SETINDENT                           for 2122
Define SCI_GETINDENT                           for 2123
Define SCI_SETUSETABS                          for 2124
Define SCI_GETUSETABS                          for 2125
Define SCI_SETLINEINDENTATION                  for 2126
Define SCI_GETLINEINDENTATION                  for 2127
Define SCI_GETLINEINDENTPOSITION               for 2128
Define SCI_GETCOLUMN                           for 2129
Define SCI_COUNTCHARACTERS                     for 2633
Define SCI_SETHSCROLLBAR                       for 2130
Define SCI_GETHSCROLLBAR                       for 2131
Define SC_IV_NONE                              for 0
Define SC_IV_REAL                              for 1
Define SC_IV_LOOKFORWARD                       for 2
Define SC_IV_LOOKBOTH                          for 3
Define SCI_SETINDENTATIONGUIDES                for 2132
Define SCI_GETINDENTATIONGUIDES                for 2133
Define SCI_SETHIGHLIGHTGUIDE                   for 2134
Define SCI_GETHIGHLIGHTGUIDE                   for 2135
Define SCI_GETLINEENDPOSITION                  for 2136
Define SCI_GETCODEPAGE                         for 2137
Define SCI_GETCARETFORE                        for 2138
Define SCI_GETREADONLY                         for 2140
Define SCI_SETCURRENTPOS                       for 2141
Define SCI_SETSELECTIONSTART                   for 2142
Define SCI_GETSELECTIONSTART                   for 2143
Define SCI_SETSELECTIONEND                     for 2144
Define SCI_GETSELECTIONEND                     for 2145
Define SCI_SETEMPTYSELECTION                   for 2556
Define SCI_SETPRINTMAGNIFICATION               for 2146
Define SCI_GETPRINTMAGNIFICATION               for 2147
Define SC_PRINT_NORMAL                         for 0
Define SC_PRINT_INVERTLIGHT                    for 1
Define SC_PRINT_BLACKONWHITE                   for 2
Define SC_PRINT_COLOURONWHITE                  for 3
Define SC_PRINT_COLOURONWHITEDEFAULTBG         for 4
Define SCI_SETPRINTCOLOURMODE                  for 2148
Define SCI_GETPRINTCOLOURMODE                  for 2149
Define SCFIND_WHOLEWORD                        for |CI$02    // 0x2
Define SCFIND_MATCHCASE                        for |CI$04    // 0x4
Define SCFIND_WORDSTART                        for |CI$00100000 // 0x00100000
Define SCFIND_REGEXP                           for |CI$00200000 // 0x00200000
Define SCFIND_POSIX                            for |CI$00400000 // 0x00400000
Define SCFIND_CXX11REGEX                       for |CI$00800000 // 0x00800000
Define SCI_FINDTEXT                            for 2150
Define SCI_FORMATRANGE                         for 2151
Define SCI_GETFIRSTVISIBLELINE                 for 2152
Define SCI_GETLINE                             for 2153
Define SCI_GETLINECOUNT                        for 2154
Define SCI_SETMARGINLEFT                       for 2155
Define SCI_GETMARGINLEFT                       for 2156
Define SCI_SETMARGINRIGHT                      for 2157
Define SCI_GETMARGINRIGHT                      for 2158
Define SCI_GETMODIFY                           for 2159
Define SCI_SETSEL                              for 2160
Define SCI_GETSELTEXT                          for 2161
Define SCI_GETTEXTRANGE                        for 2162
Define SCI_HIDESELECTION                       for 2163
Define SCI_POINTXFROMPOSITION                  for 2164
Define SCI_POINTYFROMPOSITION                  for 2165
Define SCI_LINEFROMPOSITION                    for 2166
Define SCI_POSITIONFROMLINE                    for 2167
Define SCI_LINESCROLL                          for 2168
Define SCI_SCROLLCARET                         for 2169
Define SCI_SCROLLRANGE                         for 2569
Define SCI_REPLACESEL                          for 2170
Define SCI_SETREADONLY                         for 2171
Define SCI_NULL                                for 2172
Define SCI_CANPASTE                            for 2173
Define SCI_CANUNDO                             for 2174
Define SCI_EMPTYUNDOBUFFER                     for 2175
Define SCI_UNDO                                for 2176
Define SCI_CUT                                 for 2177
Define SCI_COPY                                for 2178
Define SCI_PASTE                               for 2179
Define SCI_CLEAR                               for 2180
Define SCI_SETTEXT                             for 2181
Define SCI_GETTEXT                             for 2182
Define SCI_GETTEXTLENGTH                       for 2183
Define SCI_GETDIRECTFUNCTION                   for 2184
Define SCI_GETDIRECTPOINTER                    for 2185
Define SCI_SETOVERTYPE                         for 2186
Define SCI_GETOVERTYPE                         for 2187
Define SCI_SETCARETWIDTH                       for 2188
Define SCI_GETCARETWIDTH                       for 2189
Define SCI_SETTARGETSTART                      for 2190
Define SCI_GETTARGETSTART                      for 2191
Define SCI_SETTARGETEND                        for 2192
Define SCI_GETTARGETEND                        for 2193
Define SCI_SETTARGETRANGE                      for 2686
Define SCI_GETTARGETTEXT                       for 2687
Define SCI_TARGETFROMSELECTION                 for 2287
Define SCI_TARGETWHOLEDOCUMENT                 for 2690
Define SCI_REPLACETARGET                       for 2194
Define SCI_REPLACETARGETRE                     for 2195
Define SCI_SEARCHINTARGET                      for 2197
Define SCI_SETSEARCHFLAGS                      for 2198
Define SCI_GETSEARCHFLAGS                      for 2199
Define SCI_CALLTIPSHOW                         for 2200
Define SCI_CALLTIPCANCEL                       for 2201
Define SCI_CALLTIPACTIVE                       for 2202
Define SCI_CALLTIPPOSSTART                     for 2203
Define SCI_CALLTIPSETPOSSTART                  for 2214
Define SCI_CALLTIPSETHLT                       for 2204
Define SCI_CALLTIPSETBACK                      for 2205
Define SCI_CALLTIPSETFORE                      for 2206
Define SCI_CALLTIPSETFOREHLT                   for 2207
Define SCI_CALLTIPUSESTYLE                     for 2212
Define SCI_CALLTIPSETPOSITION                  for 2213
Define SCI_VISIBLEFROMDOCLINE                  for 2220
Define SCI_DOCLINEFROMVISIBLE                  for 2221
Define SCI_WRAPCOUNT                           for 2235
Define SC_FOLDLEVELBASE                        for |CI$000400  // $0x400
Define SC_FOLDLEVELWHITEFLAG                   for |CI$001000  // $0x1000
Define SC_FOLDLEVELHEADERFLAG                  for |CI$002000  // $0x2000
Define SC_FOLDLEVELNUMBERMASK                  for |CI$000FFF  // $0x0FFF
Define SCI_SETFOLDLEVEL                        for 2222
Define SCI_GETFOLDLEVEL                        for 2223
Define SCI_GETLASTCHILD                        for 2224
Define SCI_GETFOLDPARENT                       for 2225
Define SCI_SHOWLINES                           for 2226
Define SCI_HIDELINES                           for 2227
Define SCI_GETLINEVISIBLE                      for 2228
Define SCI_GETALLLINESVISIBLE                  for 2236
Define SCI_SETFOLDEXPANDED                     for 2229
Define SCI_GETFOLDEXPANDED                     for 2230
Define SCI_TOGGLEFOLD                          for 2231
Define SCI_TOGGLEFOLDSHOWTEXT                  for 2700
Define SC_FOLDDISPLAYTEXT_HIDDEN               for 0
Define SC_FOLDDISPLAYTEXT_STANDARD             for 1
Define SC_FOLDDISPLAYTEXT_BOXED                for 2
Define SCI_FOLDDISPLAYTEXTSETSTYLE             for 2701
Define SC_FOLDACTION_CONTRACT                  for 0
Define SC_FOLDACTION_EXPAND                    for 1
Define SC_FOLDACTION_TOGGLE                    for 2
Define SCI_FOLDLINE                            for 2237
Define SCI_FOLDCHILDREN                        for 2238
Define SCI_EXPANDCHILDREN                      for 2239
Define SCI_FOLDALL                             for 2662
Define SCI_ENSUREVISIBLE                       for 2232
Define SC_AUTOMATICFOLD_SHOW                   for |CI$0001  // $0x0001
Define SC_AUTOMATICFOLD_CLICK                  for |CI$0002  // $0x0002
Define SC_AUTOMATICFOLD_CHANGE                 for |CI$0004  // $0x0004
Define SCI_SETAUTOMATICFOLD                    for 2663
Define SCI_GETAUTOMATICFOLD                    for 2664
Define SC_FOLDFLAG_LINEBEFORE_EXPANDED         for |CI$0002  // $0x0002
Define SC_FOLDFLAG_LINEBEFORE_CONTRACTED       for |CI$0004 // $0x0004
Define SC_FOLDFLAG_LINEAFTER_EXPANDED          for |CI$0008  // $0x0008
Define SC_FOLDFLAG_LINEAFTER_CONTRACTED        for |CI$0010  // $0x0010
Define SC_FOLDFLAG_LEVELNUMBERS                for |CI$0040  // $0x0040
Define SC_FOLDFLAG_LINESTATE                   for |CI$0080  // $0x0080
Define SCI_SETFOLDFLAGS                        for 2233
Define SCI_ENSUREVISIBLEENFORCEPOLICY          for 2234
Define SCI_SETTABINDENTS                       for 2260
Define SCI_GETTABINDENTS                       for 2261
Define SCI_SETBACKSPACEUNINDENTS               for 2262
Define SCI_GETBACKSPACEUNINDENTS               for 2263
Define SC_TIME_FOREVER                         for 10000000
Define SCI_SETMOUSEDWELLTIME                   for 2264
Define SCI_GETMOUSEDWELLTIME                   for 2265
Define SCI_WORDSTARTPOSITION                   for 2266
Define SCI_WORDENDPOSITION                     for 2267
Define SCI_ISRANGEWORD                         for 2691
Define SC_IDLESTYLING_NONE                     for 0
Define SC_IDLESTYLING_TOVISIBLE                for 1
Define SC_IDLESTYLING_AFTERVISIBLE             for 2
Define SC_IDLESTYLING_ALL                      for 3
Define SCI_SETIDLESTYLING                      for 2692
Define SCI_GETIDLESTYLING                      for 2693
Define SC_WRAP_NONE                            for 0
Define SC_WRAP_WORD                            for 1
Define SC_WRAP_CHAR                            for 2
Define SC_WRAP_WHITESPACE                      for 3
Define SCI_SETWRAPMODE                         for 2268
Define SCI_GETWRAPMODE                         for 2269
Define SC_WRAPVISUALFLAG_NONE                  for |CI$0000  // $0x0000
Define SC_WRAPVISUALFLAG_END                   for |CI$0001  // $0x0001
Define SC_WRAPVISUALFLAG_START                 for |CI$0002  // $0x0002
Define SC_WRAPVISUALFLAG_MARGIN                for |CI$0004  // $0x0004
Define SCI_SETWRAPVISUALFLAGS                  for 2460
Define SCI_GETWRAPVISUALFLAGS                  for 2461
Define SC_WRAPVISUALFLAGLOC_DEFAULT            for |CI$0000  // $0x0000
Define SC_WRAPVISUALFLAGLOC_END_BY_TEXT        for |CI$0001  // $0x0001
Define SC_WRAPVISUALFLAGLOC_START_BY_TEXT      for |CI$0002  // $0x0002
Define SCI_SETWRAPVISUALFLAGSLOCATION          for 2462
Define SCI_GETWRAPVISUALFLAGSLOCATION          for 2463
Define SCI_SETWRAPSTARTINDENT                  for 2464
Define SCI_GETWRAPSTARTINDENT                  for 2465
Define SC_WRAPINDENT_FIXED                     for 0
Define SC_WRAPINDENT_SAME                      for 1
Define SC_WRAPINDENT_INDENT                    for 2
Define SCI_SETWRAPINDENTMODE                   for 2472
Define SCI_GETWRAPINDENTMODE                   for 2473
Define SC_CACHE_NONE                           for 0
Define SC_CACHE_CARET                          for 1
Define SC_CACHE_PAGE                           for 2
Define SC_CACHE_DOCUMENT                       for 3
Define SCI_SETLAYOUTCACHE                      for 2272
Define SCI_GETLAYOUTCACHE                      for 2273
Define SCI_SETSCROLLWIDTH                      for 2274
Define SCI_GETSCROLLWIDTH                      for 2275
Define SCI_SETSCROLLWIDTHTRACKING              for 2516
Define SCI_GETSCROLLWIDTHTRACKING              for 2517
Define SCI_TEXTWIDTH                           for 2276
Define SCI_SETENDATLASTLINE                    for 2277
Define SCI_GETENDATLASTLINE                    for 2278
Define SCI_TEXTHEIGHT                          for 2279
Define SCI_SETVSCROLLBAR                       for 2280
Define SCI_GETVSCROLLBAR                       for 2281
Define SCI_APPENDTEXT                          for 2282
Define SCI_GETTWOPHASEDRAW                     for 2283
Define SCI_SETTWOPHASEDRAW                     for 2284
Define SC_PHASES_ONE                           for 0
Define SC_PHASES_TWO                           for 1
Define SC_PHASES_MULTIPLE                      for 2
Define SCI_GETPHASESDRAW                       for 2673
Define SCI_SETPHASESDRAW                       for 2674
Define SC_EFF_QUALITY_MASK                     for |CI$0F  // $0xF
Define SC_EFF_QUALITY_DEFAULT                  for 0
Define SC_EFF_QUALITY_NON_ANTIALIASED          for 1
Define SC_EFF_QUALITY_ANTIALIASED              for 2
Define SC_EFF_QUALITY_LCD_OPTIMIZED            for 3
Define SCI_SETFONTQUALITY                      for 2611
Define SCI_GETFONTQUALITY                      for 2612
Define SCI_SETFIRSTVISIBLELINE                 for 2613
Define SC_MULTIPASTE_ONCE                      for 0
Define SC_MULTIPASTE_EACH                      for 1
Define SCI_SETMULTIPASTE                       for 2614
Define SCI_GETMULTIPASTE                       for 2615
Define SCI_GETTAG                              for 2616
Define SCI_LINESJOIN                           for 2288
Define SCI_LINESSPLIT                          for 2289
Define SCI_SETFOLDMARGINCOLOUR                 for 2290
Define SCI_SETFOLDMARGINHICOLOUR               for 2291
Define SCI_LINEDOWN                            for 2300
Define SCI_LINEDOWNEXTEND                      for 2301
Define SCI_LINEUP                              for 2302
Define SCI_LINEUPEXTEND                        for 2303
Define SCI_CHARLEFT                            for 2304
Define SCI_CHARLEFTEXTEND                      for 2305
Define SCI_CHARRIGHT                           for 2306
Define SCI_CHARRIGHTEXTEND                     for 2307
Define SCI_WORDLEFT                            for 2308
Define SCI_WORDLEFTEXTEND                      for 2309
Define SCI_WORDRIGHT                           for 2310
Define SCI_WORDRIGHTEXTEND                     for 2311
Define SCI_HOME                                for 2312
Define SCI_HOMEEXTEND                          for 2313
Define SCI_LINEEND                             for 2314
Define SCI_LINEENDEXTEND                       for 2315
Define SCI_DOCUMENTSTART                       for 2316
Define SCI_DOCUMENTSTARTEXTEND                 for 2317
Define SCI_DOCUMENTEND                         for 2318
Define SCI_DOCUMENTENDEXTEND                   for 2319
Define SCI_PAGEUP                              for 2320
Define SCI_PAGEUPEXTEND                        for 2321
Define SCI_PAGEDOWN                            for 2322
Define SCI_PAGEDOWNEXTEND                      for 2323
Define SCI_EDITTOGGLEOVERTYPE                  for 2324
Define SCI_CANCEL                              for 2325
Define SCI_DELETEBACK                          for 2326
Define SCI_TAB                                 for 2327
Define SCI_BACKTAB                             for 2328
Define SCI_NEWLINE                             for 2329
Define SCI_FORMFEED                            for 2330
Define SCI_VCHOME                              for 2331
Define SCI_VCHOMEEXTEND                        for 2332
Define SCI_ZOOMIN                              for 2333
Define SCI_ZOOMOUT                             for 2334
Define SCI_DELWORDLEFT                         for 2335
Define SCI_DELWORDRIGHT                        for 2336
Define SCI_DELWORDRIGHTEND                     for 2518
Define SCI_LINECUT                             for 2337
Define SCI_LINEDELETE                          for 2338
Define SCI_LINETRANSPOSE                       for 2339
Define SCI_LINEDUPLICATE                       for 2404
Define SCI_LOWERCASE                           for 2340
Define SCI_UPPERCASE                           for 2341
Define SCI_LINESCROLLDOWN                      for 2342
Define SCI_LINESCROLLUP                        for 2343
Define SCI_DELETEBACKNOTLINE                   for 2344
Define SCI_HOMEDISPLAY                         for 2345
Define SCI_HOMEDISPLAYEXTEND                   for 2346
Define SCI_LINEENDDISPLAY                      for 2347
Define SCI_LINEENDDISPLAYEXTEND                for 2348
Define SCI_HOMEWRAP                            for 2349
Define SCI_HOMEWRAPEXTEND                      for 2450
Define SCI_LINEENDWRAP                         for 2451
Define SCI_LINEENDWRAPEXTEND                   for 2452
Define SCI_VCHOMEWRAP                          for 2453
Define SCI_VCHOMEWRAPEXTEND                    for 2454
Define SCI_LINECOPY                            for 2455
Define SCI_MOVECARETINSIDEVIEW                 for 2401
Define SCI_LINELENGTH                          for 2350
Define SCI_BRACEHIGHLIGHT                      for 2351
Define SCI_BRACEHIGHLIGHTINDICATOR             for 2498
Define SCI_BRACEBADLIGHT                       for 2352
Define SCI_BRACEBADLIGHTINDICATOR              for 2499
Define SCI_BRACEMATCH                          for 2353
Define SCI_GETVIEWEOL                          for 2355
Define SCI_SETVIEWEOL                          for 2356
Define SCI_GETDOCPOINTER                       for 2357
Define SCI_SETDOCPOINTER                       for 2358
Define SCI_SETMODEVENTMASK                     for 2359
Define EDGE_NONE                               for 0
Define EDGE_LINE                               for 1
Define EDGE_BACKGROUND                         for 2
Define EDGE_MULTILINE                          for 3
Define SCI_GETEDGECOLUMN                       for 2360
Define SCI_SETEDGECOLUMN                       for 2361
Define SCI_GETEDGEMODE                         for 2362
Define SCI_SETEDGEMODE                         for 2363
Define SCI_GETEDGECOLOUR                       for 2364
Define SCI_SETEDGECOLOUR                       for 2365
Define SCI_MULTIEDGEADDLINE                    for 2694
Define SCI_MULTIEDGECLEARALL                   for 2695
Define SCI_SEARCHANCHOR                        for 2366
Define SCI_SEARCHNEXT                          for 2367
Define SCI_SEARCHPREV                          for 2368
Define SCI_LINESONSCREEN                       for 2370
Define SC_POPUP_NEVER                          for 0
Define SC_POPUP_ALL                            for 1
Define SC_POPUP_TEXT                           for 2
Define SCI_USEPOPUP                            for 2371
Define SCI_SELECTIONISRECTANGLE                for 2372
Define SCI_SETZOOM                             for 2373
Define SCI_GETZOOM                             for 2374
Define SCI_CREATEDOCUMENT                      for 2375
Define SCI_ADDREFDOCUMENT                      for 2376
Define SCI_RELEASEDOCUMENT                     for 2377
Define SCI_GETMODEVENTMASK                     for 2378
Define SCI_SETFOCUS                            for 2380
Define SCI_GETFOCUS                            for 2381
Define SC_STATUS_OK                            for 0
Define SC_STATUS_FAILURE                       for 1
Define SC_STATUS_BADALLOC                      for 2
Define SC_STATUS_WARN_START                    for 1000
Define SC_STATUS_WARN_REGEX                    for 1001
Define SCI_SETSTATUS                           for 2382
Define SCI_GETSTATUS                           for 2383
Define SCI_SETMOUSEDOWNCAPTURES                for 2384
Define SCI_GETMOUSEDOWNCAPTURES                for 2385
Define SCI_SETMOUSEWHEELCAPTURES               for 2696
Define SCI_GETMOUSEWHEELCAPTURES               for 2697
Define SC_CURSORNORMAL                         for 1
Define SC_CURSORARROW                          for 2
Define SC_CURSORWAIT                           for 4
Define SC_CURSORREVERSEARROW                   for 7
Define SCI_SETCURSOR                           for 2386
Define SCI_GETCURSOR                           for 2387
Define SCI_SETCONTROLCHARSYMBOL                for 2388
Define SCI_GETCONTROLCHARSYMBOL                for 2389
Define SCI_WORDPARTLEFT                        for 2390
Define SCI_WORDPARTLEFTEXTEND                  for 2391
Define SCI_WORDPARTRIGHT                       for 2392
Define SCI_WORDPARTRIGHTEXTEND                 for 2393
Define VISIBLE_SLOP                            for |CI$01  // $0x01
Define VISIBLE_STRICT                          for |CI$04  // $0x04
Define SCI_SETVISIBLEPOLICY                    for 2394
Define SCI_DELLINELEFT                         for 2395
Define SCI_DELLINERIGHT                        for 2396
Define SCI_SETXOFFSET                          for 2397
Define SCI_GETXOFFSET                          for 2398
Define SCI_CHOOSECARETX                        for 2399
Define SCI_GRABFOCUS                           for 2400
Define CARET_SLOP                              for |CI$01  // $0x01
Define CARET_STRICT                            for |CI$04  // $0x04
Define CARET_JUMPS                             for |CI$10  // $0x10
Define CARET_EVEN                              for |CI$08  // $0x08
Define SCI_SETXCARETPOLICY                     for 2402
Define SCI_SETYCARETPOLICY                     for 2403
Define SCI_SETPRINTWRAPMODE                    for 2406
Define SCI_GETPRINTWRAPMODE                    for 2407
Define SCI_SETHOTSPOTACTIVEFORE                for 2410
Define SCI_GETHOTSPOTACTIVEFORE                for 2494
Define SCI_SETHOTSPOTACTIVEBACK                for 2411
Define SCI_GETHOTSPOTACTIVEBACK                for 2495
Define SCI_SETHOTSPOTACTIVEUNDERLINE           for 2412
Define SCI_GETHOTSPOTACTIVEUNDERLINE           for 2496
Define SCI_SETHOTSPOTSINGLELINE                for 2421
Define SCI_GETHOTSPOTSINGLELINE                for 2497
Define SCI_PARADOWN                            for 2413
Define SCI_PARADOWNEXTEND                      for 2414
Define SCI_PARAUP                              for 2415
Define SCI_PARAUPEXTEND                        for 2416
Define SCI_POSITIONBEFORE                      for 2417
Define SCI_POSITIONAFTER                       for 2418
Define SCI_POSITIONRELATIVE                    for 2670
Define SCI_COPYRANGE                           for 2419
Define SCI_COPYTEXT                            for 2420
Define SC_SEL_STREAM                           for 0
Define SC_SEL_RECTANGLE                        for 1
Define SC_SEL_LINES                            for 2
Define SC_SEL_THIN                             for 3
Define SCI_SETSELECTIONMODE                    for 2422
Define SCI_GETSELECTIONMODE                    for 2423
Define SCI_GETLINESELSTARTPOSITION             for 2424
Define SCI_GETLINESELENDPOSITION               for 2425
Define SCI_LINEDOWNRECTEXTEND                  for 2426
Define SCI_LINEUPRECTEXTEND                    for 2427
Define SCI_CHARLEFTRECTEXTEND                  for 2428
Define SCI_CHARRIGHTRECTEXTEND                 for 2429
Define SCI_HOMERECTEXTEND                      for 2430
Define SCI_VCHOMERECTEXTEND                    for 2431
Define SCI_LINEENDRECTEXTEND                   for 2432
Define SCI_PAGEUPRECTEXTEND                    for 2433
Define SCI_PAGEDOWNRECTEXTEND                  for 2434
Define SCI_STUTTEREDPAGEUP                     for 2435
Define SCI_STUTTEREDPAGEUPEXTEND               for 2436
Define SCI_STUTTEREDPAGEDOWN                   for 2437
Define SCI_STUTTEREDPAGEDOWNEXTEND             for 2438
Define SCI_WORDLEFTEND                         for 2439
Define SCI_WORDLEFTENDEXTEND                   for 2440
Define SCI_WORDRIGHTEND                        for 2441
Define SCI_WORDRIGHTENDEXTEND                  for 2442
Define SCI_SETWHITESPACECHARS                  for 2443
Define SCI_GETWHITESPACECHARS                  for 2647
Define SCI_SETPUNCTUATIONCHARS                 for 2648
Define SCI_GETPUNCTUATIONCHARS                 for 2649
Define SCI_SETCHARSDEFAULT                     for 2444
Define SCI_AUTOCGETCURRENT                     for 2445
Define SCI_AUTOCGETCURRENTTEXT                 for 2610
Define SC_CASEINSENSITIVEBEHAVIOUR_RESPECTCASE for 0
Define SC_CASEINSENSITIVEBEHAVIOUR_IGNORECASE  for 1
Define SCI_AUTOCSETCASEINSENSITIVEBEHAVIOUR    for 2634
Define SCI_AUTOCGETCASEINSENSITIVEBEHAVIOUR    for 2635
Define SC_MULTIAUTOC_ONCE                      for 0
Define SC_MULTIAUTOC_EACH                      for 1
Define SCI_AUTOCSETMULTI                       for 2636
Define SCI_AUTOCGETMULTI                       for 2637
Define SC_ORDER_PRESORTED                      for 0
Define SC_ORDER_PERFORMSORT                    for 1
Define SC_ORDER_CUSTOM                         for 2
Define SCI_AUTOCSETORDER                       for 2660
Define SCI_AUTOCGETORDER                       for 2661
Define SCI_ALLOCATE                            for 2446
Define SCI_TARGETASUTF8                        for 2447
Define SCI_SETLENGTHFORENCODE                  for 2448
Define SCI_ENCODEDFROMUTF8                     for 2449
Define SCI_FINDCOLUMN                          for 2456
Define SCI_GETCARETSTICKY                      for 2457
Define SCI_SETCARETSTICKY                      for 2458
Define SC_CARETSTICKY_OFF                      for 0
Define SC_CARETSTICKY_ON                       for 1
Define SC_CARETSTICKY_WHITESPACE               for 2
Define SCI_TOGGLECARETSTICKY                   for 2459
Define SCI_SETPASTECONVERTENDINGS              for 2467
Define SCI_GETPASTECONVERTENDINGS              for 2468
Define SCI_SELECTIONDUPLICATE                  for 2469
Define SC_ALPHA_TRANSPARENT                    for 0
Define SC_ALPHA_OPAQUE                         for 255
Define SC_ALPHA_NOALPHA                        for 256
Define SCI_SETCARETLINEBACKALPHA               for 2470
Define SCI_GETCARETLINEBACKALPHA               for 2471
Define CARETSTYLE_INVISIBLE                    for 0
Define CARETSTYLE_LINE                         for 1
Define CARETSTYLE_BLOCK                        for 2
Define SCI_SETCARETSTYLE                       for 2512
Define SCI_GETCARETSTYLE                       for 2513
Define SCI_SETINDICATORCURRENT                 for 2500
Define SCI_GETINDICATORCURRENT                 for 2501
Define SCI_SETINDICATORVALUE                   for 2502
Define SCI_GETINDICATORVALUE                   for 2503
Define SCI_INDICATORFILLRANGE                  for 2504
Define SCI_INDICATORCLEARRANGE                 for 2505
Define SCI_INDICATORALLONFOR                   for 2506
Define SCI_INDICATORVALUEAT                    for 2507
Define SCI_INDICATORSTART                      for 2508
Define SCI_INDICATOREND                        for 2509
Define SCI_SETPOSITIONCACHE                    for 2514
Define SCI_GETPOSITIONCACHE                    for 2515
Define SCI_COPYALLOWLINE                       for 2519
Define SCI_GETCHARACTERPOINTER                 for 2520
Define SCI_GETRANGEPOINTER                     for 2643
Define SCI_GETGAPPOSITION                      for 2644
Define SCI_INDICSETALPHA                       for 2523
Define SCI_INDICGETALPHA                       for 2524
Define SCI_INDICSETOUTLINEALPHA                for 2558
Define SCI_INDICGETOUTLINEALPHA                for 2559
Define SCI_SETEXTRAASCENT                      for 2525
Define SCI_GETEXTRAASCENT                      for 2526
Define SCI_SETEXTRADESCENT                     for 2527
Define SCI_GETEXTRADESCENT                     for 2528
Define SCI_MARKERSYMBOLDEFINED                 for 2529
Define SCI_MARGINSETTEXT                       for 2530
Define SCI_MARGINGETTEXT                       for 2531
Define SCI_MARGINSETSTYLE                      for 2532
Define SCI_MARGINGETSTYLE                      for 2533
Define SCI_MARGINSETSTYLES                     for 2534
Define SCI_MARGINGETSTYLES                     for 2535
Define SCI_MARGINTEXTCLEARALL                  for 2536
Define SCI_MARGINSETSTYLEOFFSET                for 2537
Define SCI_MARGINGETSTYLEOFFSET                for 2538
Define SC_MARGINOPTION_NONE                    for 0
Define SC_MARGINOPTION_SUBLINESELECT           for 1
Define SCI_SETMARGINOPTIONS                    for 2539
Define SCI_GETMARGINOPTIONS                    for 2557
Define SCI_ANNOTATIONSETTEXT                   for 2540
Define SCI_ANNOTATIONGETTEXT                   for 2541
Define SCI_ANNOTATIONSETSTYLE                  for 2542
Define SCI_ANNOTATIONGETSTYLE                  for 2543
Define SCI_ANNOTATIONSETSTYLES                 for 2544
Define SCI_ANNOTATIONGETSTYLES                 for 2545
Define SCI_ANNOTATIONGETLINES                  for 2546
Define SCI_ANNOTATIONCLEARALL                  for 2547
Define ANNOTATION_HIDDEN                       for 0
Define ANNOTATION_STANDARD                     for 1
Define ANNOTATION_BOXED                        for 2
Define ANNOTATION_INDENTED                     for 3
Define SCI_ANNOTATIONSETVISIBLE                for 2548
Define SCI_ANNOTATIONGETVISIBLE                for 2549
Define SCI_ANNOTATIONSETSTYLEOFFSET            for 2550
Define SCI_ANNOTATIONGETSTYLEOFFSET            for 2551
Define SCI_RELEASEALLEXTENDEDSTYLES            for 2552
Define SCI_ALLOCATEEXTENDEDSTYLES              for 2553
Define UNDO_MAY_COALESCE                       for 1
Define SCI_ADDUNDOACTION                       for 2560
Define SCI_CHARPOSITIONFROMPOINT               for 2561
Define SCI_CHARPOSITIONFROMPOINTCLOSE          for 2562
Define SCI_SETMOUSESELECTIONRECTANGULARSWITCH  for 2668
Define SCI_GETMOUSESELECTIONRECTANGULARSWITCH  for 2669
Define SCI_SETMULTIPLESELECTION                for 2563
Define SCI_GETMULTIPLESELECTION                for 2564
Define SCI_SETADDITIONALSELECTIONTYPING        for 2565
Define SCI_GETADDITIONALSELECTIONTYPING        for 2566
Define SCI_SETADDITIONALCARETSBLINK            for 2567
Define SCI_GETADDITIONALCARETSBLINK            for 2568
Define SCI_SETADDITIONALCARETSVISIBLE          for 2608
Define SCI_GETADDITIONALCARETSVISIBLE          for 2609
Define SCI_GETSELECTIONS                       for 2570
Define SCI_GETSELECTIONEMPTY                   for 2650
Define SCI_CLEARSELECTIONS                     for 2571
Define SCI_SETSELECTION                        for 2572
Define SCI_ADDSELECTION                        for 2573
Define SCI_DROPSELECTIONN                      for 2671
Define SCI_SETMAINSELECTION                    for 2574
Define SCI_GETMAINSELECTION                    for 2575
Define SCI_SETSELECTIONNCARET                  for 2576
Define SCI_GETSELECTIONNCARET                  for 2577
Define SCI_SETSELECTIONNANCHOR                 for 2578
Define SCI_GETSELECTIONNANCHOR                 for 2579
Define SCI_SETSELECTIONNCARETVIRTUALSPACE      for 2580
Define SCI_GETSELECTIONNCARETVIRTUALSPACE      for 2581
Define SCI_SETSELECTIONNANCHORVIRTUALSPACE     for 2582
Define SCI_GETSELECTIONNANCHORVIRTUALSPACE     for 2583
Define SCI_SETSELECTIONNSTART                  for 2584
Define SCI_GETSELECTIONNSTART                  for 2585
Define SCI_SETSELECTIONNEND                    for 2586
Define SCI_GETSELECTIONNEND                    for 2587
Define SCI_SETRECTANGULARSELECTIONCARET        for 2588
Define SCI_GETRECTANGULARSELECTIONCARET        for 2589
Define SCI_SETRECTANGULARSELECTIONANCHOR       for 2590
Define SCI_GETRECTANGULARSELECTIONANCHOR       for 2591
Define SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE  for 2592
Define SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE  for 2593
Define SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE for 2594
Define SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE for 2595
Define SCVS_NONE                               for 0
Define SCVS_RECTANGULARSELECTION               for 1
Define SCVS_USERACCESSIBLE                     for 2
Define SCVS_NOWRAPLINESTART                    for 4
Define SCI_SETVIRTUALSPACEOPTIONS              for 2596
Define SCI_GETVIRTUALSPACEOPTIONS              for 2597
Define SCI_SETRECTANGULARSELECTIONMODIFIER     for 2598
Define SCI_GETRECTANGULARSELECTIONMODIFIER     for 2599
Define SCI_SETADDITIONALSELFORE                for 2600
Define SCI_SETADDITIONALSELBACK                for 2601
Define SCI_SETADDITIONALSELALPHA               for 2602
Define SCI_GETADDITIONALSELALPHA               for 2603
Define SCI_SETADDITIONALCARETFORE              for 2604
Define SCI_GETADDITIONALCARETFORE              for 2605
Define SCI_ROTATESELECTION                     for 2606
Define SCI_SWAPMAINANCHORCARET                 for 2607
Define SCI_MULTIPLESELECTADDNEXT               for 2688
Define SCI_MULTIPLESELECTADDEACH               for 2689
Define SCI_CHANGELEXERSTATE                    for 2617
Define SCI_CONTRACTEDFOLDNEXT                  for 2618
Define SCI_VERTICALCENTRECARET                 for 2619
Define SCI_MOVESELECTEDLINESUP                 for 2620
Define SCI_MOVESELECTEDLINESDOWN               for 2621
Define SCI_SETIDENTIFIER                       for 2622
Define SCI_GETIDENTIFIER                       for 2623
Define SCI_RGBAIMAGESETWIDTH                   for 2624
Define SCI_RGBAIMAGESETHEIGHT                  for 2625
Define SCI_RGBAIMAGESETSCALE                   for 2651
Define SCI_MARKERDEFINERGBAIMAGE               for 2626
Define SCI_REGISTERRGBAIMAGE                   for 2627
Define SCI_SCROLLTOSTART                       for 2628
Define SCI_SCROLLTOEND                         for 2629
Define SC_TECHNOLOGY_DEFAULT                   for 0
Define SC_TECHNOLOGY_DIRECTWRITE               for 1
Define SC_TECHNOLOGY_DIRECTWRITERETAIN         for 2
Define SC_TECHNOLOGY_DIRECTWRITEDC             for 3
Define SCI_SETTECHNOLOGY                       for 2630
Define SCI_GETTECHNOLOGY                       for 2631
Define SCI_CREATELOADER                        for 2632
Define SCI_FINDINDICATORSHOW                   for 2640
Define SCI_FINDINDICATORFLASH                  for 2641
Define SCI_FINDINDICATORHIDE                   for 2642
Define SCI_VCHOMEDISPLAY                       for 2652
Define SCI_VCHOMEDISPLAYEXTEND                 for 2653
Define SCI_GETCARETLINEVISIBLEALWAYS           for 2654
Define SCI_SETCARETLINEVISIBLEALWAYS           for 2655
Define SC_LINE_END_TYPE_DEFAULT                for 0
Define SC_LINE_END_TYPE_UNICODE                for 1
Define SCI_SETLINEENDTYPESALLOWED              for 2656
Define SCI_GETLINEENDTYPESALLOWED              for 2657
Define SCI_GETLINEENDTYPESACTIVE               for 2658
Define SCI_SETREPRESENTATION                   for 2665
Define SCI_GETREPRESENTATION                   for 2666
Define SCI_CLEARREPRESENTATION                 for 2667
Define SCI_STARTRECORD                         for 3001
Define SCI_STOPRECORD                          for 3002
Define SCI_SETLEXER                            for 4001
Define SCI_GETLEXER                            for 4002
Define SCI_COLOURISE                           for 4003
Define SCI_SETPROPERTY                         for 4004
Define KEYWORDSET_MAX                          for 8
Define SCI_SETKEYWORDS                         for 4005
Define SCI_SETLEXERLANGUAGE                    for 4006
Define SCI_LOADLEXERLIBRARY                    for 4007
Define SCI_GETPROPERTY                         for 4008
Define SCI_GETPROPERTYEXPANDED                 for 4009
Define SCI_GETPROPERTYINT                      for 4010
Define SCI_GETSTYLEBITSNEEDED                  for 4011
Define SCI_GETLEXERLANGUAGE                    for 4012
Define SCI_PRIVATELEXERCALL                    for 4013
Define SCI_PROPERTYNAMES                       for 4014
Define SC_TYPE_BOOLEAN                         for 0
Define SC_TYPE_INTEGER                         for 1
Define SC_TYPE_STRING                          for 2
Define SCI_PROPERTYTYPE                        for 4015
Define SCI_DESCRIBEPROPERTY                    for 4016
Define SCI_DESCRIBEKEYWORDSETS                 for 4017
Define SCI_GETLINEENDTYPESSUPPORTED            for 4018
Define SCI_ALLOCATESUBSTYLES                   for 4020
Define SCI_GETSUBSTYLESSTART                   for 4021
Define SCI_GETSUBSTYLESLENGTH                  for 4022
Define SCI_GETSTYLEFROMSUBSTYLE                for 4027
Define SCI_GETPRIMARYSTYLEFROMSTYLE            for 4028
Define SCI_FREESUBSTYLES                       for 4023
Define SCI_SETIDENTIFIERS                      for 4024
Define SCI_DISTANCETOSECONDARYSTYLES           for 4025
Define SCI_GETSUBSTYLEBASES                    for 4026
Define SC_MOD_INSERTTEXT                       for |CI$01  // $0x1
Define SC_MOD_DELETETEXT                       for |CI$02  // $0x2
Define SC_MOD_CHANGESTYLE                      for |CI$04  // $0x4
Define SC_MOD_CHANGEFOLD                       for |CI$08  // $0x8
Define SC_PERFORMED_USER                       for |CI$010  // $0x10
Define SC_PERFORMED_UNDO                       for |CI$020  // $0x20
Define SC_PERFORMED_REDO                       for |CI$040  // $0x40
Define SC_MULTISTEPUNDOREDO                    for |CI$080  // $0x80
Define SC_LASTSTEPINUNDOREDO                   for |CI$0100  // $0x100
Define SC_MOD_CHANGEMARKER                     for |CI$0200  // $0x200
Define SC_MOD_BEFOREINSERT                     for |CI$0400  // $0x400
Define SC_MOD_BEFOREDELETE                     for |CI$0800  // $0x800
Define SC_MULTILINEUNDOREDO                    for |CI$01000  // $0x1000
Define SC_STARTACTION                          for |CI$2000  // $0x2000
Define SC_MOD_CHANGEINDICATOR                  for |CI$4000  // $0x4000
Define SC_MOD_CHANGELINESTATE                  for |CI$8000  // $0x8000
Define SC_MOD_CHANGEMARGIN                     for |CI$10000  // $0x10000
Define SC_MOD_CHANGEANNOTATION                 for |CI$20000  //$0x20000
Define SC_MOD_CONTAINER                        for |CI$40000  // $0x40000
Define SC_MOD_LEXERSTATE                       for |CI$80000  // $0x80000
Define SC_MOD_INSERTCHECK                      for |CI$100000  // $0x100000
Define SC_MOD_CHANGETABSTOPS                   for |CI$200000  // $0x200000
Define SC_MODEVENTMASKALL                      for |CI$3FFFFF  // $0x3FFFFF
Define SC_UPDATE_CONTENT                       for |CI$01  // $0x1
Define SC_UPDATE_SELECTION                     for |CI$02  // $0x2
Define SC_UPDATE_V_SCROLL                      for |CI$04  // $0x4
Define SC_UPDATE_H_SCROLL                      for |CI$08  // $0x8
Define SCEN_CHANGE                             for 768
Define SCEN_SETFOCUS                           for 512
Define SCEN_KILLFOCUS                          for 256
Define SCK_DOWN                                for 300
Define SCK_UP                                  for 301
Define SCK_LEFT                                for 302
Define SCK_RIGHT                               for 303
Define SCK_HOME                                for 304
Define SCK_END                                 for 305
Define SCK_PRIOR                               for 306
Define SCK_NEXT                                for 307
Define SCK_DELETE                              for 308
Define SCK_INSERT                              for 309
Define SCK_ESCAPE                              for 7
Define SCK_BACK                                for 8
Define SCK_TAB                                 for 9
Define SCK_RETURN                              for 13
Define SCK_ADD                                 for 310
Define SCK_SUBTRACT                            for 311
Define SCK_DIVIDE                              for 312
Define SCK_WIN                                 for 313
Define SCK_RWIN                                for 314
Define SCK_MENU                                for 315
Define SCMOD_NORM                              for 0
Define SCMOD_SHIFT                             for 1
Define SCMOD_CTRL                              for 2
Define SCMOD_ALT                               for 4
Define SCMOD_SUPER                             for 8
Define SCMOD_META                              for 16
Define SC_AC_FILLUP                            for 1
Define SC_AC_DOUBLECLICK                       for 2
Define SC_AC_TAB                               for 3
Define SC_AC_NEWLINE                           for 4
Define SC_AC_COMMAND                           for 5
Define SCN_STYLENEEDED                         for 2000   // SCN - Notifications
Define SCN_CHARADDED                           for 2001
Define SCN_SAVEPOINTREACHED                    for 2002
Define SCN_SAVEPOINTLEFT                       for 2003
Define SCN_MODIFYATTEMPTRO                     for 2004
Define SCN_KEY                                 for 2005
Define SCN_DOUBLECLICK                         for 2006
Define SCN_UPDATEUI                            for 2007
Define SCN_MODIFIED                            for 2008
Define SCN_MACRORECORD                         for 2009
Define SCN_MARGINCLICK                         for 2010
Define SCN_NEEDSHOWN                           for 2011
Define SCN_PAINTED                             for 2013
Define SCN_USERLISTSELECTION                   for 2014
Define SCN_URIDROPPED                          for 2015
Define SCN_DWELLSTART                          for 2016
Define SCN_DWELLEND                            for 2017
Define SCN_ZOOM                                for 2018
Define SCN_HOTSPOTCLICK                        for 2019
Define SCN_HOTSPOTDOUBLECLICK                  for 2020
Define SCN_CALLTIPCLICK                        for 2021
Define SCN_AUTOCSELECTION                      for 2022
Define SCN_INDICATORCLICK                      for 2023
Define SCN_INDICATORRELEASE                    for 2024
Define SCN_AUTOCCANCELLED                      for 2025
Define SCN_AUTOCCHARDELETED                    for 2026
Define SCN_HOTSPOTRELEASECLICK                 for 2027
Define SCN_FOCUSIN                             for 2028
Define SCN_FOCUSOUT                            for 2029
Define SCN_AUTOCCOMPLETED                      for 2030
Define SCN_MARGINRIGHTCLICK                    for 2031


Define SCLEX_DATAFLEX                   for 122
Define SCE_DF_DEFAULT                   for 0
Define SCE_DF_IDENTIFIER                for 1
Define SCE_DF_METATAG                   for 2
Define SCE_DF_COMMENT2                  for 3
Define SCE_DF_COMMENTLINE               for 4
Define SCE_DF_PREPROCESSOR              for 5
Define SCE_DF_PREPROCESSOR2             for 6
Define SCE_DF_NUMBER                    for 7
Define SCE_DF_HEXNUMBER                 for 8
Define SCE_DF_WORD                      for 9
Define SCE_DF_STRING                    for 10
Define SCE_DF_STRINGEOL                 for 11
Define SCE_DF_SCOPEWORD                 for 12
Define SCE_DF_OPERATOR                  for 13
Define SCE_DF_ASM                       for 14

//Define MARGIN_SCRIPT_FOLD_INDEX for 1 // don't use this strange code word for "code folder margin" use below constants
Define MARGIN_BOOKMARKS    for 0
Define MARGIN_CHANGED_LINE for 1
Define MARGIN_LINE_NUMBERS for 2
Define MARGIN_CODE_FOLDING for 3


Procedure DevTest string sMethod
  //Send Info_box sMethod "DevTest"
End_Procedure

//External_Function CMRegisterControl "CMRegisterControl" CMAX_DLL_NAME Dword dwVersion Returns Integer
//External_Function CMUnregisterControl "CMUnregisterControl" CMAX_DLL_NAME Returns Integer
Function CMUnregisterControl Global Returns Integer
  Integer iVoid
  Handle hWnd
  //Get Window_Handle to hWnd
  //If (hWnd) Begin
  //  Move (DestroyWindow(hWnd)) to iVoid
  //End
  //send DevTest "CMUnregisterControl"
  function_return 0
End_Function
Function CMSetFindReplaceMRUList global Pointer pszMRUList Integer bFind Returns Integer
  send DevTest "CMSetFindReplaceMRUList"
  function_return 0
End_Function
Function CMGetFindReplaceMRUList global Pointer pszMRUList Integer bFind Returns Integer
  send DevTest "CMGetFindReplaceMRUList"
  function_return 0
End_Function
Function CMRegisterLanguage global Pointer pszName Pointer pLang Returns Integer
  send DevTest "CMRegisterLanguage"
  function_return 0
End_Function
Function CMUnregisterLanguage global Pointer pszName Returns Integer
  send DevTest "CMUnregisterLanguage"
  function_return 0
End_Function
Function CMGetMacro global Integer nMacro Pointer pMacroBuff   Returns Integer
  send DevTest "CMGetMacro"
  function_return 0
End_Function
Function CMSetMacro global Integer nMacro Pointer pMacroBuff  Returns Integer
  send DevTest "CMSetMacro"
  function_return 0
End_Function

// 2.0
Function CMUnregisterAllLanguages global  Returns Integer
  send DevTest "CMUnregisterAllLanguages"
  function_return 0
End_Function
Function CMGetLanguageDef global Pointer pszName Pointer pLang   Returns Integer
  send DevTest "CMGetLanguageDef"
  function_return 0
End_Function
//Function CMRegisterCommandInt global Integer wCmd Pointer pszName Pointer pszDesc   Returns Integer
//  send DevTest "CMRegisterCommandInt"
//  function_return 0
//End_Function


    // Possible values for piFindWrapMode
Define FindWrapMode_NoWrap      FOR 1
Define FindWrapMode_NoWrapMsg   FOR 2
Define FindWrapMode_WrapSilent  FOR 3
Define FindWrapMode_WrapAsk     FOR 4

// SciLexer should not need this as we allocate memory manually
//Set_Argument_Size 200000
