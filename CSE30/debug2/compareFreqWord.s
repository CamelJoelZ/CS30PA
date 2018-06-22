/*
 * Filename: compareFreqWord.s
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Comparison function for struct Freq.
 * Date: 04/07/18
 * Sources of help: None.
 */
	.cpu	cortex-a53
	.syntax	unified

	.equ	MAX_WORD_LEN, 50
	.equ	FP_OFFSET, 4

	.global	compareFreqWord

	.text
	.align	2
/*
 * Function Name: compareFreqWord()
 * Function Prototype: int compareFreqWord( const void * f1, const void * f2 );
 * Description: Compares struct Freq words, but not values.
 * Parameters: f1 - pointer to the first struct Freq to compare
 *             f2 - pointer to the second struct Freq to compare
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: Uses standard comparison function behavior:
 *                 -  0: f1->word == f2->word
 *                 - <0: f1->word <  f2->word
 *                 - >0: f1->word >  f2->word
 *
 * Registers Used:
 * 	r3 - offset -- holds the offset to the word member in struct Freq
 * 	r2 - n -- used to pass the n argument to strncmp
 * 	r1 - arg 2 -- second argument to strncmp
 * 	r0 - arg 1 -- first argument to strncmp
 */
compareFreqWord:
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	/* Get word offset. */
	ldr	r3, =freq_wordOffset
	ldr	r3, [r3]

	/* strncmp(freq1->word, freq2->word, MAX_WORD_LEN) */
	//ldr	r0, [r0, r3]
	//ldr	r1, [r1, r3]
	add	r0, r0, r3
	add	r1, r1, r3
	mov	r2, MAX_WORD_LEN
	bl	strncmp

	/* Return value is in r0, just return now. */

	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}
