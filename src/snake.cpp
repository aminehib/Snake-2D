#include "snake.hpp"
#include "view.hpp" // Pour utiliser les textures (head_open_...)

// Initialise le serpent à une position et une direction
void init_snake(Snake* s, int x, int y, Direction d) {
    s->x = x;
    s->y = y;
    s->dir = d;
    s->tail = nullptr;
}

// Déplacement simple de la tête uniquement
void move_snake(Snake* s) {
    switch (s->dir) {
        case NORTH: s->y -= 1; break;
        case SOUTH: s->y += 1; break;
        case EAST:  s->x += 1; break;
        case WEST:  s->x -= 1; break;
    }
}

// Affichage de la tête du serpent
void draw_snake(Window* window, Snake* s) {
    int cell_width  = window->width / 10;   // à adapter si monde ≠ 10x10
    int cell_height = window->height / 10;

    SDL_Texture* head = nullptr;

    switch (s->dir) {
        case NORTH: head = window->head_up; break;
        case SOUTH: head = window->head_down; break;
        case EAST:  head = window->head_right; break;
        case WEST:  head = window->head_left; break;
    }

    draw_texture(window, head, s->x * cell_width, s->y * cell_height, cell_width, cell_height);
}

// Change la direction du Snake, sauf si on demande un demi-tour
void change_direction(Snake* s, Direction new_dir) {
    cout << "Changement direction vers : " << new_dir << endl;
    // Interdire le demi-tour
    if ((s->dir == NORTH && new_dir == SOUTH) ||
        (s->dir == SOUTH && new_dir == NORTH) ||
        (s->dir == EAST  && new_dir == WEST)  ||
        (s->dir == WEST  && new_dir == EAST)){
        cout << "→ Demi-tour refusé" << endl;
        return;
    }

    // Sinon, on change la direction
    s->dir = new_dir;
    cout << "→ Direction changée avec succès" << endl;
}

