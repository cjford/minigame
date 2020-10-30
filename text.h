#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void text_init();
void text_render_score(SDL_Renderer* renderer, int score);
void text_render_game_over(SDL_Renderer* renderer);
void text_free_score();

#endif // TEXT_H
