100 ' CMD SOUND sample
110 CMD STOPM
120 CMD SOUND 7,7
130 CMD SOUND 23,7
140 CMD SOUND 6,30
150 CMD SOUND 22,30
160 CMD SOUND 13,12
170 CMD SOUND 29,12
180 FOR I=1 TO 30
190  FOR L=0 TO 15
200   CMD SOUND 8,L
210  NEXT L
220  FOR L=15 TO 0 STEP -3
230   CMD SOUND 8,L
240  NEXT L
250 NEXT I
260 END
