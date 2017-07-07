// TH3Workspace.h
// on 12/03/2017 by Sergey V. Natarov

Use RegistryAPI.pkg

Integer ghoToolsPane
Integer ghoOutputPane
Integer ghoOutputDialog
Integer ghoEditorPopupMenu
Integer ghoCurrentFileTab
Integer ghoWorkspaceFilesTree
#IFNDEF ghoWorkSpaceHandlerEx
  Integer ghoWorkSpaceHandlerEx
#ENDIF
String gsComputerName
String gsUserName
Integer ghoCompilerInfo
Integer ghoBuildMenu
String gsTransferWSFile
String gsTransferDDFile

// The Hammer File Types
Define KPH_FILE_EDITABLE For 0
Define KPH_FILE_MENU     For 1
Define KPH_FILE_FOLDER   For 2

Struct tTHSource
    String  sFile
    String  sBookmarks
    Integer iBookmarkCount
    Integer iCursorLine
    Integer iCursorColumn
End_Struct

Struct tTHWorkspace
    String   sName
    String   sSchema
    Integer  iShowPaths
    String   sFullName
    String   sStudio
    String   sCompiler
    String   sDBEditor
    String   sDBViewer
    String   sFFText
    String   sFFTypes
    String   sFFPath
    Integer  iFFMatchWord
    Integer  iFFMatchCase
    Integer  iFFSubFolders
    Integer  iFFShowAll
    Integer  iFFRegExp
    String[] saFiles
    String[] saFileDesc
    String[] saFolders
    String[] saExclude
    String[] saOpened
    tTHSource[] taSources
End_Struct
tTHWorkspace gtTHWorkspace

Struct tTHCompiler
    String sVersion
    String sProgID
    String sEventId
    Handle hoCompiler
End_Struct
tTHCompiler[] gtTHCompilers

// Language Definition
Struct tTHLanguage
    String      sName
    Integer     iProcedural
    Integer     iCaseSensitive
    String      sLineComments
    String      sStringDelimiter
    String      sMultiLineCommentStart
    String      sMultiLineCommentStop
    String      sEscapeChar
    String      sLineTerminationChar
    String      sMetaStart
    String      sMetaStop
    String[]    saScopeStart
    String[]    saScopeStop
    String[]    saKeywords
    String[]    saOperators
    String[]    saTags
    String[]    saEntities
    String[]    saAttributes
End_Struct

Struct tDFDefaultClasses
    String sCategory
    String sClass
    String sFile
End_Struct

Define TH_SCHEMA_DATAFLEX   for "DataFlex"
Define TH_SCHEMA_DELPHI     for "Delphi"
Define TH_SCHEMA_CCPP       for "C/C++"
Define TH_SCHEMA_PYTHON     for "Python"
Define TH_SCHEMA_WEB        for "Web"
Define TH_SCHEMA_OTHER      for "Other"

// Upto 256 chars
Function WSReadStr1 Returns String
    String  sSize sValue
    Integer iSize
    Read_Block sSize 1
    Move (Ascii(sSize)) to iSize
    If iSize ;
        Read_Block sValue iSize
    Function_Return sValue
End_Function

// Upto 65356 chars
Function WSReadStr2 Returns String
    String  sSize sValue
    Integer iSize
    Read_Block sSize 2
    Move (BytesToSHORT(sSize, 1)) to iSize
    If iSize ;
        Read_Block sValue iSize
    Function_Return sValue
End_Function

// Upto 2G chars
Function WSReadStr4 Returns String
    String  sSize sValue
    Integer iSize
    Read_Block sSize 4
    Move (BytesToDWORD(sSize, 1)) to iSize
    If iSize ;
        Read_Block sValue iSize
    Function_Return sValue
End_Function

// 0..256
Function WSReadInt1 Returns Integer
    String      sValue
    Read_Block  sValue 1
    Function_Return (Ascii(sValue))
End_Function

// 0..65536
Function WSReadInt2 Returns Integer
    String      sValue
    Read_Block  sValue 2
    Function_Return (BytesToSHORT(sValue, 1))
End_Function

// 0..2G
Function WSReadInt4 Returns Integer
    String      sValue
    Read_Block  sValue 4
    Function_Return (BytesToDWORD(sValue, 1))
End_Function

Procedure WSWriteStr1 String sValue
    Write (Character(Length(sValue)))
    Write sValue
End_Procedure

Procedure WSWriteStr2 String sValue
    Write (SHORTtoBytes(Length(sValue)))
    Write sValue
End_Procedure

Procedure WSWriteStr4 String sValue
    Write (DWordtoBytes(Length(sValue)))
    Write sValue
End_Procedure

Function CheckType String sFile Returns Integer
    String sTemp sTmp
    Move sFile To sTemp
    While "\" In sTemp
        Pos "\" In sTemp
        Left sTemp To sTmp
        Replace sTmp In sTemp with ""
    Loop
    Pos "." In sTemp
    If (Not(found)) Function_Return KPH_FILE_FOLDER
    Function_Return KPH_FILE_EDITABLE
End_Function

