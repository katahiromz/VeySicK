100 OPEN "RDATA.DAT" AS #1
110 FIELD #1, 2 AS A$, 4 AS B$, 8 AS C$
120 PRINT "ϴ � ��۸��� �� ������ �ް� �"
130 PRINT "���޼Ͻ"
140 GET #1
150 A%=CVI(A$)
160 A!=CVS(B$)
170 A#=CVD(C$)
180 PRINT A%:PRINT A!:PRINT A#
190 CLOSE:END
