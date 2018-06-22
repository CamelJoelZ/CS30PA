/*
 * Filename: debug1.h
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Holds struct definitions, function prototypes, and constants
 *              for debug1.
 * Date: 4/20/18
 * Sources of help: None.
 */
#ifndef DEBUG1_H
#define DEBUG1_H

#include <stdlib.h>

/* XXX: DO NOT EDIT ANYTHING IN THIS FILE! */

/* Array type for simplifying passing byte arrays to encryption functions. */
typedef struct byteArray {
  char * bytes;
  size_t len;
} byteArray_t ;

/* Function prototypes. */
void vigenereEnc( byteArray_t * out, byteArray_t * key, byteArray_t * in );
void vigenereDec( byteArray_t * out, byteArray_t * key, byteArray_t * in );

void xorEnc( byteArray_t * out, byteArray_t * key, byteArray_t * in );
void xorDec( byteArray_t * out, byteArray_t * key, byteArray_t * in );

long isInRange( long value, long minRange, long maxRange );
char myRand( void );
char getKeyByte( byteArray_t * key, int idx );

/* Constants. */
#define STR_HELP "--help"
#define HELP_ARG 1
#define ENC_DEC_ARG 1
#define CIPHER_ARG 2
#define KEY_ARG 3

#define MIN_ARGS 3
#define MAX_ARGS 4

#define BASE 10

/* Cipher modes. */
#define ENCODE 0
#define DECODE 1
#define NUM_CIPHERS 2

/* Encrypt + decrypt. */
#define NUM_CRYPT_FUNCS 2

/* Read buffer size. */
#define BLOCK_SIZE 100

#endif // DEBUG1_H
