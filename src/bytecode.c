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

  For interpreter implementation reasons, all opcodes increment from 0 because they
  have an O(1) lookup time.

  INSTRUCTION SET
  ===============
  00 - Depending on context can either end a string or can be ignored as NOOP.
  01 - Begin data section
  02 - end data section
  03 - begin code section.
  -- CODE SECTION SPECIFIC --
  00 - unconditional jump (takes 4 bytes as an operand -- code spot to jump to)
  01 - End script (return to engine execution)
  02 - jump if comparison flag is true (takes 4 bytes as an operand)
  03 - display text at GAT offset (takes 5 bytes as operand 2:offset;2:length;1:flags)
  04 - display image at GAT offset (takes 5 bytes as operand 2:offset;2:length;1:flags)
  05 - play sound at GAT offset (takes 5 bytes as operand 2:offset;2:length;1:flags)
  06 - get user input on option (takes n bytes as input with 2 for each GAT offset)
       max text length is defined as MAX_OPT_LENGTH in bytecode.h
  07 - after 2 bytes in a user option indicates a new optionn
  08 - compare an option at DOT offset to a value (4 bytes -- offset;value)
  09 - Load assets from x until y into AOT (8 bytes -- x;y)
  -- DATA SECTION SPECIFIC --
  00 - begin asset set
  01 - end asset set
  02 - load string into current asset set (continues reading until null-byte)
  03 - load png file based on filename (continues reading until null-byte)
  04 - load ogg file based on filename (continues reading until null-byte)
  

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
#include <stdio.h>
#include <string.h>

#include "bytecode.h"
#include "error.h"
#include "log.h"

#define FREEGAT(_entry)                     \
    for (int i=0; _entry[i] != NULL; i++) { \
        free(_entry[i]);                    \
    }

#define OP32(env)                  \
    (getNextOpcode(env) << 24) |   \
    (getNextOpcode(env) << 16) |   \
    (getNextOpcode(env) << 8)  |   \
    (getNextOpcode(env))

#define OP16(env)                 \
    (getNextOpcode(env) << 8) |   \
    (getNextOpcode(env))


static inline uint8_t getNextOpcode(script_t *env) {
    if (env->ip < env->scriptLength)
        return env->code[++env->ip];
    return OP_NOOP;
}

/*
  Opcode definitions
*/

/* opcode for no operation. */
inline static script_t *noop(script_t *env) {
    debug("noop");
    return env;
}

inline static script_t *jump(script_t *env) {
    uint32_t address;

    address = OP32(env);
    
    /* move instruction pointer to new address */
    env->ip = address;
    debug("Jump to %d", address);
    return env;
}

inline static script_t *jumpOnEqual(script_t *env) {
    if (env->cmpFlag) {
        return jump(env);
    }
    return env;
}

inline static script_t *displayText(script_t *env) {
    uint16_t gatOffset;
    uint16_t len;
    uint8_t flags;

    gatOffset = OP16(env);
    len       = OP16(env);
    flags     = getNextOpcode(env);

    debug("Display text @%d with a length of %d with flags %d",
          gatOffset, len, flags);
    
    return env;
}

inline static script_t *displayImg(script_t *env) {
    uint16_t gatOffset;
    uint16_t len;
    uint8_t flags;

    gatOffset = OP16(env);
    len       = OP16(env);
    flags     = getNextOpcode(env);


    debug("Display image @%d with a length of %d with flags %d",
          gatOffset, len, flags);
    
    return env;
}

inline static script_t *playSound(script_t *env) {
    uint16_t gatOffset;
    uint16_t len;
    uint8_t flags;

    gatOffset = OP16(env);
    len       = OP16(env);
    flags     = getNextOpcode(env);


    debug("Play sound @%d with a length of %d with flags %d",
          gatOffset, len, flags);
    
    return env;
}

inline static script_t *getUserDecision(script_t *env) {
    /* buffer for options */
    char **options = malloc(sizeof(char) * MAX_OPT_LENGTH * DEFAULT_OPTIONS);
    uint8_t stringIndex = 0;
    uint8_t charIndex = 0;
    for (uint8_t op = getNextOpcode(env); op != 0x00; op = getNextOpcode(env), charIndex++) {
        options[stringIndex][charIndex]
    }

    free(options);
    
    return env;
}

inline static script_t *loadAssets(script_t *env) {
    uint32_t startAddress;
    uint32_t endAddress;

    startAddress = OP32(env);
    endAddress   = OP32(env);

    debug("Load assets into AOT from 0x%x-0x%x", startAddress, endAddress);

    /* TODO parse loaded memory */
    
    return env;
}

/* jump table for all runtime opcodes */
opcode_t executionDispatchTable[] =
    {
     &jump,
     &noop,
     &jumpOnEqual,
     &displayText,
     &displayImg,
     &playSound,
     &getUserDecision,
     &noop, // separator
     &loadAssets,
    };

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

    env->cmpFlag = 0;
    
    return env;
}

script_t *loadScript(script_t *env, uint8_t *file, size_t fileSize) {
    env->code = malloc(sizeof(uint8_t) * fileSize);
    memcpy(env->code, file, fileSize);
    env->scriptLength = fileSize;
    return env;
}

void executeScript(script_t *env) {
    error_t err = ERROR_NONE;
    /* execute instructions (opcodes modify IP) */
    for (env->ip = 0; env->code[env->ip] != OP_EXIT; env->ip++) {
        if (env->ip > env->scriptLength) {
            err = ERROR_IP_OUT_OF_RANGE;
            debug("%d", env->ip);
            break;
        }
        if (env->code[env->ip] < MAX_OPCODE) {
            env = executionDispatchTable[env->code[env->ip]](env);
        } else { /* opcode is out of range */
            err = ERROR_INVALID_OPCODE;
            break;
        }
    }
    /* clean exit with exit opcode */
    if (err == ERROR_NONE) {
        
    } else { /* exception case */
        logError("SCRIPT", err, NULL);
        exit(1);
    }
    
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
