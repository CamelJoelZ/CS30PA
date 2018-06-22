/*
 * Filename: writeTables.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description:This function serializes the three hash
 *              tables and writes them to outFile 
 * Date: May/28/2018
 * Sources of Help: Manpage
 */ 


#include "pa4.h"
#include "pa4Strings.h"
#define NUL '\0'

/*
 * Function Name: writeTables 
 *
 * Function Prototype: void writeTables( FILE * outFile, 
 *       table_t * htbl, table_t * rtbl, table_t * eotbl );
 *
 * Description:This function serializes the three hash tables
 *             and writes them to outFile so that they can later
 *             be read and deserialized back into hashtables in 
 *             their original format 
 * Parameters: FILE * outFile, table_t * htbl, table_t * rtbl,
 *             table_t * eotbl
 * Side Effects: write contents of 3 tbls to the outFile parameter.
 * Error Condition: None 
 * Return Value: None
 *
 */
void writeTables( FILE * outFile, table_t * htbl, table_t * rtbl,
table_t * eotbl ){
  int size = htbl -> size;

  //Write the size of the tables
  fwrite(&(htbl -> size),sizeof(int),1,outFile);

  //Write all entries of htbl
  void ** toWrite = (htbl -> tbl); 
  fwrite(toWrite,sizeof(void*),size,outFile);

  //Write all entries of rtbl
  toWrite = (rtbl -> tbl); 
  fwrite(toWrite,sizeof(void*),size,outFile);
  
  // Write the strings in each bucket of eotbl
  for(int i = 0; i < size; i++){
    struct llist * cur = eotbl -> tbl[i];

    // iterate through the linked list
    while(cur != NULL){
      fputs(cur -> value,outFile);
      fputc(NUL,outFile);
      cur = cur -> next;
    }
    // write the tail node
    fputc(NUL,outFile);
  }
}
