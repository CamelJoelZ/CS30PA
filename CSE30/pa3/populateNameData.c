/*
 * Filename: populateData.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: populate the table  
 * Date: May/13/2018
 * Sources of Help: Manpage
 */ 


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "pa3.h"
#include "pa3Strings.h"

#define NL "\n"
#define TWO 2


/*
 * Function Name: populateNameData() 
 *
 * Function Prototype:int populateNameData
 *                     ( namesTable_t * table, char * dirName );
 *               
 * Description : This function will populate the table by reading in data 
 *               from files inside the directory dirName 
 *
 * Parameters:namesTable_t * table, char * dirName
 * Side Effects: None
 * Error Condition: 1. Opening a file/directory fails
 *                  2. Error with dynamically allocating memory
 *                  3. Error with the format of the data
 *
 * Return Value: 0 on success, -1 on failure. 
 *              
 */

int populateNameData( namesTable_t * table, char * dirName ){
  // indicate if error during memory allocation
  struct nameData * newAllocate = NULL;

  // NULL check for parameters
  if(table == NULL || dirName == NULL){
    return -1;
  }

  // open the dir
  errno = 0;
  DIR * dir = opendir(dirName);
  // error opening a dirctory
  if(errno != 0 || dir == NULL){
    fprintf(stderr,NL);
    // dirName passed in
    perror(dirName);
    fprintf(stderr,NL);
    return -1;
  }

  // filePath array declared
  char * filePathArr [NUM_QUADRENNIUM];

  // read all the entry and store to an array of strings
  for(int i = 0; i < NUM_QUADRENNIUM; i++){
    
    struct dirent * entryStruct;
    entryStruct = readdir(dir);
    char * name = (*entryStruct).d_name;
    int length = strlen(name);

    // excluding . and .. for entry
    if(strncmp(name,STR_CUR_DIR,length) == 0){
      i--;
      continue;
    }
    if(strncmp(name,STR_PARENT_DIR,length) == 0){
      i--;
      continue;
    }

    
    // allocate mem for element inside array 
    char * alloc = calloc(MAX_PATH_LEN,sizeof(char));

    // error when allocating memory
    if(alloc == NULL){

      //  free all allocated memory in filePathArr
      free(alloc);
      for(int f = 0; f < (i - 1); f++){
       free(filePathArr[f]);
      }

      perror(NULL);
      return -1;
    }

    char * filePath = alloc;
    // build up file paths str
    snprintf(filePath,MAX_PATH_LEN,STR_PATH_FMT,dirName,name);
    // make sure to null-terminate
    *(filePath + MAX_PATH_LEN -1) = '\0';
    // put the char ptr in the array
    filePathArr[i] = filePath;
  }
    // sort the namepath array
    qsort(filePathArr,NUM_QUADRENNIUM,sizeof(char*),filenameCompare);
    
    // iterate through the array and read each file
    for(int j = 0; j < NUM_QUADRENNIUM; j++){
      // open each file for reading
      FILE * fp;
      errno = 0;
      fp = fopen(filePathArr[j],"r");
      // error opeing a file
      if(errno != 0 || fp == NULL){
        fprintf(stderr,NL);
        perror(filePathArr[j]);
        fprintf(stderr,NL);
        
        // free all allocated memory in filePathArr
        for(int f = 0; f < NUM_QUADRENNIUM; f++){
          free(filePathArr[f]);
        }

        // return if error opening a file
        return -1;
      }
      
      // buffer to hold each line content
      char buffer[MAX_LINE_LEN];
      // indicate how many lines read
      int lineRead = 0;
      //read each line
      while(fgets(buffer,MAX_LINE_LEN,fp) != NULL && lineRead < 
            (MAX_RANK + MAX_RANK)){

        // increment line indicator
        lineRead++;
        
        // keep track of num of comma in a line
        int commaNum = 0;
        // iterate through a line 
        for(int k = 0; buffer[k] != '\0'; k++){
          
          // check the format for each line
          if(buffer[k] == ',') commaNum++;

          // change the buffer to proper format
          if(buffer[k] == ',' && commaNum <= TWO){ 
            buffer[k] = '\0';
          }
          if(buffer[k] == NEWLINE_CHAR){
            buffer[k] = '\0';
          }
        }

        // check for format error of data
        if(commaNum < TWO){

          // free all allocated memory in filePathArr
          for(int f = 0; f < NUM_QUADRENNIUM; f++){
            free(filePathArr[f]);
          }
          // less than two comma
          if(commaNum < TWO){
            fprintf(stderr,STR_ERR_NAMEDATA);
          }

          return -1;
        }


        // holder for each extracter var
        char * name;
        char * gender;
        char * rank;
        
        // extracting all elemet for a line
        name = buffer;
        gender = strchr(buffer,'\0') + 1;
        rank = strchr(gender,'\0') + 1;

        // make sure to uppercase the gender
        *gender = toupper(*gender);

        // convert rank to long value
        int errorFlag;
        long rankL = convertStr(rank,&errorFlag);
        // try to use errorFlag to do some error checking
        if(rankL == -1 || errorFlag == 1){
          fprintf(stderr,NL);
          return -1; 
        }

        // store the info into the table
        // get the hash index
        int hashIndex = getTableIndex(name,(*table).size);
          
        // get the table entry at specific index
        struct tableEntry * cur = (table -> entryPtr) + hashIndex;

        // if the entry has no names
        if(cur -> numNames == 0){
        
          newAllocate = calloc(1,sizeof(struct nameData));

          // error when allocating memory
          if(newAllocate == NULL){
             
            // FREE all allocated memory in filePathArr
            for(int f = 0; f < NUM_QUADRENNIUM; f++){
              free(filePathArr[f]);
            }

            // FREE all allocated memory of namedata in list of tableEntry 
            int sizeL = table -> size;
            struct tableEntry * startEntry = table -> entryPtr; 
            for(int q = 0; q < sizeL; q++){
              free(startEntry[q].dataPtr); 
            }

            perror(NULL);
            return -1;
          }
      
          cur -> dataPtr = newAllocate;
         // update the field of nameData just createed
            
          // update the rank
          if(*gender == MALE_CHAR){
            // update mRanks field at index i
            cur -> dataPtr -> mRanks[j] = (short)rankL;
          }
          else{
            //curNameData.fRanks[j] = (short)rankL;
            cur -> dataPtr -> fRanks[j] = (short)rankL;
          }
          // update the name 
          strncpy(cur -> dataPtr -> name,name,strlen(name)+1);

          // increment numNames
          (cur -> numNames)++;
        }
        // entry has at least one name
        else{
        
          struct nameData * nameDataFoundPtr = nameQuest(name, cur);

          // name found
          if(nameDataFoundPtr != NULL){
            // update the rank
            if(*gender == MALE_CHAR){
              // update mRanks field at index i
              nameDataFoundPtr -> mRanks[j] = (short)rankL;
            }
            else{
              (*nameDataFoundPtr).fRanks[j] = (short)rankL;
            } 
            // update the name 
            strncpy(nameDataFoundPtr -> name,name,strlen(name)+1);
          }

          // no name found
          else{
            int nameNum = cur -> numNames;

            // realloc new memory
            newAllocate = realloc(cur -> dataPtr,(nameNum + 1)  * 
                                        sizeof(struct nameData));
            if(newAllocate == NULL){
              // FREE all allocated memory in filePathArr
              for(int f = 0; f < NUM_QUADRENNIUM; f++){
                free(filePathArr[f]);
              }

              // FREE all allocated memory of namedata in list of tableEntry 
              int sizeL = table -> size;
              struct tableEntry * startEntry = table -> entryPtr; 
              for(int q = 0; q < sizeL; q++){
                free(startEntry[q].dataPtr); 
              }

              perror(NULL);
              return -1;
            }
            cur -> dataPtr = newAllocate;
            struct nameData * newAdded = cur -> dataPtr + nameNum;

            // initialize the newly allocated memory to 0
            memset(newAdded,0,sizeof(struct nameData));

            // update the field of the newly allocated struct
            if(*gender == MALE_CHAR){
              // update mRanks field at index i
              newAdded -> mRanks[j] = (short)rankL;
            }
            else{
              newAdded -> fRanks[j] = (short)rankL;
            } 
            // update the name 
            strncpy(newAdded -> name,name,strlen(name)+1);


            // increment nameNum
            (cur -> numNames)++;

          }
        }
      }
      // after reading all lines in a file close the file
      fclose(fp);
    }
  // FREE all allocated memory in filePathArr
  for(int f = 0; f < NUM_QUADRENNIUM; f++){
    free(filePathArr[f]);
  }
  return 0;
}
