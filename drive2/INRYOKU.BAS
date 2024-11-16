10 INPUT "•¨‘Ì‚P‚ÌŽ¿—Ê‚Í (Kg)";M1
20 INPUT "•¨‘Ì‚Q‚ÌŽ¿—Ê‚Í (Kg)";M2
30 INPUT "•¨‘ÌŠÔ‚Ì‹——£‚Í (m)";L
40 GOSUB *INRYOKU
50 PRINT "–œ—Lˆø—Í‚Ì‘å‚«‚³‚Í ";P;"(N) ";P/9.8;"(kgd)"
60 END
70 *INRYOKU
80 P = M1 * M2 / L / L * 6.67E-11
90 RETURN
