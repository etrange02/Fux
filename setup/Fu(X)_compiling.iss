; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!
          
#define TODAY_DOT GetDateTimeString('yy/mm/dd', '.', '')
#define TODAY     GetDateTimeString('yyyymmdd', '', '')

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId              = {{B3473793-E9EE-4923-9E8D-0CD6311484EA}
AppName            = Fu(X) 2.0
AppVersion         = {#TODAY_DOT}
VersionInfoVersion = 0.0.0.0
AppPublisher       = David Lecoconnier 
DefaultDirName     = {pf}\Fu(X)
DefaultGroupName   = Fu(X) 2.0
AllowNoIcons       = yes
OutputDir          = builds\{#TODAY}
OutputBaseFilename = Fu(X)_2.0_{#TODAY}
SetupIconFile      = ..\out\program_files\lib\play.ico
Compression        = lzma
SolidCompression   = yes
PrivilegesRequired = admin
WizardImageStretch = no
VersionInfoCompany = David Lecoconnier 

[InstallDelete]       
Type: files; Name: "{app}\Fu(X) 2.0.exe"
Type: files; Name: "{app}\Fu(X) 2.exe"   
Type: files; Name: "{app}\Fu(X)_2.exe"
Type: files; Name: "{app}\lib\suppr2.png"

[Languages]
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
;Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"
; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"
; Flags: unchecked
Name:AssocierExtensions; Description: Lecteur par d�faut (mp3, wav, ogg, wma)

[Dirs]
Name: "{userappdata}\Fu(X)"; Flags: uninsneveruninstall

[Files]
Source: "..\out\program_files\*"; Excludes: "\lib\play.png"; DestDir: "{app}";               Flags: recursesubdirs createallsubdirs ignoreversion
Source: "..\out\app_data\*";      Excludes: "\Fu(X).conf";   DestDir: "{userappdata}\Fu(X)"; Flags: recursesubdirs createallsubdirs uninsneveruninstall
; Source: "..\Web\*"; DestDir: "{app}\Web"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Fu(X) 2.0";                                                Filename: "{app}\Fu(X).exe"; WorkingDir: "{app}"
Name: "{group}\{cm:UninstallProgram,Fu(X) 2.0}";                          Filename: "{uninstallexe}"
;Name: "{commondesktop}\Fu(X) 2.0";                                        Filename: "{app}\Fu(X).exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Fu(X) 2.0"; Filename: "{app}\Fu(X).exe"; Tasks: quicklaunchicon
Name: "{userdesktop}\Fu(X) 2.0";                                          Filename: "{app}\Fu(X).exe"; WorkingDir: "{app}"; IconFilename: "{app}\lib\play.ico"

[Registry]
Root: HKCR; Subkey: ".mp3";                                  ValueType: string; ValueName: ""; ValueData: "Fu(X).mp3";                  Flags: uninsdeletevalue; Tasks : AssocierExtensions
Root: HKCR; Subkey: "Fu(X).mp3";                             ValueType: string; ValueName: ""; ValueData: "Fichier Audio MP3";          Flags: uninsdeletekey
Root: HKCR; Subkey: "Fu(X).mp3\shell\open\command";          ValueType: string; ValueName: ""; ValueData: """{app}\Fu(X).exe"" ""%1"""
Root: HKCR; Subkey: "Fu(X).mp3\DefaultIcon";                 ValueType: string; ValueName: ""; ValueData: """{app}\lib\icone_mp3.ico"""
Root: HKCR; Subkey: "Fu(X).mp3\shell\PlayWithFu(X)";         ValueType: string; ValueName: ""; ValueData: "Lire avec Fu(X) 2.0"
Root: HKCR; Subkey: "Fu(X).mp3\shell\PlayWithFu(X)\command"; ValueType: string; ValueName: ""; ValueData: """{app}\Fu(X).exe"" ""%1"""

Root: HKCR; Subkey: ".wav";                                  ValueType: string; ValueName: ""; ValueData: "Fu(X).wav";                  Flags: uninsdeletevalue; Tasks : AssocierExtensions
Root: HKCR; Subkey: "Fu(X).wav";                             ValueType: string; ValueName: ""; ValueData: "Fichier Audio WAV";          Flags: uninsdeletekey
Root: HKCR; Subkey: "Fu(X).wav\shell\open\command";          ValueType: string; ValueName: ""; ValueData: """{app}\Fu(X).exe"" ""%1"""
Root: HKCR; Subkey: "Fu(X).wav\DefaultIcon";                 ValueType: string; ValueName: ""; ValueData: """{app}\lib\icone_wav.ico"""
Root: HKCR; Subkey: "Fu(X).wav\shell\PlayWithFu(X)";         ValueType: string; ValueName: ""; ValueData: "Lire avec Fu(X) 2.0"
Root: HKCR; Subkey: "Fu(X).wav\shell\PlayWithFu(X)\command"; ValueType: string; ValueName: ""; ValueData: """{app}\Fu(X).exe"" ""%1"""

Root: HKCR; Subkey: ".ogg";                                  ValueType: string; ValueName: ""; ValueData: "Fu(X).ogg";                  Flags: uninsdeletevalue; Tasks : AssocierExtensions
Root: HKCR; Subkey: "Fu(X).ogg";                             ValueType: string; ValueName: ""; ValueData: "Fichier Audio OGG";          Flags: uninsdeletekey
Root: HKCR; Subkey: "Fu(X).ogg\shell\open\command";          ValueType: string; ValueName: ""; ValueData: """{app}\Fu(X).exe"" ""%1"""
Root: HKCR; Subkey: "Fu(X).ogg\DefaultIcon";                 ValueType: string; ValueName: ""; ValueData: """{app}\lib\icone_ogg.ico"""
Root: HKCR; Subkey: "Fu(X).ogg\shell\PlayWithFu(X)";         ValueType: string; ValueName: ""; ValueData: "Lire avec Fu(X) 2.0"
Root: HKCR; Subkey: "Fu(X).ogg\shell\PlayWithFu(X)\command"; ValueType: string; ValueName: ""; ValueData: """{app}\Fu(X).exe"" ""%1"""

[Run]
Filename: "{app}\Fu(X).exe"; Description: "{cm:LaunchProgram,Fu(X) 2.0}"; Flags: nowait postinstall skipifsilent

