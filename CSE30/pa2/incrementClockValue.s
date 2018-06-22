/*
 * Filename:incrementClockValue.s 
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: This function increment the bcd bits 
 * Date: April.29.2018
 * Sources of Help: Man page
 */
 
@ Raspberry Pi directives
	.cpu	cortex-a53	@ version of pis
	.syntax unified		@ modern arm syntax

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs
	.global incrementClockValue @ specify func as a global symbol

	.text 			@ Switch to Text segment
	.align 2		@ align on evenly divisible by 4 byte address
				@ .align n where 2^n determines alignment
/*
 * Function Name: incrementClockValue()
 * Function Prototype: unsigned char incrementClockValue
 * Description: increment the 4 bcd bits 
 * Parameters:  unsigned char BCDbits,
 		const unsigned int maxValue
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 0 if value is odd; 1 if value is even 
 * Registers used:
 *	r0 - arg1 -- value  
 */ 

incrementClockValue:	
	@ Standard prologue 
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add 	fp, sp, FP_OFFSET 	@ Set fp to base of saved registers

	@ Incoming parameters in r0,r1,r2
	add	r0, r0, 1		@ increment the bcdbits
	cmp	r0, r1			@ negative logic to else
	ble	else
if:
	mov	r0, 0
else:
	@ Standard epilogue
	sub 	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc 


