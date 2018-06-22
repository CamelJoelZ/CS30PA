/*
 * Filename: convertStr.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: convert the str to long 
 * Date: May/13/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "pa3.h"
#include "pa3Strings.h"


/*
 * Function Name: convertStr();
 *
 * Function Prototype: long convertStr( char * str, int * errorFlag ); 
 * Description : This function converts the input str to a
 *  long value using strtol(). and return corresponding
 *  error flag if happened     
 *
 * Parameters: char * str, int * errorFlag 
 * Side Effects: None
 * Error Condition: 1. Input str is a number too large
 *                   to be converted to a long
 *                  2. Input str is not a valid number
 * Return Value: Converted long on success, -1 on failure. 
 *
 */
long convertStr( char * str, int * errorFlag ){
  // null check for parameters
  if( str == NULL || errorFlag == NULL) return -1;
  
  char * endPtr;
  errno = 0;
  long ret = strtol(str,&endPtr,BASE);

  // num too large
  if(errno != 0){
    // set the erroFlag
    *errorFlag = 1;
    // print out error msg
    char errorMsg [BUFSIZ];
    snprintf(errorMsg,BUFSIZ,STR_ERR_CONVERTING,str,BASE);
    perror(errorMsg);
    //return failure
    return -1;
  }

  // str not a valid number
  if(*endPtr != '\0'){
    // set the erroFlag
    *errorFlag = 1;
    // print out error msg
    fprintf(stderr,STR_ERR_NOTINT,str);
    //return failure
    return -1;
  }
  
  // no error occured 
  *errorFlag = 0;
  return ret;
  
}
