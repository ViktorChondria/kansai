#ifndef _KANSAI_ERROR_
#define _KANSAI_ERROR_

/*
  Half-decent error system based on semi-global scoped status codes.
  I'm not a super big fan of the `if err != nil' pattern of go, but
  it's an acceptable solution.
*/
typedef enum {
              ERROR_NONE,
              ERROR_UNKNOWN,
              ERROR_INVALID_OPCODE
} error_t;
/*
  context is an all caps string to make logs more logical
    ie if its a script execution error, context = SCRIPT
  additionalInfo is optional information to be logged outside of the message.
*/
void logError(char *context, error_t code, char *additionalInfo);
#endif
