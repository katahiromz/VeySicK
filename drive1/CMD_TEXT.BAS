100 ' CMD TEXT ON/OFF sample
110 SCREEN 0,0:CLS 3
120 CIRCLE(320,100),100,2
130 PAINT(320,100),2,2
140 CMD TEXT ON
150 PRINT "*";:IF INKEY$="" THEN 150 ELSE CMD TEXT OFF
160 PRINT "*";:IF INKEY$="" tHEN 160 ELSE 140
170 END
