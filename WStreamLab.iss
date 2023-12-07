; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define AppWSLName "WStreamLab"
#define AppWSLVersion "1.2"
#define AppWSLPublisher "ELCOST"
#define AppWSLExeName "WStreamLab.exe"
#define AppWSLIcoName "WStreamLab.ico"
#define AppWSLReadme "README.txt"
#define AppWSLWebsite  "http://www.elcost.com/"

[Setup]
AppName={#AppWSLName}
AppVersion={#AppWSLVersion}
AppVerName="{#AppWSLName} {#AppWSLVersion}"
AppPublisher={#AppWSLPublisher}
AppSupportURL={#AppWSLWebsite}
AppUpdatesURL={#AppWSLWebsite}
Compression=lzma
DefaultDirName={commonpf}\{#AppWSLName}
DisableDirPage=yes
DisableProgramGroupPage=yes
LicenseFile=".\build\LICENSE"
AppId={{1E742ED4-BB2E-41C5-80E5-3BB818C42C23}
DefaultGroupName={#AppWSLName}
SolidCompression=yes
UserInfoPage=yes
PrivilegesRequiredOverridesAllowed=dialog
OutputBaseFilename="{#AppWSLName} v{#AppWSLVersion} Setup"
UninstallDisplayName="{#AppWSLName}v{#AppWSLVersion} Uninstall"
SetupLogging=yes  

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";

[Files]
Source: ".\build\WStreamLab.exe"; DestDir: "{app}"
Source: ".\build\D3Dcompiler_47.dll"; DestDir: "{app}"
Source: ".\build\libgcc_s_seh-1.dll"; DestDir: "{app}"
Source: ".\build\libstdc++-6.dll"; DestDir: "{app}"
Source: ".\build\libwinpthread-1.dll"; DestDir: "{app}"
Source: ".\build\opengl32sw.dll"; DestDir: "{app}"
Source: ".\build\Qt6Core.dll"; DestDir: "{app}"
Source: ".\build\Qt6Gui.dll"; DestDir: "{app}"
Source: ".\build\Qt6Network.dll"; DestDir: "{app}"
Source: ".\build\Qt6PrintSupport.dll"; DestDir: "{app}"
Source: ".\build\Qt6SerialBus.dll"; DestDir: "{app}"
Source: ".\build\Qt6SerialPort.dll"; DestDir: "{app}"
Source: ".\build\Qt6Svg.dll"; DestDir: "{app}"
Source: ".\build\Qt6Widgets.dll"; DestDir: "{app}"
Source: ".\build\SerialPorts.dll"; DestDir: "{app}"
Source: ".\build\watermeters.conf"; DestDir: "{app}"
Source: ".\build\watermeters.csv"; DestDir: "{app}"; Flags: uninsneveruninstall  onlyifdoesntexist
Source: ".\build\iconengines\qsvgicon.dll";DestDir: "{app}\iconengines"
Source: ".\build\imageformats\qgif.dll";DestDir: "{app}\imageformats"
Source: ".\build\imageformats\qico.dll";DestDir: "{app}\imageformats"
Source: ".\build\imageformats\qjpeg.dll";DestDir: "{app}\imageformats"
Source: ".\build\imageformats\qsvg.dll";DestDir: "{app}\imageformats"
Source: ".\build\platforms\qwindows.dll";DestDir: "{app}\platforms"
Source: ".\build\styles\qwindowsvistastyle.dll";DestDir: "{app}\styles"
Source: ".\build\translations\meter_ro_RO.qm";DestDir: "{app}\translations"
Source: ".\build\translations\meter_en_EN.qm";DestDir: "{app}\translations"
Source: ".\build\WStreamLab.ico"; DestDir: "{app}"
Source: ".\build\README.txt"; DestDir: "{app}"

[Icons]
Name: "{commondesktop}\{#AppWSLName}"; Filename: "{app}\{#AppWSLExeName}"; IconFilename: "{app}\{#AppWSLIcoName}"; Tasks: desktopicon;
Name: "{group}\{#AppWSLName}"; Filename: "{app}\{#AppWSLExeName}";IconFilename: "{app}\{#AppWSLIcoName}";
Name: "{group}\Uninstall {#AppWSLName}"; Filename: "{uninstallexe}";IconFilename: "{app}\{#AppWSLIcoName}";

[Run]
Filename: "{app}\{#AppWSLExeName}"; Description: "{cm:LaunchProgram,{#StringChange(AppWSLName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
Filename: "{app}\README.txt"; Description: "View the README.txt file"; Flags: postinstall shellexec skipifsilent

[UninstallRun]
Filename: "{cmd}"; Parameters: "/C taskkill /F /IM WStreamLab.exe"; Flags: runhidden waituntilterminated
Filename: "{cmd}"; Parameters: "/C copy ""{app}\watermeters.csv"" ""{userdesktop}\watermeters.csv"""; Flags: runhidden

[UninstallDelete]
Type: files; Name: "{app}\WStreamLab.exe"
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
Type: files; Name: "{app}\SerialPorts.dll"
Type: files; Name: "{app}\watermeters.conf"
Type: filesandordirs; Name: "{app}\styles"
Type: filesandordirs; Name: "{app}\iconengines"
Type: filesandordirs; Name: "{app}\imageformats"
Type: filesandordirs; Name: "{app}\platforms"
Type: filesandordirs; Name: "{app}\translations"
Type: files; Name: "{app}\WStreamLab.ico"
Type: files; Name: "{app}\README.txt"