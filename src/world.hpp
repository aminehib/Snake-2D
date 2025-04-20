// world.hpp — grille du monde
#ifndef WORLD_HPP
#define WORLD_HPP

#include "enum.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

struct World {
    int width;
    int height;
    FoodType* grid;
};

// Initialise le monde avec des cellules de type NONE
void init_world(World* world, int w, int h);

// Libère la mémoire allouée au monde
void free_world(World* world);

// Récupère le type de nourriture à une position donnée
FoodType get_food(World* world, int x, int y);

// Modifie le type de nourriture à une position donnée
void set_food(World* world, int x, int y, FoodType f);

// Ajoute aléatoirement une nourriture de type RED, GREEN ou BLUE
void add_random_food(World* world);

#endif
