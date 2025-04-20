// view.cpp — implémentation de l'affichage du monde
#include "view.hpp"

void init_world_view(WorldView* view, Window* window) {
    view->background = load_image(window, "img/background.png");
    view->red        = load_image(window, "img/food_red.png");
    view->green      = load_image(window, "img/food_green.png");
    view->blue       = load_image(window, "img/food_blue.png");
    view->star       = load_image(window, "img/food_star.png");
}

void free_world_view(WorldView* view) {
    SDL_DestroyTexture(view->background);
    SDL_DestroyTexture(view->red);
    SDL_DestroyTexture(view->green);
    SDL_DestroyTexture(view->blue);
    SDL_DestroyTexture(view->star);
}

void draw_world(Window* window, World* world, WorldView* view) {
    int cell_width = window->width / world->width;
    int cell_height = window->height / world->height;

    for (int y = 0; y < world->height; ++y) {
        for (int x = 0; x < world->width; ++x) {
            SDL_Texture* texture = view->background;
            switch (get_food(world, x, y)) {
                case RED: texture = view->red; break;
                case GREEN: texture = view->green; break;
                case BLUE: texture = view->blue; break;
                case STAR: texture = view->star; break;
                default: break;
            }
            draw_texture(window, texture, x * cell_width, y * cell_height, cell_width, cell_height);
        }
    }
}
