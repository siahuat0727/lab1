#include <xc.inc>
GLOBAL _add
    
    PSECT mytext, local, class=CODE, reloc=2
 
    var1L	equ 0x01
    var1U	equ 0x02
    var2L	equ 0x03
    var2U	equ 0x04
	
_add:
    ;add 1L 2L to 1L
    movf    var2L, w
    addwf   var1L, f
    
    ;add 1U 2U and carry to 1U
    movf   var2U, w
    addwfc  var1U, f
    
    return
    
    


