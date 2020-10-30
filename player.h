#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

#define PLAYER_ENTITY_TYPE "player"

void player_update(Entity *entity, GameState *game_state);
void player_handle_spawn(GameState *game_state);

#endif // PLAYER_H
