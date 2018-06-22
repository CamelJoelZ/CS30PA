/*
 * Filename: getFromTable.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Descriptions: This function takes a hash value and a table pointer 
 *               and returns the element at the relevant index of the table 
 * Date: June/02/2018
 * Sources of Help: Manpage
 */ 


#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name:getFromTable 
 *
 * Function Prototype: void * getFromTable( int hashVal, table_t * table );
 *
 * Description: This function takes a hash value and a table pointer
 *              and returns the element at the relevant index of the table
 * Parameters: int hashVal, table_t * table 
 * Side Effects: None
 * Error Condition: None 
 * Return Value: The element at the relevant index of the table. 
 *
 */
void * getFromTable( int hashVal, table_t * table ){
  // calculate the index
  int index = ((hashVal % table -> size) + table -> size) % table -> size;

  return table -> tbl[index];

}
