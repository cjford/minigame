#include "player.h"
#include "explosion.h"
#include "projectile.h"

#define ACCELERATION 0.1f
#define DECELERATION 0.8f
#define MAX_SPEED 0.5f
#define RESPAWN_MS 2000
#define WIDTH 24
#define HEIGHT 50
#define WEAPON_COOLDOWN 250.0f
#define INIT_POSITION (Vec2){100, 100}
#define INIT_VELOCITY (Vec2){0, 0}

// Helper for limiting position to world bounds
int clamp(int i, int max_i, int padding) {
  if (i > max_i - padding) {
    return max_i - padding;
  } else if (i < 0) {
    return 0;
  } else {
    return i;
  }
}

// Shoot new projectile only if allowed by cooldown
void player_handle_shoot(GameState *game_state) {
  if (game_state->input->space_pressed && game_state->player->weapon_cooldown_current <= 0) {
    game_state->player->weapon_cooldown_current = game_state->player->weapon_cooldown;
    player_projectile_spawn(game_state);
  }
  game_state->player->weapon_cooldown_current -= game_state->delta_time;
}

// Called every frame to update gamestate
void player_update(Entity *entity, GameState *game_state) {
  player_handle_shoot(game_state);

  Vec2 move = {0, 0};
  if(game_state->input->left_pressed) {
    move.x = -1.0f;
  }
  if(game_state->input->right_pressed) {
    move.x = 1.0f;
  }
  if(game_state->input->up_pressed) {
    move.y = -1.0f;
  }
  if(game_state->input->down_pressed) {
    move.y = 1.0f;
  }

  // Normalize diagonal movement vector so it's not faster than orthogonal
  // Since x and y are magnitude 1, solve for C w/pythagoras:
  // 1^2 + 1^2 = diagonal_mag^2
  // diagonal_mag = sqrt(2)
  // Divide by magnitude to normalize: 1/sqrt(2) = 0.70710678
  if(move.x != 0.0f && move.y != 0.0f) {
    vec_mult_s_inplace(&entity->velocity, 0.70710678f);
  }

  if(move.x == 0.0f && move.y == 0.0f) {
    // If we're not inputing new moves, apply velocity slowdown
    vec_mult_s_inplace(&entity->velocity, DECELERATION);
  } else {
    // Accelerate as long as we're inputting moves
    Vec2 velocity_change = vec_mult_s(move, ACCELERATION);
    vec_add_inplace(&entity->velocity, velocity_change);

    // Ignore any velocity above MAX_SPEED
    vec_clamp_s_inplace(&entity->velocity, MAX_SPEED);
  }

  // Perform the actual position move with current velocity
  move = vec_mult_s(entity->velocity, game_state->delta_time);
  vec_add_inplace(&entity->position, move);

  // Keep the player in-bounds
  entity->position.x = clamp(entity->position.x, game_state->world_w, entity->w);
  entity->position.y = clamp(entity->position.y, game_state->world_h, entity->h);

  // Animate sprite tilt based on sideways velocity
  switch((int)entity->velocity.x) {
    case -50 ... -26:
      entity->sprite->x_offset = 0;
      break;
    case -25 ... -1:
      entity->sprite->x_offset = 1;
      break;
    case 0:
      entity->sprite->x_offset = 2;
      break;
    case 1 ... 25:
      entity->sprite->x_offset = 3;
      break;
    case 26 ... 50:
      entity->sprite->x_offset = 4;
      break;
  }

  // Check for body collisions with enemies, and die if found
  for(int i = 0; i < game_state->entity_count; i++) {
    Entity *enemy_entity = game_state->entities[i];
    if (is_enemy(enemy_entity) && is_colliding(entity, enemy_entity)) {
      entity->alive = 0;
      game_state->player = NULL;
      game_state->lives--;
      explosion_spawn(game_state, entity->position);
    }
  }
}

void player_spawn(GameState *game_state) {
    Entity *player_entity = game_create_entity(game_state);

    player_entity->w = WIDTH;
    player_entity->h = HEIGHT;
    player_entity->position = INIT_POSITION;
    player_entity->velocity = INIT_VELOCITY;
    player_entity->type = PLAYER_ENTITY_TYPE;
    player_entity->sprite = get_sprite(SPRITE_PLAYER_SHIP);
    player_entity->weapon_cooldown = WEAPON_COOLDOWN;
    player_entity->weapon_cooldown_current = 0.0f;
    player_entity->lifespan_ms = -1;

    game_state->player = player_entity;
}

// Respawn after short delay
void player_handle_spawn(GameState *game_state) {
  if (game_state->player == NULL) {
    if (game_state->player_respawn_ms_elapsed >= RESPAWN_MS || game_state->ms_elapsed < RESPAWN_MS) {
      player_spawn(game_state);
      game_state->player_respawn_ms_elapsed = 0;
    } else {
      game_state->player_respawn_ms_elapsed += game_state->delta_time;
    }
  }
}
