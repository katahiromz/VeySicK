100 ' END sample
110 PRINT "Hit 'e' key to end!"
120 A$=INPUT$(1)
130 IF A$="e" OR A$="E" THEN END ELSE PRINT A$:GOTO 120
