100 ' VAR.BAS ý� ��۸���
110 A(3)=2:? A(3)
120 ERASE A:A=5
130 DIM A(12),M$(3)
140 A(11)=3:WRITE A,A(11)
150 M$(2)="JJJ":WRITE M$(2):M$(2)="KK":WRITE M$(2)
160 ERASE A,M$
170 WRITE A(3),M$(2)
180 C(100)=3
190 '***EXPECTED OUTPUT***
200 ' 2
210 '5,3
220 '"JJJ"
230 '"KK"
240 '0,""
250 'Subscript out of range
