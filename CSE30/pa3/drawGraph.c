/*
 * Filename: drawGraph.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: draw the graph we create in generateGraph 
 * Date: May/21/2018
 * Sources of Help: Manpage
 */ 


#include "pa3.h"
#include "pa3Strings.h"

#define FIVE 5
#define ARROW '>'
#define STICK '|'
/*
 * Function Name: drawGraph
 *
 * Function Prototype: void drawGraph( char arr[GRAPH_ROWS][GRAPH_COLS] )
 * Description : Prints a graph that has been previously initialized
 *   by generateGraph() to stdout
 *
 * Parameters: char arr[GRAPH_ROWS][GRAPH_COLS] 
 * Side Effects: None
 * Error Condition: None
 * Return Value: None
 *
 */
void drawGraph( char arr[GRAPH_ROWS][GRAPH_COLS] ){
  
  // formatting
  printf("%c",NEWLINE_CHAR);

  // there are 5 more rows to print to match to format
  for(int i = 0; i < GRAPH_ROWS; i++){
    for(int j = 0; j < GRAPH_COLS; j++){
      // special case for the last column
      if(j == 0 && i == GRAPH_ROWS - 1){
        printf("%c",ARROW);
      }
      // print out the rank range
      if(j == 0){
        // special case for the last row with leading >
        if(i * RANKS_PER_ROW == MAX_RANK){
          printf("%*d %c",FIVE - 1, MAX_RANK,STICK);
        }
        // first row format
        else if( i == 0){
          printf("%*d %c",FIVE,1,STICK);
        }
        // general case
        else{
          printf("%*d %c",FIVE,i * RANKS_PER_ROW,STICK);
        }
      }
      // print out space and M and F 
      printf("%c",arr[i][j]);

    }
  }
  // formatting 
  printf(STR_X_AXIS_SPACER);
  for(int l = 0; l < GRAPH_COLS; l++) printf(STR_X_AXIS_MARKER);
  printf("%c",NEWLINE_CHAR);
  // year at the bottom
  printf(STR_X_AXIS_LABEL);

}
