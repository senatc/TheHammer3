// The Hammer.h
#IFDEF DFERR_COMP_NEED_DF18_MINIMUM
#ELSE
  #REPLACE DFERR_COMP_NEED_DF18_MINIMUM    |CI14329
#ENDIF


#IF (FMAC_VERSION<18)
  #ERROR DFERR_COMP_NEED_DF18_MINIMUM YOU NEED AT MINIMUM DATAFLEX18 IN ORDER TO COMPILE THEHAMMER3
#ENDIF

// The Hammer Name & Version
Define CTH_Project_Name     for "KURANT Project"
Define CTH_Programm_Name    for "The Hammer"
Define CTH_Version_No       for "3.0"

// For a better readable code.
Define CM_NewFileName       For "Untitled"
Define TO_EDIT              For True
Define TO_VIEW              For False

Global_Variable String gsCurrentProgramFile     255
Global_Variable String gsCurrentCommandLinePara 255
Global_Variable Integer ghoFileTabs             // Define a global integer for the file-tab window 03.03.2003 BP
Global_Variable Integer ghoElementsTree


// Constants for the AppToolBarItems.
Enum_List
    Define TBItem_New       For 0
    Define TBItem_Open
    Define TBItem_Open_Pkg
    Define TBItem_Open_DD
    Define TBItem_Save
    Define TBItem_SaveAll
    Define TBItem_Print
    Define TBItem_Cut
    Define TBItem_Copy
    Define TBItem_Paste
    Define TBItem_Undo
    Define TBItem_Redo
    Define TBItem_Find
    Define TBItem_Replace
    Define TBItem_Compile
    Define TBItem_Run
    Define TBItem_Debug
    Define TBItem_Execute
    Define TBItem_Todo
End_Enum_List

// First of all, we required to identify - what files we use
// Fill this section if any new file added!
Define TH_DBFILE_VDFCLS     For 1
Define TH_DBFILE_SYSFILE    For 2
Define TH_DBFILE_VDFPROP    For 3
Define TH_DBFILE_ASDB       For 4
Define TH_DBFILE_VDFPRNT    For 5

Integer ghoNativeFiles
Object oTHNativeFiles Is a Array
    Send Delete_Data
    Set Value Item TH_DBFILE_VDFCLS     To 1
    Set Value Item TH_DBFILE_SYSFILE    To 1
    Set Value Item TH_DBFILE_VDFPROP    To 1
    Set Value Item TH_DBFILE_ASDB       To 1
    Set Value Item TH_DBFILE_VDFPRNT    To 1
    Move Self To ghoNativeFiles
End_Object

Define WM_MDIACTIVATE For |CI$0222
