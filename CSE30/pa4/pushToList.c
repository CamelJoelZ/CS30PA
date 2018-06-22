/*
 * Filename: pushToList.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: This function takes in
 *              the head of a linked list and an element
 *              to insert (a string) and then pushes the
 *              element onto the front of the linked list. 
 * Date: May/28/2018
 * Sources of Help: Manpage
 */ 

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name:  pushToList 
 *
 * Function Prototype: void pushToList( void ** head, char * str );
 *
 * Description: This function takes in
 *              the head of a linked list and an element
 *              to insert (a string) and then pushes the
 *              element onto the front of the linked list. 
 * Parameters: void ** head, char * str
 * Side Effects: allocate new memory and update the fields of head parameter. 
 * Error Condition: Error with dynamically allocating memory. 
 * Return Value: None
 *
 */
void pushToList( void ** head, char * str ){
  // allocate memory for str including null terminator
  int len = strlen(str) + 1;
  errno = 0;
  char * ret = calloc(len,sizeof(char));

  // error check for mem allocation
  if(ret == NULL || errno != 0){
    free(ret);
    perror(MEM_ERR);
    return;
  }

  // mem allocation success
  // copy str to newly allocated mem including \0
  strncpy(ret,str,len);

  // allocate memory for a new linkedList_t
  struct llist * new = calloc(1,sizeof(struct llist));

  // error check for mem allocation
  if(new == NULL){
    free(new);
    perror(MEM_ERR);
    return;
  }
  
  // point value to the new string
  new -> value = ret;
  // update the next in struct
  new -> next = *head;

  // redirect *head to the newly created struct
  *head = new;
}
