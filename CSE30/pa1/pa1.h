/*
 * File: pa1.h
 * Description: Header file that contains function prototypes and
 *              constants.
 *
 * XXX Only add constants to this file.
 * DO NOT EDIT FUNCTION PROTOTYPES OR PREDEFINED CONSTANTS
 *
 */

#ifndef PA1_H    /* Macro Guard */
#define PA1_H

/* Base to use with strtol */
#define BASE 10

/* Range limits for command line arguments */
#define HEIGHT_MIN 3
#define HEIGHT_MAX 145
#define ASCII_MIN 33
#define ASCII_MAX 126

/* Assembly function prototypes */
long isInRange( long value, long minRange, long maxRange );
void displayBowtie( long height, char border, char filler, char bowtie );
void printBowtieLine(long row, long height, char bowtie, char filler);
long isEven( long value );
void printChar( char ch );
long myRemainder( long dividend, long divisor );

/* EC Assembly function prototypes */
long numOfDigits( long num, long base );


#endif /* PA1_H */
