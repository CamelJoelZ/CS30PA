/*
 * Filename: freeLinkedList.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Descriptions: This function frees all elements in the input linked list 
 *            
 * Date: June/02/2018
 * Sources of Help: Manpage
 */ 

#include <stdlib.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: freeLinkedList.c 
 *
 * Function Prototype: void freeLinkedList( linkedList_t * head) 
 *
 * Description: This function frees all elements in the input linked list. 
 *            
 * Parameters:linkedList_t * head
 * Side Effects: deallocate the memory pointed by parameter
 * Error Condition: None 
 * Return Value: None 
 *
 */
void freeLinkedList( linkedList_t * head){ 
  // tmp var to store the next ele and the current ele
  //linkedList_t * cur = head;
  linkedList_t * next;

  // iterate through the linkedlist and free the node
  while(head != NULL){
    next = head -> next;
    free(head -> value);
    free(head);
    // reassign cur
    head = next;
  }
}
