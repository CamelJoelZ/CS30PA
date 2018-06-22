/*
 * File: pa3.h
 * Description: Header file that contains function prototypes and
 *              constants.
 *
 * XXX Only add constants to this file at the bottom.
 * DO NOT EDIT FUNCTION PROTOTYPES OR PREDEFINED CONSTANTS
 *
 */

#ifndef PA3_H      /* Macro Guard */
#define PA3_H
#include <stdio.h> /* For FILE type */

/* Arg parsing */
#define ARG_STR "hs:d:"

#define CHAR_SIZE_FLAG 's'
#define CHAR_HELP_FLAG 'h'
#define CHAR_DIR_FLAG 'd'

/* default directory */
#define DEFAULT_DIR "data/"

#define NUM_QUADRENNIUM 35

/* Hashing */
#define HASH_START_VAL 11
#define HASH_PRIME     37

/* Sizes for Hash table */
#define MAX_SIZE 20001
#define MIN_SIZE 100
#define DEFAULT_SIZE 421

/* Maximum length for a name */
#define MAX_LINE_LEN 256
#define MAX_NAME_LEN 80
#define MAX_PATH_LEN 255

/* Decades */
#define MIN_QUADRENNIUM 1880

#define NUM_RANKS NUM_QUADRENNIUM

/* Plotting Graphs */
#define GRAPH_ROWS 26
#define GRAPH_COLS 73
#define MAX_RANK 1000
#define MIN_RANK 1
#define RANKS_PER_ROW 40
#define NUM_X_AXIS_MARKS GRAPH_COLS
#define MALE_MARKER 'M'
#define FEMALE_MARKER 'F'
#define INTERSECTION_MARKER 'B'
#define SPACE_CHAR ' '
#define NEWLINE_CHAR '\n'
#define GRAPH_SCALE 2 /* Need this to space the graph a little more evenly */

/* Interactive searching */
#define GRAPH 0
#define STATS 1
#define HELP 2

/* Statistics */
#define YEARS_IN_QUADRENNIUM 4
#define NO_RANK_CHAR '-'

/* File parsing */
#define BASE 10
#define MALE_CHAR 'M'
#define FEMALE_CHAR 'F'

/* Struct Definitions */
struct nameData {
  short mRanks[NUM_RANKS];  /* Rank for the name for males by decade */
  short fRanks[NUM_RANKS];  /* Rank for the name for females by decade */
  char name[MAX_NAME_LEN];  /* Name for which we aggregate data */
};
typedef struct nameData nameData_t;

struct tableEntry {
  nameData_t * dataPtr;     /* Pointer to the first nameData struct */
  size_t numNames;          /* Number of names in this entry */
};
typedef struct tableEntry tableEntry_t;

struct namesTable {
  tableEntry_t * entryPtr;  /* Pointer to the first entry in the table */
  size_t size;              /* Size of the table */
};
typedef struct namesTable namesTable_t;


/* C Function Prototypes */
long convertStr( char * str, int * errorFlag );
int populateNameData( namesTable_t * table, char * dirName );
int filenameCompare( const void * p1, const void * p2 );
nameData_t * nameQuest( char * name, tableEntry_t * te );
void handleUserInput( namesTable_t * table );
int parseCmd( const char * const cmdString, const char * const commands[] );
void printStats( nameData_t * namePtr );
void generateGraph( nameData_t * name, char arr[GRAPH_ROWS][GRAPH_COLS] );
void drawGraph( char arr[GRAPH_ROWS][GRAPH_COLS] );

/* Assembly Function Prototypes */
int getTableIndex( char const * name, size_t tableSize );
long myRemainder( long dividend, long divisor );
long isInRange( long num, long min, long max );
int hash( const char * str );


#endif /* PA3_H */
