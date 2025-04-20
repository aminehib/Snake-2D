#include <iostream>
#include <SDL2/SDL.h>

#include "window.hpp"
#include "enum.hpp"
#include "world.hpp"
#include "view.hpp"
#include "snake.hpp"

using namespace std;

int main(int argc, char** argv) {
    // === 1. Initialisation de la fenêtre ===
    Window window;
    init_window(&window, 800, 800, "Snaketris - Test Tête Snake");

    // Couleurs de fond (facultatif ici car on affiche avec des textures)
    set_color(&window.background, 255, 255, 255, 255); // fond blanc
    set_color(&window.foreground, 0, 0, 0, 255);       // texte noir

    // === 2. Initialisation du monde ===
    World world;
    init_world(&world, 10, 10); // monde 10x10 vide

    // === 3. Initialisation de l'affichage des textures nourriture ===
    WorldView world_view;
    init_world_view(&world_view, &window);

    // === 4. Initialisation du Snake (au centre) ===
    Snake snake;
    init_snake(&snake, 5, 5, EAST); // départ au centre, direction droite

    // === 5. Boucle principale ===
    bool quit = false;
    SDL_Event event;
    Uint32 last_update = SDL_GetTicks();

    while (!quit) {
        // Gérer les événements clavier / fenêtre
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quit = true;

            // Fermer si Q est appuyée
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
                quit = true;
        }

        // Avancer automatiquement toutes les 200ms
        Uint32 now = SDL_GetTicks();
        if (now - last_update > 200) {
            move_snake(&snake);   // Déplacement de la tête
            last_update = now;
        }

        // === Affichage ===
        clear_window(&window);
        draw_world(&window, &world, &world_view); // monde vide
        draw_snake(&window, &snake);              // tête du serpent
        refresh_window(&window);
    }

    // === 6. Libération de la mémoire ===
    free_world_view(&world_view);
    free_world(&world);
    close_window(&window);

    return 0;
}
