#ifndef __KANSAI_KBC
#define __KANSAI_KBC

#include <stdint.h>

#define DEFAULT_DOT_ENTRIES 100

/*
  Global Asset Table (GAT) datastructure
*/

typedef struct {
    /* array of literal representation of strings as used by the engine */
    char **strings;
    /* array of literal binary representations of OGG files */
    uint8_t **soundfiles;
    /* array of literal binary representations of PNG files */
    uint8_t **images;
} gat_t;

/*
  Decision Offset Table (DOT) datastructure
*/
typedef struct {
    /* array of decisions remembered by the engine; 0-based */
    uint16_t *decisions;
} dot_t;

/*
  Script Environment.
  One script environment is shared between all scripts so that decisions can be
  remembered between scenes. After each script, the GAT, data, and code sections
  are all free'd by the interpreter.
*/
typedef struct {
    /* environment tables */
    gat_t gat;
    dot_t dot;
    /* data section */
    uint8_t *data;
    /* code section */
    uint8_t *code;
    /* execution context */
    uint32_t ip; /* instruction pointer */
} script_t;

/* TODO: Load save data into the DOT */
script_t *initEnv();
script_t *loadScript(script_t *env, uint8_t *file);
void executeScript(script_t *env);

#endif
