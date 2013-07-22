;Include Modern UI

  !include "MUI2.nsh"
  !include "FileAssociation.nsh"

Name "PixelSwapper 1.21"
OutFile "PixelSwapper1.21Setup.exe"
InstallDir "$PROGRAMFILES\Zeta Centauri\PixelSwapper"
InstallDirRegKey HKLM "Software\PixelSwapper" "Install_Dir"
RequestExecutionLevel admin
!define MUI_ICON "pixelswap.ico"
!define MUI_UNICON "pixelswap.ico"

;Version Information

  VIProductVersion "1.2.1.0"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "PixelSwapper"
;  VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "A test comment"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Zeta Centauri"
;  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "Test Application is a trademark of Fake company"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Copyright 2006-2012 Zeta Centauri"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "PixelSwapper Installer"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "1.2.1.0"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" "1.2.1.0"

;Interface Settings

  !define MUI_ABORTWARNING

;Pages

  !insertmacro MUI_PAGE_LICENSE "License.txt"
;  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
      !define MUI_FINISHPAGE_NOAUTOCLOSE
      !define MUI_FINISHPAGE_RUN
      !define MUI_FINISHPAGE_RUN_CHECKED
      !define MUI_FINISHPAGE_RUN_TEXT "Launch PixelSwapper"
      !define MUI_FINISHPAGE_RUN_FUNCTION "LaunchProgram"
      !define MUI_FINISHPAGE_SHOWREADME ""
      !define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
      !define MUI_FINISHPAGE_SHOWREADME_TEXT "Create Desktop Shortcut"
      !define MUI_FINISHPAGE_SHOWREADME_FUNCTION finishpageaction
  !insertmacro MUI_PAGE_FINISH
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;Languages
 
  !insertmacro MUI_LANGUAGE "English"

; The stuff to install
Section "PixelSwapper"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "PixelSwapper.exe"
  File "License.txt"
  File "pixelswap.ico"
  File "pixelswapper.htb"  

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\PixelSwapper "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PixelSwapper" "DisplayName" "PixelSwapper"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PixelSwapper" "DisplayVersion" "1.21"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PixelSwapper" "Publisher" "Zeta Centauri"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PixelSwapper" "DisplayIcon" "$INSTDIR\pixelswap.ico"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PixelSwapper" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PixelSwapper" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PixelSwapper" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".bmp" "Bitmap File"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".gif" "GIF File"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".ico" "Icon File"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".jpeg" "JPEG Image"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".jpg" "JPG Image"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".pcx" "PCX File"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".png" "PNG Image"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".pnm" "PNM File"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".tga" "TGA File"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".tif" "TIF Image"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".tiff" "TIFF Image"
  ${registerExtension} "$INSTDIR\PixelSwapper.exe" ".xpm" "XPM Image"

SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Zeta Centauri\PixelSwapper"
  CreateShortCut "$SMPROGRAMS\Zeta Centauri\PixelSwapper\PixelSwapper.lnk" "$INSTDIR\PixelSwapper.exe" "" "" 0
  ;CreateShortCut "$SMPROGRAMS\Zeta Centauri\PixelSwapper\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  WriteINIStr "$SMPROGRAMS\Zeta Centauri\PixelSwapper\PixelSwapper Website.url" "InternetShortcut" "URL" "http://zetacentauri.com/software_pixelswapper.htm"
 
SectionEnd

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PixelSwapper"
  DeleteRegKey HKLM SOFTWARE\PixelSwapper

  ; Remove files and uninstaller
  Delete $INSTDIR\PixelSwapper.exe
  Delete $INSTDIR\License.txt
  Delete $INSTDIR\pixelswapper.htb
  Delete $INSTDIR\pixelswap.ico
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Zeta Centauri\PixelSwapper\*.*"
  Delete "$DESKTOP\PixelSwapper.lnk"
  Delete "$SMPROGRAMS\Zeta Centauri\PixelSwapper\PixelSwapper Website.url"
  ;DeleteINISec "$SMPROGRAMS\Zeta Centauri\PixelSwapper\PixelSwapper Website.url" "InternetShortcut"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Zeta Centauri\PixelSwapper"
  RMDir "$SMPROGRAMS\Zeta Centauri"
  RMDir "$INSTDIR"

  ${unregisterExtension} ".bmp" "Bitmap File"
  ${unregisterExtension} ".gif" "GIF File"
  ${unregisterExtension} ".ico" "Icon File"
  ${unregisterExtension} ".jpeg" "JPEG Image"
  ${unregisterExtension} ".jpg" "JPG Image"
  ${unregisterExtension} ".pcx" "PCX File"
  ${unregisterExtension} ".png" "PNG Image"
  ${unregisterExtension} ".pnm" "PNM File"
  ${unregisterExtension} ".tga" "TGA File"
  ${unregisterExtension} ".tif" "TIF Image"
  ${unregisterExtension} ".tiff" "TIFF Image"
  ${unregisterExtension} ".xpm" "XPM Image"


SectionEnd

; This function is automatically executed when the installer finishes
;Function .onGUIEnd
;FunctionEnd

Function LaunchProgram
  ExecShell "" "$SMPROGRAMS\Zeta Centauri\PixelSwapper\PixelSwapper.lnk"
FunctionEnd

Function finishpageaction
  CreateShortcut "$DESKTOP\PixelSwapper.lnk" "$INSTDIR\PixelSwapper.exe"
FunctionEnd
