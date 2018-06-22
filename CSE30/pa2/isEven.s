/*
 * Filename: isEven.s 
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: This function check if value is even  
 * Date: April.13.2018
 * Sources of Help: Man page
 */
 
@ Raspberry Pi directives
	.cpu	cortex-a53	@ version of pis
	.syntax unified		@ modern arm syntax

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs

	.global isEven		@ specify func as a global symbol

	.text 			@ Switch to Text segment
	.align 2		@ align on evenly divisible by 4 byte address
				@ .align n where 2^n determines alignment
/*
 * Function Name: isEven()
 * Function Prototype: long isEven ( long value )
 * Description: teh function check if value is an even number
 * Parameters:  long value
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 0 if value is odd; 1 if value is even 
 * Registers used:
 *	r0 - arg1 -- value  
 */ 

isEven:	
	@ Standard prologue 
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add 	fp, sp, FP_OFFSET 	@ Set fp to base of saved registers

	@ Incoming parameters in r0,r1,r2
	mov 	r1, 2			@ para 2 for myRemainder is 2
	bl	myRemainder		@ call myRemainder
	
	cmp 	r0, 0			@ check if remainder is 0
	beq 	even	

	mov	r0, 0			@ 0 for odd
	b	end			@ jump over even block
even:
	mov	r0, 1			@ 1 for even
end:
	@ Standard epilogue
	sub 	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc 


