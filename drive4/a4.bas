100 SCREEN 3
110 A$ = ""
120 WHILE A$ <> "q"
130   CLS 3
140   FOR X = 0 TO 200 STEP 1
150     CLS 2
160     Y = X / 2
170     Y = Y + 16:PUT(X, Y), KANJI(VAL("&H"+JIS$("‚³"))), PSET, 4, 0
180     Y = Y + 16:PUT(X, Y), KANJI(VAL("&H"+JIS$("‚µ"))), PSET, 5, 0
190     Y = Y + 16:PUT(X, Y), KANJI(VAL("&H"+JIS$("‚·"))), PSET, 6, 0
200     WAIT &HA0, &H20, &H20: WAIT &HA0, &H20 '--- V-sync
210   NEXT
220   PRINT "Push any key or 'q' key"
230   A$ = INPUT$(1)
240 WEND
