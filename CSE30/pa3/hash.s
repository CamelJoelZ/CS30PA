/*
 * Filename: hash.s
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: This function will be used to create the 
 *	hash key of a string.  
 * Date: May.13.2018
 * Sources of Help: Man page
 */
 
@ Raspberry Pi directives
	.cpu	cortex-a53	@ version of pis
	.syntax unified		@ modern arm syntax

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs
	.equ 	LOCAL_OFF, 16
	.equ	HASH, -8
	.equ	STRLEN, -12
	.equ	STR, -16

	.global hash            @ specify hash as a global symbol

	.text 			@ Switch to Text segment
	.align 2		@ align on evenly divisible by 4 byte address
				@ .align n where 2^n determines alignment
/*
 * Function Name: hash()
 * Function Prototype: int hash( char const * str ); 
 * Description: create the hash key of a string 
 * Parameters:  char const * str 
 * Side Effects: None
 * Error Conditions: None
 * Return Value: return the key of str 
 *
 * Registers used:
 *	r0 - arg1 -- str
 *	r1 - hash
 *	r2 - strlen
 */ 

hash:	
	@ Standard prologue 
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add 	fp, sp, FP_OFFSET 	@ Set fp to base of saved registers
	sub 	sp, sp, LOCAL_OFF       @ allocate local var

	@ Incoming parameters in r0,r1,r2
	ldr	r1, =HashStartVal	@ Global in pa3Globals.c
	ldr	r1, [r1]
	str	r1, [fp, HASH]
	
	str 	r0, [fp, STR]		@ save para before caling func
	bl	strlen			

	str	r0, [fp, STRLEN]	@ store strlen on stack
	ldr	r0, [fp, HASH]
	
	mov	r1, 0			@ r2 : int i = 0	
	ldr	r2, [fp, STRLEN]	@ r1 : strLen
	cmp	r1, r2			@ if i < strLen
	bge	end_loop	

loop:
	ldr	r2, =HashPrime		
	ldr	r2, [r2]
	ldr	r0, [fp, HASH]	
	mul	r2, r2, r0		@ hash*HASH_PRIME
	
	ldr	r0, [fp, STR]		@ access the str[i]
	add	r0, r0, r1		@ str = str + i
	ldrb	r0, [r0]		@ r0: str[i]
	add	r0, r0, r2		@ hash * HASH_PRIME + str[i]
	str	r0, [fp, HASH]		@ hash = ...

	add	r1, r1, 1		@ increment the index
	ldr 	r2, [fp, STRLEN]	@ r1: strLen
	cmp 	r1, r2
	blt	loop			@ positive logic
end_loop:

	@ Standard epilogue
	sub 	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc 


