100 '-----------------------------------------------------------------------
110 ' N88-BASICでキーマトリックス 2021.12
120 '
130 ' I/O INP(A) &H00～&H0E, &HE0～&HEC
140 '
150 ' VL,NL,XL-BASICでは反応しないキーが存在します
160 '-----------------------------------------------------------------------
170 CLS
180 INPUT "0:PC-98(VL,NL-BASIC), 1:PC-8801(XL-BASIC) "; PC88
190 IF PC88 THEN RESTORE *PC8801:S = 4 ELSE RESTORE *PC9801: S = 0
200 PRINT "VL,NL,XL-BASICは反応しないキーがあります(Break/Ctrl+cで停止)"
210 SCREEN S
220 READ S, E
230 N = E - S
240 DIM K$(N)
250 READ T$
260 FOR I=0 TO N
270   READ K$(I)
280 NEXT
290 PRINT
300 PRINT "    "; T$
310 WHILE 1
320   LOCATE 0, 4
330   FOR A=S TO E
340     D    = INP(A)
350     A$   = RIGHT$("00"+HEX$(A), 2) + "  "
360     D$   = "  " + RIGHT$("00"+HEX$(D), 2)
370     MASK = &H80
380     FOR I=7 TO 0 STEP -1
390       B$ = MID$(K$(A-S), (7-I)*6+1, 5)
400       IF (D AND MASK) THEN A$ = A$ + B$ + " ": GOTO *NOPUSH
410         COLOR 0: PRINT A$;
420         COLOR 4: PRINT B$;
430         A$ = " "
440       *NOPUSH
450       MASK = MASK / 2
460     NEXT
470     A$ = A$ + D$
480     COLOR 0: PRINT A$
490   NEXT
500 WEND
510 END
520 '--- PC-9801
530 *PC9801
540 DATA &HE0, &HEC
550 DATA "7     6     5     4     3     2     1     0     "
560 DATA "NUM7  NUM6  NUM5  NUM4  NUM3  NUM2  NUM1  NUM0  "
570 DATA "ENTER NUM.  NUM,  NUM=  NUM+  NUM*  NUM9  NUM8  "
580 DATA "G     F     E     D     C     B     A     @     "
590 DATA "O     N     M     L     K     J     I     H     "
600 DATA "W     V     U     T     S     R     Q     P     "
610 DATA "-     ^     ]     \     [     Z     Y     X     "
620 DATA "7     6     5     4     3     2     1     0     "
630 DATA "_     /     .     ,     ;     :     9     8     "
640 DATA "CTRL  SHIFT ｶﾅ    GRPH  DEL   →    ↑    HOME  "
650 DATA "ESC   SPACE F5    F4    F3    F2    F1    STOP  "
660 DATA "CAPS  NUM/  NUM-  COPY  HELP  ←    ↓    TAB   "
670 DATA "                                    RLDN  RLUP  "
680 DATA "INS   F10   F9    F8    F7    F6    XFER  BS    "
690 '--- PC-8801FA
700 *PC8801
710 DATA &H00, &H0E
720 DATA "7     6     5     4     3     2     1     0     "
730 DATA "NUM7  NUM6  NUM5  NUM4  NUM3  NUM2  NUM1  NUM0  "
740 DATA "ENTER NUM,  NUM.  NUM=  NUM+  NUM*  NUM9  NUM8  "
750 DATA "G     F     E     D     C     B     A     @     "
760 DATA "O     N     M     L     K     J     I     H     "
770 DATA "W     V     U     T     S     R     Q     P     "
780 DATA "-     ^     ]     \     [     Z     Y     X     "
790 DATA "7     6     5     4     3     2     1     0     "
800 DATA "_     /     .     ,     ;     :     9     8     "
810 DATA "CTRL  SHIFT ｶﾅ    GRPH  DEL   →    ↑    HOME  "
820 DATA "ESC   SPACE F5    F4    F3    F2    F1    STOP  "
830 DATA "CAPS  NUM/  NUM-  COPY  HELP  ←    ↓    TAB   "
840 DATA "                                    RLDN  RLUP  "
850 DATA "DEL   INS   BS    F10   F9    F8    F7    F6    "
860 DATA "                        全角  PC    決定  変換  "
870 DATA "(0)                     SHIFL SHIFR NUMEN ENTER "
