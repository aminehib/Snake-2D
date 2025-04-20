// world.cpp — implémentation du monde
#include "world.hpp"

void init_world(World* world, int w, int h) {
    world->width = w;
    world->height = h;
    world->grid = new FoodType[w * h];
    for (int i = 0; i < w * h; ++i)
        world->grid[i] = NONE;
}

void free_world(World* world) {
    delete[] world->grid;
    world->grid = nullptr;
}

FoodType get_food(World* world, int x, int y) {
    if (x < 0 || x >= world->width || y < 0 || y >= world->height) return NONE;
    return world->grid[y * world->width + x];
}

void set_food(World* world, int x, int y, FoodType f) {
    if (x < 0 || x >= world->width || y < 0 || y >= world->height) return;
    world->grid[y * world->width + x] = f;
}

void add_random_food(World* world) {
    int x, y;
    do {
        x = rand() % world->width;
        y = rand() % world->height;
    } while (get_food(world, x, y) != NONE);

    int roll = rand() % 6; // 1/6 chance d’avoir une étoile
    FoodType type;
    if (roll == 0)
        type = STAR;
    else
        type = static_cast<FoodType>(1 + rand() % 3); // RED, GREEN, BLUE

    set_food(world, x, y, type);
}


