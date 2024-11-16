100 ' KPLOAD ƒTƒ“ƒvƒ‹ {SJIS}
110 SCREEN 3
120 DIM CHRPTN%(17)
130 CHRPTN%(0)=16
140 CHRPTN%(1)=16
150 CHRPTN%(2)=&HC007   '      *****     
160 CHRPTN%(3)=&H3018   '    **     **   
170 CHRPTN%(4)=&H0841   '   *    *    *  
180 CHRPTN%(5)=&H8442   '  *    * *    * 
190 CHRPTN%(6)=&H4444   '  *   *   *   * 
200 CHRPTN%(7)=&H2488   ' *   *     *   *
210 CHRPTN%(8)=&HD287   ' *  * ***** *  *
220 CHRPTN%(9)=&H0281   ' *      *      *
230 CHRPTN%(10)=&HC287  ' *    *****    *
240 CHRPTN%(11)=&H2289  ' *   *  *  *   *
250 CHRPTN%(12)=&H4285  ' *    * * *    *
260 CHRPTN%(13)=&H0441  '  *     *     * 
270 CHRPTN%(14)=&HE44F  '  *  *******  * 
280 CHRPTN%(15)=&H0820  '   *         *  
290 CHRPTN%(16)=&H3018  '    **     **   
300 CHRPTN%(17)=&HE007  '      ******    
310 KPLOAD &HEB9F,CHRPTN%
320 PRINT CHR$(&HEB9F)
