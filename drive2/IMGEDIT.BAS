' IMAGE EDITOR {9801} {DELAY2:2}
'--------------------------------------------------------------------------
*INIT
SCREEN 3,0:CONSOLE 0,25,0,1:COLOR 7,0:WIDTH 80,25:CLS 3
W=20:H=20
PX=400:PY=100
COL=7
CX=0:CY=0
CELLW=16:CELLH=16
MODE=0
DEF FNX(X)=CELLW*(X+1):DEF FNY(Y)=CELLH*(Y+1)
DEF FNPX(X)=PX+X:DEF FNPY(Y)=PY+Y
BYTES=((W+7)\8)*H*3+4
IND=BYTES\2+1
DIM DAT%(IND)
'--------------------------------------------------------------------------
GOSUB *DOSTART
'--------------------------------------------------------------------------
*MENU
CLS
LOCATE 0,22
PRINT "[0-7]:Set Color, [Space]:Set Pixel, [L]:Line, [B]: Box, "
PRINT "[F]: Box Fill, [C]: Clear All, [Z]:Set Size, [S]: Save, [Q]: Quit"
IF (INP(&H06) AND 1)=0 THEN COL=0:GOSUB *SETCOLOR
IF (INP(&H06) AND 2)=0 THEN COL=1:GOSUB *SETCOLOR
IF (INP(&H06) AND 4)=0 THEN COL=2:GOSUB *SETCOLOR
IF (INP(&H06) AND 8)=0 THEN COL=3:GOSUB *SETCOLOR
IF (INP(&H06) AND 16)=0 THEN COL=4:GOSUB *SETCOLOR
IF (INP(&H06) AND 32)=0 THEN COL=5:GOSUB *SETCOLOR
IF (INP(&H06) AND 64)=0 THEN COL=6:GOSUB *SETCOLOR
IF (INP(&H06) AND 128)=0 THEN COL=7:GOSUB *SETCOLOR
IF (INP(&H09) AND 64)=0 THEN GOSUB *DOSPACE
IF (INP(&H02) AND 8)=0 THEN GOSUB *CLEARALL:GOSUB *WAITKEYUP
IF (INP(&H03) AND 16)=0 THEN GOSUB *DOLINE:GOSUB *WAITKEYUP
IF (INP(&H02) AND 4)=0 THEN GOSUB *DOBOX:GOSUB *WAITKEYUP
IF (INP(&H02) AND 64)=0 THEN GOSUB *DOBOXFILL:GOSUB *WAITKEYUP
IF (INP(&H05) AND 4)=0 THEN GOSUB *SETSIZE:GOSUB *WAITKEYUP
IF (INP(&H04) AND 8)=0 THEN GOSUB *DOSAVE:GOSUB *WAITKEYUP
IF (INP(&H04) AND 2)=0 THEN GOSUB *QUERYEXIT
IF (INP(&H0A) AND 4)=0 THEN GOSUB *MOVELEFT
IF (INP(&H08) AND 4)=0 THEN GOSUB *MOVERIGHT
IF (INP(&H08) AND 2)=0 THEN GOSUB *MOVEUP
IF (INP(&H0A) AND 2)=0 THEN GOSUB *MOVEDOWN
GOTO *MENU
'--------------------------------------------------------------------------
*QUERYEXIT
INPUT "Quit (Y/N)";Q$
IF LEN(Q$)=0 THEN RETURN
Q$=LEFT$(Q$,1)
IF Q$="Y" OR Q$="y" THEN END
RETURN
'--------------------------------------------------------------------------
*WAITKEYUP
IF INKEY$<>"" GOTO *WAITKEYUP
RETURN
'--------------------------------------------------------------------------
*DOSTART
CLS 3
LOCATE 0,0:PRINT "IMAGE EDITOR";
GOSUB *DRAWGRID
GOSUB *SETCOLOR
GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*GETPIXEL
PIX=POINT(PX+X,PY+Y)
RETURN
'--------------------------------------------------------------------------
*SETPIXEL
LINE(FNX(X)+1,FNY(Y)+1)-(FNX(X+1)-1,FNY(Y+1)-1),PIX,BF
PSET(FNPX(X),FNPY(Y)),PIX
RETURN
'--------------------------------------------------------------------------
*SETCOLOR
LINE(395,295)-(421,321),7,B
LINE(400,300)-(416,316),COL,BF
RETURN
'--------------------------------------------------------------------------
*DRAWGRID
FOR Y=0 TO H:LINE(CELLW*1,CELLH*(Y+1))-(CELLW*(W+1),CELLH*(Y+1)):NEXT Y
FOR X=0 TO W:LINE(CELLW*(X+1),CELLH*1)-(CELLW*(X+1),CELLH*(H+1)):NEXT X
RETURN
'--------------------------------------------------------------------------
*DRAWCELLS
FOR Y=0 TO H
FOR X=0 TO W
PIX=POINT(PX+X,PY+Y)
GOSUB *SETPIXEL
NEXT X,Y
RETURN
'--------------------------------------------------------------------------
*DRAWCARET
C=7-PIX
IF C=PIX THEN C=7
LINE(FNX(CX)+CELLW/2,FNY(CY)+1)-(FNX(CX)+CELLW/2,FNY(CY)+CELLH-1),C
LINE(FNX(CX)+1,FNY(CY)+CELLH/2)-(FNX(CX)+CELLW-1,FNY(CY)+CELLH/2),C
RETURN
'--------------------------------------------------------------------------
*MOVELEFT
X=CX:Y=CY
GOSUB *GETPIXEL
GOSUB *SETPIXEL
IF CX>0 THEN CX=CX-1
X=CX:Y=CY
GOSUB *GETPIXEL
GOSUB *SETPIXEL
GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*MOVERIGHT
X=CX:Y=CY
GOSUB *GETPIXEL
GOSUB *SETPIXEL
IF CX+1<W THEN CX=CX+1
X=CX:Y=CY
GOSUB *GETPIXEL
GOSUB *SETPIXEL
GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*MOVEUP
X=CX:Y=CY
GOSUB *GETPIXEL
GOSUB *SETPIXEL
IF CY>0 THEN CY=CY-1
X=CX:Y=CY
GOSUB *GETPIXEL
GOSUB *SETPIXEL
GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*MOVEDOWN
X=CX:Y=CY
GOSUB *GETPIXEL
GOSUB *SETPIXEL
IF CY+1<H THEN CY=CY+1
X=CX:Y=CY
GOSUB *GETPIXEL
GOSUB *SETPIXEL
GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*DRAWALLPIXEL
FOR Y=0 TO H-1
FOR X=0 TO W-1
GOSUB *GETPIXEL
GOSUB *SETPIXEL
NEXT X,Y
RETURN
'--------------------------------------------------------------------------
*CLEARALL
LINE(FNPX(0),FNPY(0))-(FNPX(W-1),FNPY(H-1)),COL,BF
GOSUB *DRAWALLPIXEL
GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*DOSPACE
PIX=COL:X=CX:Y=CY:GOSUB *SETPIXEL:GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*DOLINE
IF SETLINE=0 THEN BX=CX:BY=CY:SETLINE=1:RETURN
LINE(FNPX(BX),FNPY(BY))-(FNPX(CX),FNPY(CY)),COL
SETLINE=0
GOSUB *DRAWALLPIXEL
GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*DOBOX
IF SETBOX=0 THEN BX=CX:BY=CY:SETBOX=1:RETURN
LINE(FNPX(BX),FNPY(BY))-(FNPX(CX),FNPY(CY)),COL,B
SETBOX=0
GOSUB *DRAWALLPIXEL
GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*DOBOXFILL
IF SETBOXFILL=0 THEN BX=CX:BY=CY:SETBOXFILL=1:RETURN
LINE(FNPX(BX),FNPY(BY))-(FNPX(CX),FNPY(CY)),COL,BF
SETBOXFILL=0
GOSUB *DRAWALLPIXEL
GOSUB *DRAWCARET
RETURN
'--------------------------------------------------------------------------
*SETSIZE
CLS
LOCATE 0,22
INPUT "Width (1-20)";W0
IF W0<=0 OR 20<W0 THEN RETURN
INPUT "Height (1-20)";H0
IF H0<=0 OR 20<H0 THEN RETURN
CLS 3
W=W0:H=H0
GOSUB *DOSTART
RETURN
'--------------------------------------------------------------------------
*DOSAVE
BYTES=((W+7)\8)*H*3+4
IND=BYTES\2+1
ERASE DAT%
DIM DAT%(IND)
GET@(FNPX(0),FNPY(0))-(FNPX(W-1),FNPY(H-1)),DAT%
CLS
LOCATE 0,22
INPUT "File name";FIL$
OPEN FIL$ FOR OUTPUT AS #1
F=0:LN=1000
LN$=RIGHT$(STR$(LN),LEN(STR$(LN))-1)
LN$=LN$+" ' image"+STR$(W)+" x"+STR$(H)+" DIM DAT%("+STR$(IND)+")"
PRINT #1,LN$
LN=LN+10
LN$=""
FOR I=0 TO IND
IF F=0 THEN LN$=RIGHT$(STR$(LN),LEN(STR$(LN))-1)+" DATA " ELSE LN$=LN$+","
LN$=LN$+"&H"+RIGHT$("000"+HEX$(DAT%(I)),4)
F=F+1
IF F=8 THEN F=0:PRINT #1,LN$:LN$="":LN=LN+10
NEXT I
IF F<>0 THEN F=0:PRINT #1,LN$:LN$="":LN=LN+10
CLOSE #1
RETURN
''--------------------------------------------------------------------------
