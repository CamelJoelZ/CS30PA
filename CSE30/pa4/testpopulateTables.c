/*
 * Filename: testpopulateTables.c
 * Author: Zhuoer Wen 
 * Userid: cs30xgz
 * Description: Unit test program to test the function populateTables().
 * Date: May/29/2018
 * Sources of Help: Man Page
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for populateTables 
 *
 * void populateTables( table_t * htbl, 
 *                      table_t * rtbl, table_t * eotbl,
 *                      FILE * dataFile );
 */
void testpopulateTables() {
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
  fprintf(stderr,"\n--------Testing a small base file\n");
  FILE * open = fopen("emails/emails_10","r");

  // populate all the tree table with emails_10
  populateTables(&htbl,&rtbl,&eotbl,open);

  // check if the corresponding slot in htbl is 1
  int indexH = hash("horizontal@hack.co");
  indexH = ((indexH % 10) + 10) % 10;
  TEST((htbl.tbl)[indexH] == (void*)1);

  // check if the corresponding slot in htbl is 1
  indexH = hash("oratorio@spam.me");
  indexH = ((indexH % 10) + 10) % 10;
  TEST((htbl.tbl)[indexH] == (void*)1);

  // check if the corresponding slot in htbl is 1
  indexH = hash("unconscious@hack.co");
  indexH = ((indexH % 10) + 10) % 10;
  TEST((htbl.tbl)[indexH] == (void*)1);

  // check if the corresponding slot in rtbl is 1
  int indexR = revHash("horizontal@hack.co");
  indexR = ((indexR % 10) + 10) % 10;
  TEST((rtbl.tbl)[indexR] == (void*)1);

  // check if the corresponding slot in rtbl is 1
  indexR = revHash("oratorio@spam.me");
  indexR = ((indexR % 10) + 10) % 10;
  TEST((rtbl.tbl)[indexR] == (void*)1);

  // check if the corresponding slot in rtbl is 1
  indexR = revHash("unconscious@hack.co");
  indexR = ((indexR % 10) + 10) % 10;
  TEST((rtbl.tbl)[indexR] == (void*)1);

  // check if the corresponding slot in eotbl has the correct val
  char * str = "horizontal@hack.co";
  // get the index of the void *  array
  int indexEO = evenOddHash(str);
  indexEO = ((indexEO % 10) + 10) % 10;

  // set to 1 when found the element in the linked list
  int found = 0;
  struct llist * cur = *(eotbl.tbl + indexEO);
  // loop through the linked list to see if there is such value
  while(cur != NULL){
    if(strcmp((cur -> value),str) == 0){
      found = 1;
      break;
    }
    cur = cur -> next;
  }
  TEST(found == 1);

  // check if the corresponding slot in eotbl has the correct val
  str = "oratorio@spam.me";
  // get the index of the void *  array
  indexEO = evenOddHash(str);
  indexEO = ((indexEO % 10) + 10) % 10;

  // set to 1 when found the element in the linked list
  found = 0;
  cur = *(eotbl.tbl + indexEO);
  // loop through the linked list to see if there is such value
  while(cur != NULL){
    if(strcmp((cur -> value),str) == 0){
      found = 1;
      break;
    }
    cur = cur -> next;
  }
  TEST(found == 1);

  // check if the corresponding slot in eotbl has the correct val
  str = "unconscious@hack.co";
  // get the index of the void *  array
  indexEO = evenOddHash(str);
  indexEO = ((indexEO % 10) + 10) % 10;

  // set to 1 when found the element in the linked list
  found = 0;
  cur = *(eotbl.tbl + indexEO);
  // loop through the linked list to see if there is such value
  while(cur != NULL){
    if(strcmp((cur -> value),str) == 0){
      found = 1;
      break;
    }
    cur = cur -> next;
  }
  TEST(found == 1);
  

  // testing a larger base file
  fprintf(stderr,"\n--------Testing a larger base file\n");
  // open the file
  FILE * larger = fopen("emails/emails_10000","r");

  // populate all the tree table with emails_10
  populateTables(&htbl,&rtbl,&eotbl,larger);

  // check if the corresponding slot in htbl is 1
  indexH = hash("dentine@hack.co");
  indexH = ((indexH % 10) + 10) % 10;
  TEST((htbl.tbl)[indexH] == (void*)1);

  // check if the corresponding slot in htbl is 1
  indexH = hash("solvency@hack.co");
  indexH = ((indexH % 10) + 10) % 10;
  TEST((htbl.tbl)[indexH] == (void*)1);

  // check if the corresponding slot in htbl is 1
  indexH = hash("lag@spam.me");
  indexH = ((indexH % 10) + 10) % 10;
  TEST((htbl.tbl)[indexH] == (void*)1);

  // check if the corresponding slot in rtbl is 1
  indexR = revHash("dentine@hack.co");
  indexR = ((indexR % 10) + 10) % 10;
  TEST((rtbl.tbl)[indexR] == (void*)1);

  // check if the corresponding slot in rtbl is 1
  indexR = revHash("solvency@hack.co");
  indexR = ((indexR % 10) + 10) % 10;
  TEST((rtbl.tbl)[indexR] == (void*)1);

  // check if the corresponding slot in rtbl is 1
  indexR = revHash("lag@spam.me");
  indexR = ((indexR % 10) + 10) % 10;
  TEST((rtbl.tbl)[indexR] == (void*)1);

  // check if the corresponding slot in eotbl has the correct val
  str = "dentine@hack.co";
  // get the index of the void *  array
  indexEO = evenOddHash(str);
  indexEO = ((indexEO % 10) + 10) % 10;

  // set to 1 when found the element in the linked list
  found = 0;
  cur = *(eotbl.tbl + indexEO);
  // loop through the linked list to see if there is such value
  while(cur != NULL){
    if(strcmp((cur -> value),str) == 0){
      found = 1;
      break;
    }
    cur = cur -> next;
  }
  TEST(found == 1);

  // check if the corresponding slot in eotbl has the correct val
  str = "solvency@hack.co";
  // get the index of the void *  array
  indexEO = evenOddHash(str);
  indexEO = ((indexEO % 10) + 10) % 10;

  // set to 1 when found the element in the linked list
  found = 0;
  cur = *(eotbl.tbl + indexEO);
  // loop through the linked list to see if there is such value
  while(cur != NULL){
    if(strcmp((cur -> value),str) == 0){
      found = 1;
      break;
    }
    cur = cur -> next;
  }
  TEST(found == 1);

  // check if the corresponding slot in eotbl has the correct val
  str = "lag@spam.me";
  // get the index of the void *  array
  indexEO = evenOddHash(str);
  indexEO = ((indexEO % 10) + 10) % 10;

  // set to 1 when found the element in the linked list
  found = 0;
  cur = *(eotbl.tbl + indexEO);
  // loop through the linked list to see if there is such value
  while(cur != NULL){
    if(strcmp((cur -> value),str) == 0){
      found = 1;
      break;
    }
    cur = cur -> next;
  }
  TEST(found == 1);
  
}

/*
 * Main driver for the tester
 */
int main() {
  fprintf( stderr, "Testing ...\n\n" );
  testpopulateTables();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
