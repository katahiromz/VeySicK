100 ' KPOS Tv {SJIS} {8801}
110 CLS
120 A$="jonrΜTvkist"
130 PRINT A$
140 LOCATE 0,1:PRINT "hW      oCg"
150 FOR I=1 TO 13
160  PRINT I,KPOS(A$,I)
170 NEXT
