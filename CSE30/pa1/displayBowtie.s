/*
 * Filename:displayBowtie.s
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: display the bowtie 
 * Data: 04/20/2018
 * Source of help: TutorialsPoint
 */

@ Raspberry Pi directives 
	.cpu    cortex-a53
	.syntax unified
	
	.section .rodata
	

	.equ    FP_OFFSET, 4
	.equ 	LOCAL_OFFSET, 16
	.equ	PARAM_OFFSET, 16
	.equ	ROW_OFF, -8
	.equ	COL_OFF, -12
	.equ	INNER_OFF, -16
	.equ	LIMIT, -20
	.equ	HEIGHT_OFF, -24
	.equ 	BORDER_OFF, -28
	.equ	FILLER_OFF, -32
	.equ	BOWTIE_OFF, -36
	
	.equ	HALF_DIVISOR, 2 
	.equ	WIDTH_MUL, 2
	.equ	NL, '\n'
	
	.global  displayBowtie

	.text
	.align 2
	
/*
 * Function Name: displayBowtie()
 * Function Prototype: void displayBowtie
 *	( long row, long height,char bowtie);
 * Description: display the bowtie
 * Parameters:  height, border, bowtie and filler
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *    r0 - height
 *    r1 - border
 *    r2 - filler
 *    r3 - bowtie
 */

displayBowtie:
@ Standard prologue
	push    {fp, lr}                @ Save registers: fp, lr
	add     fp, sp, FP_OFFSET       @ Set fp to base of saved registers
	sub 	sp, sp, LOCAL_OFFSET	@ ????????????????????????????
	sub	sp, sp, PARAM_OFFSET	

@ Incoming parameters in r0
	str	r0, [fp,HEIGHT_OFF]	@ store row to stack
	str 	r1, [fp,BORDER_OFF]	@ store height to stack
	str	r2, [fp,FILLER_OFF]	@ store bowtie char to stack
	str	r3, [fp,BOWTIE_OFF]	@ store filler char to stack
	
	mov	r3, 0			@ initialize col
	str	r3, [fp,COL_OFF]	@ store col to stack
	mov	r1, WIDTH_MUL		
	mul	r1, r1, r0		@ height*WIDTH_MUL
	add	r1, r1, 1
	str	r1, [fp,LIMIT]		@ save the loop limit
	cmp	r3, r1			
	bgt	end_for			@ opposite logic
for:
	ldr	r0,[fp,BORDER_OFF]	@ pass in para
	bl	printChar
	
	ldr	r0, [fp,COL_OFF]
	add	r0, r0, 1		@ increment col
	str	r0, [fp,COL_OFF]
	ldr	r1, [fp,LIMIT]
	cmp	r0, r1
	ble	for			@ positive logic
end_for:
	mov	r0, NL			@ print out nl
	bl	printChar

	mov 	r0, 1			@ initialize row to 1
	str	r0, [fp,ROW_OFF]	@ store row to stack
	ldr	r1, [fp,HEIGHT_OFF]	@ load height
	mov	r2, HALF_DIVISOR
	sdiv	r1, r1, r2
	str	r1, [fp,LIMIT]		@ save limti to stack
	cmp	r0, r1			@ opposite logic
	bgt	end_top_half		

top_half:
	ldr	r0, [fp, BORDER_OFF]
	bl	printChar		@ print out boder
	
	ldr	r0, [fp,ROW_OFF]
	ldr	r1, [fp,HEIGHT_OFF]
	ldr	r2, [fp,BOWTIE_OFF]
	ldr	r3, [fp,FILLER_OFF]
	bl	printBowtieLine

	ldr	r0, [fp, BORDER_OFF]
	bl	printChar		@ print out boder
	
	mov	r0, NL			@ print out nl
	bl	printChar

	ldr	r0, [fp,ROW_OFF]
	add	r0, r0, 1		@ increment row
	str	r0, [fp,ROW_OFF]
	ldr	r1, [fp,LIMIT]
	cmp	r0, r1			@ positive logic to loop
	ble	top_half

end_top_half:
	ldr	r0, [fp,BORDER_OFF]
	bl	printChar		@ print out left border
	
	mov	r0, 0			@ initialize inner to 0
	str	r0, [fp,INNER_OFF]

	mov	r1, WIDTH_MUL
	ldr	r2, [fp,HEIGHT_OFF]
	mul	r1, r1, r2		@ height*WIDTH_MUL
	str	r1, [fp,LIMIT]		

	cmp	r0, r1
	bge 	end_bowtie
bowtie:
	ldr	r0, [fp,BOWTIE_OFF]	@ print out bowtie
	bl	printChar

	ldr	r1, [fp,INNER_OFF]	@ load inner
	add	r1, r1, 1		@ increment
	str	r1, [fp,INNER_OFF]
	ldr	r2, [fp,LIMIT]		@ load limit
	cmp	r1, r2			@ positive logic to loop
	blt	bowtie
end_bowtie:

	ldr	r0, [fp,BORDER_OFF]
	bl	printChar		@ print out left border

	mov	r0, NL			@ print out nl
	bl	printChar

	ldr	r0, [fp,HEIGHT_OFF]	@ get the height
	mov	r1, HALF_DIVISOR
	sdiv	r0, r0, r1		@ row = height/HALF_DIVISOR
	str	r0, [fp,ROW_OFF]	@ store row to the stack

	cmp	r0, 0			@ opposite logic
	ble	end_bottom		
bottom_half:
	ldr	r0, [fp,BORDER_OFF]
	bl	printChar		@ printChar( border )

	ldr	r0, [fp,ROW_OFF] 	@ pass in para
	ldr	r1, [fp,HEIGHT_OFF]
	ldr	r2, [fp,BOWTIE_OFF]
	ldr	r3, [fp,FILLER_OFF]
	bl	printBowtieLine		
	
	
	ldr	r0, [fp,BORDER_OFF]
	bl	printChar		@ printChar( border )

	mov	r0, NL
	bl	printChar		@ printChar(NL)

	ldr	r0, [fp,ROW_OFF]
	sub	r0, r0, 1 		@ decrement row
	str	r0, [fp,ROW_OFF]

	cmp	r0, 0			@ positive logic to loop back
	bgt	bottom_half
end_bottom:
	mov	r0, 0 			@ initialize col = 0
	str	r0, [fp,COL_OFF]	

	ldr	r1, [fp,HEIGHT_OFF]
	mov	r2, WIDTH_MUL
	mul	r1, r1, r2		@ height * width_mul
	add	r1, r1, 1		@ height * width_mul + 1 
	str	r1, [fp,LIMIT]		@ store the limit condi of loop

	cmp	r0, r1			@ opposite logic
	bgt	end_bottom_border
bottom_border:
	ldr	r0, [fp,BORDER_OFF]
	bl	printChar

	ldr	r0, [fp,COL_OFF]	
	add	r0, r0, 1		@ increment col
	str	r0, [fp,COL_OFF]	@ store back

	ldr	r1, [fp,LIMIT]
	cmp	r0, r1
	ble	bottom_border		@ positve logic to loop

end_bottom_border:	
	mov	r0, NL
	bl	printChar		@ printChar( NL )

	

@ Standard epilogue
	sub     sp, fp, FP_OFFSET       @ Set sp to top of saved registers
	pop     {fp, pc}                @ Restore fp; restore lr into pc for
					@ 	return
