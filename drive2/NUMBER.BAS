' {8801}
NEW CMD
RANDOMIZE VAL(MID$(TIME$,7,2))
NUM=1+INT(RND(1)*50)
PRINT "*** ��� �� �ް� ***"
PRINT "��� � ��� � �� ��� � ����!"
*MAINLOOP
INPUT "��� � ƭ�خ� ��� (1-50)";N
IF N=NUM THEN *HIT
IF N<NUM THEN BEEP:PRINT N;"�� ���� �޽"
IF N>NUM THEN BEEP:PRINT N;"�� ���� �޽"
GOTO *MAINLOOP
*HIT
PRINT "���� �޽!!!"
CMD PLAY "T215@0L8DGB<D1"
