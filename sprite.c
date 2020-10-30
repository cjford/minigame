#include "sprite.h"

static Sprite *sprites[6];
static Sprite player_ship;
static Sprite player_projectile;
static Sprite enemy_small;
static Sprite explosion;
static Sprite desert_background;
static Sprite cloud_background;

void load_sprites() {
  player_ship.bmp_filename = "./assets/sprites/ship.bmp";
  player_ship.w = 16;
  player_ship.h = 24;
  player_ship.y_offset_ms_interval = 160;
  player_ship.y_offset_stage_count = 2;
  player_ship.x_offset = 0;
  player_ship.texture = NULL;

  player_projectile.bmp_filename = "./assets/sprites/player-projectile.bmp";
  player_projectile.w = 5;
  player_projectile.h = 5;
  player_projectile.y_offset_ms_interval = 160;
  player_projectile.y_offset_stage_count = 2;
  player_projectile.texture = NULL;

  enemy_small.bmp_filename = "./assets/sprites/enemy-small.bmp";
  enemy_small.w = 16;
  enemy_small.h = 16;
  enemy_small.x_offset_ms_interval = 160;
  enemy_small.x_offset_stage_count = 2;
  enemy_small.x_offset = 0;
  enemy_small.texture = NULL;

  explosion.bmp_filename = "./assets/sprites/explosion.bmp";
  explosion.w = 16;
  explosion.h = 16;
  explosion.x_offset_ms_interval = 160;
  explosion.x_offset_stage_count = 5;
  explosion.x_offset = 0;
  explosion.texture = NULL;

  cloud_background.bmp_filename = "./assets/sprites/cloud-background.bmp";
  cloud_background.texture = NULL;

  desert_background.bmp_filename = "./assets/sprites/desert-background.bmp";
  desert_background.texture = NULL;

  sprites[SPRITE_PLAYER_SHIP] = &player_ship;
  sprites[SPRITE_PLAYER_PROJECTILE] = &player_projectile;
  sprites[SPRITE_ENEMY_SMALL] = &enemy_small;
  sprites[SPRITE_EXPLOSION] = &explosion;
  sprites[SPRITE_CLOUD_BACKGROUND] = &cloud_background;
  sprites[SPRITE_DESERT_BACKGROUND] = &desert_background;
}

Sprite *get_sprite(int index) {
  return sprites[index];
}

// Change spritesheet offsets based on game time elapsed to create animations
void sprite_update_offsets(Sprite *sprite, int ms_elapsed) {
  if(sprite->x_offset_ms_interval) {
    sprite->x_offset = (ms_elapsed / sprite->x_offset_ms_interval) % sprite->x_offset_stage_count;
  };

  if(sprite->y_offset_ms_interval) {
    sprite->y_offset = (ms_elapsed / sprite->y_offset_ms_interval) % sprite->y_offset_stage_count;
  }
}
