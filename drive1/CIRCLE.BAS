100 ' CIRCLE sample
110 SCREEN 0,0:CLS 3
120 DATA 25,5,40,13,17
130 FOR I=1 TO 5
140  READ DAT:EN=ST+DAT/100*3.1415*2
150  CIRCLE(320,100),150,I,-ST,-EN
160  ST=EN
170 NEXT I
180 END
