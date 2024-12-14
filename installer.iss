﻿; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!
; !!! This file must be UTF-8 with BOM !!!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; TODO: Update the version numbers
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#define MyAppName        "VeySicK"
#define MyAppVersion     "0.5.2"
#define MyAppCompanyName "Katayama Hirofumi MZ"
#define MyAppCopyright   "(C) 2015-2024 katahiromz"
#define MyAppURL         "https://katahiromz.fc2.page/veysick"
#define MyAppDescription "Virtual BASIC Environment"

AppId={{E7F9F350-FC50-43D9-A3AA-F7475D64258F}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppCompanyName}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
DisableDirPage=no
AllowNoIcons=yes
LicenseFile=LICENSE.txt
OutputDir=.
OutputBaseFilename={#MyAppName}-{#MyAppVersion}-setup
SetupIconFile=res\Icon_100.ico
Compression=lzma
SolidCompression=yes
UninstallDisplayIcon={app}\{#MyAppName}.exe
UsePreviousAppDir=yes
VersionInfoCompany={#MyAppCompanyName}
VersionInfoCopyright={#MyAppCopyright}
VersionInfoDescription={#MyAppDescription}
VersionInfoProductName={#MyAppName}
VersionInfoProductTextVersion={#MyAppVersion}
VersionInfoProductVersion={#MyAppVersion}
VersionInfoVersion={#MyAppVersion}

[Languages]
Name: "english"; MessagesFile:  "compiler:Default.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

[Files]
Source: "README.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "LICENSE.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "HISTORY.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "VeySicK.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "doc-ja\veysick-maten-manual-ja.pdf"; DestDir: "{app}"; Flags: ignoreversion
Source: "drive0\00README.txt"; DestDir: "{app}\drive0"; Flags: ignoreversion
Source: "drive1\@load.v1"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\@load.v2"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\00README.txt"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ABS.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\AKCNV_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ANIMAL.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ASC.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ASC2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ATN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ATN2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ATTR_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\BADLINENO.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\BEEP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\BEEP2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\BLOAD98.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\BSAVE0.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\BSAVE1.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\BSAVE2.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\BSAVE3.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\BSAVE98.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CALL.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CDBL.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CHAIN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CHAIN_MERGE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CHAIN_WRITE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CHR_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CHR_2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CINT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CINT2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CIRCLE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CIRCLE2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CIRCLE98.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CLEAR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CLOSE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CLS.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_BGM.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_CLS.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_OUTM.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_PAL.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_PLAY.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_SING.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_SOUND.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_STOPM.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_TEXT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_TURTLE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_VOICE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_VOICE_COPY.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_VOICE_LFO.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CMD_VOICE_REG.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\COLOR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\COLOR_EQUAL.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\COLORAT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\COLORAT2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\COM.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\COMMON.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CONSOLE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CONT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\COPY.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\COS.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\COS2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CSNG.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CSRLIN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CSRLIN2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\CVICVSCVD.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA1.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA2.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA3.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA4.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA5.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA9.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATA10.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DATE_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DEF.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DEF_FN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DEF_FN2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DEF_USR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DELETE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DIM.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DRAW.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DSKF.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DSKI_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\DSKO_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\END.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\END2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\EOF.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ERASE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ERL_ERR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ERROR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\EXP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\FDATA.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\FIELD.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\FIX.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\FOR_NEXT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\FPOS.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\FRE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\GET.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\GETAT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\GETAT2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\GOSUB_RETURN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\GOTO.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\GOTO2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\HELP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\HEX_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\HEX_2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\IF_THEN_ELSE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INKEY_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INP88.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INP98.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INPUT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INPUT_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INPUT_2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INPUT_SHARP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INPUT_SHARP2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INPUT_WAIT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INSTR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INSTR2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\INT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KACNV_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KACNV_2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KEY.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KILL.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KINPUT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KINPUT2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KINSTR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KINSTR2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KLEN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KMID_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KPLOAD.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\KPOS.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LEFT_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LEFT_2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LEN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LEN2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LET.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LINE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LINE_INPUT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LINE_INPUT_SHARP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LINE_INPUT_SHARP2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LINE_INPUT_WAIT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LINE_INPUT2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LINE2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LINE98.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LIST.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LOC.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LOC2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LOCATE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LOF.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LOG.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LPOS.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LRDATA.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\LSET_RSET.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MAP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MERGEPROG.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MERGEPROG2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MID_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MID_2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MID_3.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MISS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MKIMKSMKD.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MOTOR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\MOUSE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\NAME.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\NEW.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\NEWDATA9.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\OCT_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_COM.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_ERROR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_ERROR2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_GOSUB.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_GOTO.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_HELP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_KEY.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_KEY2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_MOUSE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_PEN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_STOP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ON_TIME_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\OPEN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\OPTION_BASE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\OUT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PAINT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PAINT2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PAINT3.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PEEK88.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PLAY.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\POINT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\POINT2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\POINT3.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\POKE88.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\POS.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PRESET.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PRINT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PRINT_SHARP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PRINT_SHARP_USING.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PRINT_USING.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PRINT_USING2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PSET.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PUT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PUTAT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\PUTAT2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\RANDOMIZE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\RANDOMIZE2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\RDATA.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\READ.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\REM.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\RENUM.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\RESTORE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\RESUME.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\RIGHT_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\RIGHT_2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\RND.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\ROLL.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SCREEN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SEARCH.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SGN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SIN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SPACE_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SPC.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SPC2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SPACING.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SQR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\STEST.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\STOP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\STR_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\STR_2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\STRING_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SWAP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\SWAP2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\TAB.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\TAB2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\TAN.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\TDATA.DAT"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\TIME_.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\TRON.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\TRON2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\VAL.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\VAL2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\VARPTR.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\VARPTR88.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\VIEW.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\VIEW2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WAIT88.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WAIT98.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WHILE_WEND.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WHILE_WEND2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WIDTH.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WIDTH_LPRINT.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WIDTH_LPRINT2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WINDOW.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WINDOW2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WRITE.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WRITE_SHARP.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WRITE_SHARP2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive1\WRITE2.BAS"; DestDir: "{app}\drive1"; Flags: ignoreversion
Source: "drive2\00README.txt"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\BLOCK88.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\BUBBLE.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\DICE.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\DBLBUF98.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\DRAW.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\DRAW.png"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\DRAW.TXT"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\FRACTAL98.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\IMGEDIT.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\IMGGET.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\IMGLOAD.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\INRYOKU.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\JANKEN.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\KUKU.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\MANDEL98.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\MAZE.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\NUMBER.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\SAISEI98.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\SAISEI98.TXT"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\SHOOT.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\SHOOT.TXT"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\SLOT.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\BINGO.BAS"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive2\BINGO.TXT"; DestDir: "{app}\drive2"; Flags: ignoreversion
Source: "drive3\S39.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\00README.txt"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S01.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S02.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S03.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S04.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S05.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S06.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S07.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S08.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S09.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S10.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S11.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S12.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S13.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S14.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S15.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S16.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S17.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S18.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S19.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S20.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S21.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S22.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S23.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S24.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S25.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S26.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S27.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S28.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S29.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S30.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S31.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S32.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S33.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S34.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive3\S35.BAS"; DestDir: "{app}\drive3"; Flags: ignoreversion
Source: "drive4\ANK88.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\ANK98.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\BOX.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\CIRCLE.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\CIRCLE2.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\CIRCLE3.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\CSNG.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\e1.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\e2.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\e3.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\FILEOP1.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\FILEOP2.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\k1.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\KUKU.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\LINE.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\MAP.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\MOGURA.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\p1.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\PAINT.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\PAINT2.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\PANK88.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\PANK98.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\POINT.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\PRINT.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\PRINT2.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\PRINT3.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\PSET.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\SEMIGRA98.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\SUB.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\SUB2.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\TOKEI.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\TRI.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\TRI2.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\TURTLE.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\TVRAM1-88.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\TVRAM2-88.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\VAR.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\VIEW.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\WINDOW.BAS"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\00README.txt"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\a1.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\a2.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\a3.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\a4.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive4\a5.bas"; DestDir: "{app}\drive4"; Flags: ignoreversion
Source: "drive5\WORDTEST.TXT"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\00README.txt"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\MUSIC-C2.BAS"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\MUSIC-C2.TXT"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\MUSIC-C2.UTY"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\NAN.BAS"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\NAN.TXT"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\NGEN.BAS"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\NGEN.TXT"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\OTHELO.BAS"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\OTHELO.TXT"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\STARTREK.BAS"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\STARTREK.TXT"; DestDir: "{app}\drive5"; Flags: ignoreversion
Source: "drive5\WORDTEST.BAS"; DestDir: "{app}\drive5"; Flags: ignoreversion

[Icons]
Name: "{group}\VeySicK"; Filename: "{app}\VeySicK.exe"
Name: "{group}\{cm:ReadMe}"; Filename: "{app}\README.txt"
Name: "{group}\{cm:License}"; Filename: "{app}\LICENSE.txt"
Name: "{group}\{cm:History}"; Filename: "{app}\HISTORY.txt"
Name: "{group}\{cm:Manual}"; Filename: "{app}\veysick-maten-manual-ja.pdf"
Name: "{group}\{cm:ProgramOnTheWeb,VeySicK}"; Filename: "https://katahiromz.fc2.page/veysick"
Name: "{group}\{cm:UninstallProgram,VeySicK}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\VeySicK"; Filename: "{app}\VeySicK.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\VeySicK.exe"; Description: "{cm:LaunchProgram,VeySicK}"; Flags: nowait postinstall skipifsilent

[Registry]
Root: HKCU; Subkey: "Software\Katayama Hirofumi MZ\VeySicK"; Flags: deletekey uninsdeletekey

[CustomMessages]
english.ReadMe=ReadMe
english.License=License
english.History=History
english.Manual=Manual (PDF)
japanese.ReadMe=ReadMe
japanese.License=ライセンス
japanese.History=開発履歴
japanese.Manual=マニュアル (PDF)
