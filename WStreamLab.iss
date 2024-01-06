; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define AppWSLName "WStreamLab"
#define AppWSLVersion "1.2"
#define AppWSLPublisher "ELCOST"
#define AppWSLExeName "WStreamLab.exe"
#define AppWSLIconName "WStreamLab.ico"
#define AppWSLReadme "README.txt"
#define AppWSLWebsite "http://www.elcost.com/"

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
    AppId={{1E742ED4-BB2E-41C5-80E5-3BB818C42C23}}
    DefaultGroupName={#AppWSLName}
    SolidCompression=yes
    UserInfoPage=yes
    PrivilegesRequiredOverridesAllowed=dialog
    OutputBaseFilename="{#AppWSLName} v{#AppWSLVersion} Setup"
    UninstallDisplayName="{#AppWSLName} v{#AppWSLVersion} Uninstall"
    SetupLogging=yes  
    WizardImageFile=".\build\water-meter.bmp"
    WizardSmallImageFile=".\build\water-meter.bmp"

[Languages]
    Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
    Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";

[Files]
    Source: ".\build\WStreamLab.exe"; DestDir: "{app}"; Flags: ignoreversion
    Source: ".\build\D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
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
    Source: ".\build\SerialPorts.dll"; DestDir: "{app}"; Flags: ignoreversion
    Source: ".\build\watermeters.conf"; DestDir: "{app}"; Flags: uninsneveruninstall onlyifdoesntexist ignoreversion
    Source: ".\build\watermeters.csv"; DestDir: "{app}"; Flags: uninsneveruninstall onlyifdoesntexist ignoreversion
    Source: ".\build\iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines"; Flags: ignoreversion
    Source: ".\build\imageformats\qgif.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
    Source: ".\build\imageformats\qico.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
    Source: ".\build\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
    Source: ".\build\imageformats\qsvg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
    Source: ".\build\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion
    Source: ".\build\styles\qwindowsvistastyle.dll"; DestDir: "{app}\styles"; Flags: ignoreversion
    Source: ".\build\translations\meter_ro_RO.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
    Source: ".\build\translations\meter_en_EN.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
    Source: ".\build\WStreamLab.ico"; DestDir: "{app}"; Flags: ignoreversion
    Source: ".\build\README.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
    Name: "{commondesktop}\{#AppWSLName}"; Filename: "{app}\{#AppWSLExeName}"; IconFilename: "{app}\{#AppWSLIconName}"; Tasks: desktopicon;
    Name: "{group}\{#AppWSLName}"; Filename: "{app}\{#AppWSLExeName}"; IconFilename: "{app}\{#AppWSLIconName}";
    Name: "{group}\Uninstall {#AppWSLName}"; Filename: "{uninstallexe}"; IconFilename: "{app}\{#AppWSLIconName}";

[Run]
    Filename: "{app}\README.txt"; Description: "View the README.txt file"; Flags: postinstall shellexec skipifsilent

[UninstallRun]
    Filename: "{cmd}"; Parameters: "/C taskkill /F /IM WStreamLab.exe"; Flags: runhidden waituntilterminated
    Filename: "{cmd}"; Parameters: "/C copy ""{app}\watermeters.conf"" ""{userdesktop}\watermeters.conf"""; Flags: runhidden
    Filename: "{cmd}"; Parameters: "/C copy ""{app}\watermeters.csv"" ""{userdesktop}\watermeters.csv"""; Flags: runhidden

[UninstallDelete]
    ; No need to duplicate file names from [Files] section

[Dirs]
    Name: "{app}"; Flags: uninsneveruninstall
    Name: "{app}\styles"; Flags: uninsneveruninstall
    Name: "{app}\iconengines"; Flags: uninsneveruninstall
    Name: "{app}\imageformats"; Flags: uninsneveruninstall
    Name: "{app}\platforms"; Flags: uninsneveruninstall
    Name: "{app}\translations"; Flags: uninsneveruninstall
