10 INPUT "物体１の質量は (Kg)";M1
20 INPUT "物体２の質量は (Kg)";M2
30 INPUT "物体間の距離は (m)";L
40 GOSUB *INRYOKU
50 PRINT "万有引力の大きさは ";P;"(N) ";P/9.8;"(kg重)"
60 END
70 *INRYOKU
80 P = M1 * M2 / L / L * 6.67E-11
90 RETURN
