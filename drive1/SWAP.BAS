100 ' SWAP sample
110 A$="�۰":B$="�ź":C$="���òϽ":D$="�ׯòϽ"
120 GOSUB 160
130 SWAP A$,B$:SWAP C$,D$
140 GOSUB 160
150 END
160 PRINT USING "& & � & & � &     &";A$,B$,C$
170 RETURN
