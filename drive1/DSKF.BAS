100 ' DSKF sample
110 INPUT "drive number";DR
120 PRINT "Track  =";DSKF(DR,0);"/Drive"
130 PRINT "Sector =";DSKF(DR,1);"/Track"
140 PRINT "Disk space =";DSKF(DR)
150 END
