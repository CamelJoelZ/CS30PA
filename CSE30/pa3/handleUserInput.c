/*
 * Filename: handleUserInput.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: handle user input
 * Date: May/21/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "pa3.h"
#include "pa3Strings.h"

#define NL '\n'


/*
 * Function Name: handleUserInput() 
 *
 * Function Prototype: void handleUserInput( namesTable_t * table ) 
 *               
 * Description : This function allows the user to interactively
 *               search through the table for specific name.
 *
 * Parameters: namesTable_t * table 
 * Side Effects: None
 * Error Condition: 1. command not valid
 *                  2. strtok fail
 * Return Value: None 
 *
 */
void handleUserInput( namesTable_t * table ){
  // print out list of possibel commands
  printf(HELP_STR);
  printf(STR_PROMPT);

  // buffer to hold the command
  char buffer[BUFSIZ];

  // keep promting the user to enter
  while(fgets(buffer,BUFSIZ,stdin) != NULL){
    // replace the newline with a nul
    char * nl = strchr(buffer,NL);
    *nl = '\0';

    //extract the user's command
    char * extracted = strtok(buffer,SEP);
    // if could not be tokenized repromt the user
    if(extracted == NULL){

      // reprompt the user
      printf(STR_PROMPT);
      continue;
    }

    // Check to see if the command entered was valid
    static char const * const COMMANDS_LIST[] = COMMANDS;
    int index = parseCmd(extracted,COMMANDS_LIST);

    // could not find in COMMANDS
    if(index == -1){
      //print the ERR_CMD_NOT_FOUND error and reprompt the user
      fprintf(stderr,ERR_CMD_NOT_FOUND,extracted);

      // reprompt the user
      printf(STR_PROMPT);
      continue;
    }

    // help command
    if(index == HELP){
      printf(HELP_STR);

      // reprompt the user
      printf(STR_PROMPT);
      continue;
    }
    //  parse for directory name
    else{
      char * name = strtok(NULL,SEP);
      // if no name arg entered
      if(name == NULL){
        fprintf(stderr,ERR_NAME_NOT_ENTERED);

        // reprompt the user
        printf(STR_PROMPT);
        continue;
      }

      // if name is entered then modify the name

      // first char upper case
      name[0] = toupper(name[0]);
      // remaining lower case
      for(int k = 1; k < strlen(name); k++){
        name[k] = tolower(name[k]);
      }

      // calculate the index of the name
      int tableIndex = getTableIndex(name,table -> size);
      // try to find the nameData
      struct nameData * found = nameQuest(name,
                                        (table -> entryPtr) + tableIndex);
      // if not found
      if(found == NULL){
        printf( STR_NAME_NOT_FOUND,name);
        // reprompt the user
        printf(STR_PROMPT);
        continue;
      }
      // nameData found
      else{
        if(index == STATS){
          printf("%c",NL);
          printStats(found);
        }
        else if(index == GRAPH){
          char arr[GRAPH_ROWS][GRAPH_COLS];
          generateGraph(found,arr);
          drawGraph(arr);
        }
      }

    }
    // reprompt the user
    printf("%c",NL);
    printf(STR_PROMPT);
  }

}
