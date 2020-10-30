#include "explosion.h"

#define WIDTH 50
#define HEIGHT 50

void explosion_spawn(GameState *game_state, Vec2 position) {
    Entity *explosion = game_create_entity(game_state);

    explosion->position = position;
    explosion->velocity = (Vec2){0, 0};
    explosion->w = WIDTH;
    explosion->h = HEIGHT;
    explosion->type = EXPLOSION_ENTITY_TYPE;
    explosion->sprite = get_sprite(SPRITE_EXPLOSION);
    explosion->alive = 1;
    explosion->lifespan_ms = explosion->sprite->x_offset_ms_interval * explosion->sprite->x_offset_stage_count;
}

// Update until lifespan expired - i.e. play animation then dissapear
void explosion_update(Entity *entity, GameState *game_state) {
  if(entity->lifespan_ms <= 0) {
    entity->alive = 0;
  } else {
    entity->lifespan_ms -= game_state->delta_time;
  }
}
