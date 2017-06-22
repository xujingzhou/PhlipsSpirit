# Microsoft Developer Studio Project File - Name="HelpTip" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HelpTip - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Man.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Man.mak" CFG="HelpTip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HelpTip - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HelpTip - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HelpTip - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "HelpTip - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "HelpTip - Win32 Release"
# Name "HelpTip - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\About.cpp
# End Source File
# Begin Source File

SOURCE=.\Advertise.cpp
# End Source File
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\CREDITSTATIC.CPP
# End Source File
# Begin Source File

SOURCE=.\DownloadAddress.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpTip.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpTip.rc
# End Source File
# Begin Source File

SOURCE=.\HelpTipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\Ntray.cpp
# End Source File
# Begin Source File

SOURCE=.\SetRing.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TransparentWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\XInfoTip.cpp
# End Source File
# Begin Source File

SOURCE=.\xShadeButton.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\About.h
# End Source File
# Begin Source File

SOURCE=.\Advertise.h
# End Source File
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\CREDITSTATIC.H
# End Source File
# Begin Source File

SOURCE=.\DownloadAddress.h
# End Source File
# Begin Source File

SOURCE=.\FlatEdit.h
# End Source File
# Begin Source File

SOURCE=.\HelpTip.h
# End Source File
# Begin Source File

SOURCE=.\HelpTipDlg.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\Ntray.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetRing.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TransparentWnd.h
# End Source File
# Begin Source File

SOURCE=.\XInfoTip.h
# End Source File
# Begin Source File

SOURCE=.\xShadeButton.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\120.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ANGRY1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ANGRY2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ANGRY3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\angry4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b32.ico
# End Source File
# Begin Source File

SOURCE=.\res\check.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close.bmp
# End Source File
# Begin Source File

SOURCE=.\res\drop.cur
# End Source File
# Begin Source File

SOURCE=.\res\FUNK1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FUNK2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FUNK3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FUNK4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\HelpTip.ico
# End Source File
# Begin Source File

SOURCE=.\res\HelpTip.rc2
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDLE1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idle10001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idle10002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idle10003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idle10004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDLE2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDLE3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDLE4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDLE5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDLE6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDLE7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDLE8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RUN9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sling10001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sling10002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sling10003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sling10004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sling10005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sling10006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sling10007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sling10008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transform10013.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TrayIcon.ico
# End Source File
# Begin Source File

SOURCE=.\res\WALK1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10013.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10014.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10015.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10016.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10017.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10018.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10019.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10020.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10021.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10022.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10023.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk10024.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK9.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\IDR_WAVE.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
