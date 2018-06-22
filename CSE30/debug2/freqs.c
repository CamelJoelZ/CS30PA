/*
 * Filename: freqs.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Contains the main method to run the word frequency program.
 * Date: 04/20/18
 * Sources of help: None.
 */
#include <stdio.h>
#include <stdlib.h>

#include "debug2.h"
#include "debug2Strings.h"

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: Runs the frequency program.
 * Parameters: argc - number of command line arguments
 *             argv - pointers to the command line arguments
 * Side Effects: Prints the frequency of (a) word(s) to the user.
 * Error Conditions: Opening file fails (does not exist or permission error).
 *                   Memory allocation fails (not enough memory).
 * Return Value: EXIT_SUCCESS if program runs to completion, 
 *               EXIT_FAILURE, otherwise.
 */
int main( int argc, char * argv[] ) {

  if ( argc == 1 ) {
    fprintf( stderr, "Please supply a file name.\n" );
    return EXIT_FAILURE;
  }

  // File is the first argument to exec.
  char * inFilename = argv[1];
  FILE * inFile = fopen( inFilename, "r" );

  // File error checking.
  if ( inFile == NULL ) {
    perror( inFilename );
    return EXIT_FAILURE;
  }

  int numWords = 0;
  struct Freq * wordsList = NULL;

  // Read in buffers at a time, print out
  numWords = parseFile( &wordsList, inFile );

  // Some funky error occurred in parseFile()
  if ( numWords < 0 ) {
    return EXIT_FAILURE;
  }

  // Interactive search!
  //handleUserInput( *wordsList, numWords );
  handleUserInput( wordsList, numWords );

  // Free the list
  if ( numWords ) {
    free( wordsList );
  }

  return EXIT_SUCCESS;
}
