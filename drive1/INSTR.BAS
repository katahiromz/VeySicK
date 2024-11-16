100 ' INSTR sample
110 A$="abcdefghijklmnopqrstuvwxyz"
120 ALP$=INPUT$(1)
130 ALP=ASC(ALP$)
140 IF ALP>64 AND ALP<91 THEN ALP=ALP+32
150 A=INSTR(A$,CHR$(ALP))
160 IF A=0 THEN PRINT ALP$;" Ê ±ÙÌ§ÍÞ¯Ä ÃÞÊ ±ØÏ¾Ý":END
170 PRINT USING "! Ê ## ÊÞÝÒ É ±ÙÌ§ÍÞ¯Ä ÃÞ½";ALP$,A
180 END
