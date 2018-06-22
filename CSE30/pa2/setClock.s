/*
 * Filename: setClock
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: set the time 
 * Data: 04/29/2018
 * Source of help: TutorialsPoint
 */

@ Raspberry Pi directives 
	.cpu    cortex-a53
	.syntax unified
	
	
	.equ	LOCAL, 16
	.equ	CLOCK, -8
	.equ	PTR, -12
	.equ	TMP, -16

	.equ	BASE, 10
	.equ    FP_OFFSET, 4
	.equ	SECOND, 1
	.equ	THIRD, 2
	.equ	FOURTH, 3
	.equ	MOVE, 4
	.global setClock 

	.text
	.align 2
	
/*
 * Function Name: setCLock()
 * Function Prototype: void setClock
 * Description: set the time
 * Parameters: clock - the time info array
 *	       tmpPtr - ptr to the time info struct
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *    r0 - arg1 --- clock
 *    r1 - arg2 --- tmPtr
 */

setClock:
@ Standard prologue
	push    {fp, lr}                @ Save registers: fp, lr
	add     fp, sp, FP_OFFSET       @ Set fp to base of saved registers
	sub 	sp, sp, LOCAL		@ declare local var
@ Incoming parameters in r0
	str	r0, [fp,CLOCK]		@ save the para1 to local var
	str	r1, [fp,PTR]		@ save the para2 to local var

	@ modifying hour
      	ldr	r0, =tInfo_hourOffset 	@ ldr the addr of hour info
	ldr	r0, [r0]		@ get the value in hour addr
	ldr	r1, [fp,PTR]
	ldr	r0, [r1,r0]		@ get the hour value to r0
	str	r0, [fp,TMP]		@ save the value of hour to TMP

	mov	r1, BASE
	bl	myRemainder		@ extract the unit to r0

	ldr	r2, [fp,TMP]		@ get the hour value back
	mov	r1, BASE
	sdiv	r1, r2, r1		@ extract the tenth 
	lsl	r1, MOVE		@ lsl 4 digit to arrange tenth

	orr	r0, r0, r1		@ bit operation to get bcd rep
	ldr	r1, [fp,CLOCK]		@ get the addr of clock array

	str	r0, [r1]		@ str hour to array[0]
		
	@ modifying min
      	ldr	r0, =tInfo_minOffset 	@ ldr the addr of min info
	ldr	r0, [r0]		@ get the value in min offset addr
	ldr	r1, [fp,PTR]
	ldr	r0, [r1,r0]		@ get min hour value to r0
	str	r0, [fp,TMP]		@ save the value of hour to TMP

	mov	r1, BASE
	bl	myRemainder		@ extract the unit to r0

	ldr	r2, [fp,TMP]		@ get the min value back
	mov	r1, BASE
	sdiv	r1, r2, r1		@ extract the tenth 
	lsl	r1, MOVE		@ lsl 4 digit to arrange tenth

	orr	r0, r0, r1		@ bit operation to get bcd rep
	ldr	r1, [fp,CLOCK]		@ get the addr of clock array

	strb	r0, [r1,SECOND]		@ str hour to array[1]
		
	@ modifying second
      	ldr	r0, =tInfo_secOffset 	@ ldr the addr of sec info
	ldr	r0, [r0]		@ get the value in sec offset addr
	ldr	r1, [fp,PTR]
	ldr	r0, [r1,r0]		@ get sec value to r0
	str	r0, [fp,TMP]		@ save the value of sec to TMP

	mov	r1, BASE
	bl	myRemainder		@ extract the unit to r0

	ldr	r2, [fp,TMP]		@ get the sec value back
	mov	r1, BASE
	sdiv	r1, r2, r1		@ extract the tenth 
	lsl	r1, MOVE		@ lsl 4 digit to arrange tenth

	orr	r0, r0, r1		@ bit operation to get bcd rep
	ldr	r1, [fp,CLOCK]		@ get the addr of clock array

	strb	r0, [r1,THIRD]		@ str hour to array[2]

	@ modifying am and pm
      	ldr	r0, =tInfo_ampmOffset 	@ ldr the addr of min info
	ldr	r0, [r0]		@ get the value in min offset addr
	ldr	r1, [fp,PTR]
	ldr	r0, [r1,r0]		@ get min hour value to r0

	ldr	r1, [fp,CLOCK]		@ get the addr of clock array

	strb	r0, [r1,FOURTH]		@ str hour to array[3]
@ Standard epilogue
	sub     sp, fp, FP_OFFSET       @ Set sp to top of saved registers
	pop     {fp, pc}                @ Restore fp; restore lr into pc for
					@ 	return
