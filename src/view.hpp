// view.hpp — affichage du monde avec textures
#ifndef VIEW_HPP
#define VIEW_HPP

#include "window.hpp"
#include "world.hpp"
#include "snake.hpp"
#include <SDL2/SDL_image.h>

struct WorldView {
    SDL_Texture* background;
    SDL_Texture* red;
    SDL_Texture* green;
    SDL_Texture* blue;
    SDL_Texture* star;
};

struct SnakeView {
    SDL_Texture* head_open_up;
    SDL_Texture* head_open_down;
    SDL_Texture* head_open_left;
    SDL_Texture* head_open_right;

    SDL_Texture* head_close_up;
    SDL_Texture* head_close_down;
    SDL_Texture* head_close_left;
    SDL_Texture* head_close_right;

    SDL_Texture* body_red;
    SDL_Texture* body_green;
    SDL_Texture* body_blue;
};

// Charge les textures du monde
void init_world_view(WorldView* view, Window* window);

// Libère les textures
void free_world_view(WorldView* view);

// Dessine le monde en utilisant les textures
void draw_world(Window* window, World* world, WorldView* view);

void init_snake_view(SnakeView* view, Window* window);

void draw_snake(Window* window, Snake* s, SnakeView* sv);

#endif
