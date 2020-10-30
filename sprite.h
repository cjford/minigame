#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#define SPRITE_PLAYER_SHIP 0
#define SPRITE_PLAYER_PROJECTILE 1
#define SPRITE_ENEMY_SMALL 2
#define SPRITE_EXPLOSION 3
#define SPRITE_CLOUD_BACKGROUND 4
#define SPRITE_DESERT_BACKGROUND 5

typedef struct sprite {
  char *bmp_filename;
  SDL_Texture* texture;
  int y_offset_ms_interval;
  int y_offset_stage_count;
  int x_offset_ms_interval;
  int x_offset_stage_count;
  int x_offset;
  int y_offset;
  int w;
  int h;
} Sprite;

void sprite_update_offsets(Sprite *sprite, int ms_elapsed);
void load_sprites();
Sprite *get_sprite(int index);

#endif // SPRITE_H
