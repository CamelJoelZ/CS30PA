/*
 * Filename: generateGraph.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: generate the graph corresponding to the data 
 * Date: May/21/2018
 * Sources of Help: Manpage
 */ 


#include "pa3.h"
#include "pa3Strings.h"

#define NL '\n'
#define TWO 2


/*
 * Function Name: generateGraph() 
 *
 * Function Prototype: void generateGraph( nameData_t * name, 
 *               char arr[GRAPH_ROWS][GRAPH_COLS] ) 
 * Description : This function will populate arr, a 
 *               2d-array that contains the graph for 
 *               the name data within name. 
 *
 * Parameters:  nameData_t * name, char arr[GRAPH_ROWS][GRAPH_COLS]  
 * Side Effects: None
 * Error Condition: None
 * Return Value: None 
 *
 */
void generateGraph( nameData_t * name, char arr[GRAPH_ROWS][GRAPH_COLS]){
  short * mRanks = name -> mRanks;
  short * fRanks = name -> fRanks;

  int rankIndex = 0;
  // iterate thorugh columns
  for(int i = 0; i < GRAPH_COLS; i++){

    int mRow = mRanks[rankIndex] / RANKS_PER_ROW;
    // for name with no rank
    if(mRanks[rankIndex] == 0) mRow = GRAPH_ROWS - 1;

    int fRow = fRanks[rankIndex] / RANKS_PER_ROW;
    // for name with no rank
    if(fRanks[rankIndex] == 0) fRow = GRAPH_ROWS - 1;

    // iterate through rows 
    for(int j = 0; j < GRAPH_ROWS; j++){
      // for new line char
      if(i == GRAPH_COLS - TWO) arr[j][i] = NEWLINE_CHAR;
      // for null terminator
      else if(i == GRAPH_COLS - 1) arr[j][i] = '\0';
      // for space
      else arr[j][i] = SPACE_CHAR;
    }
    
    // ranks in every odd column for format matching
    if((i % TWO != 0) && (i != GRAPH_COLS - TWO)){
      // overwrite grid which should have m f or b
      if(mRow == fRow) arr[mRow][i] = INTERSECTION_MARKER;
      else{
        arr[mRow][i] = MALE_MARKER;
        arr[fRow][i] = FEMALE_MARKER;
      }
      // increment the rankIndex every two i++
      if(rankIndex < NUM_QUADRENNIUM - 1){
        rankIndex++;
      }
    }
  }
}
