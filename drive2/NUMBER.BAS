' {8801}
NEW CMD
RANDOMIZE VAL(MID$(TIME$,7,2))
NUM=1+INT(RND(1)*50)
PRINT "*** ∂Ωﬁ ±√ πﬁ∞— ***"
PRINT "‹¿º … ∫∫€ ∆ ±Ÿ ∂Ωﬁ ¶ ±√√»!"
*MAINLOOP
INPUT "∂Ωﬁ ¶ ∆≠≥ÿÆ∏ º√» (1-50)";N
IF N=NUM THEN *HIT
IF N<NUM THEN BEEP:PRINT N;"÷ÿ µµ∑≤ √ﬁΩ"
IF N>NUM THEN BEEP:PRINT N;"÷ÿ ¡≤ª≤ √ﬁΩ"
GOTO *MAINLOOP
*HIT
PRINT "æ≤∂≤ √ﬁΩ!!!"
CMD PLAY "T215@0L8DGB<D1"
