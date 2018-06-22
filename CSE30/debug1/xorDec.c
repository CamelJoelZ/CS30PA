/*
 * Filename: xorDec.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Defines the XOR decryption function.
 * Date: 4/20/18
 * Sources of help: None.
 */

#include "debug1.h"

/* XXX: DO NOT EDIT ANYTHING IN THIS FILE! */

/*
 * Function Name: xorDec()
 * Function Prototype: void xorDec( byteArray_t * out,
 *                                  byteArray_t * key,
 *                                  byteArray_t * in );
 * Description: Decrypts ciphertext into plaintext, using a given key and the
 *              XOR operation on each byte.
 * Parameters: out - Output array of the plaintext. Must be the same
 *                   len as the 'in' parameter.
 *             key - Key to XOR with the given ciphertext.
 *             in  - Input array of the ciphertext.
 * Side Effects: The 'out' array may be modified.
 *               Random number generator state may be modified.
 * Error Conditions: None.
 * Return Value: None.
 */
void xorDec( byteArray_t * out, byteArray_t * key, byteArray_t * in ) {
  for ( int i = 0; i < out->len; i++ ) {
    out->bytes[i] = in->bytes[i] ^ getKeyByte(key, i);
  }
}
