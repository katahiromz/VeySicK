100 T1$ = CHR$(&HF0)+CHR$(&H00)+CHR$(&H00)
110 T2$ = CHR$(&H55)+CHR$(&HFF)+CHR$(&H55)
120 SCREEN 3: CLS 3
130 LINE(10,5)-(629,10), 6, BF, T1$
140 LINE(10,5)-(629,10), 0, B , &HFF00
150 POINT(10,20)
160 X = 80
170 Y = 160
180 A$ = "c6y&hf0f0;d100e100y&hffff;z5z=t1$;t=x;,=y;q200,100bf40z=t2$;p6"
190 DRAW "a0s1x=a$;a1s0.5x=a$;a2s0.2x=a$;a3s0.1x=a$;"
