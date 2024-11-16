100 INPUT "´²½³¼Þ ¦ ÅÆ¶ ³¯Ã ¸ÀÞ»²",A$
110 PRINT
120 PRINT "¾ÞÝÀ² ¦ 2Â Æ ÌÞÝ¶Â ¼Ï½"
130 AL$=LEFT$(A$,LEN(A$)\2)
140 AR$=RIGHT$(A$,LEN(A$)-LEN(A$)\2)
150 PRINT AL$;SPACE$(3);AR$
160 PRINT
170 PRINT "2Ó¼Þ ½ÞÂ Æ Ü¹Ï½"
180 FOR I=1 TO LEN(A$) STEP 2
190  PRINT MID$(A$,I,2);SPACE$(3);
200 NEXT
210 END
