100 ' MID$ sample
110 DATA My name is !!!!!!!!
120 DATA Kako,Aikawa,Terada,Nakahara
130 READ A$
140 FOR I=1 TO 4
150  READ NA$:MID$(A$,12)=NA$
160  PRINT A$
170 NEXT
180 END
