#include <string>
#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "lib.h"

Coordinate SIZE = {720, 720};

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
    "Platformer", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED,
    SIZE.x,
    SIZE.y,
    SDL_WINDOW_SHOWN
  );
  SDL_Renderer* renderer = SDL_CreateRenderer(
    window, 
    -1, 
    SDL_RENDERER_ACCELERATED
  );

  std::unordered_map<std::string, bool> events_map;
  events_map["HOLD_KEY_RIGHT"] = false;
  events_map["HOLD_KEY_LEFT"] = false;
  events_map["HOLD_KEY_UP"] = false;

  Platform ground = Platform({0, SIZE.y-25}, {SIZE.x, 25});
  Platform p1 = Platform({250, SIZE.y-75}, {100, 25});
  Platform p2 = Platform({400, SIZE.y-175}, {100, 25}); 
  Platform p3 = Platform({550, SIZE.y-75}, {100, 25}); 
  Platform p4 = Platform({600, SIZE.y-125}, {100, 25});
  std::vector<GameObject*> platforms = {&ground, &p1, &p2, &p3, &p4};
  Player player = Player({20, 10}, platforms);

  std::vector<GameObject*> gameobjects = {&ground, &p1, &p2, &p3, &p4, &player};
  // main loop
  bool running = true; 
  while (running) {
    // events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RIGHT) {
          events_map["HOLD_KEY_RIGHT"] = true;
        } else if (event.key.keysym.sym == SDLK_LEFT) {
          events_map["HOLD_KEY_LEFT"] = true;
        } else if (event.key.keysym.sym == SDLK_UP) {
          events_map["HOLD_KEY_UP"] = true;
        }
      } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_RIGHT) {
          events_map["HOLD_KEY_RIGHT"] = false;
        } else if (event.key.keysym.sym == SDLK_LEFT) {
          events_map["HOLD_KEY_LEFT"] = false;
        } else if (event.key.keysym.sym == SDLK_UP) {
          events_map["HOLD_KEY_UP"] = false;
        }
      }
    }

    // render
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    for (int i=0; i<static_cast<int>(gameobjects.size()); i++){
      GameObject* gp = gameobjects[i];
      gp->update(&events_map);
      SDL_Rect rect = {gp->position.x, gp->position.y, gp->size.x, gp->size.y};
      SDL_SetRenderDrawColor(
        renderer, gp->fill.r, gp->fill.g, gp->fill.b, gp->fill.a
      );
      SDL_RenderFillRect(renderer, &rect);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 60); // Cap at 60 FPS
  }

  // clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
