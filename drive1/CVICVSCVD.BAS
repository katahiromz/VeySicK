100 ' CVI/CVS/CVD sample
110 OPEN "RDATA.DAT" AS #1
120 FIELD #1, 2 AS D1$, 4 AS D2$, 8 AS D3$
130 GET #1,1
140 A%=CVI(D1$)
150 B=CVS(D2$)
160 C#=CVD(D3$)
170 PRINT "A =";A%
180 PRINT "B =";B
190 PRINT "C =";C#
200 CLOSE
210 END
