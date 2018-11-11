#include <stdint.h>
#include "env.h"
#include "entity.h"

#ifndef _KANSAI_STATE_
#define _KANSAI_STATE_

/*
  Given that Kansai is implemented as a state machine, we
  need a series of states to transition between.
  
  id:       currently used for nothing, but is an identifier for the current state.
  update:   abstract state updating method; custom for each state, but is where
            the state-specific logic is implemented.
  entities: the entities in each scene. Each entity has a `update' method that gets 
            called given the entity is onscreen.
*/
struct state_t {
    uint32_t id;
    uint32_t (*update)(struct env_t *env, struct state_t *this);
    struct entity_t **entities;
};

#endif
