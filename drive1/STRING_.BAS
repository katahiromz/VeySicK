100 ' STRING$ sample
110 INPUT "Ó¼ÞÚÂ ¦ Æ­³Ø®¸ ¼Ã ¸ÀÞ»²";A$
120 L=LEN(A$)
130 PRINT STRING$(L+4,"+")
140 PRINT "+ ";SPC(L+1);"+"
150 PRINT "+ ";A$;" +"
160 PRINT "+ ";SPC(L+1);"+"
170 PRINT STRING$(L+4,"+")
180 END
