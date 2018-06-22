/*
 * Filename: interpretTime.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: parse time 
 * Date: April/29/2018
 * Sources of Help: Manpage
 */ 

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include "pa2.h"
#include "test.h"
#include "pa2Strings.h"

/*
 * parse time and save the valid one to struct
 *
 * unsigned long interpretTime(struct tInfo * tInfoPtr, const char * time)
 */


unsigned long interpretTime( struct tInfo * tInfoPtr, const char * time ) {
  // return var
  unsigned long bitmap = 0;

  // create a copy of const char time
  char buffer[BUFSIZ] = {'\0'};
  strncpy(buffer, time, BUFSIZ);
  // make sure null terminate
  buffer[BUFSIZ-1] = '\0';
  
  /* 
   * WRONG FORMAT ERROR CHECK
   */
  int count = 0;
  for(int i = 0; i < BUFSIZ; i++){
    if(buffer[i] == CHAR_SEPARATOR) count++;
  }

  if(count != 2){
    bitmap |= ERR_TIME_FORMAT;
    return bitmap;
  }
  
  /*
   * PARSING TIME
   */
  char * ret;
  char * end;
  // parsing hour
  errno = 0;
  long hour;
  hour = strtol( buffer, &end, BASE);

  // change hour to 12 if it is 0
  if(hour == 0) hour = DEFAULT_HR;

  // check if hour ends with :
  if(*end != CHAR_SEPARATOR || errno != 0){
    bitmap |= ERR_TIME_NUM;
  }

  // check if hour in range
  if(errno == 0){
    if(isInRange(hour,MIN_HR,MAX_HR+1) != 1){
      bitmap |= ERR_TIME_RANGE;
    }
  }

  // move the ptr forward to get min:sec
  ret = strchr( buffer, CHAR_SEPARATOR);
  ret = ret + 1;

  // parsing minute 
  errno = 0;
  long minute;
  minute = strtol( ret, &end, BASE);
  if(*end != CHAR_SEPARATOR || errno != 0){
    bitmap |= ERR_TIME_NUM;
  }

  // check if minute in range
  if(errno == 0){
    if(isInRange(minute,MIN_MIN,MAX_MIN+1) != 1){
      bitmap |= ERR_TIME_RANGE;
    }
  }
  
  // extract the sec in buffer
  ret = strchr( ret, CHAR_SEPARATOR);
  ret = ret + 1;
  
  // parsing second
  errno = 0;
  long second;
  second = strtol( ret, &end, BASE);

  if(errno != 0){
    bitmap |= ERR_TIME_NUM;
  }

  // check if second in range
  if(errno == 0){
    if(isInRange(second,MIN_SEC,MAX_SEC+1) != 1){
      bitmap |= ERR_TIME_RANGE;
    }
  }

  // parse am pm 
  if(*end != 'a' && *end != 'A' && *end != 'p' && *end != 'P'){
    bitmap |= ERR_TIME_FORMAT; 
  }

  // check if appending string after a or p
  end ++;
  if(*end != '\0'){
    bitmap |= ERR_TIME_FORMAT; 
  }

  // set the struct if no error occurs
  if(bitmap == 0){
    // put the ptr back to am pm part
    end --;
    // special handle for hour
    if(hour == 0) hour = 12; 
    // populate the struct
    (*tInfoPtr).tm_sec = second;
    (*tInfoPtr).tm_min = minute;
    (*tInfoPtr).tm_hour = hour;
    (*tInfoPtr).am_pm = toupper(*end);
  }
  // return 
  return bitmap;
}
