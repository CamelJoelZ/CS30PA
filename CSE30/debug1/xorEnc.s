/*
 * Filename: xorEnc.s
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Defines the XOR encryption function.
 * Date: 4/20/18
 * Sources of help: None.
 */
	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4		@ Offset to frame pointer for prologue.

	.equ	LOCAL_SPACE, 8		@ Space and offsets for local vars.
	.equ	I_OFFSET, -8

	.equ	PARAM_SPACE, 16		@ Space and offsets for formal params.
	.equ	OUT_OFFSET, -16
	.equ	KEY_OFFSET, -20
	.equ	IN_OFFSET, -24

	.global	xorEnc

	.text
	.align	2
/*
 * Function Name: xorEnc()
 * Function Prototype: void xorEnc( byteArray_t * out,
 *                                  byteArray_t * key,
 *                                  byteArray_t * in );
 * Description: Encrypts plaintext into ciphertext, using a given key and the
 *              XOR operation on each byte.
 * Parameters: out - Output array of the ciphertext. Must be the same
 *                   len as the 'in' parameter.
 *             key - Key to XOR with the given plaintext.
 *             in  - Input array of the plaintext.
 * Side Effects: Random number generator state may be modified.
 * Error Conditions: None.
 * Return Value: None.
 *
 * Registers used:
 * 	r0 - arg1 - out array
 * 	r1 - arg2 - key array
 * 	r2 - arg3 - in array
 * 	r0-r3 - tmp - scratchpad registers for intermediate operations
 *
 * Local variables:
 * 	i - [fp - 8] -- index for looping across out/in arrays
 */
xorEnc:
	push	{fp, lr}
	add     fp, sp, FP_OFFSET


	/* Allocate space for local vars and formal params. */
	sub	sp, sp, LOCAL_SPACE
	sub	sp, sp, PARAM_SPACE

	/* Save formal params for use later. */
	str	r0, [fp, OUT_OFFSET]
	str	r1, [fp, KEY_OFFSET]
	str	r2, [fp, IN_OFFSET]

	/* i = 0 */
	mov	r3, 0
	str	r3, [fp, I_OFFSET]

	/* i < out->len */
	ldr	r2, [fp, I_OFFSET]		@ r2 = i

	ldr	r3, [fp, OUT_OFFSET]
	ldr	r1, =byteArray_lenOffset
	ldr	r1, [r1]
	ldr	r3, [r3, r1]			@ r3 = out->len

	cmp	r2, r3
	bge	endloop				@ opposite logic skip to end

loop:
	/* Calculate in->bytes[i] ^ getKeyByte(key, i) */
	ldr	r0, [fp, KEY_OFFSET]
	ldr	r1, [fp, I_OFFSET]
	bl	getKeyByte			@ r0 = getKeyByte(key, i)

	ldr	r3, [fp, IN_OFFSET]
	ldr	r2, =byteArray_bytesOffset
	ldr	r2, [r2]
	ldr	r3, [r3, r2]			@ r3 = in->bytes

	ldr	r2, [fp, I_OFFSET]
	ldrb	r1, [r3, r2]			@ r1 = in->bytes[i]

	eor	r0, r0, r1			@ r0 = in byte ^ key byte

	/* Store the sum into out->bytes[i] */
	ldr	r3, [fp, OUT_OFFSET]
	ldr	r2, =byteArray_bytesOffset
	ldr	r2, [r2]
	ldr	r3, [r3, r2]			@ r3 = out->bytes

	ldr	r2, [fp, I_OFFSET]		@ r2 = i
	strb	r0, [r3, r2]			@ store r0 into out->bytes[i]

	/* i++ */
	ldr	r3, [fp, I_OFFSET]
	add	r3, r3, 1
	str	r3, [fp, I_OFFSET]		@ i++

	/* i < out->len */
	ldr	r2, [fp, I_OFFSET]		@ r2 = i

	ldr	r3, [fp, OUT_OFFSET]
	ldr	r1, =byteArray_lenOffset
	ldr	r1, [r1]
	ldr	r3, [r3, r1]			@ r3 = out->len

	cmp	r2, r3
	blt	loop				@ positive logic to loop again
endloop:

	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}
