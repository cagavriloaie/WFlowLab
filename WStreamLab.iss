#define AppName "WStreamLab"
#define AppVersion "1.8"
#define AppPublisher "ELCOST"
#define AppExeName "WStreamLab.exe"
#define AppIconName "WStreamLab.ico"
#define AppReadme "README_RO_EN.txt"
#define AppWebsite "http://www.elcost.com/"
#define AppOutputDir "output"
#define AppWizardImage "build\WStreamLab.bmp"
#define AppWizardSmallImage "build\WStreamLab.bmp"

[Setup]
; Unique identifier for the application
AppId={{3F8A2C5E-1B4D-4A7C-9E2F-6D8B5A4C3E1F}
AppName={#AppName}
AppVersion={#AppVersion}
AppPublisher={#AppPublisher}
AppSupportURL={#AppWebsite}
AppUpdatesURL={#AppWebsite}
AppPublisherURL={#AppWebsite}
AppCopyright=Copyright © 2026 ELCOST
AppComments=Water meters calibration.
AppMutex=MyAppMutex

; Version information
VersionInfoVersion=1.8.0.0
VersionInfoCompany={#AppPublisher}
VersionInfoDescription=Water Meter Calibration Software
VersionInfoCopyright=Copyright © 2026 {#AppPublisher}
VersionInfoProductName={#AppName}
VersionInfoProductVersion=1.8.0

; Output settings
OutputBaseFilename={#AppName}_v{#AppVersion}_Setup
OutputDir={#AppOutputDir}
OutputManifestFile={#AppExeName}
SetupLogging=yes

; Installation settings
DefaultDirName={pf}\{#AppName}
DefaultGroupName={#AppName}
UninstallDisplayName={#AppName} v{#AppVersion} Uninstall
DefaultUserInfoName=John Doe
DefaultUserInfoOrg=ELCOST
PrivilegesRequired=admin
AllowCancelDuringInstall=yes
DisableDirPage=yes
DisableProgramGroupPage=yes
ChangesAssociations=yes

; Compression settings
Compression=lzma2/ultra64
SolidCompression=yes
LZMAUseSeparateProcess=yes
LZMANumBlockThreads=2

; System requirements
MinVersion=6.1sp1
ArchitecturesAllowed=x86 x64
ArchitecturesInstallIn64BitMode=

; Wizard appearance
WizardImageFile={#AppWizardImage}
WizardSmallImageFile={#AppWizardSmallImage}
SetupIconFile=".\build\{#AppIconName}"

[Code]
procedure InitializeWizard;
begin
  WizardForm.Font.Name := 'Segoe UI';
end;

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
; Romanian language (uncomment if you have Romanian.isl in your Inno Setup installation)
; Name: "romanian"; MessagesFile: "compiler:Languages\Romanian.isl"

[Tasks]
Name: "desktopicon"; Description: "Create a desktop icon"; GroupDescription: "Additional icons"

[Files]
; Documentation
Source: ".\build\{#AppReadme}"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\PROCES_CALCUL_VERIFICARE_CONTOARE.md"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\VERIFICATION_METHOD_PROCESS.md"; DestDir: "{app}"; Flags: ignoreversion

; Main executable and icon
Source: ".\build\{#AppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\{#AppIconName}"; DestDir: "{app}"; Flags: ignoreversion

; Configuration files (preserve user settings on reinstall)
Source: ".\build\watermeters.conf"; DestDir: "{app}"; Flags: onlyifdoesntexist uninsneveruninstall
Source: ".\build\watermeters.csv"; DestDir: "{app}"; Flags: onlyifdoesntexist

; MinGW Runtime DLLs
Source: ".\build\libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion

; DirectX Shader Compiler (deployed by windeployqt)
Source: ".\build\D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion

; Qt 6.7.1 Core DLLs
Source: ".\build\Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6SerialBus.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6SerialPort.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6Svg.dll"; DestDir: "{app}"; Flags: ignoreversion

; OpenGL software renderer
Source: ".\build\opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion

; Qt Plugins
Source: ".\build\canbus\*.dll"; DestDir: "{app}\canbus"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\generic\*.dll"; DestDir: "{app}\generic"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\iconengines\*.dll"; DestDir: "{app}\iconengines"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\imageformats\*.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\networkinformation\*.dll"; DestDir: "{app}\networkinformation"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\platforms\*.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\styles\*.dll"; DestDir: "{app}\styles"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\tls\*.dll"; DestDir: "{app}\tls"; Flags: ignoreversion recursesubdirs createallsubdirs

; Translations
Source: ".\build\translations\*.qm"; DestDir: "{app}\translations"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{commondesktop}\{#AppName}"; Filename: "{app}\{#AppExeName}"; IconFilename: "{app}\{#AppIconName}"; Tasks: desktopicon; Comment: "Create a desktop shortcut for {#AppName}"
Name: "{group}\{#AppName}"; Filename: "{app}\{#AppExeName}"; IconFilename: "{app}\{#AppIconName}"; Comment: "Run {#AppName}"
Name: "{group}\Uninstall {#AppName}"; Filename: "{uninstallexe}"; IconFilename: "{app}\{#AppIconName}"; Comment: "Uninstall {#AppName}"

[Run]
; Run README and application after the Finish button is pressed
Filename: "{app}\{#AppExeName}"; Flags: nowait postinstall
Filename: "notepad.exe"; Parameters: "{app}\{#AppReadme}"; Flags: shellexec postinstall

[UninstallRun]
; Închide aplicația dacă rulează
Filename: "{cmd}"; Parameters: "/C taskkill /F /IM {#AppExeName}"; Flags: runhidden waituntilterminated

; Creează folderul WSTREAMLAB_OLD pe desktop (dacă nu există deja)
Filename: "{cmd}"; Parameters: "/C mkdir ""{userdesktop}\WSTREAMLAB_OLD"""; Flags: runhidden

; Copiază fișierele în acel folder
Filename: "{cmd}"; Parameters: "/C copy ""{app}\watermeters.conf"" ""{userdesktop}\WSTREAMLAB_OLD\watermeters.conf"""; Flags: runhidden
Filename: "{cmd}"; Parameters: "/C copy ""{app}\watermeters.csv"" ""{userdesktop}\WSTREAMLAB_OLD\watermeters.csv"""; Flags: runhidden


[UninstallDelete]
; Main application files
Type: files; Name: "{app}\{#AppExeName}"
Type: files; Name: "{app}\{#AppIconName}"

; Documentation
Type: files; Name: "{app}\README*.txt"
Type: files; Name: "{app}\PROCES_CALCUL_VERIFICARE_CONTOARE.md"
Type: files; Name: "{app}\VERIFICATION_METHOD_PROCESS.md"

; Note: watermeters.conf and watermeters.csv are preserved (uninsneveruninstall flag)

; Runtime DLLs
Type: files; Name: "{app}\libgcc_s_seh-1.dll"
Type: files; Name: "{app}\libstdc++-6.dll"
Type: files; Name: "{app}\libwinpthread-1.dll"
Type: files; Name: "{app}\D3Dcompiler_47.dll"
Type: files; Name: "{app}\opengl32sw.dll"

; Qt DLLs
Type: files; Name: "{app}\Qt6Core.dll"
Type: files; Name: "{app}\Qt6Gui.dll"
Type: files; Name: "{app}\Qt6Widgets.dll"
Type: files; Name: "{app}\Qt6Network.dll"
Type: files; Name: "{app}\Qt6PrintSupport.dll"
Type: files; Name: "{app}\Qt6SerialBus.dll"
Type: files; Name: "{app}\Qt6SerialPort.dll"
Type: files; Name: "{app}\Qt6Svg.dll"

; Qt Plugin directories
Type: files; Name: "{app}\canbus\*"
Type: dirifempty; Name: "{app}\canbus"

Type: files; Name: "{app}\generic\*"
Type: dirifempty; Name: "{app}\generic"

Type: files; Name: "{app}\iconengines\*"
Type: dirifempty; Name: "{app}\iconengines"

Type: files; Name: "{app}\imageformats\*"
Type: dirifempty; Name: "{app}\imageformats"

Type: files; Name: "{app}\networkinformation\*"
Type: dirifempty; Name: "{app}\networkinformation"

Type: files; Name: "{app}\platforms\*"
Type: dirifempty; Name: "{app}\platforms"

Type: files; Name: "{app}\styles\*"
Type: dirifempty; Name: "{app}\styles"

Type: files; Name: "{app}\tls\*"
Type: dirifempty; Name: "{app}\tls"

Type: files; Name: "{app}\translations\*"
Type: dirifempty; Name: "{app}\translations"

