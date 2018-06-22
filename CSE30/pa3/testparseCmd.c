/*
 * Filename: testparseCmd.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function parseCmd.c
 * Date: May/15/2018
 * Sources of Help: ManPage
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "pa3Strings.h"

#define GRAPHINDEX 0
#define STATSINDEX 1
#define HELPINDEX 2
#define NULLINDEX 3


/*
 * Unit Test for parseCmd.c
 *
 * int parseCmd( const char * const cmdString,
 *                const char * const commands[] );
 *
 */
void testparseCmd() {
 // all the commands in this program
 static char const * const COMMANDS_LIST[] = COMMANDS;

 // testing case that cmdstring is not in the commands arr
 const char * const cmdString = "sss";
 TEST(parseCmd(cmdString,COMMANDS_LIST) == -1);

 // testing case that cmdstring is not in the commands arr
 const char * const cmdString1 = "aaa";
 TEST(parseCmd(cmdString1,COMMANDS_LIST) == -1);

 // testing case that cmdstring is in the commands arr
 const char * const cmdString2 = "graph";
 TEST(parseCmd(cmdString2,COMMANDS_LIST) == GRAPHINDEX);

 // testing case that cmdstring is in the commands arr
 const char * const cmdString3 = "stats";
 TEST(parseCmd(cmdString3,COMMANDS_LIST) == STATSINDEX);

 // testing case that cmdstring is in the commands arr
 const char * const cmdString4 = "help";
 TEST(parseCmd(cmdString4,COMMANDS_LIST) == HELPINDEX);

}

/*
 * main driver for the testing 
 *
 * int main() {
 */
int main() {
  (void) fprintf( stderr, "Testing ...\n\n" );
  testparseCmd();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
