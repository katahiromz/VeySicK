1000 '
1010 '  DISK-BASIC SYSTEM DISK generator for PC-8801MK2
1020 '
1030 '  Copyright (C) 1983 by Personal Computer Div, NEC
1040 '
1050 '         Version 1.0       (83/09/22)
1060 '
1070   DEFINT A-Z
1080 '
1090   CLS:PRINT "DISK-BASIC SYSTEM DISK GENERATOR"
1100 '
1110   MAXDRV=PEEK(&HEC7D)
1120   DMADRV=PEEK(&HEF60)
1130   IF MAXDRV=DMADRV THEN PRINT "Can't run.":BEEP:END
1140   DRIVE=DMADRV+1
1150   PA=&HFC:PB=&HFD:PC=&HFE:CW=&HFF
1160   BTOP=VARPTR(#0)+9 ' buffer top adrs
1170 '
1180   PRINT
1190   PRINT "Mount NEW disk on drive";DRIVE
1200   INPUT "Sure(y/n)";A$
1210   IF A$<>"Y" AND A$<>"y" THEN BEEP:GOTO 1200
1220 '   physical formatting
1230   PRINT
1240   PRINT "Physical formatting."
1250   A=5 ' format command
1260   GOSUB *OUT.CMD
1270   A=0 ' drive number (mini)
1280   GOSUB *OUT.DAT
1290   FOR WT!=0 TO 22000:NEXT
1300   GOTO *SYS.FORM
1310 *OUT.CMD
1320   OUT CW,15
1330 *OUT.DAT
1340   IF (INP(PC) AND 2)=0 THEN 1340
1350   OUT CW,14
1360   OUT PB,A:OUT CW,9
1370   IF (INP(PC) AND 4)=0 THEN 1370
1380   OUT CW,8
1390   IF INP(PC) AND 4 THEN 1390
1400   RETURN
1410 '   system formatting
1420 *SYS.FORM
1430   PRINT
1440   PRINT "System formatting."
1450   FIELD #0,255 AS F1$,1 AS F2$
1460 '   fat
1470   RS$=CHR$(254):FR$=CHR$(255)
1480   FAT$=STRING$(160,FR$)
1490   MID$(FAT$,1,10)=RS$+RS$+FR$+FR$+RS$+RS$+FR$+FR$+RS$+RS$
1500   MID$(FAT$,75,2)=RS$+RS$
1510   FAT$=FAT$+STRING$(255-LEN(FAT$),0)
1520   LSET F1$=FAT$:LSET F2$=CHR$(0)
1530   FOR SEC=14 TO 16
1540     DSKO$ DRIVE,1,18,SEC
1550   NEXT SEC
1560 '  dir
1570   LSET F1$=STRING$(255,CHR$(255)):LSET F2$=CHR$(255)
1580   FOR SEC=1 TO 12
1590     DSKO$ DRIVE,1,18,SEC
1600   NEXT SEC
1610 '  id
1620   LSET F1$=STRING$(255,0):F2$=CHR$(0)
1630   DSKO$ DRIVE,1,18,13
1640 '   write disk code
1650   PRINT
1660   DIM WRITE.SEC(2,16)
1670   RESTORE *WS.TABLE
1680   FOR TRK=0 TO 2
1690     FOR SEC=1 TO 16
1700       READ WRITE.SEC(TRK,SEC)
1710     NEXT SEC
1720   NEXT TRK
1730 *WS.TABLE
1740   DATA 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0
1750   DATA 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1
1760   DATA 1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0
1770 '
1780   RESTORE *N.SYS.DATA
1790   FOR TRK=0 TO 2
1800     FOR SEC=1 TO 16
1810       IF WRITE.SEC(TRK,SEC)=0 THEN *SKIP
1820       FOR BYT=0 TO 255
1830         READ A$ : DT=VAL("&H"+A$)
1840         POKE BTOP+BYT,DT
1850       NEXT BYT
1860       PRINT "Writing track";TRK*2;"sector";SEC
1870       DSKO$ DRIVE,0,TRK,SEC
1880     *SKIP
1890     NEXT SEC
1900   NEXT TRK
1910 '
1920   PRINT
1930   PRINT "Completed.":BEEP
1940 '
1950   END
1960 *N.SYS.DATA : DISK-BASIC VERSION ' [20-Sep-1981] '
1970 ' TRK= 0              SEC= 1 
1980 DATA 3A,02,00,3C,C2,A8,77,00,00,00,00,00,00,00,00,00
1990 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2000 DATA 00,00,3E,17,CD,7C,01,3E,0F,CD,83,01,C3,C2,C0,21
2010 DATA 38,C0,CD,ED,52,C3,BC,C0,4E,4F,4E,20,44,49,53,4B
2020 DATA 20,42,41,53,49,43,0D,0A,00,F5,79,2F,3C,C6,11,F5
2030 DATA 3E,EA,92,FE,10,30,02,E1,F5,F1,B7,CD,99,00,38,05
2040 DATA 82,57,F1,B7,C9,F1,37,C9,F1,F1,F5,32,B9,ED,3E,02
2050 DATA CD,21,01,F1,F5,47,CA,C2,00,CD,5A,01,E6,40,CA,68
2060 DATA 01,CD,87,C0,C3,C2,00,3E,12,CD,7C,01,0E,80,CD,97
2070 DATA C0,0D,20,FA,10,F6,C9,3E,0B,D3,FF,DB,FE,E6,01,28
2080 DATA FA,3E,0A,D3,FF,DB,FC,12,13,3E,0D,D3,FF,DB,FE,E6
2090 DATA 01,20,FA,DB,FC,12,13,3E,0C,D3,FF,C9,AF,32,C7,ED
2100 DATA 37,C9,11,00,C1,01,02,00,AF,32,C5,ED,3E,01,B7,CD
2110 DATA 99,00,3E,C3,32,B3,F1,21,68,C0,22,B4,F1,11,00,C2
2120 DATA 01,03,00,AF,32,C5,ED,CD,49,C0,38,D0,04,04,0E,01
2130 DATA CD,49,C0,38,C7,04,04,0E,01,CD,49,C0,38,BE,11,A5
2140 ' TRK= 0             SEC= 2 
2150 DATA C2,01,0D,25,CD,49,C0,38,06,3A,A6,C2,C6,01,3F,F5
2160 DATA 21,FE,FF,22,52,EB,3E,00,32,4D,EB,32,98,ED,32,46
2170 DATA EB,21,58,EF,22,56,EF,21,C2,EF,22,2A,F0,38,07,3A
2180 DATA A7,C2,FE,10,38,1F,21,68,C2,CD,ED,52,CD,5C,3E,38
2190 DATA F5,D7,B7,3E,05,28,0E,CD,D5,4C,20,EA,7A,B7,20,E6
2200 DATA 7B,FE,10,30,E1,32,CE,E9,3C,87,2F,3C,5F,16,FF,21
2210 DATA 70,D2,19,22,CF,E9,E5,3A,C7,ED,87,2F,3C,5F,19,22
2220 DATA D1,E9,2B,EB,E1,01,09,01,AF,91,4F,F5,3E,00,98,47
2230 DATA 00,3A,CE,E9,3C,00,00,00,00,00,00,00,00,EB,09,EB
2240 DATA 73,23,72,23,3D,20,F6,F1,B7,01,5B,FF,3E,00,F5,3A
2250 DATA C7,ED,2A,D1,E9,20,E6,1B,1B,F1,D5,2A,CF,E9,5E,23
2260 DATA 56,21,09,00,19,22,D3,E9,AF,3D,32,F0,E9,CD,16,E2
2270 DATA AF,32,F0,E9,CD,EF,D4,3E,C3,32,B3,F1,21,13,D4,22
2280 DATA B4,F1,E1,F1,DA,C8,17,2B,22,54,EF,11,D5,FE,19,2B
2290 DATA F9,22,50,EB,22,8F,EF,21,00,80,AF,77,BE,20,05,2F
2300 DATA 77,BE,28,04,01,00,40,09,EB,7A,ED,47,21,7A,18,01
2310 ' TRK= 0             SEC= 3 
2320 DATA 0C,00,ED,B0,06,0A,EB,11,C9,00,73,23,72,23,10,FA
2330 DATA 36,00,23,22,54,EB,21,38,18,CD,ED,52,CD,DD,47,CD
2340 DATA E1,3D,21,32,18,06,06,7E,23,D3,C1,D3,C3,10,F8,3E
2350 DATA FF,D3,C8,D3,CA,D3,E4,ED,5E,FB,21,FF,FF,22,52,EB
2360 DATA 11,96,EC,21,A8,C2,01,FD,00,7E,A7,CA,82,3C,ED,B0
2370 DATA EB,06,FD,2B,7E,A7,28,04,FE,20,20,03,10,F5,2B,23
2380 DATA AF,77,21,95,EC,C3,EF,3C,54,77,6F,20,73,75,72,66
2390 DATA 61,63,65,20,64,69,73,6B,20,76,65,72,73,69,6F,6E
2400 DATA 20,5B,32,30,2D,53,65,70,2D,31,39,38,31,5D,0D,0A
2410 DATA 48,6F,77,20,6D,61,6E,79,20,66,69,6C,65,73,28,30
2420 DATA 2D,31,35,29,00,7D,00,00,00,00,00,00,00,00,00,00
2430 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2440 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2450 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2460 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2470 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2480 ' TRK= 1             SEC= 3 
2490 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2500 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2510 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2520 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2530 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2540 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2550 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
2560 DATA 00,00,46,49,45,4C,44,20,6F,76,65,72,66,6C,6F,77
2570 DATA 00,49,6E,74,65,72,6E,61,6C,20,65,72,72,6F,72,00
2580 DATA 42,61,64,20,66,69,6C,65,20,6E,75,6D,62,65,72,00
2590 DATA 46,69,6C,65,20,6E,6F,74,20,66,6F,75,6E,64,00,42
2600 DATA 61,64,20,66,69,6C,65,20,6D,6F,64,65,00,46,69,6C
2610 DATA 65,20,61,6C,72,65,61,64,79,20,6F,70,65,6E,00,44
2620 DATA 69,73,6B,20,6E,6F,74,20,6D,6F,75,6E,74,65,64,00
2630 DATA 44,69,73,6B,20,49,2F,4F,20,65,72,72,6F,72,00,46
2640 DATA 69,6C,65,20,61,6C,72,65,61,64,79,20,65,78,69,73
2650 ' TRK= 1             SEC= 4 
2660 DATA 74,73,00,44,69,73,6B,20,61,6C,72,65,61,64,79,20
2670 DATA 6D,6F,75,6E,74,65,64,00,44,69,73,6B,20,66,75,6C
2680 DATA 6C,00,49,6E,70,75,74,20,70,61,73,74,20,65,6E,64
2690 DATA 00,42,61,64,20,66,69,6C,65,20,6E,61,6D,65,00,44
2700 DATA 69,72,65,63,74,20,73,74,61,74,65,6D,65,6E,74,20
2710 DATA 69,6E,20,66,69,6C,65,00,42,61,64,20,61,6C,6C,6F
2720 DATA 63,61,74,69,6F,6E,20,74,61,62,6C,65,00,42,61,64
2730 DATA 20,64,72,69,76,65,20,6E,75,6D,62,65,72,00,42,61
2740 DATA 64,20,73,75,72,66,61,63,65,2F,74,72,61,63,6B,2F
2750 DATA 73,65,63,74,6F,72,00,44,65,6C,65,74,65,64,20,72
2760 DATA 65,63,6F,72,64,00,52,65,6E,61,6D,65,20,61,63,72
2770 DATA 6F,73,73,20,64,69,73,6B,73,00,53,65,71,75,65,6E
2780 DATA 74,69,61,6C,20,61,66,74,65,72,20,50,55,54,00,53
2790 DATA 65,71,75,65,6E,74,69,61,6C,20,49,2F,4F,20,6F,6E
2800 DATA 6C,79,00,46,69,6C,65,20,6E,6F,74,20,4F,50,45,4E
2810 DATA 00,46,69,6C,65,20,77,72,69,74,65,20,70,72,6F,74
2820 ' TRK= 1             SEC= 5 
2830 DATA 65,63,74,65,64,00,44,69,73,6B,20,6F,66,66,6C,69
2840 DATA 6E,65,00,F1,F1,F5,32,B9,ED,3E,02,30,14,3E,14,CD
2850 DATA 7C,01,3A,C6,ED,CD,83,01,CD,E9,01,E6,40,20,2C,3E
2860 DATA 11,CD,21,01,F1,F5,47,38,11,CA,50,D4,CD,5A,01,E6
2870 DATA 40,CA,68,01,CD,6C,D4,C3,C2,00,CD,8C,D4,C3,C2,00
2880 DATA CD,63,D4,C2,68,01,F1,D1,C1,B7,C9,F1,D1,C1,E3,E1
2890 DATA C3,AA,E9,E5,21,C2,D4,22,FA,E9,18,07,E5,21,C0,D4
2900 DATA 22,FA,E9,E1,AF,32,FC,E9,3E,12,CD,7C,01,0E,80,CD
2910 DATA 97,D4,0D,20,FA,10,F6,3A,FC,E9,B7,C9,0E,80,CD,CC
2920 DATA D4,0D,20,FA,10,F6,C9,3E,0B,D3,FF,DB,FE,E6,01,28
2930 DATA FA,3E,0A,D3,FF,DB,FC,CD,F9,E9,13,3E,0D,D3,FF,DB
2940 DATA FE,E6,01,20,FA,DB,FC,CD,F9,E9,13,3E,0C,D3,FF,C9
2950 DATA 12,C9,EB,BE,EB,C8,3E,FF,32,FC,E9,C9,DB,FE,E6,02
2960 DATA 28,FA,1A,13,D3,FD,3E,09,D3,FF,DB,FE,E6,04,28,FA
2970 DATA 1A,13,D3,FD,3E,08,D3,FF,DB,FE,E6,04,20,FA,C9,21
2980 DATA FB,D4,11,E1,F0,01,35,01,ED,B0,C9,C3,AB,E1,C3,AE
2990 ' TRK= 1             SEC= 6 
3000 DATA E1,C3,B1,E1,C3,46,E8,C3,1D,E8,C3,35,E8,C3,92,E1
3010 DATA C3,95,E1,C3,98,E1,C3,75,18,C3,83,DB,C3,7F,E0,C3
3020 DATA 75,18,C3,75,18,C3,75,18,C3,75,18,C3,75,18,C3,75
3030 DATA 18,C3,75,18,C3,75,18,C3,75,18,C3,75,18,C3,75,18
3040 DATA C3,3F,E2,C3,E7,E2,C3,3C,E4,C3,74,D7,C3,E6,E2,C3
3050 DATA 00,E2,C3,B0,DD,C3,B1,DD,C3,31,DB,C3,9E,DD,C3,D2
3060 DATA DF,C3,D1,DF,C3,FD,DD,C3,44,E2,C3,CD,E1,C3,C8,E1
3070 DATA C3,C9,E0,C3,0C,E8,C3,0A,E4,C3,1D,E1,C3,0D,DB,C3
3080 DATA 01,E4,C3,62,E8,C3,7A,D6,C3,90,E8,C9,BE,00,C3,6B
3090 DATA E8,C3,3C,D6,C3,43,D6,C3,D6,D6,C3,4A,D6,C3,52,D6
3100 DATA C9,00,00,C3,30,D6,C3,E4,D6,C3,70,D6,C9,E0,00,C3
3110 DATA 8A,D6,C3,A7,D6,C3,C3,D7,C9,00,00,C3,A6,E8,C9,00
3120 DATA 00,C3,F0,D6,C3,5E,D6,C3,DF,D6,C9,00,00,C9,3D,00
3130 DATA C9,A6,00,C9,7C,00,C9,B9,00,C9,A7,00,C9,66,00,C9
3140 DATA B4,00,C3,0E,D7,C9,00,00,C9,3D,00,C9,A0,00,C9,54
3150 DATA 00,C9,8F,00,C9,76,00,C9,CA,00,C9,B9,00,C9,77,00
3160 ' TRK= 1             SEC= 7 
3170 DATA C9,AE,00,C9,9C,00,C9,00,00,C9,46,00,C9,06,00,C9
3180 DATA B3,00,C9,10,00,C9,8A,00,C9,B1,00,C9,92,00,C9,39
3190 DATA 00,C9,C7,00,C9,EA,00,C9,39,00,C3,BE,D6,C9,00,00
3200 DATA D8,FE,0E,C8,FE,0D,C8,E3,E1,C3,AB,DD,2A,4E,EB,22
3210 DATA 9A,EF,C9,2A,9A,EF,22,4E,EB,C9,AF,32,4E,EB,32,4F
3220 DATA EB,C9,E5,2A,4E,EB,7C,B5,E1,C8,E3,C3,7D,E3,FE,23
3230 DATA C0,CD,F9,56,E5,CD,C1,DA,EB,E1,E3,23,23,23,E3,C9
3240 DATA 2A,4E,EB,7C,B5,C8,E1,C3,BE,47,7B,FE,32,D8,FE,4A
3250 DATA D0,D6,31,5F,21,71,D2,C3,5B,3C,2A,4E,EB,7C,B5,C8
3260 DATA 01,08,00,09,7E,E1,D5,F5,11,22,48,CD,95,40,D1,7A
3270 DATA D1,DA,22,48,C3,54,48,E5,FE,23,C2,8A,25,D7,FE,F4
3280 DATA E1,7E,C8,C1,CD,7E,E8,E5,21,95,EC,C3,35,49,E5,2A
3290 DATA 4E,EB,7C,B5,E1,C8,E3,D5,11,0C,57,CD,95,40,D1,E1
3300 DATA D2,28,57,C3,D3,49,CD,08,E2,3A,F0,E9,E6,01,C0,AF
3310 DATA 32,F0,E9,C9,E5,D7,FE,F4,E1,7E,C8,0E,02,C3,7E,E8
3320 DATA E3,E1,3A,C8,ED,B7,28,0C,78,FE,25,C2,B3,E9,79,FE
3330 ' TRK= 1             SEC= 8 
3340 DATA 0E,DA,B3,E9,F1,F1,E1,37,C9,AF,32,F3,E9,C9,7B,FE
3350 DATA 1B,20,F6,3A,F3,E9,B7,28,F0,F1,06,F0,16,7F,21,96
3360 DATA EC,CD,4A,D7,5F,D6,80,9F,B2,57,7B,A2,77,FE,0D,28
3370 DATA 0C,FE,0A,20,05,78,FE,F0,28,E7,23,10,E4,AF,77,3D
3380 DATA 32,54,EA,3C,21,95,EC,C3,F2,3C,CD,CC,E3,D0,F1,3A
3390 DATA F0,E9,E6,80,32,F0,E9,CD,90,E8,AF,32,F3,E9,3A,DB
3400 DATA E9,B7,21,FA,41,E5,C2,F4,3D,E1,21,60,3B,CD,ED,52
3410 DATA AF,C3,9F,3C,CD,FA,56,A7,CA,A5,44,3A,C7,ED,BB,DA
3420 DATA A5,44,E5,21,AD,D7,E3,C5,D5,F5,43,AF,32,C5,ED,CD
3430 DATA B8,D7,3A,CB,ED,32,FD,E9,3E,0A,32,CB,ED,CD,5A,01
3440 DATA 3A,FD,E9,32,CB,ED,F1,D1,C1,B7,E3,E1,C9,3A,FD,E9
3450 DATA 32,CB,ED,E3,E1,C3,B3,E9,3E,05,CD,7C,01,78,3D,CD
3460 DATA 83,01,C9,EB,2A,4E,EB,7C,B5,EB,C8,D1,C3,98,E8,2A
3470 DATA D5,E9,46,23,23,7E,B7,CA,A7,E9,23,EB,78,87,4F,47
3480 DATA 26,00,68,19,7E,3C,28,15,79,B7,28,09,0D,26,00,69
3490 DATA 19,7E,3C,28,09,78,FE,9F,30,EE,04,18,E3,48,36,C0
3500 ' TRK= 1             SEC= 9 
3510 DATA EB,2B,35,23,EB,2A,4E,EB,23,7E,B7,3C,71,28,08,3D
3520 DATA 77,C5,CD,AD,D9,C1,71,06,08,DA,06,01,2A,D5,E9,2B
3530 DATA 2B,36,FF,23,23,23,7E,B7,20,03,3E,10,77,90,DA,E9
3540 DATA E4,77,C9,2A,4E,EB,23,7E,CD,8D,D9,06,00,6F,26,00
3550 DATA 19,7E,04,36,FF,FE,C0,38,F4,1B,1A,80,12,1B,12,EB
3560 DATA 2B,2B,2B,36,FF,EB,C9,3D,F2,5F,D8,DA,83,E9,D0,CD
3570 DATA EE,DA,C2,8C,E9,1E,00,16,0E,F5,3A,CB,ED,32,FD,E9
3580 DATA 3E,01,32,CB,ED,F1,CD,3D,E5,20,01,1C,14,7A,D6,11
3590 DATA 20,F4,F5,3A,FD,E9,32,CB,ED,F1,B3,CA,80,E9,3E,03
3600 DATA 93,C4,2B,E5,2A,D5,E9,36,25,2B,2B,36,00,23,23,23
3610 DATA 23,E5,23,AF,06,A0,4E,23,0C,20,01,3C,10,F8,F5,01
3620 DATA 0D,25,2A,D3,E9,3E,01,B7,CD,39,E7,3D,38,01,7E,2A
3630 DATA D5,E9,2B,E6,70,77,F1,E1,77,C9,20,63,6F,70,69,65
3640 DATA 73,20,6F,66,20,61,6C,6C,6F,63,61,74,69,6F,6E,20
3650 DATA 62,61,64,20,6F,6E,20,64,72,69,76,65,20,00,3D,F2
3660 DATA F6,D8,DA,83,E9,D0,4F,CD,EE,DA,C8,3A,CE,E9,47,78
3670 ' TRK= 1             SEC= 10 
3680 DATA CD,C1,DA,28,0C,23,23,23,23,7E,B9,78,C5,CC,0C,DD
3690 DATA C1,05,F2,FF,D8,79,CD,EE,DA,2B,36,40,2B,7E,B7,28
3700 DATA 06,CD,F5,E4,DA,80,E9,2A,D5,E9,36,FF,2B,36,00,2B
3710 DATA 36,00,C9,CD,57,D9,2A,4E,EB,23,7E,CD,8D,D9,6F,26
3720 DATA 00,19,05,5F,28,08,7E,FE,C0,38,F0,7B,37,C9,7E,D6
3730 DATA C0,3F,30,01,B9,7B,C9,06,00,0E,08,7B,04,91,5F,7A
3740 DATA DE,00,57,30,F6,7B,C6,08,20,03,3E,08,05,4F,0D,C9
3750 DATA 7E,E6,60,23,7E,23,46,48,C0,CD,8D,D9,0E,00,18,09
3760 DATA 6F,26,00,19,7E,0C,CA,80,E9,B8,20,F4,C9,2A,D5,E9
3770 DATA 23,23,23,EB,C9,7E,E6,60,C0,23,23,5E,23,46,CD,8D
3780 DATA D9,26,00,19,7E,D6,C0,3F,D0,B8,C0,37,C9,2A,4E,EB
3790 DATA 7E,E6,60,23,7E,23,4E,23,47,7E,C0,78,CD,8D,D9,0E
3800 DATA 00,6F,47,26,00,19,0C,CA,80,E9,7E,FE,C0,38,F2,0D
3810 DATA D6,C0,C9,C5,69,26,00,29,29,29,EB,C1,C9,AF,32,D9
3820 DATA E9,16,01,CD,6E,E5,1E,10,7E,3C,28,34,3D,20,08,22
3830 DATA D7,E9,EB,22,D9,E9,EB,01,DC,E9,D5,E5,1E,09,0A,BE
3840 ' TRK= 1             SEC= 11 
3850 DATA 20,0F,23,03,1D,20,F7,D1,E1,22,D9,E9,EB,22,D7,E9
3860 DATA C9,E1,11,10,00,19,D1,1D,20,CE,14,7A,FE,0D,20,C3
3870 DATA 3A,D9,E9,B7,28,10,2A,D7,E9,3A,DA,E9,BA,28,05,C6
3880 DATA 80,32,DA,E9,B7,C9,7B,C6,80,32,D9,E9,C9,CD,8F,4A
3890 DATA E5,CD,59,54,7E,B7,CA,86,E9,23,5E,23,66,6B,5F,E5
3900 DATA 57,CD,BA,DA,28,0B,47,CD,BA,DA,28,05,FE,3A,78,28
3910 DATA 06,3E,31,E1,E5,5A,37,E3,E1,F5,01,DC,E9,16,09,1C
3920 DATA 1D,28,3E,7E,FE,20,DA,86,E9,FE,2E,28,20,02,03,23
3930 DATA 15,20,ED,F1,F5,D6,31,DA,83,E9,FE,08,D2,83,E9,57
3940 DATA 3A,DC,E9,3C,CA,86,E9,F1,E1,C9,23,18,D3,7A,FE,09
3950 DATA CA,86,E9,FE,03,DA,86,E9,28,F0,3E,20,02,03,15,18
3960 DATA EC,3E,20,02,03,15,20,F9,18,C9,7E,23,1D,C9,CD,FD
3970 DATA 56,6F,3A,CE,E9,BD,DA,AD,E9,26,00,29,EB,2A,CF,E9
3980 DATA 19,7E,23,66,6F,3A,F0,E9,3C,C8,7E,B7,C8,E5,11,04
3990 DATA 00,19,7E,CD,EE,DA,E1,7E,B7,C9,3D,DA,83,E9,26,00
4000 DATA 6F,3A,C7,ED,3D,BD,DA,83,E9,7D,32,C6,ED,29,EB,2A
4010 ' TRK= 1             SEC= 12 
4020 DATA D1,E9,19,7E,23,66,6F,7E,22,D5,E9,3C,C9,2B,D7,FE
4030 DATA 23,CC,59,42,CD,FA,56,E3,E5,CD,C1,DA,CA,A1,E9,22
4040 DATA 4E,EB,E6,60,C0,EB,2A,D5,E9,7E,3C,EB,C0,77,C3,8F
4050 DATA E9,CD,3D,DA,D5,E5,CD,71,DB,E1,CD,9B,40,41,CD,9B
4060 DATA 40,53,CD,3D,DA,E3,7C,38,04,BA,C2,B9,E9,CD,EE,DA
4070 DATA CA,8F,E9,CD,DD,D9,CA,95,E9,CD,71,DB,CD,DD,D9,C2
4080 DATA 9E,E9,11,E5,E9,CD,77,DB,3A,DA,E9,57,CD,86,E5,E1
4090 DATA C9,21,DC,E9,11,E5,E9,06,09,4E,1A,77,79,12,13,23
4100 DATA 10,F7,C9,01,65,48,C5,CD,3D,DA,7E,FE,82,1E,04,20
4110 DATA 3F,D7,FE,85,1E,01,28,37,FE,DB,1E,40,28,31,FE,9C
4120 DATA 28,18,FE,49,28,1D,CD,9B,40,41,CD,9B,40,50,CD,9B
4130 DATA 40,50,CD,9B,40,81,1E,08,18,16,D7,CD,9B,40,C8,1E
4140 DATA 02,18,0D,D7,CD,9B,40,42,CD,9B,40,4D,1E,20,2B,D7
4150 DATA CD,9B,40,41,CD,9B,40,53,D5,7E,FE,23,CC,59,42,CD
4160 DATA FA,56,B7,CA,AD,E9,1E,D5,2B,5F,D7,C2,DF,3B,E3,7B
4170 DATA F5,E5,CD,C1,DA,C2,98,E9,D1,D5,E5,7A,CD,EE,DA,E1
4180 ' TRK= 1             SEC= 13 
4190 DATA D1,20,06,7B,E6,60,CA,8F,E9,73,23,36,FF,23,23,23
4200 DATA 72,F1,CD,19,DB,7E,36,00,47,32,DB,E9,E6,60,C2,B7
4210 DATA DC,78,F5,CD,DD,D9,28,10,F1,E6,86,CA,9E,E9,37,CD
4220 DATA D9,DC,CD,56,DF,C3,93,DC,E5,11,09,00,19,7E,23,5E
4230 DATA 2A,4E,EB,23,73,23,23,23,23,23,23,E6,F1,77,E1,F1
4240 DATA FE,08,28,29,47,E6,05,20,3A,C5,E5,CD,D9,DC,CD,17
4250 DATA DF,DA,98,E9,CD,33,D8,2A,4E,EB,23,36,FF,E1,F1,E6
4260 DATA 82,20,BF,77,3A,DA,E9,57,CD,86,E5,E1,C9,CD,AD,D9
4270 DATA 2A,4E,EB,23,23,70,23,B7,28,04,3D,77,18,0F,2A,4E
4280 DATA EB,36,02,2A,4E,EB,23,7E,23,77,23,36,00,23,23,AF
4290 DATA 77,23,36,00,23,7E,F6,02,77,CD,A3,E4,2B,77,2A,4E
4300 DATA EB,3A,DB,E9,77,E1,C9,23,11,EE,E9,1A,87,77,23,77
4310 DATA 13,1A,3D,FE,08,38,03,34,D6,08,23,77,E5,23,23,23
4320 DATA 23,7E,F6,20,77,E1,C3,9D,DC,D5,E5,2A,D5,E9,2B,F5
4330 DATA 7E,E6,10,C2,AA,E9,3E,14,CD,7C,01,3A,C6,ED,CD,83
4340 DATA 01,CD,E9,01,E6,40,C2,AA,E9,F1,D1,38,0C,F5,21,09
4350 ' TRK= 1             SEC= 14 
4360 DATA 00,19,7E,E6,10,C2,AA,E9,F1,EB,D1,C9,E5,B7,20,08
4370 DATA 3A,F0,E9,E6,01,C2,AC,E4,CD,C1,DA,28,20,22,4E,EB
4380 DATA E5,CD,D5,E4,28,13,2A,4E,EB,7E,E6,60,20,08,11,06
4390 DATA 00,19,7E,B7,28,23,CD,48,E6,CD,A3,E4,E1,E5,11,07
4400 DATA 00,19,77,67,6F,22,4E,EB,E1,86,36,00,28,06,2A,D5
4410 DATA E9,23,7E,B7,E1,C8,C3,E9,E4,2A,D5,E9,23,34,EB,2A
4420 DATA 4E,EB,01,02,00,09,6E,26,00,13,13,19,35,7E,FE,C0
4430 DATA 20,C7,2A,4E,EB,23,7E,26,00,6F,19,4F,7E,FE,C0,30
4440 DATA B8,47,6F,26,00,19,7E,FE,C0,78,38,EB,EB,06,00,09
4450 DATA 36,C8,EB,36,FF,2A,D5,E9,23,23,34,C3,39,DD,CD,3D
4460 DATA DA,1E,10,AF,CD,E7,DB,AF,C3,0C,DD,D8,E3,E1,37,11
4470 DATA F6,AF,F5,CD,3D,DA,F1,F5,28,0E,7E,D6,2C,B7,20,08
4480 DATA D7,CD,9B,40,52,F1,37,F5,F5,AF,1E,01,CD,E7,DB,2A
4490 DATA 4E,EB,01,07,00,09,F1,9F,E6,80,F6,01,32,F0,E9,F1
4500 DATA F5,9F,32,DB,E9,7E,B7,FA,81,DE,F1,C4,E1,3D,AF,CD
4510 DATA 19,DB,AF,3D,32,F3,E9,32,54,EA,C3,9F,3C,CD,3D,DA
4520 ' TRK= 1             SEC= 15 
4530 DATA 2B,D7,1E,80,37,28,0B,CD,9B,40,2C,CD,9B,40,41,B7
4540 DATA 1E,02,F5,3C,32,F1,E9,AF,CD,E7,DB,F1,D2,0C,57,E5
4550 DATA CD,86,5B,2A,54,EB,E5,CD,1F,E7,CD,2C,E7,0C,D1,2A
4560 DATA A0,EF,7D,93,6F,7C,9A,2C,2D,28,05,F2,3F,DE,3C,3C
4570 DATA FE,08,38,02,3E,08,B7,37,EB,C4,5B,E7,B7,F5,47,0E
4580 DATA 00,09,EB,2A,A0,EF,CD,95,40,28,0F,38,0D,F1,D5,CD
4590 DATA CF,D7,2A,4E,EB,23,23,71,18,BD,2A,4E,EB,23,23,5E
4600 DATA 16,00,CD,8D,D9,19,F1,86,77,CD,1A,D8,E1,AF,C3,0C
4610 DATA DD,F1,CA,C2,E9,CD,E1,3D,CD,08,E2,AF,CD,C1,DA,36
4620 DATA 80,22,4E,EB,CD,AD,D9,47,C5,2A,54,EB,E5,CD,1F,E7
4630 DATA CD,8D,D9,68,26,00,19,7E,FE,C0,30,23,E1,E5,F5,11
4640 DATA 00,08,19,CD,04,DF,F1,2A,4E,EB,23,23,77,CD,2C,E7
4650 DATA 0C,E1,3E,08,B7,CD,5B,E7,11,00,08,19,E5,18,CE,E1
4660 DATA C1,78,F5,57,1E,00,E5,14,19,CD,04,DF,CD,1F,E7,CD
4670 DATA 2C,E7,0C,E1,F1,B7,C4,5B,E7,CD,76,3D,23,22,A0,EF
4680 DATA CD,F4,3D,AF,32,F0,E9,CD,0C,DD,3A,DB,E9,B7,C2,FA
4690 ' TRK= 1             SEC= 16 
4700 DATA 41,C3,82,3C,EB,2A,50,EB,EB,CD,95,40,D8,CD,E1,3D
4710 DATA AF,32,F0,E9,C3,B4,3B,2A,4E,EB,23,46,23,23,23,4E
4720 DATA E5,2A,CF,E9,3A,CE,E9,3C,F5,F1,3D,FA,53,DF,F5,5E
4730 DATA 23,56,23,1A,B7,28,F2,13,1A,B8,20,ED,13,13,13,1A
4740 DATA B9,20,E6,F1,E3,F5,CD,95,40,20,04,F1,E3,18,DB,F1
4750 DATA E1,37,C9,E1,B7,C9,F5,3A,D9,E9,B7,F2,8A,DF,D6,82
4760 DATA B7,7A,32,DA,E9,30,17,E2,A7,E9,FE,0D,28,18,E5,2A
4770 DATA D3,E9,7E,F5,36,FF,14,CD,86,E5,F1,77,18,07,E5,01
4780 DATA 10,00,09,36,FF,E1,7B,32,D9,E9,3A,DA,E9,C6,80,57
4790 DATA E5,DC,6E,E5,CD,CF,D7,11,DC,E9,E1,CD,77,DB,F1,E6
4800 DATA 80,EB,2A,D5,E9,2B,B6,F5,3A,F1,E9,B7,28,08,AF,32
4810 DATA F1,E9,F1,E6,DF,F5,F1,12,2A,4E,EB,23,E5,23,23,23
4820 DATA 23,23,23,77,E1,7E,13,12,3A,DA,E9,E6,7F,57,C3,86
4830 DATA E5,F6,37,F5,CD,3C,4E,CD,FA,27,D5,CD,9B,40,F1,CD
4840 DATA 8F,4A,C1,E3,E5,C5,CD,59,54,46,E3,7E,4F,C5,E5,F5
4850 DATA 23,5E,23,56,B7,CA,55,E0,2A,54,EB,CD,95,40,30,30
4860 ' TRK= 2             SEC= 1 
4870 DATA 2A,A0,EF,CD,95,40,38,28,59,16,00,2A,50,EB,19,EB
4880 DATA 2A,79,EF,CD,95,40,DA,68,E0,F1,79,CD,03,53,E1,C1
4890 DATA E3,D5,C5,CD,59,54,C1,D1,E3,C5,E5,23,73,23,72,F5
4900 DATA F1,E1,23,5E,23,56,C1,E1,D5,23,5E,23,56,EB,D1,79
4910 DATA 90,30,01,41,79,90,4F,F1,D4,5F,E0,04,05,28,0B,7E
4920 DATA 12,23,13,18,F7,C1,C1,C1,C1,C1,DC,5F,E0,E1,C9,3E
4930 DATA 20,0C,0D,C8,12,13,18,FA,F1,E1,C1,E3,EB,20,09,C5
4940 DATA 78,CD,9B,52,CD,C8,52,C1,E3,C5,E5,F5,C3,19,E0,2B
4950 DATA D7,FE,23,CC,59,42,CD,FA,56,E5,CD,C1,DA,CD,6E,E6
4960 DATA D1,AF,47,4F,E5,09,EB,7E,FE,2C,C2,0A,E8,D5,C5,CD
4970 DATA F9,56,F5,7E,CD,9B,40,41,CD,9B,40,53,CD,3C,4E,CD
4980 DATA FA,27,F1,C1,E3,04,81,38,01,05,C2,A4,E9,EB,91,77
4990 DATA 81,23,73,23,72,D1,E1,18,CA,7E,CD,50,E1,F5,D5,CD
5000 DATA E6,E0,E3,4F,7E,E6,8F,81,77,E1,F1,D0,E5,3A,DA,E9
5010 DATA 57,CD,86,E5,E1,C9,7E,CD,9B,40,2C,CD,8F,4A,E5,CD
5020 DATA 59,54,7E,B7,CA,AC,E4,23,5E,23,56,47,0E,00,21,16
5030 ' TRK= 2             SEC= 2 
5040 DATA E1,E5,1A,13,FE,50,2E,10,C8,FE,52,2E,40,C8,FE,45
5050 DATA 2E,20,C8,2E,00,C9,79,B5,4F,10,E3,E1,C9,D7,CD,9B
5060 DATA 40,28,CD,50,E1,7E,CD,9B,40,29,E5,1A,F5,3E,03,CD
5070 DATA 9B,52,EB,F1,06,03,11,4A,E1,4F,1A,13,A1,1A,13,20
5080 DATA 02,3E,20,77,23,10,F3,C3,C8,52,40,52,20,45,10,50
5090 DATA FE,23,28,14,CD,8F,4A,CD,D8,4D,28,1D,CD,FD,56,E5
5100 DATA CD,EA,DA,2B,EB,E1,B7,C9,D7,CD,FA,56,E5,CD,C1,DA
5110 DATA CA,A1,E9,11,07,00,19,18,EB,CD,40,DA,E5,7A,CD,EE
5120 DATA DA,CA,8F,E9,CD,DD,D9,C2,9E,E9,11,09,00,19,EB,E1
5130 DATA 37,C9,3E,02,01,3E,04,01,3E,08,F5,CD,3A,52,F1,CD
5140 DATA 9B,52,2A,77,EF,CD,FD,26,C3,B4,54,3E,01,01,3E,03
5150 DATA 01,3E,07,F5,CD,59,54,F1,BE,D2,A5,44,3C,23,4E,23
5160 DATA 66,69,32,45,EF,C3,F5,26,01,57,D8,18,03,01,EE,D8
5170 DATA 3A,C7,ED,20,19,E5,C5,F5,11,DF,E1,D5,C5,B7,C9,F1
5180 DATA C1,3D,F2,D6,E1,E1,C9,C1,E1,7E,FE,2C,C0,D7,C5,7E
5190 DATA FE,23,CC,59,42,CD,FA,56,E3,E5,11,E7,E1,D5,37,E9
5200 ' TRK= 2             SEC= 3 
5210 DATA 01,0C,DD,3A,CE,E9,18,CB,3A,F0,E9,B7,F8,01,0C,DD
5220 DATA AF,3A,CE,E9,18,BD,AF,47,78,CD,C1,DA,36,00,3A,CE
5230 DATA E9,04,90,30,F3,06,00,78,CD,EE,DA,2B,36,00,23,36
5240 DATA FF,23,36,00,04,3A,C7,ED,90,20,EC,32,F0,E9,C9,3E
5250 DATA 01,32,49,EB,1E,01,28,08,CD,FA,56,2B,D7,C2,DF,3B
5260 DATA 7B,E5,CD,EA,DA,CA,8F,E9,16,01,CD,6E,E5,D5,06,10
5270 DATA 7E,3C,CA,C7,E2,3D,28,3D,16,09,7E,23,DF,15,28,18
5280 DATA 7A,FE,03,20,F5,E5,23,23,23,7E,E6,80,28,02,C6,0E
5290 DATA C6,20,E6,7F,DF,E1,18,E2,E5,C5,3E,20,DF,AF,CD,B3
5300 DATA D9,69,26,00,2C,CD,13,2D,C1,CD,CF,E2,E6,0F,28,0A
5310 DATA 3E,20,DF,18,F4,11,09,00,19,E5,E1,11,07,00,19,CD
5320 DATA DB,E2,4F,CD,CF,E2,C6,0F,B9,D4,DD,47,10,A2,D1,14
5330 DATA 7A,FE,0D,DA,5A,E2,D5,D1,CD,DD,47,E1,C3,65,48,3A
5340 DATA 49,EB,B7,3A,99,ED,C8,3A,48,EB,C9,3A,49,EB,B7,3A
5350 DATA 4A,EB,C8,3E,50,C9,F6,AF,F5,CD,0D,DB,7E,E6,60,C2
5360 DATA C2,E9,23,23,5E,23,4E,D1,F1,F5,D5,28,0A,23,23,23
5370 ' TRK= 2             SEC= 4 
5380 DATA 23,7E,E6,10,C2,AA,E9,E1,2B,D7,E3,E5,CA,77,E3,E1
5390 DATA E3,CD,9B,40,2C,2B,CD,A0,44,2B,D7,C2,DF,3B,E3,E5
5400 DATA CD,33,D9,30,29,F1,CA,BC,E9,F5,78,B7,28,17,2A,D5
5410 DATA E9,23,23,3D,BE,D2,A7,E9,C5,CD,CF,D7,C1,10,F9,C5
5420 DATA CD,AD,D9,58,C1,79,C6,C0,77,C5,CD,1A,D8,C1,CD,D5
5430 DATA E4,28,0F,F1,F5,7E,F6,04,77,43,F1,F5,C5,CC,48,E6
5440 DATA C1,58,2A,4E,EB,23,23,73,23,71,F1,F5,CC,BA,E5,F1
5450 DATA C4,9A,E5,E1,C3,65,48,CD,1F,E7,58,18,D1,E1,F1,E5
5460 DATA D5,C5,F5,2A,4E,EB,11,07,00,19,7E,E6,04,C2,BF,E9
5470 DATA 7E,E6,10,C2,AA,E9,7E,2B,2B,E6,02,E5,C4,19,E6,E1
5480 DATA 23,5E,23,7E,F6,08,77,23,7B,F1,E5,F5,D6,0D,28,05
5490 DATA 34,FE,13,9F,86,77,23,16,00,EB,19,F1,77,E1,F5,2B
5500 DATA 2B,34,7E,B7,CC,A0,E5,F1,C1,D1,E1,C9,C5,E5,D5,2A
5510 DATA 4E,EB,11,07,00,19,7E,E6,04,C2,BF,E9,7E,E6,02,2B
5520 DATA E5,D6,01,3F,DC,19,E6,E1,38,13,2B,7E,23,5E,34,BE
5530 DATA 23,20,04,7E,F6,02,77,23,23,16,00,19,7E,D1,E1,C1
5540 ' TRK= 2             SEC= 5 
5550 DATA C9,CD,CC,E3,DA,BC,E9,C3,50,23,D7,CD,9B,40,28,CD
5560 DATA 62,E4,F5,7E,CD,9B,40,29,F1,E5,CD,EA,DA,3E,FF,C5
5570 DATA CD,9B,52,EB,C1,E5,2A,D3,E9,3E,01,B7,CD,5B,E7,D1
5580 DATA 2A,D3,E9,EB,0E,FF,CD,58,E4,C3,C8,52,CD,62,E4,F5
5590 DATA 2B,D7,C2,DF,3B,E3,E5,2A,D3,E9,F1,E5,CD,EA,DA,E1
5600 DATA 37,3E,01,CD,5B,E7,E1,C9,E5,1A,77,23,13,0D,20,F9
5610 DATA E1,C9,CD,FA,56,F5,7E,CD,9B,40,2C,CD,FA,56,FE,02
5620 DATA D2,89,E9,32,EE,E9,7E,CD,9B,40,2C,CD,FA,56,FE,28
5630 DATA D2,89,E9,87,47,3A,EE,E9,80,32,EE,E9,F5,7E,CD,9B
5640 DATA 40,2C,CD,FA,56,3D,FE,10,D2,89,E9,3C,32,EF,E9,C1
5650 DATA 4F,F1,C9,CD,6B,E6,E5,06,00,CD,CF,E4,E1,C9,2A,4E
5660 DATA EB,11,08,01,19,06,FF,7E,B7,28,0A,FE,1A,78,C8,B7
5670 DATA 3C,23,C0,37,C9,78,D6,01,47,2B,30,EB,23,AF,C9,AF
5680 DATA 77,23,10,FC,C9,D5,2A,4E,EB,11,07,00,19,7E,E6,08
5690 DATA D1,C9,2A,D5,E9,23,7E,B7,C8,F5,C5,D5,E5,CD,F5,E4
5700 DATA E1,D1,C1,F1,C9,01,0E,00,21,F5,E9,7E,36,00,23,77
5710 ' TRK= 2             SEC= 6 
5720 DATA C5,CD,8D,D9,EB,06,25,AF,32,F4,E9,3E,01,37,CD,DA
5730 DATA E7,C1,30,01,04,0C,79,FE,11,38,E5,2B,2B,3A,F6,E9
5740 DATA 32,F5,E9,AF,77,B0,C8,FE,03,3F,D8,C6,30,DF,21,CA
5750 DATA D8,CD,ED,52,3A,C6,ED,C6,31,DF,C3,DD,47,D5,AF,32
5760 DATA F5,E9,06,25,4A,CD,8D,D9,EB,7B,B7,28,02,3E,FF,3C
5770 DATA CD,56,E5,9F,D1,C9,3E,01,2A,D3,E9,CD,39,E7,D8,CD
5780 DATA 8D,D9,2A,D3,E9,06,A0,7E,23,12,13,10,FA,C9,D5,4A
5790 DATA 06,25,AF,32,F5,E9,2A,D3,E9,3E,01,B7,E5,CD,DA,E7
5800 DATA DA,B3,E9,E1,D1,C9,D5,AF,32,F5,E9,32,F4,E9,4A,06
5810 DATA 25,2A,D3,E9,3E,01,37,C3,7C,E5,CD,73,E6,C3,57,E6
5820 DATA CD,57,E6,CD,73,E6,30,19,CD,A3,E4,36,1A,2B,2B,7E
5830 DATA F6,08,77,AF,2B,77,2B,36,00,C9,CD,74,E6,DA,BC,E9
5840 DATA 37,F5,CD,0E,E7,2A,4E,EB,CD,95,D9,0E,FF,30,29,CD
5850 DATA AE,E4,47,38,06,B7,20,03,06,00,37,9F,4F,F1,38,06
5860 DATA 79,3C,28,02,36,1A,2A,4E,EB,7E,FE,08,20,0D,36,02
5870 DATA 78,B7,F5,20,08,CD,A3,E5,F1,06,00,F5,AF,2A,4E,EB
5880 ' TRK= 2             SEC= 7 
5890 DATA 11,07,00,19,F5,7E,E6,FD,77,F1,2B,77,2B,70,F1,D0
5900 DATA 0C,CA,34,DA,04,05,C8,B7,C9,F5,CD,D5,E4,C4,48,E6
5910 DATA F1,F5,CD,75,E6,38,10,F1,F5,37,CD,C1,E5,38,08,F1
5920 DATA 23,23,23,23,7E,B7,C9,F1,D8,23,23,23,36,00,23,36
5930 DATA 00,23,7E,E6,FD,77,37,C9,2A,4E,EB,CD,95,D9,30,07
5940 DATA CD,AE,E4,38,02,36,1A,CD,1F,E7,7E,E6,F7,77,CD,2C
5950 DATA E7,CD,6B,E6,3E,01,37,CD,5B,E7,C9,2A,4E,EB,11,09
5960 DATA 00,19,C9,F6,37,2A,4E,EB,E5,F5,CD,95,D9,30,05,F1
5970 DATA DA,AC,E4,F5,E1,E3,7E,23,23,46,23,4E,E6,60,20,4D
5980 DATA 0C,79,FE,09,3F,30,1E,E5,CD,8D,D9,68,AF,67,19,0E
5990 DATA 01,46,E1,3E,BF,B8,30,2F,F1,F5,3F,30,2A,E5,CD,CF
6000 DATA D7,E1,41,0E,01,F1,F5,3F,30,1D,C5,E5,CD,8D,D9,68
6010 DATA 26,00,19,3E,C0,81,5F,7E,BB,30,0A,FE,C0,3F,30,05
6020 DATA 34,CD,1A,D8,37,E1,C1,E3,E1,71,2B,70,C9,FE,20,20
6030 DATA 12,0C,79,FE,09,38,03,04,0E,01,78,FE,A0,D2,A7,E9
6040 DATA 3F,18,E4,CD,2C,E7,E5,11,FF,E6,D5,2A,3B,EA,E9,78
6050 ' TRK= 2             SEC= 8 
6060 DATA E1,87,47,79,FE,09,38,03,04,D6,08,4F,18,DC,CD,1F
6070 DATA E7,7E,E6,F3,77,CD,2C,E7,23,23,3E,01,C3,5B,E7,2A
6080 DATA 4E,EB,23,23,46,23,4E,23,23,23,23,C9,78,B7,1F,47
6090 DATA 3E,00,30,02,C6,08,81,4F,C9,F5,3E,0A,32,C5,ED,F1
6100 DATA EB,F5,2A,D5,E9,34,28,02,70,34,35,F1,D5,F5,CD,99
6110 DATA 00,38,04,F1,E1,B7,C9,F1,E1,18,E5,F5,AF,32,F4,E9
6120 DATA E5,2A,4E,EB,7C,B5,28,0A,7E,B7,28,06,11,07,00,19
6130 DATA 18,04,2A,D5,E9,2B,7E,E6,20,32,F5,E9,7E,2F,E6,40
6140 DATA 32,C8,ED,E1,F1,5F,30,07,3A,C8,ED,B7,28,01,37,7B
6150 DATA F5,38,03,20,01,37,F5,3A,C8,ED,B7,3E,1A,20,02,3E
6160 DATA 19,CD,7C,01,F1,CD,E2,E7,38,1A,F1,3F,D0,3F,C0,F5
6170 DATA CD,CA,E7,D2,0A,E8,3A,F4,E9,3C,32,F4,E9,FE,04,38
6180 DATA C3,F1,37,C9,F1,20,FB,F5,18,EC,3E,06,CD,7C,01,CD
6190 DATA E9,01,E6,41,FE,01,37,C8,3F,C9,F5,E5,2A,D5,E9,2B
6200 DATA 18,9A,F5,E5,2A,D5,E9,7E,3C,28,0D,16,25,7A,90,28
6210 DATA 07,5F,7A,96,AB,FC,E2,E4,E1,F1,CD,39,E7,F5,78,FE
6220 ' TRK= 2             SEC= 9 
6230 DATA 25,C2,0A,E8,79,FE,0E,DC,E2,E4,F1,C9,CD,FD,56,CD
6240 DATA EA,DA,CA,8F,E9,23,23,6E,26,00,C3,A8,29,CD,BE,DA
6250 DATA CA,A1,E9,E5,CD,70,D9,CD,D3,D9,E1,23,23,23,6E,26
6260 DATA 00,19,C3,9C,27,CD,BE,DA,CA,A1,E9,CD,B0,D9,F5,CD
6270 DATA D3,D9,F1,6F,18,E9,CD,BE,DA,CA,A1,E9,E5,CD,95,D9
6280 DATA E1,20,0B,11,05,00,19,7E,23,96,B7,20,01,37,9F,C3
6290 DATA 89,26,CD,BE,DA,E5,23,23,4E,18,BC,D8,F1,E5,2A,4E
6300 DATA EB,7C,B5,E1,CA,3B,42,AF,CD,0C,DD,C3,9B,E9,FE,23
6310 DATA C0,CD,F9,56,CD,9B,40,2C,7B,E5,CD,19,DB,E1,7E,C9
6320 DATA 01,58,3E,C5,AF,C3,0C,DD,CD,D8,4D,01,99,49,11,20
6330 DATA 2C,20,18,5A,18,15,C1,01,65,48,C5,CD,7E,E8,CD,3C
6340 DATA 4E,CD,FA,27,D5,01,F9,45,AF,57,5F,F5,C5,E5,CD,CC
6350 DATA E3,DA,BC,E9,FE,20,20,04,14,15,20,F2,FE,22,20,0E
6360 DATA 47,7B,FE,2C,78,20,07,50,58,CD,CC,E3,38,47,21,96
6370 DATA EC,06,FF,4F,7A,FE,22,79,28,28,FE,0D,E5,28,50,E1
6380 DATA FE,0A,20,1E,4F,7B,FE,2C,79,C4,77,E9,E5,CD,CC,E3
6390 ' TRK= 2             SEC= 10 
6400 DATA E1,38,22,FE,0D,20,0B,7B,FE,20,28,12,FE,2C,3E,0D
6410 DATA 28,0C,B7,28,09,BA,28,0D,BB,28,0A,CD,77,E9,E5,CD
6420 DATA CC,E3,E1,30,BE,E5,FE,22,28,04,FE,20,20,27,CD,CC
6430 DATA E3,38,22,FE,20,28,F7,FE,2C,28,1A,FE,0D,20,09,CD
6440 DATA CC,E3,38,11,FE,0A,28,0D,2A,4E,EB,01,06,00,09,35
6450 DATA 23,7E,E6,FD,77,E1,36,00,21,95,EC,7B,D6,20,28,07
6460 DATA 06,00,CD,AC,52,E1,C9,CD,D8,4D,F5,D7,F1,F5,DC,BE
6470 DATA 2B,F1,D4,B7,2B,E1,C9,B7,C8,77,23,05,C0,C1,28,D6
6480 DATA 1E,40,01,1E,41,01,1E,3E,01,1E,42,01,1E,3B,01,1E
6490 DATA 38,01,1E,43,01,1E,3A,01,1E,37,01,1E,3F,01,1E,35
6500 DATA 01,1E,47,01,1E,32,01,1E,3C,01,1E,48,01,1E,34,01
6510 DATA 1E,33,01,1E,39,01,1E,49,01,1E,44,01,1E,3D,01,1E
6520 DATA 45,01,1E,46,AF,32,F0,E9,32,F1,E9,C3,F9,3B,00,00
6530 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
6540 DATA 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
6550 DATA 00,00,00,00,00,00,00,00,00,C3,C0,D4,00,01,41,53
