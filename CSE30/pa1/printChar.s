/*
 * Filename:printChar.s
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: print a single char
 * Data: 04/20/2018
 * Source of help: TutorialsPoint
 */

@ Raspberry Pi directives 
	.cpu    cortex-a53
	.syntax unified
	
	.section .rodata
	
fmt:	.asciz	"%c"

	.equ    FP_OFFSET, 4
	.global  printChar

	.text
	.align 2
	
/*
 * Function Name: printChar()
 * Function Prototype: void printChar( char ch );
 * Description: print a single char to stdout
 * Parameters: ch - the char to print
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *    r0 - arg1 --- char
 */

printChar:
@ Standard prologue
	push    {fp, lr}                @ Save registers: fp, lr
	add     fp, sp, FP_OFFSET       @ Set fp to base of saved registers

@ Incoming parameters in r0
	mov  	r1,r0			@ move r0 to r1
	ldr 	r0, =fmt		@ gets address of format string
  	bl 	printf               	@ Calls printf
       

@ Standard epilogue
	sub     sp, fp, FP_OFFSET       @ Set sp to top of saved registers
	pop     {fp, pc}                @ Restore fp; restore lr into pc for
					@ 	return
