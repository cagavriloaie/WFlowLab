#define AppName "Water Stream Laboratory"
#define AppVersion "1.3"
#define AppPublisher "ELCOST"
#define AppExeName "WStreamLab.exe"
#define AppIconName "WStreamLab.ico"
#define AppReadme "README.txt"
#define AppWebsite "http://www.elcost.com/"
#define AppOutputDir "output"

[Setup]
AppName={#AppName}
AppVersion={#AppVersion}
AppPublisher={#AppPublisher}
AppSupportURL={#AppWebsite}
AppUpdatesURL={#AppWebsite}
AppCopyright=Copyright © 2024 ELCCOST
AppComments=Water meters calibration.
AppMutex=MyAppMutex
OutputBaseFilename="{#AppName}_v{#AppVersion}_Setup"
DefaultDirName={pf}\{#AppName}
DefaultGroupName={#AppName}
UninstallDisplayName={#AppName} v{#AppVersion} Uninstall
SetupLogging=yes
WizardImageFile=".\build\water-meter.bmp"
WizardSmallImageFile=".\build\water-meter.bmp"
OutputDir={#AppOutputDir}
OutputManifestFile=AppExeName
PrivilegesRequired=admin
AllowCancelDuringInstall=yes
DisableDirPage=yes
DisableProgramGroupPage=yes
ChangesAssociations=yes
AppPublisherURL=http://www.elcost.com
DefaultUserInfoName=John Doe
DefaultUserInfoOrg=ELCCOST

[Code]
procedure InitializeWizard;
begin
  WizardForm.Font.Style := WizardForm.Font.Style + [fsBold]; // Make the font bold
end;

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "Create a desktop icon"; GroupDescription: "Additional icons"

[Files]
Source: ".\build\{#AppReadme}"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6SerialBus.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6SerialPort.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\Qt6Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\watermeters.conf"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\watermeters.csv"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\{#AppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\{#AppIconName}"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\canbus\*.dll"; DestDir: "{app}\canbus"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\generic\*.dll"; DestDir: "{app}\generic"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\iconengines\*.dll"; DestDir: "{app}\iconengines"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\imageformats\*.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\networkinformation\*.dll"; DestDir: "{app}\networkinformation"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\platforms\*.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\styles\*.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\tls\*.dll"; DestDir: "{app}\tls"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\translations\*.qm"; DestDir: "{app}\translations"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\build\translations\*.ts"; DestDir: "{app}\translations"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{commondesktop}\{#AppName}"; Filename: "{app}\{#AppExeName}"; IconFilename: "{app}\{#AppIconName}"; Tasks: desktopicon
Name: "{group}\{#AppName}"; Filename: "{app}\{#AppExeName}"; IconFilename: "{app}\{#AppIconName}"
Name: "{group}\Uninstall {#AppName}"; Filename: "{uninstallexe}"; IconFilename: "{app}\{#AppIconName}"

[Run]
Filename: "notepad.exe"; Parameters: "{app}\{#AppReadme}"; Description: "View the README.txt file"; Flags: postinstall shellexec skipifsilent

[UninstallRun]
Filename: "{cmd}"; Parameters: "/C taskkill /F /IM {#AppExeName}"; Flags: runhidden waituntilterminated
Filename: "{cmd}"; Parameters: "/C copy ""{app}\watermeters.conf"" ""{userdesktop}\watermeters.conf"""; Flags: runhidden
Filename: "{cmd}"; Parameters: "/C copy ""{app}\watermeters.csv"" ""{userdesktop}\watermeters.csv"""; Flags: runhidden

[UninstallDelete]
Type: files; Name: "{app}\{#AppExeName}"
Type: files; Name: "{app}\D3Dcompiler_47.dll"
Type: files; Name: "{app}\libgcc_s_seh-1.dll"
Type: files; Name: "{app}\libstdc++-6.dll"
Type: files; Name: "{app}\libwinpthread-1.dll"
Type: files; Name: "{app}\opengl32sw.dll"
Type: files; Name: "{app}\Qt6Core.dll"
Type: files; Name: "{app}\Qt6Gui.dll"
Type: files; Name: "{app}\Qt6Network.dll"
Type: files; Name: "{app}\Qt6PrintSupport.dll"
Type: files; Name: "{app}\Qt6SerialBus.dll"
Type: files; Name: "{app}\Qt6SerialPort.dll"
Type: files; Name: "{app}\Qt6Svg.dll"
Type: files; Name: "{app}\Qt6Widgets.dll"
Type: files; Name: "{app}\watermeters.conf"
Type: files; Name: "{app}\watermeters.csv"
Type: files; Name: "{app}\canbus\*"
Type: files; Name: "{app}\generic\*"
Type: files; Name: "{app}\iconengines\*"
Type: files; Name: "{app}\imageformats\*"
Type: files; Name: "{app}\networkinformation\*"
Type: files; Name: "{app}\platforms\*"
Type: files; Name: "{app}\styles\*"
Type: files; Name: "{app}\tls\*"
Type: files; Name: "{app}\translations\*"
