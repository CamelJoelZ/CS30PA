/*
 * Filename: debug2Strings.h
 * Author: Bugs Bunny
 * UserId: cs30x420
 * Description: Important strings for the program to print.
 * Date: 04/20/18
 * Sources of help: None.
 */

/* XXX: DO NOT MODIFY THIS FILE */

#ifndef DEBUG2_STRINGS_H
#define DEBUG2_STRINGS_H

#define STR_USAGE "\nUsage: %s inputFile\n"\

#define HELP_STR "\nCommands are:\n" \
        "\tfreqs [word1, word2, ...]   Print the frequency of a word or the\n" \
        "\t                            sum of frequencies of many words.\n"\
        "\tdisplay                     Display the entire frequencies table.\n"\
        "\thelp                        Display this message.\n\n"
#define STR_PROMPT "Please enter a command: "
#define STR_DISPLAY_FMT "%s: %u\n"
#define STR_SUM_FREQS "\nSum of frequencies of the words: %u\n\n"

#define SEP " (),:.;!?{}/-*<>@&|\"\n\t"
#define COMMANDS {"freqs", "display", "help", NULL}
#define ERR_CMD_NOT_FOUND "\n%s is not a command.\n\n"
#define ERR_WORD_NOT_ENTERED "\nNo word entered.\n\n"
#define ERR_MEM_LIMIT_EXCEEDED "\nMemory limit exceeded.\n\n"

#endif /* DEBUG2_STRINGS_H */

