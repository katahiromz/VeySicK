100 ' KMID$ サンプル {SJIS}
A$="ABC漢字とDEF日本語"
B$=KMID$(A$,4,3)+KMID$(A$,10,3)
C$=KMID$(A$,1,3)+KMID$(A$,7,3)
PRINT A$;" ---> ";B$;" + ";C$
