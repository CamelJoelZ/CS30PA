/*
 * Filename: parallel_sqrtSumMinMax.c
 * Author: Zhuoer Wen 
 * Userid: May/18/2018
 * Description: Sums the square root of each element in array a[] and finds the
 *              minimum and maximum value in the array.
 *              (Parallel version)
 * Date: May/18/2018
 * Sources of Help: Man Page
 */

#include <math.h> // Needed for sqrt() function prototype

/*
 * See pamt1.h for definition of struct result1
 */

#include "pamt1.h"

/*
 * Function name: parallel_sqrtSumMinMax()
 *
 * Function prototype:
 *      struct result1 parallel_sqrtSumMinMax( unsigned char a[],
 *                                             size_t arraySize );
 *
 * Description: Gets the square root of each element (sqrt(a[i])) and adds
 *              this to an accumulating sum.
 *              Find the min and max values in the array.
 *
 * Parameters: a[]        array to perform square root, min, and max 
 *             arraySize  size of the array
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: A struct result1 populated with the sum of the square roots
 *               of each element, overall min and max values.
 *
 *               Because floating point addition is not associative,
 *               values of sum may have slightly different values between the
 *               sequential and parallel versions due to rounding error.
 *
 *               However, the values should be the same in each respective
 *               version when run multiple times with the same size array.
 *               (The sum in the sequential version should be the same when
 *               run multiple times with the same size array. The sum in the
 *               parallel version should be the same when run multiple
 *               times with the same size array.)
 *
 *               The min and max values should exactly match those of the
 *               sequential version.
 */

struct result1 parallel_sqrtSumMinMax( unsigned char a[], size_t size ) {
  struct result1 result1;

  // Create three local variables
  double sum = sqrt(a[0]);
  unsigned int max = a[0];
  unsigned int min = a[0];

#pragma omp parallel for reduction(+:sum) \
                         reduction(min:min) \
                         reduction(max:max)
  // Iterate over all of the remaining elements in the array 
  // (starting with the second element).  
  for(int i = 1; i < size; i++){
    // update sum
    sum += (sqrt(a[i]));
    // check min and max
    if(a[i] < min) min = a[i];
    if(a[i] > max) max = a[i];
  }

  result1.sum = sum;
  result1.max = max;
  result1.min = min;

  return result1; // return the struct by value
}

