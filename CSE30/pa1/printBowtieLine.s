/*
 * Filename:printBowtieLine.s
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: print a line of bowtie figure
 * Data: 04/20/2018
 * Source of help: TutorialsPoint
 */

@ Raspberry Pi directives 
	.cpu    cortex-a53
	.syntax unified
	
	.section .rodata
	

	.equ    FP_OFFSET, 4
	.equ 	DECLARE_OFF, 24
	.equ	INDEX_OFF, -8
	.equ	LIMIT_OFF, -12
	.equ	ROW_OFF, -16
	.equ	HEIGHT_OFF, -20
	.equ	BOWTIE_OFF, -24
	.equ 	FILLER_OFF, -28
	
	.equ	WIDTH_MUL, 2

	.global  printBowtieLine

	.text
	.align 2
	
/*
 * Function Name: printBowtieLine()
 * Function Prototype: void printChar( long row, long height,char bowtie);
 * Description: print line of char to form a line of bowtie
 * Parameters: row, height, bowtie and filler
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *    r0 - row
 *    r1 - height
 *    r2 - bowtie
 *    r3 - filler
 */

printBowtieLine:
@ Standard prologue
	push    {fp, lr}                @ Save registers: fp, lr
	add     fp, sp, FP_OFFSET       @ Set fp to base of saved registers
	sub 	sp, sp, DECLARE_OFF	@ ????????????????????????????

@ Incoming parameters in r0
	str	r0, [fp,ROW_OFF]	@ store row to stack
	str 	r1, [fp,HEIGHT_OFF]	@ store height to stack
	str	r2, [fp,BOWTIE_OFF]	@ store bowtie char to stack
	str	r3, [fp,FILLER_OFF]	@ store filler char to stack

	mov	r2, WIDTH_MUL
	mul	r1, r1, r2	
	mul	r0, r0, r2
	sub	r0, r1, r0
	sub 	r0, r0, 1		@ calculate limit for 2nd loop
	str	r0, [fp,LIMIT_OFF]	@ store the limit to stack

 	mov	r1, WIDTH_MUL
	ldr	r0, [fp, ROW_OFF]

	mul	r0, r1, r0		@ calculate startnig index
	str	r0, [fp,INDEX_OFF]	@ store the index to stack

	cmp	r0, 1			@ check if index out of limit
	blt	end_Lloop		@ opposite logic	
loop:
	ldr 	r0, [fp,BOWTIE_OFF]	@ pass in para
	bl	printChar		@ print the char
	
	ldr	r0, [fp,INDEX_OFF]	@ load the index back
	sub	r0, r0, 1		@ decrement the index
	str	r0, [fp,INDEX_OFF]	@ store the index back
	cmp	r0, 1
	bge	loop			@ positive logic 

end_Lloop:

 	mov	r1, WIDTH_MUL
	ldr	r0, [fp, ROW_OFF]
	mul	r0, r1, r0		@ calculate startnig index
	str	r0, [fp,INDEX_OFF]	@ store the index to stack

	ldr	r1, [fp,LIMIT_OFF]	@ load the limit
	cmp	r0, r1			@ check if index out of limit
	bgt	end_Iloop		@ opposite logic	
iloop:
	ldr 	r0, [fp,FILLER_OFF]	@ pass in para
	bl	printChar		@ print the char
	
	ldr	r0, [fp,INDEX_OFF]	@ load the index back
	add	r0, r0, 1		@ decrement the index
	str	r0, [fp,INDEX_OFF]	@ store the index back
	ldr	r1, [fp,LIMIT_OFF]	@ load the limit 
	cmp	r0, r1
	ble	iloop			@ positive logic 
end_Iloop:

 	mov	r1, WIDTH_MUL
	ldr	r0, [fp, ROW_OFF]
	mul	r0, r1, r0		@ calculate startnig index
	str	r0, [fp,INDEX_OFF]	@ store the index to stack

	cmp	r0, 1			@ check if index out of limit
	blt	end_Rloop		@ opposite logic	
rloop:
	ldr 	r0, [fp,BOWTIE_OFF]	@ pass in para
	bl	printChar		@ print the char
	
	ldr	r0, [fp,INDEX_OFF]	@ load the index back
	sub	r0, r0, 1		@ decrement the index
	str	r0, [fp,INDEX_OFF]	@ store the index back
	cmp	r0, 1
	bge	rloop			@ positive logic 
end_Rloop:

@ Standard epilogue
	sub     sp, fp, FP_OFFSET       @ Set sp to top of saved registers
	pop     {fp, pc}                @ Restore fp; restore lr into pc for
					@ 	return
