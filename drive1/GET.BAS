100 ' GET sample
110 OPEN "ADDRESS.DAT" AS #1
120 FIELD #1, 30 AS A$, 20 AS B$, 50 AS C$
130 FOR I=1 TO LOF(1)
140  GET #1,I
150  PRINT "NAME",A$
160  PRINT "TEL",B$
170  PRINT "ADDRESS",C$
180 NEXT I
190 CLOSE:END
