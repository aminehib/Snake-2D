// view.hpp — affichage du monde avec textures
#ifndef VIEW_HPP
#define VIEW_HPP

#include "window.hpp"
#include "world.hpp"
#include <SDL2/SDL_image.h>

struct WorldView {
    SDL_Texture* background;
    SDL_Texture* red;
    SDL_Texture* green;
    SDL_Texture* blue;
    SDL_Texture* star;
};

// Charge les textures du monde
void init_world_view(WorldView* view, Window* window);

// Libère les textures
void free_world_view(WorldView* view);

// Dessine le monde en utilisant les textures
void draw_world(Window* window, World* world, WorldView* view);

#endif
