/*
 * Filename: printStats.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: prints out rank info for give nameData struct
 * Date: May/21/2018
 * Sources of Help: Manpage
 */ 


#include "pa3.h"
#include "pa3Strings.h"

#define NL '\n'


/*
 * Function Name: printStats() 
 *
 * Function Prototype:void printStats( nameData_t * namePtr );
 *               
 * Description :This function prints out the ranking information 
 *              for the given nameData struct.
 *
 * Parameters: nameData_t * namePtr
 * Side Effects: None
 * Error Condition:None
 * Return Value:None 
 *              
 */
void printStats( nameData_t * namePtr ){

  // First print the header for the stats
  printf(STATS_HEADER);

  //print out info for each quadrennium
  short * fRank = namePtr -> fRanks; 
  short * mRank = namePtr -> mRanks; 
  int mHighest = MAX_RANK;
  int fHighest = MAX_RANK;
  int mYear = 0;
  int fYear = 0;
  char * name = namePtr -> name;
  int multipleYearM = 0;
  int multipleYearF = 0;
  

  // iterate through the arr
  for(int i = 0; i < NUM_RANKS; i++){
    
    // no rank for both male and female
    if(fRank[i] < MIN_RANK && mRank[i] < MIN_RANK ){
      printf(STATS_FMT_NEITHER,MIN_QUADRENNIUM + YEARS_IN_QUADRENNIUM * i,
      FEMALE_CHAR,NO_RANK_CHAR,MALE_CHAR,NO_RANK_CHAR);
    }

    // no rank for female
    else if(fRank[i] < MIN_RANK){ 
      printf(STATS_FMT_NO_FEMALE,MIN_QUADRENNIUM + YEARS_IN_QUADRENNIUM * i,
      FEMALE_CHAR,NO_RANK_CHAR,MALE_CHAR,mRank[i]);

      // keep track of the highest rank
      if(mRank[i] <= mHighest){
        mHighest = mRank[i];
        mYear = MIN_QUADRENNIUM + YEARS_IN_QUADRENNIUM * i;
      }
    }

    // no rank for male
    else if(mRank[i] < MIN_RANK){ 
      printf(STATS_FMT_NO_MALE,MIN_QUADRENNIUM + YEARS_IN_QUADRENNIUM * i,
      FEMALE_CHAR,fRank[i],MALE_CHAR,NO_RANK_CHAR);

      // keep track of the highest rank
      if(fRank[i] <= fHighest){
        fHighest = fRank[i];
        fYear = MIN_QUADRENNIUM + YEARS_IN_QUADRENNIUM * i;
      }
    }

    // has rank for both male and female
    else{
      printf(STATS_FMT_BOTH,MIN_QUADRENNIUM + YEARS_IN_QUADRENNIUM * i,
      FEMALE_CHAR,fRank[i],MALE_CHAR,mRank[i]);
      // keep track of the highest rank
      if(mRank[i] <= mHighest){
        mHighest = mRank[i];
        mYear = MIN_QUADRENNIUM + YEARS_IN_QUADRENNIUM * i;
      }
      // keep track of the highest rank
      if(fRank[i] <= fHighest){
        fHighest = fRank[i];
        fYear = MIN_QUADRENNIUM + YEARS_IN_QUADRENNIUM * i;
      }

    }
  }
  
  // iterate again to see if there are multiple years for highest rank
  for(int j = 0; j < NUM_RANKS; j++){
    if(fRank[j] == fHighest) multipleYearF++;
    if(mRank[j] == mHighest) multipleYearM++;

  }

  //  print out message indicating whether the name has highest rank
  // for female
  if(fHighest != MAX_RANK){
    // only one year the highest
    if(multipleYearF == 1)
    printf(F_HIGH_RANK,name,"",fYear,fHighest);
    if(multipleYearF > 1)
    printf(F_HIGH_RANK,name,STR_MOST_RECENT,fYear,fHighest);
  }
  else{
    printf(F_NO_HIGH_RANK,name);
  }
  // for male
  if(mHighest != MAX_RANK){
    // only one year the highest
    if(multipleYearM == 1)
    printf(M_HIGH_RANK,name,"",mYear,mHighest);
    if(multipleYearM > 1)
    printf(M_HIGH_RANK,name,STR_MOST_RECENT,mYear,mHighest);
  }
  else{
    printf(M_NO_HIGH_RANK,name);
  }
}
