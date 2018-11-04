#ifndef PARSER_H

struct sprite_t {
    char *filepath;
    char *name;
};

struct character_t {
    struct sprite_t **sprites;
    unsigned int spriteCount;
};

struct scene_t {
    char *name;
    char *instructions; /* raw instructions */
    unsigned int instructionCount;
};

void interpretScript(struct env_t *env, char *script);

#endif
#define PARSER_H
