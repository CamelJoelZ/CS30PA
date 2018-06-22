/*
 * Filename: testpushToList.c
 * Author: Zhuoer Wen 
 * Userid: cs30xgz
 * Description: Unit test program to test the function pushToList().
 * Date: May/29/2018
 * Sources of Help: Man Page
 */

#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for pushToList.c
 *
 * void pushToList( void ** head, char * str );
 */
void testpushToList() {
  // declare a head 
  linkedList_t * head;

  // push the first ele to the list
  char * str = "okk";
  pushToList((void **)&head,str);
  TEST(head -> next == NULL);
  TEST(strcmp(head -> value,str) == 0);

  // push the second ele to the list
  str = "ccc";
  pushToList((void **)&head,str);
  TEST(head -> next != NULL);
  TEST(strcmp(head -> next -> value,"okk") == 0);
  TEST(strcmp(head -> value,str) == 0);

  // push the third ele to the list
  str = "diaofeitian";
  pushToList((void **)&head,str);
  TEST(head -> next != NULL);
  TEST(strcmp(head -> next -> value,"ccc") == 0);
  TEST(strcmp(head -> next ->  next -> value,"okk") == 0);
  TEST(strcmp(head -> value,str) == 0);

  // push the fourth ele to the list
  str = "zhaoritian";
  pushToList((void **)&head,str);
  TEST(head -> next != NULL);
  TEST(strcmp(head -> next -> next -> value,"ccc") == 0);
  TEST(strcmp(head -> next ->  next -> next -> value,"okk") == 0);
  TEST(strcmp(head -> value,str) == 0);

  // push the fourth ele to the list
  str = "sitdown";
  pushToList((void **)&head,str);
  TEST(head -> next != NULL);
  TEST(strcmp(head -> next -> next -> value,"diaofeitian") == 0);
  TEST(strcmp(head -> next ->  next -> next -> value,"ccc") == 0);
  TEST(strcmp(head -> value,str) == 0);

}

/*
 * Main driver for the tester
 */
int main() {
  fprintf( stderr, "Testing ...\n\n" );
  testpushToList();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
