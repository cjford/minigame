#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game.h"

#define PLAYER_PROJECTILE_ENTITY_TYPE "player_projectile"

void player_projectile_update(Entity *entity, GameState *game_state);
void player_projectile_spawn(GameState *game_state);

#endif // PROJECTILE_H
