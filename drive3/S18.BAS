100 SCREEN 0,0:CLS 3
110 XD=40:YD=20
120 BYTE=((XD+7)\8)*YD*3+4
130 FACT=BYTE\2+1
140 DIM G%(FACT)
150 LINE(0,0)-STEP(XD-1,YD-1),1,B
160 CIRCLE(XD/2-1,YD/2-1),YD/2,2
170 GET(0,0)-STEP(XD-1,YD-1),G%
180 FOR X=0 TO 500 STEP 100
190  PUT(X,100),G%
200 NEXT
