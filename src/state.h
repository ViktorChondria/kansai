#include <stdint.h>
#include "env.h"
#include "entity.h"

#ifndef _KANSAI_STATE_
#define _KANSAI_STATE_

typedef struct state_ state_t;

/*
  Given that Kansai is implemented as a state machine, we
  need a series of states to transition between.
  
  id:       currently used for nothing, but is an identifier for the current state.
  update:   abstract state updating method; custom for each state, but is where
            the state-specific logic is implemented.
  entities: the entities in each scene. Each entity has a `update' method that gets 
            called given the entity is onscreen.
*/
struct state_ {
    uint32_t id;
    uint32_t (*update)(env_t *env, state_t *this);
    entity_t **entities;
};

#endif
