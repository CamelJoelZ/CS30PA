/*
 * Filename: accumulateWordCount.s
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Sums up the frequency of the word's count with currCount.
 * Date: 04/20/18
 * Sources of help: None.
 */

	.cpu	cortex-a53
	.syntax unified         @ modern arm syntax

	.equ	FP_OFFSET, 4 

	.equ	LOCAL_VAR_SPACE, 112
	.equ	PARAM_SPACE, 16
	.equ	ADD_ARG_SPACE, 8

	.equ	KEY_OFFSET, -60		@ offset of struct key from fp
	.equ	DEF_OFFSET, -116	@ offset of struct default from fp

	.equ	CURR_COUNT_OFF, -120	@ offset of currCount (r0) from fp
	.equ	WORDSLIST_OFF, -124	@ offset of wordsList (r1) from fp
	.equ	NUMWORDS_OFF, -128	@ offset of numWords (r2) from fp
	.equ	WORD_OFF, -132		@ offset of word (r3) from fp

	.equ	ARG5_OFFSET, 0		@ offset of arg5 from sp
	.equ	ARG6_OFFSET, 4		@ offset of arg6 from sp

	.equ	MAX_WORD_LEN, 50	@ see debug2.h

	.global	accumulateWordCount

	.text
	.align	2

/*
 * Function Name: accumulateWordCount()
 * Function Prototype: unsigned int 
 *                     accumulateWordCount( unsigned int currCount, 
 *                                          struct Freq * wordsList
 *                                          int numWords, char * word );
 * Description: Attempts to find the word's frequency in the wordsList by
 *              invoking bsearchd() to find the struct Freq containing the
 *              word, and adding that struct's count value to currCount to sum
 *              up the total frequency value.
 * Parameters: currCount - current sum of frequencies as calculated from 
 *                         previous iterations of this function
 *             wordsList - pointer to the array of struct Freq
 *             numWords - number of words in the wordsList
 *             word - word to calculate the frequency of
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: The sum of currCount and the word's frequency.
 *
 * Registers Used:
 *      r0 - arg 1 -- first argument to strncpy and bsearchd
 *      r1 - arg 2 -- second argument to strncpy and bsearchd
 *      r2 - arg 3 -- third argument to strncpy and bsearchd
 *                 -- holds offset of struct Freq's word and count members
 *                 -- holds address of function compareFreqWord
 *      r3 - arg 4 -- fourth argument to bsearchd
 *                 -- holds address of local key and def structs
 *                 -- holds value of currCount
 *
 * Local variables:
 *      key - [fp - 60]  - struct Freq to populate with word to use in bsearchd
 *      def - [fp - 116] - default struct to return if bsearchd() cannot find
 *                         the struct with the same word as key's word
 */
accumulateWordCount:

	push	{fp, lr}			@ Prologue
	add	fp, sp, FP_OFFSET

	sub	sp, sp, LOCAL_VAR_SPACE 
	sub	sp, sp, PARAM_SPACE
	sub	sp, sp, ADD_ARG_SPACE

	str	r0, [fp, CURR_COUNT_OFF]	@ save r0-r3
	str	r1, [fp, WORDSLIST_OFF]
	str	r2, [fp, NUMWORDS_OFF]
	str	r3, [fp, WORD_OFF]

	/* In order for us to call bsearchd(), we need a 'key' for it to
	 * compare against the other array elements. So we will populate
	 * a temporary struct Freq with the word (since that's all
	 * compareFreqWord is using). */

	/* Copy word into key's word field */
	add	r3, fp, KEY_OFFSET		@ calculate key.word address
	ldr	r2, =freq_wordOffset
	ldr	r2, [r2]
	add	r0, r3, r2
	ldr	r1, [fp, WORD_OFF]
	mov	r2, MAX_WORD_LEN

	@ strncpy(key.word, word, MAX_WORD_LEN)
	bl	strncpy

	/* bsearchd() will return the default if the key word did not match
	 * any array element. So we must provide it with one (same type as 
	 * key) */

	/* Initialize def.count = 0 */
	add	r3, fp, DEF_OFFSET		@ calculate def.count address
	ldr	r2, =freq_countOffset
	ldr	r2, [r2]
	add	r3, r3, r2
	mov	r2, 0
	str	r2, [r3]			@ store 0 into def.count

	/* Prepare to call bsearchd() */
	add	r3, fp, DEF_OFFSET		@ calculate &def
	str	r3, [sp, ARG5_OFFSET]		@ store at arg5 space
	ldr	r2, =compareFreqWord		@ get compareFreqWord address
	str	r2, [sp, ARG6_OFFSET]		@ store at arg6 space

	/* bsearchd(&key, wordsList, numWords, sizeof(struct Freq), 
	 *          &def, compareFreqWord); */
	add	r0, fp, KEY_OFFSET
	ldr	r1, [fp, WORDSLIST_OFF]
	ldr	r2, [fp, NUMWORDS_OFF]
	ldr	r3, =freq_sizeof
	ldr	r3, [r3]

	bl	bsearchd

	/* Return currCount + found->count */
	ldr	r2, =freq_countOffset
	ldr	r2, [r2]
	ldr	r2, [r0, r2]			@ get value of found's count

	ldr	r3, [fp, CURR_COUNT_OFF]
	add	r0, r3, r2			@ add to currCount

	sub	sp, fp, FP_OFFSET		@ Epilogue
	pop	{fp, pc}

