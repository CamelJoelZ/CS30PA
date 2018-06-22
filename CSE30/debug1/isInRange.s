/*
 * Filename: isInRange.s
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Determines if the passed long longInt is between
 *   the passed long longMin and longMax (exclusive)
 * Date: 4/20/18
 * Sources of Help: Rick Ord & Interwebz
 */

	.cpu	cortex-a53
	.syntax	unified

	.equ	FP_OFFSET, 4

	.global isInRange

	.text
	.align	2

/* XXX: DO NOT EDIT ANYTHING IN THIS FILE! */

/*
 * Function name: isInRange()
 * Function prototype: long isInRange( long value,
 *                                     long minRange,
 *                                     long maxRange );
 * Description: Determines if the passed long longInt is between
 *              the passed long longMin and longMax (exclusive)
 * Parameters:  arg 1: long value -- the long to check the range of
 *              arg 2: long minRange -- the long that is the minimum (inclusive)
 *              arg 3: long maxRange -- the long that is the maximum (exclusive)
 * Side Effects: None
 * Error Conditions: minRange is greater than or equal to maxRange -> return -1
 * Return Value: 0 if longInt is not in the range, 1 otherwise.
 *
 * Registers Used:
 *   r0 - arg 1 -- the long passed in to check if within range
 *   r1 - arg 2 -- the long passed in for the minimum of the range
 *   r2 - arg 3 -- the long passed in for the maximum of the range
 *
 * Local Variables: None.
 */
isInRange:

	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	cmp	r1, r2
	bge	invalid

	cmp	r0, r1
	blt	error		@ value < min_in_range

	cmp	r0, r2
	bge	error		@ value > max_in_range

	mov	r0, 1		@ return 1 - value in range
	b	return

invalid:
	mov	r0, -1		@ return -1 since min > max
	b	return

error:
	mov	r0, 0		@ return 0 - not in range

return:
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}

