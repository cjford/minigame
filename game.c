#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"
#include "explosion.h"
#include "sprite.h"

#define GAME_INIT_LIVES 3

void input_update(Input *input) {
  static SDL_Event e;

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
        input->quit_requested = 1;
    }
    if (e.type == SDL_MOUSEBUTTONDOWN){
        input->quit_requested = 1;
    }

    if (e.type == SDL_KEYDOWN) {
      if(e.key.keysym.sym == SDLK_LEFT) {
        input->left_pressed = 1;
      } else if(e.key.keysym.sym == SDLK_RIGHT) {
        input->right_pressed = 1;
      } else if(e.key.keysym.sym == SDLK_UP) {
        input->up_pressed = 1;
      } else if(e.key.keysym.sym == SDLK_DOWN) {
        input->down_pressed = 1;
      } else if(e.key.keysym.sym == SDLK_SPACE) {
        input->space_pressed = 1;
      }
    }
    if (e.type == SDL_KEYUP) {
      if(e.key.keysym.sym == SDLK_LEFT) {
        input->left_pressed = 0;
      } else if(e.key.keysym.sym == SDLK_RIGHT) {
        input->right_pressed = 0;
      } else if(e.key.keysym.sym == SDLK_UP) {
        input->up_pressed = 0;
      } else if(e.key.keysym.sym == SDLK_DOWN) {
        input->down_pressed = 0;
      } else if(e.key.keysym.sym == SDLK_SPACE) {
        input->space_pressed = 0;
      }
    }
  }
}

void entity_update(Entity *entity, GameState *game_state) {
  sprite_update_offsets(entity->sprite, game_state->ms_elapsed);

  if (entity->alive) {
    if (is_player(entity)) {
      player_update(entity, game_state);
    } else if (is_player_projectile(entity)) {
      player_projectile_update(entity, game_state);
    } else if (is_enemy(entity)) {
      enemy_update(entity, game_state);
    } else if (is_explosion(entity)) {
      explosion_update(entity, game_state);
    }
  }
}

void update_entities(GameState *game_state) {
  for(int i = 0; i < game_state->entity_count; i++) {
    entity_update(game_state->entities[i], game_state);
  }
}


int is_explosion(Entity *entity) {
  return strcmp(entity->type, EXPLOSION_ENTITY_TYPE) == 0;
}

int is_player(Entity *entity) {
  return strcmp(entity->type, PLAYER_ENTITY_TYPE) == 0;
}

int is_enemy(Entity *entity) {
  return strcmp(entity->type, ENEMY_ENTITY_TYPE) == 0;
}

int is_player_projectile(Entity *entity) {
  return strcmp(entity->type, PLAYER_PROJECTILE_ENTITY_TYPE) == 0;
}

void free_dead_entities(GameState *game_state) {
  int write_head = 0;
  int diff = 0;

  for(int i = 0; i < game_state->entity_count; i++) {
    if(!game_state->entities[i]->alive) {
      free(game_state->entities[i]);
      diff++;
    } else {
      if(write_head != i) {
        game_state->entities[write_head] = game_state->entities[i];
      }
      write_head++;
    }
  }

  game_state->entity_count -= diff;
}

int is_colliding(Entity *entity1, Entity *entity2) {
  int x_collision = (entity1->position.x < entity2->position.x + entity2->w) &&
                    (entity1->position.x + entity1->w > entity2->position.x);

  int y_collision = (entity1->position.y < entity2->position.y + entity2->h) &&
                    (entity1->position.y + entity1->h > entity2->position.y);

  return x_collision && y_collision;
}

Entity* game_create_entity(GameState *game_state) {
  Entity *entity = malloc(sizeof(Entity));
  entity->alive = 1;
  game_state->entities[game_state->entity_count] = entity;
  game_state->entity_count++;

  return entity;
}

Entity* game_create_static_entity(GameState *game_state) {
  Entity *entity = malloc(sizeof(Entity));
  entity->type = "static";
  game_state->static_entities[game_state->static_entity_count] = entity;
  game_state->static_entity_count++;

  return entity;
}

GameState *game_init(int window_width, int window_height) {
  GameState *game_state = malloc(sizeof(GameState));
  memset(game_state, 0, sizeof(GameState));

  Input *input = malloc(sizeof(Input));
  memset(input, 0, sizeof(Input));

  game_state->input = input;
  game_state->lives = GAME_INIT_LIVES;
  game_state->world_w = window_width;
  game_state->world_h = window_height;

  load_sprites();

  Entity *desert_background_entity = game_create_static_entity(game_state);
  desert_background_entity->sprite = get_sprite(SPRITE_DESERT_BACKGROUND);

  Entity *cloud_background_entity = game_create_static_entity(game_state);
  cloud_background_entity->sprite = get_sprite(SPRITE_CLOUD_BACKGROUND);

  return game_state;
};

// Called every frame to update game state. All game logic happens here:
// Spawn/despawn, animation state, collisions, movement
void game_update(GameState *game_state) {
  enemy_handle_spawn(game_state);
  player_handle_spawn(game_state);

  update_entities(game_state);
  free_dead_entities(game_state);
}
