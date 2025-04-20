// Étape 1 : enum.hpp — types fondamentaux
#ifndef ENUM_HPP
#define ENUM_HPP

// Directions du Snake
enum Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

// Types de nourriture
enum FoodType {
    NONE,
    RED,
    GREEN,
    BLUE,
    STAR
};

// Statut du jeu
enum Statut {
    BEGIN,
    PLAY,
    PAUSE,
    GAMEOVER
};

#endif
