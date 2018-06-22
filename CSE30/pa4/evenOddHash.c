/*
 * Filename: evenOddHash.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: compute the hash key 
 * Date: May/28/2018
 * Sources of Help: Manpage
 */ 

#include <string.h>
#include "pa4.h"
#include "pa4Strings.h"
#define TWO 2

/*
 * Function Name: evenOddHash
 *
 * Function Prototype:int evenOddHash( char * str ); 
 *
 * Description : This function is also similar to
 *  hash.s, the only difference is that to compute 
 *  the hash key, it iterates through the string first
 *  by by even and then by odd indices. 
 *  
 * Parameters:char * str  
 * Side Effects: None
 * Error Condition:None  
 * Return Value: The hash key of str. 
 *
 */
int evenOddHash( char * str ){
  int hash = HASH_START_VAL;
  int strl = strlen(str);

  // even round
  for(int i = 0; i < strl; i += TWO){
    hash = hash * HASH_PRIME + str[i];
  }

  // odd round
  for(int j = 1; j < strl; j += TWO){
    hash = hash * HASH_PRIME + str[j];
  }

  return hash;
}
