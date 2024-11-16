100 ' KINPUT サンプル {SJIS}
110 CLS
120 LOCATE 0,0  : PRINT "日本語を入力してください。"
130 LOCATE 30,0 : KINPUT A$
140 LOCATE 0,2  : PRINT "入力した日本語は「";A$;"」です。"
