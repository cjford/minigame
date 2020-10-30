#include "text.h"

#define FONT_PATH "./assets/fonts/PTM55FT.ttf"
#define FONT_SIZE 24

#define GAME_OVER_TEXT "GAME OVER"
#define GAME_OVER_TEXT_W 200
#define GAME_OVER_TEXT_H 50

#define SCORE_TEXT "Score"
#define SCORE_TEXT_W 100
#define SCORE_TEXT_H 50
#define SCORE_TEXT_PADDING 10

static TTF_Font* font;
static SDL_Color text_color = {255, 255, 255};

static SDL_Rect game_over_text_texture_rect;
static SDL_Surface* game_over_text_surface;
static SDL_Texture* game_over_text_texture;

static SDL_Rect score_text_texture_rect;
static SDL_Surface* score_text_surface;
static SDL_Texture* score_text_texture;

static char score_text_buf[16];

void text_init(SDL_Renderer* renderer, int window_width, int window_height) {
  if(TTF_Init() == -1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }

  font = TTF_OpenFont(FONT_PATH, FONT_SIZE);

  score_text_texture_rect.w = SCORE_TEXT_W;
  score_text_texture_rect.h = SCORE_TEXT_H;
  score_text_texture_rect.x = SCORE_TEXT_PADDING;
  score_text_texture_rect.y = window_height - score_text_texture_rect.h;

  game_over_text_texture_rect.w = GAME_OVER_TEXT_W;
  game_over_text_texture_rect.h = GAME_OVER_TEXT_H;
  game_over_text_texture_rect.x = (window_width / 2) - (game_over_text_texture_rect.w / 2);
  game_over_text_texture_rect.y = (window_height / 2) - (game_over_text_texture_rect.h / 2);

  game_over_text_surface = TTF_RenderText_Solid(font, GAME_OVER_TEXT, text_color);
  game_over_text_texture = SDL_CreateTextureFromSurface(renderer, game_over_text_surface);
}

void text_render_score(SDL_Renderer* renderer, int score) {
  sprintf(score_text_buf, "%s: %d", SCORE_TEXT, score);

  score_text_surface = TTF_RenderText_Solid(font, score_text_buf, text_color);
  score_text_texture = SDL_CreateTextureFromSurface(renderer, score_text_surface);

  SDL_RenderCopy(renderer, score_text_texture, NULL, &score_text_texture_rect);
}

void text_free_score() {
  SDL_FreeSurface(score_text_surface);
  SDL_DestroyTexture(score_text_texture);
}

void text_render_game_over(SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, game_over_text_texture, NULL, &game_over_text_texture_rect);
}
