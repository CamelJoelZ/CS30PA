/*
 * Filename: populateTables.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: This function is in charge of populating 3 hash tables 
 * Date: May/28/2018
 * Sources of Help: Manpage
 */ 

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "pa4.h"
#include "pa4Strings.h"
#define NEWLINE '\n'
#define NUL '\0'

/*
 * Function Name: populateTables 
 *
 * Function Prototype: void populateTables( table_t * htbl, 
 *  table_t * rtbl, table_t * eotbl, FILE * dataFile );
 *
 * Description: This function is in charge of populating 3 hash tables 
 *              by reading in the dataFile, grabbing each line through
 *              fgets(), and computing the hash value from each of the
 *              3 hash functions
 * Parameters:table_t * htbl, table_t * rtbl, table_t * eotbl,FILE * dataFile
 * Side Effects: 3 tables in the parameters will be populated with dataFile
 * Error Condition: None 
 * Return Value: None
 *
 */
void populateTables( table_t * htbl, table_t * rtbl, table_t * eotbl,
FILE * dataFile ){
  char buffer[BUFSIZ];
  
  int sizeH = htbl -> size;
  int sizeR = rtbl -> size;
  int sizeE = eotbl -> size;
  // iterate through the dataFile
  while(fgets(buffer,BUFSIZ,dataFile) != NULL){
    // find newline char in a line and replace it with null terminator
    char * found = strchr(buffer,NEWLINE);
    *found = NUL;

    // lower case every ele in the buffer
    for(int i = 0; buffer[i] != NUL; i++){
      buffer[i] = tolower(buffer[i]);
    }

    // generate three hashes for each string 
    int hashKey = hash(buffer); 
    hashKey = ((hashKey % sizeH) + sizeH) % sizeH;
    // for revHash
    int hashRev = revHash(buffer);
    hashRev = ((hashRev % sizeR) + sizeR) % sizeR;
    // for evenOdd Hash
    int hashEO = evenOddHash(buffer);
    hashEO = ((hashEO % sizeE) + sizeE) % sizeE;

    // index into the hash tables htbl and rtbl and set the entry to 1
    (htbl -> tbl)[hashKey] = (void*)1;
    (rtbl -> tbl)[hashRev] = (void*)1;

    //the string is pushed to the front of that linked list,
    void ** head = (eotbl -> tbl) + hashEO;
    pushToList(head,buffer);
  }

}
