#ifndef ENEMY_H
#define ENEMY_H

#include "game.h"

#define ENEMY_ENTITY_TYPE "enemy"

void enemy_update(Entity *entity, GameState *game_state);
void enemy_handle_spawn(GameState *game_state);

#endif // ENEMY_H
