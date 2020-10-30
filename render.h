#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#include "game.h"

int render_init();
void render_quit();
void render_all(GameState *game_state);

#endif // RENDER_H
