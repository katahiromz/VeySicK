100 '-------------------------------------------
110 ' �΂Ƃ�Q�[��
120 '-------------------------------------------
130 PRINT "�΂����݂�1�`3���Ō�Ɏ��ƕ���"
140 N = 20
150 *LOOP
160 PRINT USING "�c�� ## �ł��B";N;
170 IF N = 1 THEN PRINT "���̏����ł��B":END
180 INPUT "�����܂���(1�`3)";K
190 IF K < 1 OR K > 3 OR K > N-1 THEN *LOOP
200 N = N - K
210 PRINT USING "�c�� ## �ł��B";N;
220 IF N = 1 THEN PRINT "���̕����ł��B":END
230 K = (N-1) MOD 4
240 IF K = 0 THEN K = INT(RND(1)*3)+1:
250 PRINT K;"���܂����B"
260 N = N - K
270 GOTO *LOOP
