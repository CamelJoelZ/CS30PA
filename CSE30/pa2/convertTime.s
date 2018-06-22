/*
 * Filename: convertTime
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: convert the time
 * Data: 05/06/2018
 * Source of help: TutorialsPoint
 */

@ Raspberry Pi directives 
	.cpu    cortex-a53
	.syntax unified
	
	
	.equ	LOCAL, 8
	.equ	OURTIME, -8
	.equ	TM, -12
	.equ	MAXHOUR, 24
	.equ	TWELVE, 12
	.equ	AM, 'A'
	.equ	PM, 'P'

	.equ    FP_OFFSET, 4
	.global convertTime 

	.text
	.align 2
	
/*
 * Function Name: convertTime()
 * Function Prototype: void convertTime
 * Description: convert the time
 * Parameters: struct tInfo * ourTime- the time struct to poptlate
 *	       tmpPtr - ptr to the time info struct
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *    r0 - arg1 --- ourTime
 *    r1 - arg2 --- tmPtr
 */

convertTime:
@ Standard prologue
	push    {fp, lr}                @ Save registers: fp, lr
	add     fp, sp, FP_OFFSET       @ Set fp to base of saved registers
	sub 	sp, sp, LOCAL		@ declare local var
@ Incoming parameters in r0
	str	r0, [fp,OURTIME]	@ save the para1 to local var
	str	r1, [fp,TM]		@ save the para2 to local var

	@ retrieving hour value
      	ldr	r0, =tm_hour_offset      @ ldr the addr of min info
	ldr	r0, [r0]		@ offset value in r0 
	ldr	r1, [fp,TM]		@ ptr address in r1
	ldr	r0, [r1,r0]		@ hour val in r0
	@ convert to 24 if 0
	cmp	r0, 0			@ change it to 24 if 0
	bne	notZero
zero:
	mov	r0, MAXHOUR		@ change to 24
notZero:
	@ determin if am or pm
	mov	r1, TWELVE		@ r1 = 12
	cmp	r0, r1
	bgt	pm
am:
	@ retrieve the addr of am_pm
	ldr	r1, =tInfo_ampmOffset    @ offset addr in r1
	ldr	r1, [r1]		@ offset val in r1
	ldr	r2, [fp,OURTIME]	@ addr of the start of ourtime
	add	r2, r1, r2		@ the addr of ampm in the struct
	mov	r1, AM
	strb	r1, [r2]		@ save the am val to ourtime
	b 	hour

pm:
	@ retrieve the addr of am_pm
	ldr	r1, =tInfo_ampmOffset    @ offset addr in r1
	ldr	r1, [r1]		@ offset val in r1
	ldr	r2, [fp,OURTIME]	@ addr of the start of ourtime
	add	r2, r1, r2		@ the addr of ampm in the struct
	mov	r1, PM
	strb	r1, [r2]		@ save the pm val to ourtime
	@ change from 24 hours format to 12 when pm
	sub	r0, r0, TWELVE
hour:
	@ save the hour to struct ourtime
	ldr	r1, =tInfo_hourOffset    @ offset addr in r1
	ldr	r1, [r1]		@ offset val in r1
	ldr	r2, [fp,OURTIME]	@ addr of the start of ourtime
	str	r0, [r2,r1]		@ save the hour val to ourtime
		
	@ retrieving minute value
      	ldr	r0, =tm_min_offset      @ ldr the addr of min info
	ldr	r0, [r0]		@ offset value in r0 
	ldr	r1, [fp,TM]		@ ptr address in r1
	ldr	r0, [r1,r0]		@ minute val in r0
	@ finding the address of mem var of OURTIME
	ldr	r1, =tInfo_minOffset    @ offset addr in r1
	ldr	r1, [r1]		@ offset val in r1
	ldr	r2, [fp,OURTIME]	@ addr of the start of ourtime
	str	r0, [r2,r1]		@ save the minute val to ourtime

	@ retrieving second value
      	ldr	r0, =tm_sec_offset      @ ldr the addr of sec info
	ldr	r0, [r0]		@ offset value in r0 
	ldr	r1, [fp,TM]		@ ptr address in r1
	ldr	r0, [r1,r0]		@ sec val in r0
	@ finding the address of mem var of OURTIME
	ldr	r1, =tInfo_secOffset    @ offset addr in r1
	ldr	r1, [r1]		@ offset val in r1
	ldr	r2, [fp,OURTIME]	@ addr of the start of ourtime
	str	r0, [r2,r1]		@ save the sec val to ourtime

@ Standard epilogue
	sub     sp, fp, FP_OFFSET       @ Set sp to top of saved registers
	pop     {fp, pc}                @ Restore fp; restore lr into pc for
					@ 	return
