100 ' HEX$ sample
110 PRINT "    -0 -1 -2 -3 -4 -5 -6 -7 -8 -9"
120 FOR I=0 TO 9
130  PRINT STR$(I);"- ";
140  FOR J=0 TO 9
150   PRINT RIGHT$("0"+HEX$(I*10+J),2);" ";
160  NEXT J
170  PRINT
180 NEXT I
190 END
