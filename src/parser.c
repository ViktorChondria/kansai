#include <stdlib.h>
#include <string.h>

#include "parser.h"

/*
  parse a script into the subdivided structures
*/
struct script_t *parseScript(char *script) {
    
}


/*
  This tokenizer is pretty expensive, but overall
  fairly safe and intuitive (I tried to cut down on)
  weird hacks because strtok is already ambiguously
  cross platform.
  returns NULL on error.
*/
static char **tokenize (char *str, char *delim) {
    /*
      count the tokens
      always want count to be n+1 because might not end in delim.
     */
    unsigned int count = 1; 
    for (int i=0; str[i] != NULL; i++) if (str[i] == *delim) count++;
    if (count == 0)
        return NULL;

    // copy the string to a mutable region.
    char *buf = malloc(sizeof(char) * strlen(str));
    strcpy(buf, str);
    str = buf;
    
    char **tokens = malloc(sizeof(char) * count);
    unsigned int i = 0;
    char *token = strtok(str, delim);
    while (token != NULL) {
        /* each token needs to be free'd individually */
        tokens[i] = malloc(sizeof(char) * strlen(token));
        /* using strncpy here would be redundant */
        strcpy(tokens[i], token);
        token = strtok(NULL, delim);
        i++;
    }
    
    return tokens;
}
