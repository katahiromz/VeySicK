100 ' SWAP sample
110 ' �o�u���\�[�g
120 C=100:DIM A(C)
130 ' �����Ő���100����
140 FOR I=1 TO C
150  A(I)=RND*100
160 NEXT
170 ' �����ŕ��בւ�
180 FOR I=1 TO C-1
190  FOR J=I+1 TO C
200   IF A(I)>A(J) THEN SWAP A(I),A(J)
210  NEXT J
220 NEXT I
230 FOR I=1 TO C
240  PRINT USING "####";A(I);
250 NEXT
