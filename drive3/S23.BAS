100 LINE INPUT "������ � ��� ��޻� ";A$
110 IF A$="" THEN 190
120 B$=""
130 FOR I=1 TO LEN(A$)
140  D$=MID$(A$,I,1):D=ASC(D$)
150  IF D>=97 AND D<=122 THEN D$=CHR$(D-32)
160  B$=B$+D$
170 NEXT I
180 PRINT:PRINT B$
190 END
