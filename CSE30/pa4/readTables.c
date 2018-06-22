/*
 * Filename: readTables.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Descriptions: Read from outFile and populate the three hashtables
 *               serialized in writeTables(). 
 *            
 * Date: June/02/2018
 * Sources of Help: Manpage
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

#define NUL '\0'
/*
 * Function Name:  readTables 
 *
 * Function Prototype: void readTables( FILE * inFile, table_t * htbl, 
 *                       table_t * rtbl, table_t * eotbl )
 *
 * Description: This function frees all elements in the input linked list. 
 *            
 * Parameters: FILE * inFile, table_t * htbl, table_t * rtbl, 
 *             table_t * eotbl
 * Side Effects: new memory allocated for tbl field of 3 tbls in 
 *               parameters.
 * Error Condition: Error with dynamically allocating memory.  
 * Return Value: None 
 *
 */
void readTables( FILE * inFile, table_t * htbl, table_t * rtbl,
table_t * eotbl ){

  // read size 
  int size;
  fread(&size,sizeof(int),1,inFile);
  // populate size 
  htbl -> size = size;
  rtbl -> size = size;
  eotbl -> size = size;

  // dynamically allocate space for tbl for htbl rtbl and eotbl
  htbl -> tbl = calloc(size,sizeof(void*));
  rtbl -> tbl = calloc(size,sizeof(void*));
  eotbl -> tbl = calloc(size,sizeof(void*));
  
  // read content of htbl
  fread(htbl -> tbl, sizeof(void*),size,inFile);
  
  // read content for rtbl 
  fread(rtbl -> tbl, sizeof(void*),size,inFile);
 
  
  char buffer[BUFSIZ] = {0};
  // read content for eotbl 
  //for(int index = 0; index < size; index++)
  int index = 0;
  int remain = 0;
  char * start = NULL;
  int numRead = 0;

  while((numRead = fread(buffer + remain,sizeof(char),BUFSIZ - remain,inFile))
  != 0){

    
    start = buffer;
    // iterate through the buffer
    while(start < buffer + numRead + remain ){
      
      // check the head
      if(*start == NUL && start < buffer + numRead + remain){
        index++;
        start++;
      }
      else{
        // check if there is null terminator after start
        if(strchr(start,NUL) == NULL) break;
        if(strchr(start,NUL) >= buffer + numRead + remain) break;

        // push the extracted name node to the linked list
        pushToList((eotbl -> tbl) + index,start);

        // update start to the one byte after string
        start = strchr(start,NUL) + 1;

        // if reach the end of the buffer
        if(start == buffer + numRead + remain) break;

      }
    }
    // calculate the len of the appending str
    remain = buffer + numRead + remain - start;
    // put the extra appending str to the front
    memmove(buffer,start,remain);
    
  }
}  
    


