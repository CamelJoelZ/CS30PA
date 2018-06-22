/*
 * Filename: debug1Globals.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Define global variables to calculate the offsets of members
 *              within structs.
 * Date: 4/20/18
 * Sources of help: None.
 */
#include <stddef.h> // for offsetof()
#include "debug1.h"

/* XXX: DO NOT EDIT ANYTHING IN THIS FILE! */

size_t byteArray_bytesOffset = offsetof( byteArray_t, bytes );
size_t byteArray_lenOffset = offsetof( byteArray_t, len );
