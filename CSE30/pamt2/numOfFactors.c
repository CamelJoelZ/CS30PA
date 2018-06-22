/* Filename: numOfFactors.c
 * Author: Zhuoer Wen 
 * Userid: cs30xgz
 * Description: determine hwo many factors evenly divide into it  
 * Date: May/31/2018
 */
#define TWO 2
/*
 * Function name: numOfFactors()
 *
 * Function prototype: long long numOfFactors( long long n,
 *                                             long long lo,
 *                                             long long hi );
 *
 * Params: n is the value we are checking to determine how many factors
 *           evenly divide into it.
 *         lo is the low (inclusive) range of possible factors to check.
 *         hi is the high (exclusive) range of possible factors to check.
 *
 * Algorithm:
 *   if n <= 1 return 0 (we won't deal with values less than 2). By definition,
 *       prime numbers are greater than 1.
 *
 *   if lo <= 1, set lo to 2 (we won't deal with factors less than 2).
 *
 *   set the return value to 1 since n is evenly divisible by 1.
 *
 *   loop thru the range [lo, hi) as factors incrementing by 1 each time
 *       thru the loop checking if n is evenly divisible by each factor.
 *       If it is evenly divisible, increment the number of
 *       evenly-divisible factors for this range.
 *   
 *   There may be other more efficient algorithms, but this will do.
 *   We want to see how multi-threading in C with OpenMP
 *   might improve overall performance for this particular algorithm.
 *
 * Side Effects: None.
 *
 * Error Conditions: None.
 *
 * Return value: long long int indicating the number of evenly-divisible
 *               factors in n.
 */

long long numOfFactors( long long n,
                        long long lo,
                        long long hi ) {
  // return value 
  long long int ret = 1;

  // if n <= 1
  if(n <= 1) return 0;

  // if lo <= 1
  if(lo <= 1) lo = TWO;

  // iteratr through the lo - hi
  for(long long i = lo; i < hi; i++){
    long long divisible = n % i;
    
    // evenly divisible
    if(divisible == 0) ret++;
  }

  return ret;
}

