100 ' ************************************
110 ' *    マウスのサンプルプログラム    *
120 ' ************************************
130 CLS 3:C=4
140 LOCATE 0,2:PRINT "右ボタンを押すとカーソルが青になります"
150 LOCATE 0,1:PRINT "左ボタンを押すと線が引けます"
160 MOUSE 0
170 ON MOUSE(2) GOSUB *DRAWLINE   :MOUSE(2) ON
180 ON MOUSE(3) GOSUB *CHANGEMODE :MOUSE(3) ON
190 ON MOUSE(4) GOSUB *STOPDRAW   :MOUSE(4) ON
200 MOUSE 1,,,1
210 LOCATE 10,1:PRINT "押すと線が引けます"
220 GOSUB *DISPLAYCOORDINATE
230 GOTO 210
240 '
250 *MOUSEEND
260 MOUSE 6
270 CLS 3:END
280 '
290 ' **************************************
300 ' *    このプログラムのサブルーチン    *
310 ' **************************************
320 *DRAWLINE
330 FLAG=0
340 LOCATE 10,1:PRINT "離すと元に戻ります"
350 POINT(MOUSE(0),MOUSE(1))
360 MOUSE 1,,,0:LINE -(MOUSE(0),MOUSE(1)),C:MOUSE 1,,,1
370 IF FLAG=0 THEN 360 ELSE RETURN 220
380 '***********************************
390 *STOPDRAW
400 FLAG=-1:RETURN
410 '***********************************
420 *CHANGEMODE
430 IF MODE=3 THEN RETURN *MOUSEEND
440 MOUSE 5,MODE:MODE=MODE+1
450 LOCATE 26,2
460 ON MODE GOTO 470,480,490
470 PRINT "赤":C=1:RETURN
480 PRINT "緑":C=2:RETURN
490 PRINT "消えてプログラムが終了します":C=4:RETURN
500 '***********************************
510 *DISPLAYCOORDINATE
520 MOUSE(3) STOP
530 LOCATE 0,0:PRINT "X=";MOUSE(0),"Y=";MOUSE(1)
540 MOUSE(3) ON
550 RETURN
