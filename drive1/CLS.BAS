100 ' CLS sample
110 SCREEN 0,0
120 GOSUB 180:BEEP:CLS 1
130 GOSUB 180:BEEP:CLS 2
140 GOSUB 180:BEEP:CLS 3
150 GOSUB 180:VIEW(200,50)-(400,150)
160 BEEP:CLS 3
170 END
180 FOR I=1 TO 20
190  FOR J=1 TO 50:PRINT "*";:NEXT J
200  LINE(0,0)-(I*30,199),7
210 NEXT I
220 RETURN
