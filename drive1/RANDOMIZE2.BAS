100 'RANDOMIZE sample
110 T$=TIME$
120 T=VAL(MID$(T$,7,2))+(VAL(MID$(T$,4,2))+VAL(MID$(T$,1,2))*60)*60
130 T=T-FIX(T/32767)*32767
140 RANDOMIZE T
150 FOR I=1 TO 10
160   PRINT USING "####";RND*100;
170 NEXT
