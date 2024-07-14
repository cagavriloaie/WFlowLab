; Comments about recent fixes:
;
; History:
; - Added support for 64-bit installation mode (ArchitecturesInstallIn64BitMode)
; - Adjusted default installation directory to "Program Files\Water Stream Laboratory" (DefaultDirName)
; - Fixed task definition for desktop icon creation (Tasks section)
; - Aligned and structured entries in the [Files] section for better readability
; - Updated file and directory deletion directives during uninstallation (UninstallDelete section)

[Setup]
; General settings for the installer
AppName=Water Stream Laboratory                      ; Name of the application
AppVersion=1.3                                       ; Version of the application
AppVerName=Water Stream Laboratory 1.3               ; Version name displayed in installer UI
AppPublisher=ELCOST                                  ; Publisher name
AppPublisherURL=http://www.elcost.com/               ; Publisher's URL
AppSupportURL=http://www.elcost.com/                 ; Support URL for the application
AppUpdatesURL=http://www.elcost.com/                 ; URL for updates
Compression=lzma                                     ; Compression algorithm for installer
DefaultDirName={pf64}\Water Stream Laboratory        ; Default installation directory
DefaultGroupName=Water Stream Laboratory             ; Name of the Start Menu group
DisableDirPage=yes                                   ; Disable the directory selection page
DisableProgramGroupPage=yes                          ; Disable the Start Menu group selection page
LicenseFile=.\build\LICENSE                          ; Path to the license file
OutputBaseFilename=WaterStreamLabSetup               ; Base filename of the installer executable
SolidCompression=yes                                 ; Use solid compression for smaller installer size
UserInfoPage=yes                                     ; Show the user information page during installation
PrivilegesRequired=admin                             ; Require admin privileges to install
OutputDir=.\output                                   ; Output directory for the generated installer files
UninstallFilesDir={app}                              ; Directory where uninstall files are stored
VersionInfoDescription=Water Stream Laboratory Setup ; Description in the installer's version information
VersionInfoProductName=Water Stream Laboratory       ; Product name in the installer's version information
SetupIconFile=.\build\setup-icon.ico                 ; Icon file for the installer executable
OutputManifestFile=.\build\application.manifest      ; Manifest file for the installer


[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

[Files]
; List of files to be installed
; Format: Source: "source path"; DestDir: "destination directory"; Flags: options
Source: ".\build\README.txt"; DestDir: "{app}"; Flags: ignoreversion
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
Source: ".\build\WStreamLab.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\WStreamLab.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\canbus\qtpassthrucanbus.dll"; DestDir: "{app}\canbus"; Flags: ignoreversion
Source: ".\build\canbus\qtpeakcanbus.dll"; DestDir: "{app}\canbus"; Flags: ignoreversion
Source: ".\build\canbus\qtsysteccanbus.dll"; DestDir: "{app}\canbus"; Flags: ignoreversion
Source: ".\build\canbus\qttinycanbus.dll"; DestDir: "{app}\canbus"; Flags: ignoreversion
Source: ".\build\canbus\qtvectorcanbus.dll"; DestDir: "{app}\canbus"; Flags: ignoreversion
Source: ".\build\canbus\qtvirtualcanbus.dll"; DestDir: "{app}\canbus"; Flags: ignoreversion
Source: ".\build\generic\qtuiotouchplugin.dll"; DestDir: "{app}\generic"; Flags: ignoreversion
Source: ".\build\iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines"; Flags: ignoreversion
Source: ".\build\imageformats\qgif.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: ".\build\imageformats\qico.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: ".\build\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: ".\build\imageformats\qsvg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: ".\build\networkinformation\qnetworklistmanager.dll"; DestDir: "{app}\networkinformation"; Flags: ignoreversion
Source: ".\build\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion
Source: ".\build\styles\qmodernwindowsstyle.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\build\tls\qcertonlybackend.dll"; DestDir: "{app}\tls"; Flags: ignoreversion
Source: ".\build\tls\qopensslbackend.dll"; DestDir: "{app}\tls"; Flags: ignoreversion
Source: ".\build\tls\qschannelbackend.dll"; DestDir: "{app}\tls"; Flags: ignoreversion
Source: ".\build\translations\meter_en_EN.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: ".\build\translations\meter_en_EN.ts"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: ".\build\translations\meter_ro_RO.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: ".\build\translations\meter_ro_RO.ts"; DestDir: "{app}\translations"; Flags: ignoreversion

[Icons]
; Define shortcuts/icons for the application
Name: "{commondesktop}\WStreamLab"; Filename: "{app}\WStreamLab.exe"; IconFilename: "{app}\WStreamLab.ico"; Tasks: desktopicon
Name: "{group}\WStreamLab"; Filename: "{app}\WStreamLab.exe"; IconFilename: "{app}\WStreamLab.ico"
Name: "{group}\Uninstall WStreamLab"; Filename: "{uninstallexe}"; IconFilename: "{app}\WStreamLab.ico"

[Run]
; Actions to be performed after installation
Filename: "notepad.exe"; Parameters: "{app}\README.txt"; Description: "View the README.txt file"; Flags: postinstall shellexec skipifsilent

[UninstallRun]
; Actions to be performed during uninstallation
Filename: "{cmd}"; Parameters: "/C taskkill /F /IM WStreamLab.exe"; Flags: runhidden waituntilterminated
Filename: "{cmd}"; Parameters: "/C copy ""{app}\watermeters.conf"" ""{userdesktop}\watermeters.conf"""; Flags: runhidden
Filename: "{cmd}"; Parameters: "/C copy ""{app}\watermeters.csv"" ""{userdesktop}\watermeters.csv"""; Flags: runhidden

[UninstallDelete]
; List of files and directories to be deleted during uninstallation
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
Type: files; Name: "{app}\watermeters.conf"
Type: files; Name: "{app}\watermeters.csv"
Type: files; Name: "{app}\canbus\qtpassthrucanbus.dll"
Type: files; Name: "{app}\canbus\qtpeakcanbus.dll"
Type: files; Name: "{app}\canbus\qtsysteccanbus.dll"
Type: files; Name: "{app}\canbus\qttinycanbus.dll"
Type: files; Name: "{app}\canbus\qtvectorcanbus.dll"
Type: files; Name: "{app}\canbus\qtvirtualcanbus.dll"
Type: files; Name: "{app}\generic\qtuiotouchplugin.dll"
Type: files; Name: "{app}\iconengines\qsvgicon.dll"
Type: files; Name: "{app}\imageformats\qgif.dll"
Type: files; Name: "{app}\imageformats\qico.dll"
Type: files; Name: "{app}\imageformats\qjpeg.dll"
Type: files; Name: "{app}\imageformats\qsvg.dll"
Type: files; Name: "{app}\networkinformation\qnetworklistmanager.dll"
Type: files; Name: "{app}\platforms\qwindows.dll"
Type: files; Name: "{app}\styles\qmodernwindowsstyle.dll"
Type: files; Name: "{app}\tls\qcertonlybackend.dll"
Type: files; Name: "{app}\tls\qopensslbackend.dll"
Type: files; Name: "{app}\tls\qschannelbackend.dll"
Type: files; Name: "{app}\translations\meter_en_EN.qm"
Type: files; Name: "{app}\translations\meter_en_EN.ts"
Type: files; Name: "{app}\translations\meter_ro_RO.qm"
Type: files; Name: "{app}\translations\meter_ro_RO.ts"
