!include "MUI2.nsh"
!include "FileFunc.nsh"

; --- Version (overridden by CI via -DVERSION=x.y.z) ---
!ifndef VERSION
    !define VERSION "0.0.0"
!endif

; --- General ---
Name "Lumina Inventory System ${VERSION}"
OutFile "LuminaInventorySystem-Setup.exe"
InstallDir "$PROGRAMFILES64\Lumina Inventory System"
InstallDirRegKey HKLM "Software\LuminaInventorySystem" "InstallDir"
RequestExecutionLevel admin

; Embed version info into the .exe metadata
VIProductVersion "${VERSION}.0"
VIAddVersionKey "ProductName" "Lumina Inventory System"
VIAddVersionKey "ProductVersion" "${VERSION}"
VIAddVersionKey "FileVersion" "${VERSION}"
VIAddVersionKey "FileDescription" "Lumina Inventory System Installer"
VIAddVersionKey "LegalCopyright" "Alexandre Beaulieu"

; --- UI ---
!define MUI_ICON "icons\lumina.ico"
!define MUI_ABORTWARNING
!define MUI_WELCOMEPAGE_TITLE "Lumina Inventory System ${VERSION} Setup"
!define MUI_WELCOMEPAGE_TEXT "This will install Lumina Inventory System ${VERSION} on your computer.$\r$\n$\r$\nClick Next to continue."

; --- Pages ---
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

; --- Check for existing installation and silently uninstall ---
Function .onInit
    ReadRegStr $0 HKLM "Software\LuminaInventorySystem" "InstallDir"
    StrCmp $0 "" done

    ; An existing install was found — check its version
    ReadRegStr $1 HKLM "Software\LuminaInventorySystem" "Version"
    StrCmp $1 "${VERSION}" same_version upgrade

same_version:
    MessageBox MB_YESNO|MB_ICONQUESTION \
        "Lumina Inventory System ${VERSION} is already installed.$\r$\n$\r$\nDo you want to reinstall it?" \
        IDYES upgrade
    Abort

upgrade:
    ; Silently run the old uninstaller, wait for it to finish
    IfFileExists "$0\Uninstall.exe" 0 done
    ExecWait '"$0\Uninstall.exe" /S _?=$0'
    Delete "$0\Uninstall.exe"
    RMDir "$0"

done:
FunctionEnd

; --- Install ---
Section "Install"
    SetOutPath "$INSTDIR"

    ; Copy all files from the package directory
    File /r "package\*.*"

    ; Write version and install path to registry
    WriteRegStr HKLM "Software\LuminaInventorySystem" "InstallDir" "$INSTDIR"
    WriteRegStr HKLM "Software\LuminaInventorySystem" "Version" "${VERSION}"

    ; Add/Remove Programs entry
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem" \
        "DisplayName" "Lumina Inventory System"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem" \
        "DisplayVersion" "${VERSION}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem" \
        "Publisher" "Alexandre Beaulieu"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem" \
        "UninstallString" '"$INSTDIR\Uninstall.exe"'
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem" \
        "QuietUninstallString" '"$INSTDIR\Uninstall.exe" /S'
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem" \
        "DisplayIcon" '"$INSTDIR\InventorySystem.exe"'
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem" \
        "NoModify" 1
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem" \
        "NoRepair" 1

    ; Estimate installed size (in KB) for Add/Remove Programs
    ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
    IntFmt $0 "0x%08X" $0
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem" \
        "EstimatedSize" $0

    ; Create uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

    ; Start Menu shortcuts
    CreateDirectory "$SMPROGRAMS\Lumina Inventory System"
    CreateShortcut "$SMPROGRAMS\Lumina Inventory System\Lumina Inventory System.lnk" \
        "$INSTDIR\InventorySystem.exe"
    CreateShortcut "$SMPROGRAMS\Lumina Inventory System\Uninstall.lnk" \
        "$INSTDIR\Uninstall.exe"

    ; Desktop shortcut
    CreateShortcut "$DESKTOP\Lumina Inventory System.lnk" \
        "$INSTDIR\InventorySystem.exe"
SectionEnd

; --- Uninstall ---
Section "Uninstall"
    ; Remove files
    RMDir /r "$INSTDIR"

    ; Remove shortcuts
    Delete "$DESKTOP\Lumina Inventory System.lnk"
    RMDir /r "$SMPROGRAMS\Lumina Inventory System"

    ; Remove registry keys
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LuminaInventorySystem"
    DeleteRegKey HKLM "Software\LuminaInventorySystem"
SectionEnd
