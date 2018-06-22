/*
 * Filename: parseFile.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Defines the function for parsing a file for its words and
 *              filling the words list.
 * Date: 04/20/18
 * Sources of help: None.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug2.h"
#include "debug2Strings.h"

/*
 * Function Name: parseFile()
 * Function Prototype: int parseFile( struct Freq ** wordsListPtr,
 *                                    FILE * inFile );
 * Description: Scans across the inFile and inserts all the words of inFile
 *              into a struct Freq list, and returns the list through
 *              the wordsListPtr output parameter.
 * Parameters: wordsListPtr - a pointer to the struct Freq * to be updated to
 *                            point to the newly created words list
 *             inFile - the file to read from
 * Side Effects: Reads from inFile. Updates the wordsListPtr output
 *               parameter.
 * Error Conditions: None.
 * Return Value: The number of words read from inFile.
 */
int parseFile( struct Freq ** wordsListPtr, FILE * inFile ) {

  int numWords = 0; // Keeps count of the number of words.
  char buf[BUFSIZ];  // Intermediate buffer for reading from file.
  struct Freq * wordsList = NULL; // Local ptr to the list we are building.
  int nelems; // Holds how many bytes were read on each fread call.

  // Loop across the file, reading into buf until no more bytes can be read.
  while ( ( nelems = fread( buf, sizeof( char ), BUFSIZ - 1, inFile ) ) ) {
    buf[nelems] = '\0'; // Nul-terminate the buffer.

    // Split words using strtok until there are no more tokens.
    char * word = strtok( buf, SEP );
    while ( word ) {

      // There is nothing in the list, but there is a word to store. 
      // Create the first struct.
      if ( !wordsList ) {

        wordsList = calloc( 1, sizeof( struct Freq ) );

        // Handle memory limit.
        if ( !wordsList ) {
          fprintf( stderr, ERR_MEM_LIMIT_EXCEEDED );
          return -1;
        }

        // Fill new entry with word and initial count.
        strncpy( wordsList[0].word, word, MAX_WORD_LEN );
        wordsList[0].word[MAX_WORD_LEN - 1] = '\0';
        wordsList[0].count = 1;

        // Update the total number of words
        numWords += 1;

      } else {

        // Check to see if word is already in the list.
        struct Freq key;
        strncpy( key.word, word, MAX_WORD_LEN );
        key.word[MAX_WORD_LEN - 1] = '\0';

        struct Freq * found = bsearchd( &key, wordsList, numWords, 
                                        sizeof( struct Freq ),
                                        NULL, compareFreqWord );

        // If so, update frequency.
        if ( found ) {

          found->count += 1;

        // Otherwise, create new struct to store word and frequency.
        } else {

          // Make more space for the new entry.
          struct Freq * tmp = realloc( wordsList,
                                      (numWords + 1) * sizeof( struct Freq ) );

          // Handle memory limit.
          if ( !tmp ) {
            fprintf( stderr, ERR_MEM_LIMIT_EXCEEDED );
            free( wordsList );
            return -1;
          }

          // reset wordlist
          wordsList = tmp;

          // Insert into sorted array.
          // We will continually shift over the structs until we find the index
          // where the new word needs to go.
          int i;
          for ( i = numWords; i > 0 && 
              strncmp( word, wordsList[i - 1].word, MAX_WORD_LEN ) < 0; i-- ) {

            strncpy( wordsList[i].word, wordsList[i - 1].word, MAX_WORD_LEN );
            wordsList[i].count = wordsList[i - 1].count;
          }

          // Go back, and populate the frequency struct at this location.
          strncpy( wordsList[i].word, word, MAX_WORD_LEN );
          wordsList[i].word[MAX_WORD_LEN - 1] = '\0';
          wordsList[i].count = 1;

          // Update the total number of words
          numWords += 1;
        }
      }

      // Get the next word.
      word = strtok( NULL, SEP );
    }
  }

  // Set the original pointer in main to point to heap allocated space.
  *wordsListPtr = wordsList;
  return numWords;
}
