100 ' RIGHT$ sample
A$="ABCDEFGHIJ"
FOR I=1 TO LEN(A$)
  B$=RIGHT$(A$,I)
  PRINT B$
NEXT I
