100 ' ON MOUSE GOSUB {MS-DOS}
110 MOUSE 0
120 ON MOUSE(2) GOSUB 160:MOUSE(2) ON
130 ON MOUSE(3) GOSUB 170:MOUSE(3) ON
140 PRINT "--- ϳ� �� ���� � �د� ��� ---"
150 GOTO 150
160 PRINT "X, Y = ";MOUSE(0);MOUSE(1);" (����)":RETURN
170 PRINT "X, Y = ";MOUSE(0);MOUSE(1);" (з�)":RETURN
