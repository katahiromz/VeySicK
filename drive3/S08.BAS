100 INPUT A
110 FLG=0
120 IF A<0 THEN A=ABS(A):FLG=1
130 PRINT SQR(A);
140 IF FLG THEN PRINT "i" ELSE PRINT
150 END
