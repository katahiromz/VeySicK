100 ' ERROR sample
110 ON ERROR GOTO 180
120 INPUT "3 �� � ����(+) � ƭ�خ� �ø�޻�:";N
130 IF FIX(N)<>N THEN ERROR 251
140 IF N<100 OR N>999 THEN ERROR 250
150 PRINT USING "<###>";N
160 ON ERROR GOTO 0
170 END
180 IF ERR=250 THEN PRINT " 3 �� �� 100 �� 999 !!!"
190 IF ERR=251 THEN PRINT " �ޯ�� � ƭ�خ� �޷Ͼ� "
200 PRINT
210 RESUME 120
