#include <stdio.h>
#include "error.h"

static const char *errorMessages[] =
{
 "",
 "Unknown error encountered.",
 /* script errors */
 "Invalid opcode encountered during script execution", /*ERROR_INVALID_OPCODE*/
 "Instruction pointer out of range"
};

void logError(char *context, error_t code, char *additionalInfo) {
    printf("[ERROR:%s] %s. %s\n", context, errorMessages[code],
           (additionalInfo) ? additionalInfo : "");
}
