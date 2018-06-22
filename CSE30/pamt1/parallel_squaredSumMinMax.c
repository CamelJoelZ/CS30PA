/*
 * Filename: parallel_squaredSumMinMax.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Sums the square of each element in array a[] and finds the
 *              minimum and maximum value in the array.
 *              (Parallel version)
 * Date: May.18.2018
 * Sources of Help: Man Page 
 */

/*
 * See pamt1.h for definition of struct result
 */

#include "pamt1.h"

/*
 * Function name: parallel_squaredSumMinMax()
 *
 * Function prototype:
 *      struct result parallel_squaredSumMinMax( unsigned char a[],
 *                                               size_t arraySize );
 *
 * Description: squares each element (a[i] * a[i]) and adds this to an
 *              accumulating sum. Find the min and max values in the array.
 *
 * Parameters: a[]        array to perform sum of squares, min, and max 
 *             arraySize  size of the array
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: A struct result populated with the sum of the squares
 *               of each element, overall min and max values.
 *
 *               These values should exactly match those of the
 *               sequential version.
 */

struct result parallel_squaredSumMinMax( unsigned char a[], size_t size ) {
  struct result result;

  // Create three local variables
  unsigned long long int sum = a[0] * a[0];
  unsigned int max = a[0];
  unsigned int min = a[0];

#pragma omp parallel for reduction(+:sum) \
                         reduction(min:min) \
                         reduction(max:max)
  // Iterate over all of the remaining elements in the array 
  // (starting with the second element).  
  for(int i = 1; i < size; i++){
    // update sum
    sum += (a[i] * a[i]);
    // check min and max
    if(a[i] < min) min = a[i];
    if(a[i] > max) max = a[i];
  }

  result.sum = sum;
  result.max = max;
  result.min = min;

  return result; // return the struct by value
}

