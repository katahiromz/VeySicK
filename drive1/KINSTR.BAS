100 ' KINSTR サンプル {SJIS}
110 PRINT "漢字を含む文字列を１つ入力してください";:KINPUT K1$
120 PRINT "漢字を含む文字列をもう一つ入力してください";:KINPUT K2$
130 PRINT KINSTR(K1$,K2$)
