100 ' COS sample
110 SCREEN 2
120 CLS 3
130 PI=3.14159:D=PI/180
140 LINE(0,50)-(360,50)
150 LOCATE 0,2
160 PRINT "0";TAB(11);"1/2";TAB(22);"1";TAB(34);"3/2";TAB(46);"2"
170 FOR I=0 TO 360
180  S=SIN(I*D):C=COS(I*D)
190  SY=CINT(50-S*50)
200  CY=CINT(50-C*50)
210  PSET(I,SY):PSET(I,CY)
220 NEXT
