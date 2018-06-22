/*
 * Filename: handleUserInput.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Implements the interactive prompt for the frequency analysis
 *              program.
 * Date: 04/20/18
 * Sources of help: None.
 */
#include <stdio.h>
#include <string.h>

#include "debug2.h"
#include "debug2Strings.h"

/*
 * Function Name: handleUserInput()
 * Function Prototype: void handleUserInput( struct Freq * wordsList,
 *                                           unsigned int numWords );
 * Description: Interactively search through the list for a given word.
 * Parameters: wordsList - the list of words with data on each word's frequency
 *             numWords - the number of words in the list
 * Side Effects: Reads from stdin. Prints to stdout and stderr.
 * Error Conditions: None.
 * Return Value: None.
 */
void handleUserInput( struct Freq * wordsList, unsigned int numWords ) {

  const char * const COMMANDS_LIST[] = COMMANDS; // Array of accepted commands.
  char buf[BUFSIZ]; // Temporary buffer for holding user input.

  // Show program usage string and prompt user for input.
  printf( HELP_STR );
  printf( STR_PROMPT );

  // Keep reading input until EOF.
  while( fgets( buf, BUFSIZ, stdin ) != NULL ) {

    // Get the command (first token) from user input.
    const char * const cmd = strtok( buf, SEP );

    // If there is no token (e.g. empty string), just reprompt.
    if ( !cmd ) {
      printf( STR_PROMPT );
      continue;
    }

    // If there is a token but it's not a valid command, error and reprompt.
    int cmdNo;
    if ( ( cmdNo = parseCmd( cmd, COMMANDS_LIST ) ) == -1 ) {
      fprintf( stderr, ERR_CMD_NOT_FOUND, cmd );
      printf( STR_PROMPT );
      continue;
    }

    // If its the help flag, print help and continue.
    if ( cmdNo == HELP ) {
      printf( HELP_STR );
      printf( STR_PROMPT );
      continue;
    }

    // If display flag, display the whole array.
    if ( cmdNo == DISPLAY ) {
      printf( "\n" );
      for ( unsigned int i = 0; i < numWords; i++ ) {
        printf( STR_DISPLAY_FMT, wordsList[i].word, wordsList[i].count );
      }
      printf( "\n" );
      printf( STR_PROMPT );
      continue;
    }

    // Otherwise, convert the consecutive arguments to a word and store them
    // in an array.
    char * word = strtok( NULL, SEP );
    if ( word == NULL ) {
      fprintf( stderr, ERR_WORD_NOT_ENTERED );
      printf( STR_PROMPT );
      continue;
    }

    // Tokenize all words input by user and sum all the frequencies.
    unsigned int sumFreqs = 0 ; // Conveniently set to 0.
    while ( word ) {
      sumFreqs = accumulateWordCount( sumFreqs, wordsList, numWords, word );
      word = strtok( NULL, SEP );
    }

    // Display results.
    printf( STR_SUM_FREQS, sumFreqs );
    printf( STR_PROMPT );
  }

  printf( "\n" );
}
