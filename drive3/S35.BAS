100 A0$="��ʊ���ABC" ' {SJIS}
110 PRINT A0$
120 K0$=AKCNV$(A0$)
130 PRINT K0$
140 K1$=KMID$(K0$,1,4)+KMID$(K0$,7,4)
150 PRINT K1$
160 A1$=KACNV$(K1$)
170 PRINT A1$
