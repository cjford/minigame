#include "render.h"
#include "text.h"

static SDL_Renderer *renderer;
static SDL_Window *window;

int render_init(SDL_Window *window) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
      "This is a game window",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
      printf("Could not create window: %s\n", SDL_GetError());
      return 1;
    } else {
      printf("Created a window\n");
    }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  text_init(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

  return 0;
}

void render_quit() {
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}

void load_sprite_texture(Sprite *sprite) {
  SDL_Surface* texture_surface;

  texture_surface = SDL_LoadBMP(sprite->bmp_filename);
  if (texture_surface == NULL) {
    printf("Error loading sprite: %s\n", sprite->bmp_filename);
  }

  sprite->texture = SDL_CreateTextureFromSurface(renderer, texture_surface);
  SDL_FreeSurface(texture_surface);
}

void render_sprite(Sprite *sprite, int x, int y, int w, int h) {
  if(!sprite->texture) {
    load_sprite_texture(sprite);
  }

  if(!w || !h) { // No spatial data, it's a background / static entity
    SDL_RenderCopy(renderer, sprite->texture, NULL, NULL);
  } else {
    SDL_Rect texture_dest;
    SDL_Rect texture_src;

    texture_src.x = sprite->x_offset * sprite->w;
    texture_src.y = sprite->y_offset * sprite->h;
    texture_src.w = sprite->w;
    texture_src.h = sprite->h;

    texture_dest.x = x;
    texture_dest.y = y;
    texture_dest.w = w;
    texture_dest.h = h;

    SDL_RenderCopy(renderer, sprite->texture, &texture_src, &texture_dest);
  }
}

void render_sprite_lives(int lives, int window_width, int window_height) {
  for(int i = 0; i < lives; i++) {
    render_sprite(
      get_sprite(SPRITE_PLAYER_SHIP),
      window_width - 30 - ((get_sprite(SPRITE_PLAYER_SHIP)->w * i) + (5 * i)),
      window_height - get_sprite(SPRITE_PLAYER_SHIP)->h - 10,
      get_sprite(SPRITE_PLAYER_SHIP)->w,
      get_sprite(SPRITE_PLAYER_SHIP)->h
    );
  }
}

void render_entity(Entity *entity) {
  render_sprite(
    entity->sprite,
    entity->position.x,
    entity->position.y,
    entity->w,
    entity->h
  );
}

void render_all(GameState *game_state) {
  int entity_index = 0;

  if (game_state->static_entity_count > 0) {
    for(entity_index = 0; entity_index < game_state->static_entity_count; entity_index++) {
      render_entity(game_state->static_entities[entity_index]);
    }
  }
  if (game_state->entity_count > 0) {
    for(entity_index = 0; entity_index < game_state->entity_count; entity_index++) {
      render_entity(game_state->entities[entity_index]);
    }
  }

  if (game_state->lives > 0) {
    render_sprite_lives(game_state->lives, game_state->world_w, game_state->world_h);
  } else {
    text_render_game_over(renderer);
  }

  text_render_score(renderer, game_state->score);

  SDL_RenderPresent(renderer);

  // Due to dynamic score text, we create a new texture each frame
  // and must free it after rendering
  text_free_score();
}
