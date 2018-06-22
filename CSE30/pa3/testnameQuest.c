/*
 * Filename: testnameQuest.c
 * Author: Zhuoer Wen 
 * Userid: cs30xgz
 * Description: Unit test program to test the function nameQuest().
 * Date: May/16/2018
 * Sources of Help: ManPage
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"


/* Helper function to build the table for you */
void _setup( namesTable_t *table, size_t size, char *dirName ) {

  tableEntry_t * entries = calloc(size, sizeof(tableEntry_t));
  
  table->entryPtr = entries;
  table->size = size;
}

/*
 * Unit Test for nameQuest.c
 *
 * nameData_t * nameQuest( char * name, tableEntry_t * te );
 *
 * tester is the tableEntry struct to hold 5 name 
 */
void testnameQuest() {

  struct tableEntry tester;
  tester.dataPtr = calloc(5,sizeof(struct nameData));
  tester.numNames = 5;

  // populate the field of each nameData struct
  strncpy((*(tester.dataPtr)).name, "JOEL", MAX_NAME_LEN);
  strncpy((*(tester.dataPtr+1)).name, "MAX", MAX_NAME_LEN);
  strncpy((*(tester.dataPtr+2)).name, "STAN", MAX_NAME_LEN);
  strncpy((*(tester.dataPtr+3)).name, "BOMB", MAX_NAME_LEN);
  strncpy((*(tester.dataPtr+4)).name, "SASA", MAX_NAME_LEN);

  // check if name quest find the correct ptr
  TEST(nameQuest("JOEL",&tester) == tester.dataPtr);

  // test for name in the list 
  TEST(nameQuest("MAX",&tester) == tester.dataPtr + 1);

  // test for name in the list 
  TEST(nameQuest("STAN",&tester) == tester.dataPtr + 2);

  // test for name in the list 
  TEST(nameQuest("BOMB",&tester) == tester.dataPtr + 3);

  // test for name in the list 
  TEST(nameQuest("SASA",&tester) == tester.dataPtr + 4);

  // test for name not in the list 
  TEST(nameQuest("NONAME",&tester) == NULL);

  // test for first para NULL
  TEST(nameQuest(NULL,&tester) == NULL);

  // test for second para NULL
  TEST(nameQuest("NONAME",NULL) == NULL);
}

/*
 * Unit Test for nameQuest.c
 *
 * main driver for the test
 *
 * int main() {
 */
int main() {
  (void) fprintf( stderr, "Testing populateNameData...\n\n" );
  testnameQuest();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
