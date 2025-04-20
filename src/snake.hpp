#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "enum.hpp"
#include "window.hpp"

// Un anneau du corps (on l’utilisera plus tard)
struct Ring {
    int x, y;
    Ring* prev;
    Ring* next;
};

// Le serpent lui-même
struct Snake {
    int x, y;           // Position de la tête
    Direction dir;      // Direction actuelle
    Ring* tail;         // Corps (sera géré après)
};

// Fonctions de base
void init_snake(Snake* s, int x, int y, Direction d);
void move_snake(Snake* s);
void draw_snake(Window* window, Snake* s);

#endif
