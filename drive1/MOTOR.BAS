100 ' MOTOR sample
110 MOTOR 1
120 PRINT "Rewind and set the tape."
130 INPUT "Are you ready (y/n)";A$
140 IF LEFT(A$,1)<>"y" AND LEFT(A$,1)<>"Y" THEN END
150 PRINT:MOTOR 0
160 PRINT "Push PLAY button."
170 INPUT "Are you ready (y/n)";A$
180 IF LEFT(A$,1)<>"y" AND LEFT(A$,1)<>"Y" THEN END
190 MOTOR
200 END
