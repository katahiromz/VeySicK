100 '-------------------------------------------
110 ' 石とりゲーム
120 '-------------------------------------------
130 PRINT "石を交互に1～3個取り最後に取ると負け"
140 N = 20
150 *LOOP
160 PRINT USING "残り ## 個です。";N;
170 IF N = 1 THEN PRINT "私の勝ちです。":END
180 INPUT "何個取りますか(1～3)";K
190 IF K < 1 OR K > 3 OR K > N-1 THEN *LOOP
200 N = N - K
210 PRINT USING "残り ## 個です。";N;
220 IF N = 1 THEN PRINT "私の負けです。":END
230 K = (N-1) MOD 4
240 IF K = 0 THEN K = INT(RND(1)*3)+1:
250 PRINT K;"個取りました。"
260 N = N - K
270 GOTO *LOOP
