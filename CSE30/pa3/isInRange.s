/*
 * Filename: isInRange.s
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: This function determines whether value is in
 * the range between minRange (inclusive) and maxRange
 * Date: April.13.2018
 * Sources of Help: Man page
 */
 
@ Raspberry Pi directives
	.cpu	cortex-a53	@ version of pis
	.syntax unified		@ modern arm syntax

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs

	.global isInRange	@ specify sum3 as a global symbol

	.text 			@ Switch to Text segment
	.align 2		@ align on evenly divisible by 4 byte address
				@ .align n where 2^n determines alignment
/*
 * Function Name: isInRange()
 * Function Prototype: long isInRange( long value, long minRange, long maxRang
 * Description: determines whether value is in the range between minRange 
 * (inclusive) and maxRange (exclusive
 * Parameters:  long value 
 *	  	long minRange
 *		long maxRange 
 * Side Effects: None
 * Error Conditions: None
 * Return Value: -1 if an error occurred. Otherwise, return 1 
 *	 if value is in range and 0 if not in range.
 *
 * Registers used:
 *	r0 - arg1 -- VALUE
 *      r1 - arg2 -- MINRANGE
 *	r2 - arg3 -- MAXRANGE
 */ 

isInRange:	
	@ Standard prologue 
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add 	fp, sp, FP_OFFSET 	@ Set fp to base of saved registers

	@ Incoming parameters in r0,r1,r2
	cmp 	r1, r2			@ compare min range and max range
	bge 	error			@ branch to error

	cmp	r0, r1 			@ compare value with min range
	blt	outRange		@ branch outRange if value < minRange
	
	cmp	r0, r2			@ compare value with max range
	bge 	outRange		@ branch outRange if value >= maRange

	mov 	r0, 1 			@ return 1 if within range
	b 	end

outRange:
	mov 	r0, 0 			@ return 0 if out of range	
	b 	end			@ go to the end of the func
error:
	mov 	r0, -1 
end:

	@ Standard epilogue
	sub 	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc 


