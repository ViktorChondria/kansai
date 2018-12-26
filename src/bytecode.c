/*
  The Kansai engine uses a bytecode system to abstract away the creation of
  narrative sections (like those that would be seen in a visual novel) from
  engine code allowing for more standard game distribution.

  Kansai bytecode (KBC) is a non-fixed-width instruction set with the minimum
  instruction size being 0 and the maximum being undefined. For example, a text
  section may read in bytes until a stop byte is received.

  KBC files are defined in two sections: the code section and the data section.
  
    The code section is where all of the linear instructions are set out with
    jump paths being defined by the compiler using the higher-level language's
    labels assigned to internal addresses. This is where the result of the
    compiler goes basically

    The data section is a series of tables pointing to filenames. The compiler
    defines when a given table should be loaded into memory and the engine loads
    those assets into the Global Asset Table (GAT). When a given area of the game
    wants to use those assets, the compiler selects them just based on an offset.
    mneumonic pseudocode for this might look like
      LOAD SCENE01   ;; load the assets for scene 1 into the GAT
      DISP 04        ;; display the 5th entry in the GAT
      UNLOAD         ;; free the GAT's scene section.

  Conditional options (decisions) are stored as integers (which the user selected)
  at an offset remembered by the compiler based on labels put in by the programmer.
  At any time, the comparison instruction can go in and branch based on previous
  decisions. This is called the Decision Offset Table (DOT).


  INSTRUCTION SET
  ===============
  00 - Depending on context can either end a string or can be ignored as NOOP.
  01 - Begin data section
  02 - end data section
  03 - begin code section.
  04 - End script (return to engine execution)
  -- CODE SECTION SPECIFIC --
  07 - unconditional jump (takes 4 bytes as an operand -- code spot to jump to)
  08 - jump if comparison flag is true (takes 4 bytes as an operand)
  10 - display text at GAT offset (takes 3 bytes as operand 2:offset;1:flags)
  11 - display image at GAT offset (takes 3 bytes as operand 2:offset;1:flags)
  12 - play sound at GAT offset (takes 3 bytes as operand 2:offset;1:flags)
  1F - get user input on option (takes n bytes as input with 2 for each GAT offset)
  30 - after 2 bytes in a user option indicates a new optionn
  20 - compare an option at DOT offset to a value (4 bytes -- offset;value)
  21 - Load assets from x until y into AOT (4 bytes -- x;y)
  -- DATA SECTION SPECIFIC --
  0F - begin asset set
  1F - end asset set
  10 - load string into current asset set (continues reading until null-byte)
  11 - load png file based on filename (continues reading until null-byte)
  12 - load ogg file based on filename (continues reading until null-byte)
  

  An example bytecode script:
  01 11 6D 69 61 2e 70 6E 67 00 10 74 65 73 74 20 73 74 72 69 6E 67 00 10
  6F 70 74 69 6F 6E 31 00 10 6F 70 74 69 6F 6E 32 00 02 03 21 00 01 00 16
  10 00 01 00 11 00 00 00 1F 00 02 30 00 03 04 00 00 00 00 00 00 00 00 00

  equivalent pseudo-asm
  data:
    LOAD "mia.png"     ;; image to display
    LOAD "test string" ;; test string to display as dialogue
    LOAD "option1"     ;; option 1 for user selection
    LOAD "option2"     ;; option 2 for user selection
  code:
    LGAT 01,16         ;; load assets from offset 0x01 until offset 0x16 into the GAT
    DISP 01,00         ;; display the text at offset 0x01 with no flags.
    DiSP 02,00         ;; display the image at offset 0x00 with no flags
    OPT  03,04         ;; display a user option with the text at offset 03 and 04.
    EXIT               ;; exit script    
*/
#include <stdlib.h>
#include "bytecode.h"

#define FREEGAT(_entry) \
    for (int i=0; _entry[i] != NULL; i++) { \
        free(_entry[i]); \
    }
    

script_t *initEnv() {
    script_t *env = malloc(sizeof(script_t));
    
    /* init DOT */
    env->dot.decisions = malloc(sizeof(uint16_t) * DEFAULT_DOT_ENTRIES);
    
    /* init GAT */
    env->gat.strings = NULL;
    env->gat.soundfiles = NULL;
    env->gat.images = NULL;

    env->data = NULL;
    env->code = NULL;

    env->ip = 0;
    
    return env;
}

script_t *loadScript(script_t *env, uint8_t *file) {
    return env;
}

void executeScript(script_t *env) {
    /* cleanup */
    env->ip = 0; /* reset execution context */

    if (env->data) free(env->data);
    if (env->code) free(env->code);
    
    if (env->gat.strings) {
        FREEGAT(env->gat.strings);
    }
    
    if (env->gat.soundfiles) {
        FREEGAT(env->gat.soundfiles);
    }
    
    if (env->gat.images) {
        FREEGAT(env->gat.images);
    }
}
