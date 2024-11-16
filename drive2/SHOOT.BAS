10 '¼­°Ã¨Ý¸Þ¹Þ°Ñ N88-Basic byTatuakicado 2017
20 'main
30 cls:defint A-Z:x=5:y=5:dim xt(100),yt(100):gosub 120
40 'main
50 in$=inkey$
60 if in$=chr$(&h1C) then x=x+1:gosub 120
70 if in$=chr$(&h1D) then x=x-1:gosub 120
80 if in$=chr$(&h1E) then y=y-1:gosub 120
90 if in$=chr$(&h1F) then y=y+1:gosub 120
100 if in$=" " then gosub 310:gosub 190
110 goto 40
120 if x<=0 then x=0
130 if y<=0 then y=0
140 if x>=50 then x=50
150 if y>=20 then y=20
160 locate xx,yy:print " "
170 locate x,y:print "(^3^)/"
180 XX=X:YY=Y:gosub 290:gosub 310:gosub 260:return
190 for i=6 to 50
200 locate x+i,y:print "-"
210 NEXT I
220 FOR I=6 TO 50
230 LOCATE x+i,Y:PRINT " "
240 NEXT I
250 gosub 290:gosub 350:return
260 for oi=1 to 30:locate xt(oi),yt(oi):print "@":next oi
270 return
280 'teki
290 if ccii>=30 then locate 5,5:print " -= GAME OVER =-" else return
300 in$=inkey$:if in$=" " then end else 300
310 ccii=ccii+1
320 xt(ccii)=int(rnd*50)+1
330 yt(ccii)=int(rnd*20)+1
340 return
350 for i=1 to ccii:if xt(i)=>x and xt(i)<=x+50 and yt(i)=y then gosub 370
360 next i:return
370 locate xt(i),yt(i):print " ":xt(i)=0:yt(i)=0
380 teki=teki+1
390 locate 5,21:print " het=>";teki
400 return
