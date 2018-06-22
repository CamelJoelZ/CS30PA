/*
 * Filename: main.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Main program driver.
 * Date: 4/20/18
 * Sources of help: None.
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "debug1.h"
#include "debug1Strings.h"

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: Encrypts or decrypts user input using a cipher specified by the
 *              user.
 * Parameters: argc - number of command-line arguments
 *             argv - array of command-line arguments passed in by user
 * Side Effects: A message to stderr will be printed to indicate how many bytes
 *               were written to the output stream.
 *               Errors (see Error Conditions) will prompt a message to be
 *               printed indicating what went wrong.
 * Error Conditions: User does not specify whether they want to decrypt or
 *                   encrypt, or specifies an invalid option.
 *                   User does not specify a cipher index or specifies an
 *                   invalid index (i.e. something that is not a valid integer
 *                   or not within the range [0, 1]).
 * Return Value: EXIT_SUCCESS if program runs to completion, EXIT_FAILURE
 *               otherwise.
 */
int main( int argc, char * argv[] ) {

  // "ciphers is an array of pointers to functions, each taking byteArray_t
  // pointers as input and returning void"
  //void (*ciphers)(byteArray_t *, byteArray_t *, byteArray_t *)[] = { 
  void (* ciphers []) (byteArray_t *, byteArray_t *, byteArray_t *) = { 
    vigenereEnc, vigenereDec, xorEnc, xorDec,
  };

  // Checks that user knows how to run the program.
  if ( argc < MIN_ARGS ) {
    fprintf( stderr, STR_USAGE, argv[0] );
    return EXIT_FAILURE;
  }

  // Sees if the user passed in the help flag
  if ( strncmp( argv[HELP_ARG], STR_HELP, BUFSIZ ) == 0 ) {
    printf( STR_USAGE, argv[0] );
    return EXIT_SUCCESS;
  }

  // Determines whether the user wants to encrypt or decrypt.
  char encDecFlag = *argv[ENC_DEC_ARG];
  if ( encDecFlag != 'e' && encDecFlag != 'd' ) {
    fprintf( stderr, STR_INVALID_ENC_DEC_FLAG );
    return EXIT_FAILURE;
  }
  int mode = (encDecFlag == 'e' ? ENCODE : DECODE);

  // Checks if cipher index is valid.
  errno = 0;
  char * endptr;
  long cipherIdx = strtol( argv[CIPHER_ARG], &endptr, BASE );
  if ( errno != 0 ) {
    char buf[BUFSIZ];
    snprintf( buf, BUFSIZ, STR_ERR_CONVERTING, 
              STR_CIPHER_INDEX, argv[CIPHER_ARG], BASE );
    perror( buf );
    return EXIT_FAILURE;
  }
  if ( *endptr != '\0' ) {
    fprintf( stderr, STR_INVALID_INT, STR_CIPHER_INDEX, argv[CIPHER_ARG] );
    return EXIT_FAILURE;
  }
  if ( !isInRange( cipherIdx, 0, NUM_CIPHERS ) ) {
    fprintf( stderr, STR_CIPHER_IDX_INVALID );
    return EXIT_FAILURE;
  }

  // Grabs the key string.
  char * keyArg = NULL;
  if ( argc == MAX_ARGS ) {
    keyArg = argv[KEY_ARG];
  }

  // Generates a cipher.
  byteArray_t input = { 0, 0 };
  byteArray_t output = { 0, 0 };
  byteArray_t key = { 0, 0 };

  // Populates the key struct, if user passed in a key.
  if ( keyArg ) {
    key.bytes = keyArg;
    key.len = strlen(keyArg) + 1;
  } else {
    key.bytes = "";
    key.len = 1;
  }

  // Performs cipher operation on input data, and write result to a file.
  FILE * inFile = stdin;
  FILE * outFile = stdout;

  // Reads in some bytes from the file.
  int totalBytes = 0;
  int numBytes;
  char data[BLOCK_SIZE];
  char buf[BLOCK_SIZE];
  while( ( numBytes = fread(data, sizeof( char ), BLOCK_SIZE, inFile) ) > 0 ) {
    totalBytes += numBytes;

    // Sets input and output fields.
    input.bytes = data;
    input.len = numBytes;
    output.bytes = buf;
    output.len = numBytes;

    // Calls the encrypt/decrypt function of cipher.
    int funcIdx = cipherIdx * NUM_CRYPT_FUNCS + mode;
    (*ciphers[funcIdx])(&output, &key, &input);

    // Writes the bytes to the stream.
    fwrite( output.bytes, sizeof( char ), numBytes, outFile );
  }

  // Prints resulting message to stderr so it doesn't conflict with the file.
  fprintf( stderr, STR_WRITTEN_BYTES, totalBytes );

  // Closes the file streams.
  fclose(inFile);
  fclose(outFile);

  return EXIT_SUCCESS;
}
