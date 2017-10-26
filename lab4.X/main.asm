LIST p=18f4520		
#include<p18f4520.inc>
#include<lab4mac.asm>

ORG	0x00 ; setting initial address
    
INITIAL:    NUMS10	     ;// 載入16組數字至120~12F address
	    LFSR 0,0X120    ; 設定FSR0為0x120當作i
	    LFSR 1,0X120    ; 設定FSR1為0x120當作j  
	    
MAIN:	    NOP
	    NOP
	    rcall SBRT
	    GOTO CHECK ; 排序完後跳至check檢查排序是否正確
	    
SBRT:	    ; // 可任意的增加label數量
DO1:
	    movff FSR0L,FSR1L
	    movff FSR0H,FSR1H
	    rcall SBRT2
	    INCF FSR0L
	    btfss  FSR0L, 4
	    GOTO DO1
	    return
	    
SBRT2:	  
	    MOVF INDF0 , 0, 0
	    CPFSLT INDF1
	    GOTO ED
	    SWAP INDF0, INDF1
ED:	    INCF FSR1L
	    btfss  FSR1L, 4
	    GOTO SBRT2
	    return
	    
CHECK:	    RTLST ; 檢查是否排序正確
	    NOP
	    END