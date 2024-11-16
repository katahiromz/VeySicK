100 ' KINSTR サンプル {SJIS}
110 CLS
120 M$="中森明菜,石川秀美,菊池桃子,本田美奈子"
130 INPUT "お名前は ";N$
140 F=KINSTR(M$,N$)
150 PRINT
160 IF F=0 THEN PRINT "はじめまして ";N$;" さん"
170 IF F<>0 THEN PRINT "ようこそ ";N$;" さん"
