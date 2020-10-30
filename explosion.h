#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "game.h"

#define EXPLOSION_ENTITY_TYPE "explosion"

void explosion_update(Entity *entity, GameState *game_state);
void explosion_spawn(GameState *game_state, Vec2 position);

#endif // EXPLOSION_H
