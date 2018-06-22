/*
 * Filename: parseCmd.c
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Defines a function for determining which command was given in
 *              the interactive prompt.
 * Date: 04/20/18
 * Sources of help: None.
 */

#include <string.h>
#include "debug2.h"

/*
 * Function Name: parseCmd()
 * Function Prototype: int parseCmd( const char * const cmdString,
 *                                   const char * const commands[] );
 * Description: Finds the index of a command string within an array of accepted
 *              command strings.
 * Parameters: cmdString - the command to search for
 *             commands - the array of accepted commands to search through
 * Side Effects: None.
 * Error Conditions: Either input argument is NULL. Returns -1 in this case.
 * Return Value: Index of the command if found, -1 if not found or
 *               either pointer argument is NULL.
 */
int parseCmd( const char * const cmdString, const char * const commands[] ) {

  // Error if either pointer is NULL.
  if ( commands ==  NULL || cmdString == NULL ) {
    return -1;
  }

  // Loop across array, comparing each command string.
  for ( int i = 0; commands[i] != NULL; ++i ) {
    if ( strncmp( commands[i], cmdString, strlen(commands[i]) + 1 ) == 0 ) {
      return i; // Found, return index.
    }
  }

  return -1; // Not found.
}
