/*
 * Filename: vigenereDec.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Defines the vigenere decryption function.
 * Date: 4/20/18
 * Sources of help: None.
 */

#include "debug1.h"

/* XXX: DO NOT EDIT ANYTHING IN THIS FILE! */

/*
 * Function Name: vigenereDec()
 * Function Prototype: void vigenereDec( byteArray_t * out,
 *                                       byteArray_t * key,
 *                                       byteArray_t * in );
 * Description: Decrypts ciphertext into plaintext, using a given key to
 *              perform a positional shift operation on each byte
 *              (Vigenere cipher).
 * Parameters: out - Output array of the decrypted plaintext. Must be the same
 *                   len as the 'in' parameter.
 *             key - Key used to determine shifts to decrypt ciphertext.
 *             in  - Input array of the ciphertext.
 * Side Effects: The 'out' array may be modified.
 *               Random number generator state may be modified.
 * Error Conditions: None.
 * Return Value: None.
 */
void vigenereDec( byteArray_t * out, byteArray_t * key, byteArray_t * in ) {
  // Decrypt all in bytes to out bytes.
  for ( int i = 0; i < out->len; i++ ) {
    out->bytes[i] = in->bytes[i] - getKeyByte(key, i);
  }
}
