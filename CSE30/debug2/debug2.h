/*
 * Filename: freqs.h
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Important constants and function prototypes.
 * Date: 04/20/18
 * Sources of help: None.
 */

/* XXX: DO NOT MODIFY THIS FILE */

#ifndef DEBUG2_H
#define DEBUG2_H

#include <stdio.h>

/* Constants */
#define MAX_WORD_LEN 50
#define TABLE_SIZE 420
#define HASH_PRIME 31

#define FREQS 0
#define DISPLAY 1
#define HELP 2

/* Struct definitions */
struct Freq {
  char word[MAX_WORD_LEN]; // Word whose frequency we're counting.
  unsigned int count;      // How often the word appears.
};

/* Function prototypes */
void handleUserInput( struct Freq * wordsList, unsigned int numWords );
int parseCmd( const char * const cmdString, const char * const commands[] );
int parseFile( struct Freq ** wordsListPtr, FILE * inFile );
void * bsearchd( const void * key,
                 const void * base,
                 size_t nmemb,
                 size_t size,
                 void * def,
                 int (*compar)( const void *, const void * ) );

unsigned int accumulateWordCount( unsigned int currCount, 
                                  struct Freq * wordsList,
                                  int numWords, char * word );
int compareFreqWord( const void * f1, const void * f2 );

#endif // DEBUG2_H
