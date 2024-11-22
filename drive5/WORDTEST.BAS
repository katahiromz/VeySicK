100 '-------------------------------------------------
110 '英熟語テスト・検索プログラム
120 '  ＰＣ８８０１－Ｎ８８日本語ＢＡＳＩＣ用
130 '               Ｂｅ－１
140 '-------------------------------------------------
150 *SHOKI
160 SCREEN 4:WIDTH 80,20
170 OPEN "1:DATA" AS #1
180 FIELD #1,15 AS S$,15 AS I$
190 OPEN "1:MISS" AS #2
200 FIELD #2,15 AS MS$,15 AS MI$
210 '-------------------------------------------------
220 'メニュー
230 '-------------------------------------------------
240 *MENU
250 CLS
260 LOCATE 25,1:PRINT "英熟語テスト・検索プログラム"
270 LOCATE 30,3:PRINT "１－－テスト"
280 LOCATE 30,5:PRINT "２－－検  索"
290 LOCATE 30,7:PRINT "３－－登　録、削　除、変　更"
300 LOCATE 30,9:PRINT "４－－結果報告"
310 LOCATE 30,11:PRINT "５－－データ一覧"
320 LOCATE 30,13:PRINT "６－－終了"
330 INPUT "どれを行いますか";D
340 IF D=1 THEN *TEST
350 IF D=2 THEN *KENSAKU
360 IF D=3 THEN *TOUROKU
370 IF D=4 THEN *HOUKOKU
380 IF D=5 THEN *ITIRAN
390 IF D=6 THEN *SHURYOU
400 '-------------------------------------------------
410 'テスト　
420 '-------------------------------------------------
430 *TEST
440 INPUT "順番＝１、ランダム＝２";Q
450 IF Q=1 THEN *ZYUN ELSE *RAMDOM
460 *ZYUN
470 S=0:M=0
480 FOR I=1 TO LOF(1)
490 GET #1,I
500 CLS
510 PRINT "スペル－－";S$
520 A$=INKEY$
530 IF A$="" THEN 520 ELSE 540
540 PRINT "意  味－－";I$
550 INPUT "正解－１、まちがい－２、やめる－Ｑ";P$
560 IF P$="1" THEN S=S+1
570 IF P$="2" THEN M=M+1:GOSUB *MTOUROKU
580 IF P$="Q" THEN I=LOF(1)
590 CLS:NEXT I:GOTO *MENU
600 *RAMDOM
610 S=0:M=0
620 L=INT(RND*32667+1)
630 RANDOMIZE L
640 INPUT "何番まで";N
650 IF N>LOF(1) THEN 640
660 I=INT(RND*N+1)
670 GET #1,I
680 CLS
690 PRINT "スペル－－－";S$
700 A$=INKEY$:IF A$="" THEN 700 ELSE 710
710 PRINT "意　味－－－";I$
720 INPUT "正解－１、まちがい－２、やめる－Ｑ";P$
730 IF P$="1" THEN S=S+1
740 IF P$="2" THEN M=M+1:GOSUB *MTOUROKU
750 IF P$="Q" THEN *MENU
760 CLS:GOTO 660
770 *MTOUROKU
780 LSET MS$=S$:LSET MI$=I$
790 PUT #2
800 RETURN
810 '------------------------------------------------
820 '検索
830 '------------------------------------------------
840 *KENSAKU
850 INPUT "スペル＝";K$
860 FOR I=1 TO LOF(1)
870 GET #1,I
880 V$=LEFT$(K$,3)
890 X$=LEFT$(S$,3)
900 IF X$=V$ THEN PRINT "意味＝";I$ ELSE NEXT I:PRINT "登録されていません！！"
910 A$=INKEY$:IF A$="" THEN 910 ELSE GOTO *MENU
920 '-----------------------------------------------
930 '登録、削除、変更
940 '-----------------------------------------------
950 *TOUROKU
960 CLS:LOCATE 25,2:PRINT "１－－単語登録"
970 LOCATE 25,4:PRINT "２－－全データ削除"
980 LOCATE 25,6:PRINT "３－－間違いデータ削除"
990 LOCATE 25,8:PRINT "４－－データ変更"
1000 INPUT "どれをしますか";B$
1010 IF B$="1" THEN *TTOUROKU
1020 IF B$="2" THEN CLOSE:KILL "DATA":GOTO *SHOKI
1030 IF B$="3" THEN CLOSE:KILL "MISS":GOTO*SHOKI
1040 IF B$="4" THEN *HENKOU
1050 *TTOUROKU
1060 LINE INPUT "スペル（やめる＝end）＝";SP$
1070 IF SP$="end" THEN 1110
1080 LINE INPUT "意味＝";IM$
1090 LSET S$=SP$:LSET I$=IM$
1100 PUT #1
1110 GOTO *MENU
1120 *HENKOU
1130 CLS:PRINT "どのデータを変更しますか？"
1140 INPUT "スペル＝";HE$
1150 FOR I=1 TO LOF(1)
1160 GET #1,I
1170 HS$=LEFT$(S$,3):UI$=LEFT$(HE$,3)
1180 IF HS$=UI$ THEN 1190 ELSE NEXT I:PRINT "登録されていません！！":GOTO *MENU
1190 PRINT "現在のスペルは  ";S$;" です。"
1200 INPUT "新しいスペルを入力してください";HH$
1210 PRINT "現在の意味は  ";I$;" です。"
1220 INPUT "新しい意味を入力してください";II$
1230 LSET S$=HH$:LSET I$=II$
1240 PUT #1,I
1250 PRINT "変更されました。"
1260 A$=INKEY$:IF A$="" THEN 1260 ELSE GOTO *MENU
1264 IF W=1 THEN 1490 ELSE 1495
1270 '-----------------------------------------------
1280 '結果報告
1290 '-----------------------------------------------
1300 *HOUKOKU
1310 CLS:LOCATE 30,2:PRINT "結　果  報　告"
1320 IF S+M=0 THEN PRINT "テストされていません！！" ELSE 1350
1330 A$=INKEY$:IF A$="" THEN 1330
1340 GOTO *MENU
1350 LOCATE 25,4:PRINT "問題数－－";M+S
1360 LOCATE 25,6:PRINT "正　解－－";S
1370 LOCATE 25,8:PRINT "間違い－－";M
1380 LOCATE 25,11:PRINT "得点－－";S/(S+M)*100;"点"
1390 A$=INKEY$:IF A$="" THEN 1390 ELSE *MENU
1400 '-----------------------------------------------
1410 'データ一覧
1420 '-----------------------------------------------
1430 *ITIRAN
1440 CLS:LOCATE 28,2:PRINT "１－－全データ一覧"
1450 LOCATE 28,4:PRINT "２－－間違いデータ一覧"
1460 INPUT "どちらにしますか";G
1462 INPUT "ディスプレイ出力＝１、プリンタ出力＝２";W
1470 FOR I=1 TO LOF(G)
1480 GET #G,I
1485 IF W=1 THEN 1490 ELSE 1495
1490 IF G=1 THEN PRINT S$;"          ";I$:GOTO 1500 ELSE PRINT MS$;"         ";MI$:GOTO 1500
1495 IF G=1 THEN LPRINT S$;"          ";I$ ELSE LPRINT MS$;"          ";MI$
1500 A$=INKEY$:IF A$="S" THEN 1500
1510 NEXT I
1520 A$=INKEY$:IF A$="" THEN 1520 ELSE GOTO *MENU
1530 '-----------------------------------------------
1540 '終了
1550 '-----------------------------------------------
1560 *SHURYOU
1570 CLOSE:END
