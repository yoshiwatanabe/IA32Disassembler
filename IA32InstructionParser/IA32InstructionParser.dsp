# Microsoft Developer Studio Project File - Name="IA32InstructionParser" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=IA32InstructionParser - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IA32InstructionParser.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IA32InstructionParser.mak" CFG="IA32InstructionParser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IA32InstructionParser - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IA32InstructionParser - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IA32InstructionParser - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IA32INSTRUCTIONPARSER_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IA32INSTRUCTIONPARSER_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "IA32InstructionParser - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IA32INSTRUCTIONPARSER_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IA32INSTRUCTIONPARSER_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/IA32Parser.dll" /pdbtype:sept
# Begin Special Build Tool
ProjDir=.
TargetDir=.\Debug
TargetName=IA32Parser
SOURCE="$(InputPath)"
PostBuild_Desc=Copying...
PostBuild_Cmds=copy $(TargetDir)\$(TargetName).DLL                     $(PROJDIR)\..\debug\IA32Parser.dll	copy $(TargetDir)\$(TargetName).Lib                     $(PROJDIR)\..\Lib\IA32Parser.Lib	copy IA32InstructionParser.h                     $(PROJDIR)\..\Include\IA32InstructionParser.h
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "IA32InstructionParser - Win32 Release"
# Name "IA32InstructionParser - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\IA32DisplacementPart.cpp
# End Source File
# Begin Source File

SOURCE=.\IA32ImmediatePart.cpp
# End Source File
# Begin Source File

SOURCE=.\IA32InstructionBody.cpp
# End Source File
# Begin Source File

SOURCE=.\IA32InstructionParser.cpp
# End Source File
# Begin Source File

SOURCE=.\IA32ModrmPart.cpp
# End Source File
# Begin Source File

SOURCE=.\IA32OpcodePart.cpp
# End Source File
# Begin Source File

SOURCE=.\IA32PrefixPart.cpp
# End Source File
# Begin Source File

SOURCE=.\InstructionParserImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\IA32CommonDefinition.h
# End Source File
# Begin Source File

SOURCE=.\IA32DisplacementPart.h
# End Source File
# Begin Source File

SOURCE=.\IA32ImmediatePart.h
# End Source File
# Begin Source File

SOURCE=.\IA32InstructionBody.h
# End Source File
# Begin Source File

SOURCE=.\IA32InstructionParser.h
# End Source File
# Begin Source File

SOURCE=.\IA32ModrmPart.h
# End Source File
# Begin Source File

SOURCE=.\IA32OpcodePart.h
# End Source File
# Begin Source File

SOURCE=.\IA32PrefixPart.h
# End Source File
# Begin Source File

SOURCE=.\InstructionParserImpl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
