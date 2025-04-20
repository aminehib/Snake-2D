#include "snake.hpp"
#include <iostream>

// Initialise le serpent à une position et une direction
void init_snake(Snake* s, int x, int y, Direction d) {
    s->x = x;
    s->y = y;
    s->dir = d;
    s->head = nullptr;
    s->tail = nullptr;
}

// Déplacement du serpent (tête + anneaux)
void move_snake(Snake* s, World* world) {
    int prev_x = s->x;
    int prev_y = s->y;

    // === Déplacer la tête ===
    switch (s->dir) {
        case NORTH: s->y -= 1; break;
        case SOUTH: s->y += 1; break;
        case EAST:  s->x += 1; break;
        case WEST:  s->x -= 1; break;
    }

    FoodType current_cell = get_food(world, s->x, s->y);
    s->open_mouth = (current_cell != NONE);


    // === Déplacer les anneaux ===
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

// Vérifie si la tête touche un anneau du corps
bool check_self_collision(Snake* s) {
    Ring* current = s->tail;
    while (current) {
        if (current->x == s->x && current->y == s->y) {
            return true;
        }
        current = current->next;
    }
    return false;
}


// Change de direction (sans demi-tour)
void change_direction(Snake* s, Direction new_dir) {
    if ((s->dir == NORTH && new_dir == SOUTH) ||
        (s->dir == SOUTH && new_dir == NORTH) ||
        (s->dir == EAST  && new_dir == WEST)  ||
        (s->dir == WEST  && new_dir == EAST)) {
        cout << "Tentative de demi-tour ignorée." << endl;
        return;
    }
    s->dir = new_dir;
}

// Ajoute un anneau derrière la tête
void add_ring(Snake* s, FoodType food) {
    Ring* new_ring = new Ring;
    new_ring->x = s->x;
    new_ring->y = s->y;
    new_ring->food = food;
    new_ring->prev = s->head;
    new_ring->next = nullptr;

    if (s->head) {
        s->head->next = new_ring;
    } else {
        s->tail = new_ring;
    }

    s->head = new_ring;
}

// Supprime le milieu d’un triplet de même couleur
void check_triple_color(Snake* s) {
    Ring* r = s->tail;
    while (r && r->next && r->next->next) {
        FoodType a = r->food;
        FoodType b = r->next->food;
        FoodType c = r->next->next->food;

        if (a == b && b == c) {
            Ring* mid = r->next;
            r->next = mid->next;
            if (mid->next) mid->next->prev = r;

            if (s->head == mid) s->head = mid->prev;
            if (s->tail == mid) s->tail = mid->next;

            delete mid;
            std::cout << " Triplet détecté : anneau du milieu supprimé." << std::endl;
            return;
        }
        r = r->next;
    }
}


