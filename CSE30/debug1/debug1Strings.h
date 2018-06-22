/*
 * Filename: debug1Strings.h
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Defines strings used throughout the debug1 code.
 * Date: 4/20/18
 * Sources of help: None.
 */
#ifndef DEBUG1_STRINGS_H
#define DEBUG1_STIRNGS_H

/* XXX: DO NOT EDIT ANYTHING IN THIS FILE! */

#define STR_USAGE "\nUsage: %s [--help] {d,e} {0,1} [key]\n" \
    "\t--help\t(optional) Displays the usage string.\n" \
    "\t{d,e}\t(required) Decipher(d) or encipher(e).\n" \
    "\t{0,1}\t(required) Cipher_Index (type):\n" \
    "\t\t\t\t0 - Vigenere\n" \
    "\t\t\t\t1 - XOR\n" \
    "\tkey\t(optional) String used to encrypt data.\n" \
    "\n"

#define STR_CIPHER_INDEX "Cipher_Index"
#define STR_WRITTEN_BYTES "\n\tWrote %d bytes to stdout.\n\n"

/* Error Strings. */
#define STR_ERR_CONVERTING "\n\t converting %s(%s) in base(%d) to long"
#define STR_INVALID_INT "\n\t%s: Invalid int '%s'\n"
#define STR_CIPHER_IDX_INVALID "Error: Didn't specify a valid cipher index.\n"
#define STR_INVALID_ENC_DEC_FLAG "\n\tNot a valid encrypt or decrypt flag.\n"

#endif // DEBUG1_STRINGS_H
