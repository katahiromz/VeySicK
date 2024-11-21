10 'SCREEN 0: CONSOLE ,,,,1
20 PRINT "  0 1 2 3 4 5 6 7 8 9 A B C D E F "
30 FOR L = 0 TO 15
40   PRINT HEX$(L)+" "+chr$(&HA5)+" "+chr$(&HA5)+" ";
50   FOR H = 2 TO 15
60     PRINT CHR$(H * 16 + L)+" ";
70   NEXT
80   PRINT
90 NEXT
