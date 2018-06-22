/*
 * Filename: beginUserQuery.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Descriptions: This function handles user interaction 
 *               to search the tables and reports number 
 *               of collisions occurred as the user searches 
 *               for emails. 
 *            
 * Date: June/02/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "pa4.h"
#include "pa4Strings.h"

#define NEWLINE '\n'
#define NUL '\0'
#define TABLETHREE 3
#define TABLETWO 2
#define TABLEONE 1

/*
 * Function Name: beginUserQuery.c 
 *
 * Function Prototype: void beginUserQuery(int counts[], table_t * htbl,
                       table_t * rtbl, table_t * eotbl, int statsOn);
 *
 * Description: This function handles user interaction to search the tables 
 *              and reports number of collisions occurred as the user 
 *              searches for emails. 
 *            
 * Parameters: int counts[], table_t * htbl, table_t * rtbl,
 *             table_t * eotbl, int statsOn)
 * Side Effects: update 3 tables and also the counts array in the parameter. 
 *              print out prompt and error message accordingly.
 * Error Condition: None 
 * Return Value: None 
 *
 */
void beginUserQuery(int counts[], table_t * htbl, table_t * rtbl,
table_t * eotbl, int statsOn){
  char buffer[BUFSIZ];  
  int numSearch = 0;
  // prompt the user
  printf(USER_PROMPT);


  while(fgets(buffer,BUFSIZ,stdin) != NULL){
    if( *buffer == NEWLINE){
      printf(USER_PROMPT);
      continue;
    }

    // find newline char in a line and replace it with null terminator
    char * found = strchr(buffer,NEWLINE);
    *found = NUL;
    
    // lower case every ele in the buffer
    for(int i = 0; buffer[i] != NUL; i++){
      buffer[i] = tolower(buffer[i]);
    }

    // check the string in three tables by calling checkTables(). 
    int ret = checkTables(buffer,htbl,rtbl,eotbl);
    // If checkTables() returns the macro IN_TABLE
    if(ret == IN_TABLE){
      printf(FOUND_IN_ALL,buffer);
    }
    // for not stats mode
    if(ret != IN_TABLE && statsOn != 1){
      printf(WORD_NOT_FOUND,buffer);
    }
    // If the string is found in at least one table
    else if(ret >= 1 && ret != IN_TABLE && statsOn == 1){
      printf(FOUND_IN_SOME,buffer,ret);
    }
    // If the string in not found in any of the tables
    else if(ret == 0 && statsOn == 1){
      printf(WORD_NOT_FOUND,buffer);
    }

    // update collisions occurred
    for(int r = 0; r <= ret ; r++){
      counts[r] ++;    
    }
    
    // uodate number of search done
    numSearch++;
    // reprompt the user
    printf(USER_PROMPT);
  } 
  
  // Lastly, print a newline before exiting the function
  printf("%c",NEWLINE);
  
  // prints out corresponding msg
 
  if(statsOn == 1){
    // report collisons stats
    printf(STATS_FOUND,counts[IN_TABLE]);
    printf(STATS_COLLISION,counts[TABLETHREE],TABLETHREE);
    printf(STATS_COLLISION,counts[TABLETWO],TABLETWO);
    printf(STATS_COLLISION,counts[TABLEONE],TABLEONE);
    printf(STATS_TOTAL,numSearch);

  }
}
