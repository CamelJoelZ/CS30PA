/*
 * Filename: testwriteTables.c
 * Author: Zhuoer Wen 
 * Userid: cs30xgz
 * Description: Unit test program to test the function writeTables().
 * Date: May/29/2018
 * Sources of Help: Man Page
 */

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for writeTables 
 *
 * void writeTables( FILE * outFile, table_t * htbl, table_t * rtbl,
 *                    table_t * eotbl );
 *
 */
void testwriteTables() {
  // declare three structs 
  table_t htbl;
  table_t rtbl;
  table_t eotbl;

  // intialize the structs 
  htbl.size = 10;
  rtbl.size = 10;
  eotbl.size = 10;

  //void ** eo = calloc(10,sizeof(void *));
  void * ht[10] = {0};
  void * rt[10] = {0};
  void * eo[10] = {0};

  htbl.tbl = ht;
  rtbl.tbl = rt;
  eotbl.tbl = eo;

  // open the file
  FILE * open = fopen("emails/emails_10","r");

  // populate all the tree table with emails_10
  populateTables(&htbl,&rtbl,&eotbl,open);

  // open the outfile
  FILE * outFile = fopen("testw","w");
  writeTables(outFile,&htbl,&rtbl,&eotbl); 
}

/*
 * Main driver for the tester
 */
int main() {
  fprintf( stderr, "Testing ...\n\n" );
  testwriteTables();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
