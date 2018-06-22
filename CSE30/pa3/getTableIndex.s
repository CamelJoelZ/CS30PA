/*
 * Filename: getTableIndex.s 
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: This function will calculate the index into the hashtable  
 * Date: May.13.2018
 * Sources of Help: Man page
 */
 
@ Raspberry Pi directives
	.cpu	cortex-a53	@ version of pis
	.syntax unified		@ modern arm syntax

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs
	.equ 	LOCAL_OFF, 8	
	.equ	NAME, -8
	.equ	SIZE, -12

	.global getTableIndex	@ specify hash as a global symbol

	.text 			@ Switch to Text segment
	.align 2		@ align on evenly divisible by 4 byte address
				@ .align n where 2^n determines alignment
/*
 * Function Name: getTableIndex()
 * Function Prototype: int getTableIndex( char const * name, size_t tableSi 
 * Description: This function will calculate the index into the hashtable 
 * Parameters:  char const * name
 *		size_t tableSize
 * Side Effects: None
 * Error Conditions: None
 * Return Value: return the index of name in the hashtable 
 *
 * Registers used:
 *	r0 - arg1 -- str
 *	r1 - arg2
 */ 

getTableIndex:	
	@ Standard prologue 
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add 	fp, sp, FP_OFFSET 	@ Set fp to base of saved registers
	sub 	sp, sp, LOCAL_OFF       @ allocate local var

	@ Incoming parameters in r0,r1,r2
	str	r0, [fp, NAME]		@ store para before func call
	str	r1, [fp, SIZE]

	bl	hash	
	cmp	r0, 0			@ check if hash value is negative
	bge	positive
negative:
	neg	r0, r0			@ turn negative to positive
positive:
	ldr	r1, [fp, SIZE]		@ second para = tableSize
	bl	myRemainder

	@ Standard epilogue
	sub 	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc 


