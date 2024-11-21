100 '------------------------------------------------------------
110 ' Palette for NL,XL-BASIC,N88-BASIC
120 '
130 ' Alt+5
140 '------------------------------------------------------------
150 SCREEN 0: CLS 3
160 WINDOW(0,0)-(639,399)
170 C = 2
180 S = 3
190 FOR Y=10 TO 199 STEP S
200   LINE(0, 200 - Y)-(639, 200 - Y), C
210   LINE(0, 200 + Y)-(639, 200 + Y), C
220   C = C + 1
230   IF C > 7 THEN C = 2
240   S = S + 0.2
250 NEXT
260 FOR X=10 TO 319 STEP 20
270   LINE(320 + X, 190)-(320 + X * 8,   0), 1
280   LINE(320 - X, 190)-(320 - X * 8,   0), 1
290   LINE(320 + X, 210)-(320 + X * 8, 399), 1
300   LINE(320 - X, 210)-(320 - X * 8, 399), 1
310 NEXT
320 PRINT "Push any key or 'q' key"
330 A$ = ""
340 WHILE A$ <> "q"
350   A$ = ""
360   WHILE A$ = ""
370     FOR I=2 TO 7
380       FOR S=2 TO 7
390         IF S = I THEN C = 1 ELSE C = 0
400         COLOR=(S, C)
410       NEXT
420 '      WAIT &HA0,&H20,&H20:WAIT &HA0,&H20 '--- Vsync  (PC-9801)
430 '      WAIT &H40,&H20,&H20:WAIT &H40,&H20 '--- Vblank (PC-8801)
440       FOR K=0 TO 1000:NEXT
450     NEXT
460     A$ = INKEY$
470   WEND
480   IF A$ <> "q" THEN COLOR: A$ = INPUT$(1)
490 WEND
