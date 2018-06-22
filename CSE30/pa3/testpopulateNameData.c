/*
 * Filename: testpopulateNameDatac
 * Author: Zhuoer Wen 
 * Userid: cs30xgz
 * Description: Unit test program to test the function populateNaneData().
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
  

  /* Call populateNameData and check that there were no errors*/
  TEST( populateNameData( table, dirName ) == 0 );

}

/*
 * Unit Test for populateNameData.c
 *
 * int populateNameData( namesTable_t * table, char * dirName );
 *
 * Populates the namesTable with data from dirName.
 */
void testpopulateNameData() {
  
  /* Test 1: Smallest table size */
  printf("Test 1: small dataset and small table size\n");

  char *dirName = "testData/reallySmallData";
  int tableSize = 1;
  namesTable_t table;

  _setup( &table, tableSize, dirName );
  
  /* Validate the data in the table. */
  TEST( table.entryPtr[0].numNames != 0 );

  /* Search to see if the name John is present with correct ranks */
  nameData_t * name = nameQuest( "Jim", table.entryPtr );

  TEST( name != NULL );
  TEST( name->mRanks[0] == 48 && name->mRanks[1] == 50 );

  // search for Mary
  name = nameQuest( "Mary", table.entryPtr );

  TEST( name != NULL );
  TEST( name->fRanks[0] == 1 && name->fRanks[17] == 2 );
  
  // search for Taylor
  name = nameQuest( "Taylor", table.entryPtr );

  TEST( name == NULL );

  /* Test 2: Test with a larger table size */
  printf("\nTest 2: small dataset and largertable size\n");
  tableSize = 4;
  _setup( &table, tableSize, dirName );

  /* At least one name hashes to index 0 from this dataset, check to see if
   * it is present
   */
  TEST( table.entryPtr[0].numNames != 0 );

  // search for Jim
  int index = getTableIndex("Jim", tableSize);
  name = nameQuest( "Jim", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 48 && name->mRanks[1] == 50 );

  // search for Mary
  index = getTableIndex("Mary", tableSize);
  name = nameQuest( "Mary", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 0 && name->fRanks[0] == 1 );

  // search for sam
  index = getTableIndex("Sam", tableSize);
  name = nameQuest( "Sam", table.entryPtr + index);
  TEST( name == NULL );

  // search for john 
  index = getTableIndex("John", tableSize);
  name = nameQuest( "John", table.entryPtr + index);
  TEST( name == NULL );


  /* Test 3: larger dataset and small table size*/
  printf("\nTest 3: larger dataset and small table size\n");
  dirName = "testData/smallData";
  tableSize = 1;

  _setup( &table, tableSize, dirName );
  
  /* Validate the data in the table. */
  TEST( table.entryPtr[0].numNames != 0 );

  // search for Jim
  index = getTableIndex("Jim", tableSize);
  name = nameQuest( "Jim", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 48 && name->mRanks[1] == 50 );

  // search for Mary
  index = getTableIndex("Mary", tableSize);
  name = nameQuest( "Mary", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 0 && name->fRanks[0] == 1 );

  // search for SAm
  index = getTableIndex("Sam", tableSize);
  name = nameQuest( "Sam", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 31 && name->fRanks[0] == 0 );

  // search for John 
  index = getTableIndex("John", tableSize);
  name = nameQuest( "John", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 1 && name->fRanks[0] == 0 );

  /* Test 4: larger dataset and larger table size*/
  printf("\nTest 4: larger dataset and larger table size\n");
  dirName = "testData/smallData";
  tableSize = 19;

  _setup( &table, tableSize, dirName );
  
  /* Validate the data in the table. */
  TEST( table.entryPtr[0].numNames != 0 );

  // search for Jim
  index = getTableIndex("Jim", tableSize);
  name = nameQuest( "Jim", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 48 && name->mRanks[1] == 50 );

  // search for Mary
  index = getTableIndex("Mary", tableSize);
  name = nameQuest( "Mary", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 0 && name->fRanks[0] == 1 );

  // search for Joel
  index = getTableIndex("Sam", tableSize);
  name = nameQuest( "Sam", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 31 && name->fRanks[0] == 0 );

  // search for Rick 
  index = getTableIndex("John", tableSize);
  name = nameQuest( "John", table.entryPtr + index);
  TEST( name != NULL );
  TEST (  name->mRanks[0] == 1 && name->fRanks[0] == 0 );

}
/*
 * Unit Test for populateNameData.c
 *
 * main driver to run the testing function 
 *
 * print out the corresponding infomation about the test 
 */

int main() {
  (void) fprintf( stderr, "Testing populateNameData...\n\n" );
  testpopulateNameData();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
