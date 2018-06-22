/*
 * Filename: debug2Globals.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Defines global variables for use in assembly modules.
 * Date: 04/20/18
 * Sources of help: None.
 */

/* XXX: DO NOT MODIFY THIS FILE */

#include <stddef.h> // offsetof()
#include "debug2.h"

/* struct Freq offsets and sizeof the struct. */
size_t freq_wordOffset = offsetof( struct Freq, word );
size_t freq_countOffset = offsetof( struct Freq, count );
size_t freq_sizeof = sizeof( struct Freq );
