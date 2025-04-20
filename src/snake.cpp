#include "snake.hpp"
#include "view.hpp" // Pour utiliser les textures (head_open_...)

// Initialise le serpent à une position et une direction
void init_snake(Snake* s, int x, int y, Direction d) {
    s->x = x;
    s->y = y;
    s->dir = d;
    s->head = nullptr;
    s->tail = nullptr;
}

// Déplacement du serpent ( tête et corps)
void move_snake(Snake* s) {
    int prev_x = s->x;
    int prev_y = s->y;

    // === Déplacer la tête ===
    switch (s->dir) {
        case NORTH: s->y -= 1; break;
        case SOUTH: s->y += 1; break;
        case EAST:  s->x += 1; break;
        case WEST:  s->x -= 1; break;
    }

    // === Déplacement des anneaux ===
    Ring* current = s->head;
    while (current) {
        int temp_x = current->x;
        int temp_y = current->y;

        current->x = prev_x;
        current->y = prev_y;

        prev_x = temp_x;
        prev_y = temp_y;

        current = current->prev;
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
// Affichage de les anneaux (corps du serpent)
void draw_body(Window* window, Snake* s) {
    int cell_width  = window->width / 10;
    int cell_height = window->height / 10;

    Ring* current = s->tail;
    while (current) {
        SDL_Texture* body = nullptr;

        // Choisir la texture selon la couleur (nourriture)
        switch (current->food) {
            case RED:   body = window->body_red;   break;
            case GREEN: body = window->body_green; break;
            case BLUE:  body = window->body_blue;  break;
            default: break;
        }

        if (body) {
            draw_texture(window, body,
                         current->x * cell_width,
                         current->y * cell_height,
                         cell_width, cell_height);
        }

        current = current->next;
    }
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

// Ajoute un anneau juste derrière la tête du Snake
void add_ring(Snake* s, FoodType food) {
    Ring* new_ring = new Ring;

    // La nouvelle position de l’anneau = ancienne position de la tête
    new_ring->x = s->x;
    new_ring->y = s->y;
    new_ring->food = food;

    new_ring->prev = s->head;
    new_ring->next = nullptr;

    if (s->head) {
        s->head->next = new_ring;
    } else {
        // Si c’est le tout premier anneau, c’est aussi la queue
        s->tail = new_ring;
    }

    // Met à jour la nouvelle tête du corps
    s->head = new_ring;
}


