/*
 * Filename: myRemainder.s
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: This function return the remainder after division.
 * Date: April.13.2018
 * Sources of Help: Man page
 */
 
@ Raspberry Pi directives
	.cpu	cortex-a53	@ version of pis
	.syntax unified		@ modern arm syntax

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs

	.global myRemainder	@ specify func as a global symbol

	.text 			@ Switch to Text segment
	.align 2		@ align on evenly divisible by 4 byte address
				@ .align n where 2^n determines alignment
/*
 * Function Name: myRemainder()
 * Function Prototype: long myRemainder( long dividend, long divisor )
 * Description: return the remainder after division.
 * Parameters:  long dividend
 *	  	long divisor
 * Side Effects: None
 * Error Conditions: None
 * Return Value: -1 if Divisor is zero, else the remainder 
 * Registers used:
 *	r0 - arg1 -- dividend 
 *      r1 - arg2 -- divisor
 */ 

myRemainder:	
	@ Standard prologue 
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add 	fp, sp, FP_OFFSET 	@ Set fp to base of saved registers

	@ Incoming parameters in r0,r1,r2
	sdiv 	r2, r0, r1		@ save the result to r2
	mul	r2, r2, r1		@ save the result to r2
	sub 	r0, r0, r2 		@ return the remainder

	@ Standard epilogue
	sub 	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc 


