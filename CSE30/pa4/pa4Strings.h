/*
 * File: pa4Strings.h
 * Description: Header file containing strings that are displayed to the user.
 * 
 * XXX DO NOT EDIT THIS FILE
 *
 */

#ifndef PA4_STRINGS_H /* Header guard */
#define PA4_STRINGS_H

/* Search Strings */
#define RTABLE_FILE_ERR "Error opening table file for reading"
#define MISSING_INFILE "Search requires an infile argument.\n"
#define EXTRA_ARGS "Too many args to %s.\n"
#define TABLE_SIZE_ERR "Table size must be in the range of [%d-%d]\n"
#define LONG_SEARCH_USAGE "\nUsage: ./search -i inFile [-x] [-h]\n"\
  "    -i inFile -- The file containing the hash tables to search\n"\
  "    -x        -- Prints statistics for search, including linked list \n"\
  "                 and table collisions.\n"\
  "    -h        -- Displays this long usage message\n\n"
#define SHORT_SEARCH_USAGE "\nUsage: ./search -i inFile [-x] [-h]\n\n"
#define STATS_FOUND "%d email(s) were found to be SPAM.\n"
#define STATS_COLLISION "%d collision(s) occured in table %d.\n"
#define STATS_TOTAL "%d total searches.\n"


/* Create Strings */
#define WTABLE_FILE_ERR "Error opening table file for writing"
#define FILTER_ERR "Error opening input filter file"
#define INVALID_NUM "%s is not a valid number.\n"
#define TOO_LARGE_NUM "%s could not be converted to a long in base %d"
#define ARG_ERR "Missing file args\n"
#define LONG_CREATE_USAGE ""\
  "\nUsage: ./create -i dataFile -o outFile [-s size] [-h]\n"\
  "    -i/--infile dataFile -- The file containing the data\n"\
  "    -o/--output outFile  -- The file to output hash tables to\n"\
  "    -s/--size size       -- The size of the hash tables.\n"\
  "                            If not specified defaults to 5000.\n"\
  "    -h/--help            -- Displays this long usage message\n\n"\

#define SHORT_CREATE_USAGE ""\
  "\nUsage: ./create -i dataFile -o outFile [-s size] [-h]\n\n"


/* Interactive Strings */
#define USER_PROMPT "Enter a word: "
#define WORD_NOT_FOUND "%s is not SPAM!\n"
#define FOUND_IN_SOME "%s was found in %d tables.\n"
#define FOUND_IN_ALL "%s is SPAM!\n"

#endif
