/*
 * Filename: nameQuest.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: search for a specific name struct 
 * Date: May/13/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>
#include <string.h>

#include "pa3.h"
#include "pa3Strings.h"



/*
 * Function Name: nameQuest() 
 *
 * Function Prototype:nameData_t *nameQuest( char * name, tableEntry_t * te) 
 *               
 * Description : This function performs a linear search through the array 
 *               of nameData_t structs in the table entry te, looking
 *               for the struct containing the specified name
 *
 * Parameters: char * name, tableEntry_t * te
 * Side Effects: None
 * Error Condition: 1.  either of the pointers passed in are NULL 
 *
 * Return Value: If found, return a pointer to the struct containing name. 
 *                 Otherwise return NULL
 *
 */

nameData_t * nameQuest( char * name, tableEntry_t * te ){
  // null check for parameters
  if( name == NULL || te == NULL) return NULL;
  
  // number of names in this entry
  int num = (*te).numNames;

  // length to compare in strncmp includnign \0
  int length = strlen(name) + 1;

  // set the ptr correctly to the array of nameData
  struct nameData * ptr = (*te).dataPtr;

  // loop through the table entry to find if name in the tableEntry
  for(int i = 0; i < num; i++){

    // set thet current struct using ptr
    struct nameData cur = *ptr;
    char * curName = cur.name;
    int ret = strncmp(name, curName, length);
    // return ptr to the struct if the same
    if( ret == 0) return ptr;
    // increment the ptr if not the same
    else ptr++;

  }
  // return null if not found
  return NULL;
}
