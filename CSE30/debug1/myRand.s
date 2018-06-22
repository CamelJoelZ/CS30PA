/*
 * Filename: myRand.s
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Defines a deterministic random number generation function.
 * Date: 4/20/18
 * Sources of help: None.
 */
	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4

	.equ	RNG_SHIFT, 16		@ Shift amt used in the RNG algorithm.
	.equ	RNG_SEED, 0xEAFFFFFE	@ Seed used for deterministic RNG.

	// FIX------------------
	.global myRand

	/* Use a static variable to keep track of
	 * random number generator state. Initial value: 0. */
	.bss
	.align	2
random:
	.skip	4

	.text
	.align	2
/*
 * Function Name: myRand()
 * Function Prototype: char myRand( void );
 * Description: Returns a random byte.
 * Parameters: None.
 * Side Effects: Random number generator is modified.
 * Error Conditions: None.
 * Return Value: A random byte.
 *
 * Registers used:
 * 	r0 - tmp - holds temporary values between operations
 * 	r1 - random - used to hold intermediate values of random static var
 * 	r2 - &random - holds address of static var so we can store back
 * 	r3 - RNG_SEED - holds value of RNG_SEED for use in algorithm
 *
 * Local variables: None.
 */
myRand:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET
	
	ldr	r3, =RNG_SEED		@ load large constant seed
	ldr	r2, =random		@ load random static var to generate num
	ldr	r1, [r2]

	mul	r1, r1, r1		@ random *= random

	lsr	r0, r1, RNG_SHIFT
	orr	r1, r1, r0		@ random |= (random >> RNG_SHIFT)

	add	r1, r1, r3		@ random += RNG_SEED

	lsr	r1, r1, RNG_SHIFT
	str	r1, [r2]		@ random >>= RNG_SHIFT

	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}
