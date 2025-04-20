// view.cpp — implémentation de l'affichage du monde
#include "view.hpp"
#include <SDL2/SDL.h>

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
            // 1. Dessiner d'abord le fond
            draw_texture(window, view->background,
                         x * cell_width, y * cell_height,
                         cell_width, cell_height);
    
            // 2. Ensuite, s'il y a de la nourriture, la dessiner PAR-DESSUS
            SDL_Texture* food_texture = nullptr;
            switch (get_food(world, x, y)) {
                case RED:   food_texture = view->red; break;
                case GREEN: food_texture = view->green; break;
                case BLUE:  food_texture = view->blue; break;
                case STAR:  food_texture = view->star; break;
                default: break;
            }
    
            if (food_texture) {
                // Dessin plus petit que la cellule (centré)
                int margin = cell_width / 4; // 25% de marge
                draw_texture(window, food_texture,
                             x * cell_width + margin,
                             y * cell_height + margin,
                             cell_width - 2 * margin,
                             cell_height - 2 * margin);
            }
        }
    }
    
}

void init_snake_view(SnakeView* view, Window* window) {
    // Têtes - ouvertes
    view->head_open_up    = load_image(window, "img/head_open_up.png");
    view->head_open_down  = load_image(window, "img/head_open_down.png");
    view->head_open_left  = load_image(window, "img/head_open_left.png");
    view->head_open_right = load_image(window, "img/head_open_right.png");

    // Têtes - fermées
    view->head_close_up    = load_image(window, "img/head_close_up.png");
    view->head_close_down  = load_image(window, "img/head_close_down.png");
    view->head_close_left  = load_image(window, "img/head_close_left.png");
    view->head_close_right = load_image(window, "img/head_close_right.png");

    // Corps
    view->body_red   = load_image(window, "img/body_red.png");
    view->body_green = load_image(window, "img/body_green.png");
    view->body_blue  = load_image(window, "img/body_blue.png");
}

// Affiche la tête + le corps du serpent avec textures directionnelles
void draw_snake(Window* window, Snake* s, SnakeView* sv) {
    int cell_width  = window->width / 10;
    int cell_height = window->height / 10;

    // === Affichage de la tête ===
    SDL_Texture* head = nullptr;
    if (s->open_mouth) {
        set_color(&window->foreground, 255, 0, 0, 255); 
        int text_y = (s->y == 0) ? s->y * cell_height : (s->y - 1) * cell_height;
        draw_text(window, "MIAM !", s->x * cell_width, text_y, 20);
                switch (s->dir) {
            case NORTH: head = sv->head_open_up; break;
            case SOUTH: head = sv->head_open_down; break;
            case EAST:  head = sv->head_open_right; break;
            case WEST:  head = sv->head_open_left; break;
        }
    } else {
        switch (s->dir) {
            case NORTH: head = sv->head_close_up; break;
            case SOUTH: head = sv->head_close_down; break;
            case EAST:  head = sv->head_close_right; break;
            case WEST:  head = sv->head_close_left; break;
        }
    }
    int margin_head = cell_width * 0.075;
    draw_texture(window, head,
                 s->x * cell_width + margin_head,
                 s->y * cell_height + margin_head,
                 cell_width - 2 * margin_head,
                 cell_height - 2 * margin_head);
                
    // === Affichage du corps (anneaux) ===
    Ring* current = s->tail;
    while (current) {
        SDL_Texture* body = nullptr;

        switch (current->food) {
            case RED:   body = sv->body_red; break;
            case GREEN: body = sv->body_green; break;
            case BLUE:  body = sv->body_blue; break;
            default: break;
        }

        // Sauter l’anneau qui est exactement sur la tête
        if (current->x != s->x || current->y != s->y) {
            int margin_body = cell_width * 0.075; 
            draw_texture(window, body,
                         current->x * cell_width + margin_body,
                         current->y * cell_height + margin_body,
                         cell_width - 2 * margin_body,
                         cell_height - 2 * margin_body);
        }
        current = current->next;
    }
}
