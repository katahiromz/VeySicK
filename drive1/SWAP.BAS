100 ' SWAP sample
110 A$="ÀÛ°":B$="ÊÅº":C$="±²¼Ã²Ï½":D$="·×¯Ã²Ï½"
120 GOSUB 160
130 SWAP A$,B$:SWAP C$,D$
140 GOSUB 160
150 END
160 PRINT USING "& & Ê & & ¦ &     &";A$,B$,C$
170 RETURN
