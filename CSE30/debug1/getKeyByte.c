/*
 * Filename: getKeyByte.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Defines a function to conditionally extract a byte from a key.
 * Date: 4/20/18
 * Sources of help: None.
 */

#include "debug1.h"

/* XXX: DO NOT EDIT ANYTHING IN THIS FILE! */

/*
 * Function Name: getKeyByte()
 * Function Prototype: char getKeyByte( byteArray_t * key, int idx );
 * Description: Gets the key byte at an index, or generates a random byte
 *              if the key's byte is nul ('\0'). Indexes past the end of the
 *              key are wrapped around so that they still index into the key.
 * Parameters: key - The key to access.
 *             idx - The index in the key to access.
 * Side Effects: Random number generator state may be modified.
 * Error Conditions: None.
 * Return Value: The character of the key at 'idx', or a random byte.
 */
char getKeyByte( byteArray_t * key, int idx ) {
  char b = key->bytes[idx % key->len]; // Wrap index so we stay in bounds.
  if (b == '\0') {
    return myRand(); // Produce a rand number if byte is nul.
  } else {
    return b;        // Otherwise, use byte of the key.
  }
}
