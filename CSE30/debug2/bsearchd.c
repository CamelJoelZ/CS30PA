/*
 * Filename: bsearchd.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Binary search wrapper which also lets the user specify a
 *              default return value.
 * Date: 04/14/18
 * Sources of help: None.
 */

#include <stdlib.h> // bsearch()

/* XXX: DO NOT MODIFY THIS FILE */

/*
 * Function Name: bsearchd()
 * Function Prototype:
 *    void * bsearchd( const void *key,
 *                     const void *base,
 *                     size_t nmemb,
 *                     size_t size,
 *                     void *def,
 *                     int (*compar)( const void *, const void * ) );
 * Description: Does a binary search on an array, but returns a default
 *              value instead of NULL if the given key doesn't exist in
 *              the array.
 * Parameters: key - the value to search for in the array
 *             base - the sorted array to search through
 *             nmemb - the number of members in the array
 *             size - the size of each member in the array
 *             def - the default value to return
 *             compar - the comparison function to use when searching
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: A pointer to the value within the array, or to the
 *               default value.
 */
void * bsearchd( const void * key,
                 const void * base,
                 size_t nmemb,
                 size_t size,
                 void * def,
                 int (*compar)( const void *, const void * ) ) {

  // Delegate to standard library bsearch fn.
  void * res = bsearch( key, base, nmemb, size, compar );

  // Check for NULL and return default value if necessary.
  if ( res == NULL ) {
    return def;
  } else {
    return res;
  }
}
