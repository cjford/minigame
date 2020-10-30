#ifndef GAME_H
#define GAME_H

#include "sprite.h"
#include "vec2.h"

typedef struct entity {
  int w;
  int h;

  Vec2 position;
  Vec2 velocity;

  char *type;
  int alive;
  int lifespan_ms;
  float weapon_cooldown;
  float weapon_cooldown_current;

  Sprite *sprite;
} Entity;

typedef struct input {
  int left_pressed;
  int right_pressed;
  int up_pressed;
  int down_pressed;
  int space_pressed;
  int quit_requested;
} Input;

typedef struct game_state {
  Entity *player;
  Input *input;
  Entity *entities[200];
  Entity *static_entities[5];
  int entity_count;
  int static_entity_count;
  int delta_time;
  int ms_elapsed;
  int lives;
  int score;
  int player_respawn_ms_elapsed;
  int world_w;
  int world_h;
} GameState;

//void game_render(SDL_Renderer* renderer, GameState *game_state);
void input_update(Input *input);
void game_update(GameState *game_state);
//void entity_update(Entity *entity, GameState *game_state);
//void free_dead_entities(GameState *game_state);
//void update_entities(GameState *game_state);
//void entity_render(SDL_Renderer* renderer, Entity *entity);
int is_colliding(Entity *entity1, Entity *entity2);

Entity* game_create_entity(GameState *game_state);
Entity* game_create_static_entity(GameState *game_state);

int is_player(Entity *entity);
int is_enemy(Entity *entity);
int is_player_projectile(Entity *entity);
int is_explosion(Entity *entity);

GameState *game_init(int window_width, int window_height);
#endif // GAME_H
