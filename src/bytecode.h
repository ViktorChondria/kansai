#ifndef _KANSAI_KBC_
#define _KANSAI_KBC_

#include <stdint.h>

#define MAX_OPCODE 10
#define DEFAULT_DOT_ENTRIES 100
#define DEFAULT_OPTIONS 4 /* I find it very unlikely we'll see more than 4. */
#define MAX_OPT_LENGTH 1024

/*
  Global Asset Table (GAT) datastructure
*/

/* opcodes to remove the otherwise abundant magic numbers */
typedef enum {
              OP_NOOP,
              OP_EXIT,
              OP_JMP,
              OP_JE,
              OP_DISPLAYTEXT,
              OP_DISPLAYIMAGE,
              OP_PLAYSOUND,
              OP_USEROPTION,
              OP_OPTIONSEPERATOR, // NOT OPCODE -> SEPARATES OPTIONS.
              OP_CMP,
              OP_LOADAOT
} opcode;

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
    /* was the last comparison a success */
    uint8_t cmpFlag;
    /* length of current script */
    uint64_t scriptLength;
} script_t;


/* TODO: Load save data into the DOT */
script_t *initEnv();
script_t *loadScript(script_t *env, uint8_t *file, size_t fileSize);
void executeScript(script_t *env);

/* opcode function pointer for dispatch table */
typedef script_t *(*opcode_t)(script_t *);

#endif
