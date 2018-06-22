/*
 * Filename: parseCmd.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: parse the command 
 * Date: May/13/2018
 * Sources of Help: Manpage
 */ 


#include <stdio.h>
#include <string.h>
#include "pa3.h"
#include "pa3Strings.h"



/*
 * Function Name: parseCmd() 
 *
 * Function Prototype:int parseCmd( const char * const cmdString
 *                               ,const char * const commands[] );
 *               
 * Description :This function checks to see if the cmdString 
 *              is in the commands array
 *
 * Parameters:const char * const cmdString,const char * const commands[]
 * Side Effects: None
 * Error Condition: None 
 *
 * Return Value: If cmdString is found, return the index of
 *                 cmdString in the commands array 
 *                 return -1 to indicate cmdString was 
 *                 not in the commands array.
 */
int parseCmd( const char * const cmdString, const char * const commands[] ){

  //null check for cmdString
  if(cmdString == NULL) return -1;
  if(commands == NULL) return -1;

  // length of cmdString including the null terminator
  int length = strlen(cmdString) + 1;
  
  // start index 
  int index = 0;
  // loop through the array
  while( commands[index] != NULL ){
    int ret = strncmp(cmdString, commands[index], length); 
    // return the index if two are the same
    if(ret == 0)  return index;
    // if not the same go to the next element
    else index++;
  }

  // already go over the whole array and cmdString not found
  return -1;

}
