#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"
#include "render.h"

#define FRAMES_PER_SECOND 60

int main(int argc, char *argv[]) {
    // Initialize SDL resources (window/renderer) + TTF text resources
    render_init();

    GameState *game_state = game_init(WINDOW_WIDTH, WINDOW_HEIGHT);
    int elapsed, left;
    Uint32 start_ticks, end_ticks;

    while(1) { // Game loop
      start_ticks = SDL_GetTicks();

      if (game_state->input->quit_requested) { break; }

      input_update(game_state->input);
      game_update(game_state);
      render_all(game_state);

      end_ticks = SDL_GetTicks();
      elapsed = end_ticks - start_ticks;
      left = (1000/FRAMES_PER_SECOND) - elapsed;

      game_state->delta_time = elapsed + left;
      game_state->ms_elapsed += game_state->delta_time;

      // Use up remaining frame budget to stay at constant FPS
      if((left) > 0) {
        SDL_Delay(left);
      }

    }

    render_quit();
    return 0;
}
