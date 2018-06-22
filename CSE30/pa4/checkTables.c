/*
 * Filename: checkTables.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Descriptions: This function reports the number of tables the 
 *               input string was seen in. 
 *              
 * Date: June/02/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: checkTables
 *
 * Function Prototype: int checkTables( char * str, table_t * htbl, 
                       table_t * rtbl, table_t * eotbl );
 *
 * Description: This function reports the number of tables the 
 *              input string was seen in.
 *          
 * Parameters: char * str, table_t * htbl, table_t * rtbl, table_t * eotbl 
 * Side Effects: None
 * Error Condition: None 
 * Return Value: Number of tables the string was found in, or IN_TABLE 
 *               if it is found in all three tables and the
 *               linked list attached to the 3rd table
 *
 */
int checkTables(char * str, table_t * htbl, table_t * rtbl, table_t * eotbl){
  // local var
  int hashVal;
  void * ret;
  linkedList_t * cur;
  int count = 0;
  //int strLen = strlen(str);

  // Check htbl first
  hashVal = hash(str);
  ret = getFromTable(hashVal,htbl);
  if((int)ret == 1){
    count++;
  }
  else{
    return count;
  }

  // check rtbl
  hashVal = revHash(str);
  ret = getFromTable(hashVal,rtbl);
  if((int)ret == 1){
    count++;
  }
  else{
    return count;
  }

  // check eotbl
  hashVal = evenOddHash(str);
  cur = getFromTable(hashVal,eotbl);
  if(cur == NULL){
    return count;
  }
  else{
    count++;
    // iterate over the linkedList
    while(cur != NULL){
      if(strncmp(cur -> value,str,BUFSIZ) == 0) return IN_TABLE;

      // update cur and next
      cur = cur -> next;
    }
    return count;

  }
}
