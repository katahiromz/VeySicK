100 WIDTH 80,25:CLS
110 CONSOLE 0,25,0,0
120 LOCATE 0,0
130 PRINT "�۸� Ӱ��":PRINT
140 GOSUB *PRINTCHR
150 GOSUB *KEYSUB
160 CONSOLE 0,25,0,1
170 LOCATE 0,0
180 PRINT "�װ Ӱ�� ":PRINT
190 GOSUB *PRINTCHR
200 END
210 *PRINTCHR
220 FOR I=0 TO 31
230  PRINT "-COMPUTER-";
240 NEXT I
250 GOSUB *KEYSUB
260 FOR I=0 TO 7
270  COLOR@(I*10,2)-(I*10+9,5),I
280 NEXT I
290 RETURN
300 *KEYSUB
310 LOCATE 0,10
320 PRINT "��ڶ �� � ��� ��޻�";
330 A$=INPUT$(1)
340 RETURN
