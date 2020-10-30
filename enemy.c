#include "enemy.h"

#define SPAWN_INTERVAL_MS 500
#define INIT_VELOCITY 0.05f
#define WIDTH 36
#define HEIGHT 36

void enemy_update(Entity *entity, GameState *game_state) {
  Vec2 move = vec_mult_s(entity->velocity, game_state->delta_time);
  vec_add_inplace(&entity->position, move);
}

void enemy_spawn(GameState *game_state, Vec2 position) {
    Entity *enemy_entity = game_create_entity(game_state);

    enemy_entity->position = position;
    enemy_entity->velocity = (Vec2){0, INIT_VELOCITY};
    enemy_entity->w = WIDTH;
    enemy_entity->h = HEIGHT;
    enemy_entity->type = ENEMY_ENTITY_TYPE;
    enemy_entity->sprite = get_sprite(SPRITE_ENEMY_SMALL);
    enemy_entity->lifespan_ms = -1;
}

void enemy_handle_spawn(GameState *game_state) {
  if (game_state->ms_elapsed % SPAWN_INTERVAL_MS == 0) {
    Vec2 position = { (rand() % game_state->world_w - 50), 0 };
    enemy_spawn(game_state, position);
  }
}
