#include "projectile.h"
#include "enemy.h"
#include "explosion.h"
#include "game.h"

#define INIT_VELOCITY 0.7f
#define WIDTH 10
#define HEIGHT 10

// Called every frame to update gamestate
void player_projectile_update(Entity *entity, GameState *game_state) {
  Vec2 move = vec_mult_s(entity->velocity, game_state->delta_time);
  vec_add_inplace(&entity->position, move);

  // Check for enemy collision and kill if found
  for(int i = 0; i < game_state->entity_count; i++) {
    Entity *enemy_entity = game_state->entities[i];
    if (is_enemy(enemy_entity) && is_colliding(entity, enemy_entity)) {
      entity->alive = 0;
      enemy_entity->alive = 0;
      game_state->score++;
      explosion_spawn(game_state, enemy_entity->position);
    }
  }

  // Dispose of projectile if it flew offscreen without hitting anything
  if (entity->position.y < 0 && entity->alive) {
    entity->alive = 0;
  }
}

void player_projectile_spawn(GameState *game_state) {
    Entity *projectile = game_create_entity(game_state);

    projectile->position.x = game_state->player->position.x;
    projectile->position.y = game_state->player->position.y;
    projectile->w = WIDTH;
    projectile->h = HEIGHT;
    projectile->velocity = (Vec2){0, INIT_VELOCITY * -1};
    projectile->type = PLAYER_PROJECTILE_ENTITY_TYPE;
    projectile->sprite = get_sprite(SPRITE_PLAYER_PROJECTILE);
    projectile->lifespan_ms = -1;
}
