1 ' **************************************
2 ' OTHELO GAME by IBM 5550 Multstation
3 ' Copyright (C) 1986 �[�l�������Y�i���j
4 ' NEC PC-8801mk2SR ������� By 1987 Y.Sasaki
5 ' **************************************
10 'CLOSE:SAVE"A:OTHELO.BAS",A:"'REM "���"
20 CONSOLE ,,0,1
90 DEFINT A-Z :SCREEN 4:WIDTH 80,20
91 COLOR  7
100 REM IRO=VAL(INPUT$(1))
105 IRO=1
110 COLOR  7
120 REM ---------- ��� ��ò  ------
130 DIM A(7,7):HC=0:HY=0:CLS:GOTO 1220
140 KK=0:P=5:PB=5:GC=4
150 FOR I=0 TO 7:FOR J=0 TO 7:A(I,J)=0:NEXT :NEXT :CLS
160 REM ---------- ���� ��ò ------
170 LOCATE 58,23:PRINT FE$;
180 LOCATE 60,1:PRINT "-- KEY --";
190 LOCATE 60,2:PRINT "'.'    ��";
200 LOCATE 60,4:PRINT "'0'    �c";:LOCATE 58,6:PRINT "'���s��'��";
210 LOCATE 60,8:PRINT "'SPC' �߽";:LOCATE 58,10:PRINT "'S' -���_-";
220 LOCATE 60,12:PRINT "--�߽--�c�";:LOCATE 58,14:PRINT "�M��   ";P;:LOCATE 58,15:PRINT "�����-�";PB
230 LOCATE 58,17:PRINT "COMMENT-";
235 REM PLAY"mb ms o3 l8e l16e l16f l2g l8f l8g l8f l4e"
240 GOSUB 1790
250 CIRCLE(178,164),18:CIRCLE(226,208),18:A(3,3)=-1:A(4,4)=-1
260 CIRCLE(226,164),18:CIRCLE(178,208),18:PAINT(226,164):PAINT(178,208):A(4,3)=1:A(3,4)=1
270 GOTO 510
280 REM ---------- �� � ƭ�خ� ----
290 X=0:Y=0
291 LINE(10,5)-(394,5),0:LINE(10,6)-(394,6),0
292 LINE(5,10)-(5,362),0:LINE(6,10)-(6,362),0
300 X=(X-8)*SGN(X)+7:Y=(Y-8)*SGN(Y)+7
310 X=(X+1)*SGN(7-X):Y=(Y+1)*SGN(7-Y)
320 GOSUB 1620
330 P3$=INKEY$:IF P3$=CHR$(13) THEN 380
340 IF P3$="." THEN X=(X+1)*SGN(7-X):GOTO 300
350 IF P3$="0" THEN Y=(Y+1)*SGN(7-Y):GOTO 300
355 IF P3$="1" THEN 290
360 IF P3$=" " THEN GOSUB 1660:BEEP:LOCATE 46,19:PRINT " �߽";:GOSUB 870:FOR I=1 TO 1000:NEXT I:GOTO 430
370 IF P3$="S" THEN GC=64:GOTO 500 ELSE 300
380 GOSUB 1620
390 IF A(X,Y)<>0 THEN KK=0:GOTO 410
400 KX=X:KY=Y:CC=0:KK=0:K=-1:GOSUB 540
410 IF KK=0 THEN GOSUB 1660:FOR SMM=1 TO 100:BEEP 1:BEEP 0:NEXT SMM:LOCATE 46,19:PRINT "�łĂ܂���!!";:GOTO 290 ELSE GC=GC+1:IF GC=64 THEN 500
420 REM ---------- �����-�     ----
430 GOSUB 1660:GOSUB 1830:LOCATE 46,19:PRINT "Computer";:LOCATE 46,20:PRINT "    is";:LOCATE 46,21:PRINT "  thinking.";
440 RESTORE 700
450 READ C,D:IF C=9 AND D=9 THEN GOSUB 810:GOTO 510
460 IF A(C,D)<>0 THEN 450
470 KX=C:KY=D
480 KK=0:K=1:CC=1:GOSUB 540
490 IF KK=0 THEN 450
500 GC=GC+1:IF GC>=64 THEN GOSUB 1660:LOCATE 46,19:PRINT " GAME";:LOCATE 46,21:PRINT "      END";:GOTO 920
510 GOSUB 1660:GOSUB 1830:LOCATE 46,19:PRINT "�M���";:LOCATE 51,19:PRINT "���޽";
520 GOTO 290
530 REM ---------- ���ٶ  ?   -----
540 FOR AX=-1 TO 1:FOR AY=-1 TO 1
550 IF AX=0 AND AY=0 THEN 680
560 N=2
570 A=KX+AX*N:B=KY+AY*N
580 IF A<0 OR A>7 THEN 680
590 IF B<0 OR B>7 THEN 680
600 IF KX+AX<0 OR KX+AX>7 THEN 680
610 IF KY+AY<0 OR KY+AY>7 THEN 680
620 IF A(KX+AX*(N-1),KY+AY*(N-1))<>-K THEN 680
630 IF A(A,B)=K THEN 650
640 N=N+1:GOTO 570
650 KK=1:FOR I=0 TO N:YK=KX+AX*I:TT=KY+AY*I:IF CC<>1 THEN Y3=YK:T3=TT:GOSUB 1570:YK=Y3:TT=T3
660 IF I=0 THEN FOR O=0 TO 100:NEXT
670 GOSUB 1510:A(KX+AX*I,KY+AY*I)=K:NEXT:YK=KX:TT=KY:GOSUB 1510
680 NEXT:NEXT :RETURN
690 REM ---------- �����-� ����� � ��-� ---
700 DATA 0,7,7,0,0,0,7,7,2,2,5,2
710 DATA 2,5,5,5,3,2,4,5,5,4,2,3
720 DATA 5,3,4,2,2,4,3,5,2,0,3,0
730 DATA 4,0,5,0,0,2,0,3,0,4,0,5
740 DATA 7,2,7,3,7,4,7,5,2,7,3,7,4,7,5,7
750 DATA 2,1,3,1,4,1,5,1,2,6,3,6
760 DATA 4,6,5,6,1,2,1,3,1,4,1,5,6,2
770 DATA 6,3,6,4,6,5,1,1,6,6,6,1
780 DATA 1,6,0,1,1,0,6,0,7,1,0,6
790 DATA 1,7,6,7,7,6,9,9
800 REM ---------- �� � - �����-� ---
810 PB=PB-1
820 GOSUB 1660:LOCATE 46,19:PRINT "������-�";:LOCATE 46,21:PRINT " �߽�Ͻ";
830 LOCATE 53,15:PRINT PB;
840 IF PB<0 THEN N$=" �M��":GOTO 920
850 RETURN
860 REM ---------- �� � - �ЂƁ@ ----
870 P=P-1
880 LOCATE 53,14:PRINT P;
890 IF P<0 THEN N$=" �����-�":GOTO 920
900 RETURN
910 REM ---------- ��-�   �I�@�� ----
915 WIDTH 80,25
920 GOSUB 1110
930 CLS:GOSUB 1790
940 IF IRO<>0 THEN LOCATE 24,23:PRINT CHR$(&HFA);
950 GN=0:GC=0
960 CC=0:FOR I=1 TO YO:YK=GN:TT=GC:GOSUB 1510:GN=GN+1:IF GN>7 THEN GN=0:GC=GC+1
970 NEXT
980 CC=1:FOR I=1 TO CO:YK=GN:TT=GC:GOSUB 1510:GN=GN+1:IF GN>7 THEN GN=0:GC=GC+1
990 NEXT
1000 LOCATE 56,1:PRINT "*��-� �I��"
1001 IF N$<>" �M��" THEN REM PLAY"mb o2 mn l4c l8c l16c l4c l8e- l16d l8d l16c l8c o1l16b o2l4c"
1010 LOCATE 56,4:PRINT  N$:IF N$=" ����" THEN 1020 ELSE LOCATE 56,5:PRINT "    �":LOCATE 56,6:PRINT "    �� �޽ !!"
1020 LOCATE 56,9:PRINT "  - ���_ - ";
1030 LOCATE 56,11:PRINT "�M��   :";YO
1040 LOCATE 56,12:PRINT "�����-�:";CO
1050 LOCATE 56,14:PRINT "�ō��_"
1060 LOCATE 56,15:PRINT "���-�- :";HY
1070 LOCATE 56,16:PRINT "�����-�:";HC
1080 LOCATE 56,18:INPUT "PUSH (Y/N)"; NN$:IF NN$="y" OR NN$="Y" THEN GOTO 140
1081 CLOSE:LOCATE ,,1:CLS:END
1090 IF IRO<>0 THEN LOCATE 45,9:PRINT  FC;:LOCATE 45,16:PRINT F9;:LOCATE 56,22:PRINT  FE$;
1100 IF "Y"=INKEY$ THEN CLS:GOTO 1220 ELSE 1105
1105 IF "N"=INKEY$ THEN 1890 ELSE 1100
1110 CO=0:YO=0:FOR I=0 TO 7:FOR J=0 TO 7
1120 IF A(I,J)=1 THEN CO=CO+1:GOTO 1140
1130 IF A(I,J)=-1 THEN YO=YO+1
1140 NEXT :NEXT
1150 IF CO>HC THEN HC=CO
1160 IF YO>HY THEN HY=YO
1170 IF  P<0 OR PB<0 THEN RETURN
1180 IF CO<YO THEN N$=" �M��":RETURN
1190 IF CO>YO THEN N$="�����-�":RETURN
1200 IF CO=YO THEN N$=" ����"
1210 RETURN
1220 PRINT :PRINT :PRINT :PRINT :PRINT
1230 IF IRO<>0 THEN COLOR 7
1240 IF IRO<>0 THEN COLOR 7
1310 IF IRO<>0 THEN COLOR 7
1320 PRINT :PRINT :PRINT "     0 �M��     X  �����-�":PRINT
1330 PRINT :PRINT :PRINT "      PLEASE PUSH  'RETURN' KEY  !":PRINT :PRINT
1335 BEEP
1340 IF INKEY$=CHR$(13) THEN 140 ELSE 1340
1500 REM --------- �� � ��       ----
1509 COLOR 0
1510 YK=YK*48+34
1520 TT=TT*44+32
1530 CIRCLE(YK,TT),18
1540 IF CC=1 THEN PAINT(YK,TT)
1550 RETURN
1560 REM --------- �� � ��       ----
1570 YK=YK*48+34
1580 TT=TT*44+32
1585 CIRCLE(YK,TT),18
1590 PAINT(YK,TT),0
1600 RETURN
1610 REM --------- �� � �� �޼�  ----
1620 LINE(X*48+11,5)-(X*48+57,5):LINE(X*48+12,6)-(X*48+56,6)
1630 LINE(5,Y*44+11)-(5,Y*44+53):LINE(6,Y*44+12)-(6,Y*44+52)
1640 RETURN
1650 REM --------- ����          ----
1660 LOCATE 46,19:PRINT "          ";:LOCATE 46,20:PRINT "          ";:LOCATE 46,21:PRINT "           ";:LOCATE 46,23:PRINT "            ";
1670 RETURN
1680 REM ----------------------------
1710 LINE(10,10)-(394,362),,B
1780 REM ---------- ��� � ��     ----
1790 LINE(10,10)-(394,362),,B
1810 FOR GN=1 TO 7:LINE(9,10+GN*44)-(393,10+GN*44):LINE(10+GN*48,9)-(10+GN*48,361):NEXT
1820 RETURN
1830 CO=0:YO=0:FOR I=0 TO 7:FOR J=0 TO 7
1840 IF A(I,J)=1 THEN CO=CO+1:GOTO 1860
1850 IF A(I,J)=-1 THEN YO=YO+1
1860 NEXT:NEXT
1870  LOCATE 25,21:PRINT "�M��:";YO;"---";CO;"���@";
1880 RETURN
1890 END
