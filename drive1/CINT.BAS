100 ' CINT sample
110 INPUT "A,D";A,D%
120 GOSUB 140
130 END
140 AD=CINT(A*10^D%+.5)/10^D%
150 PRINT A,AD
160 RETURN
