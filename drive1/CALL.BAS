100 ' CALL sample {GRPH}
110 CLEAR ,&HDFFF
120 GOSUB 210
130 CONSOLE 0,25,0,1:WIDTH 80,25:CLS
140 FOR I=1 TO 80*24
150  PRINT "é";
160 NEXT I
170 CLS:FOR I=1 TO 500:NEXT I
180 VAD%=&HF3C8:AC=&HE000
190 CALL AC(VAD%)
200 END
210 FOR AD=&HE000 TO &HE015
220  READ DA:POKE AD,DA
230 NEXT AD
240 RETURN
250 DATA &H7E           :'      LD   A,(HL)
260 DATA &H23           :'      INC  HL
270 DATA &H66           :'      LD   H,(HL)
280 DATA &H6F           :'      LD   L,A
290 DATA &H3E,&HE9      :'      LD   A,"é"
300 DATA &H11,&H28,&H00 :'      LD   DE,40
310 DATA &H0E,&H19      :'      LD   C,25
320 DATA &H06,&H50      :' L1:  LD   B,80
330 DATA &H77           :' L2:  LD   (HL),A
340 DATA &H23           :' INC  HL
350 DATA &H10,&HFC      :'      DJNZ L2
360 DATA &H19           :'      ADD  HL,DE
370 DATA &H0D           :'      DEC  C
380 DATA &H20,&HF6      :'      JR   NZ,L1
390 DATA &H0D           :'      RET
