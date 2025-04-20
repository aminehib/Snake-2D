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
        // Ajout initial de nourritures
    int nb_food = 1 + rand() % 2; // soit 1 soit 2
    for (int i = 0; i < nb_food; ++i) {
        add_random_food(&world);
    }


    // === 3. Initialisation de l'affichage des textures nourriture ===
    WorldView world_view;
    init_world_view(&world_view, &window);

    // === 4. Initialisation du Snake (au centre) ===
    Snake snake;
    init_snake(&snake, 5, 5, EAST); // départ au centre, direction droite

    // === 5. Boucle principale ===
    bool quit = false;
    bool gameover = false;
    SDL_Event event;
    Uint32 last_update = SDL_GetTicks();
    
    while (!quit) {
        // === 1. Gestion des événements ===
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                SDL_Keycode key = event.key.keysym.sym;
                cout << "Touche pressée : " << SDL_GetKeyName(key) << endl;
    
                switch (key) {
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_UP:
                        change_direction(&snake, NORTH);
                        break;
                    case SDLK_DOWN:
                        change_direction(&snake, SOUTH);
                        break;
                    case SDLK_LEFT:
                        change_direction(&snake, WEST);
                        break;
                    case SDLK_RIGHT:
                        change_direction(&snake, EAST);
                        break;
                }
            }
        }
    
        // === 2. Déplacement automatique (toutes les 500 ms) ===
        Uint32 now = SDL_GetTicks();
        if (!gameover && now - last_update > 500) {
            move_snake(&snake); 

            // collision avec soi-même
            if (check_self_collision(&snake)) {
                cout << "💥 Auto-collision ! GAME OVER " << endl;
                gameover = true;
            }
    
            // vérifier les collisions
            if (snake.x < 0 || snake.x >= world.width ||
                snake.y < 0 || snake.y >= world.height) {
                cout << " Le Snake a touché un mur ! GAME OVER" << endl;
                gameover = true;
            }

            // Vérifie si le Snake mange une nourriture
            FoodType eaten = get_food(&world, snake.x, snake.y);
            if (eaten != NONE) {
                set_food(&world, snake.x, snake.y, NONE);
            
                // Nourriture étoile → ne pas ajouter d’anneau, mais activer le tetris
                if (eaten == STAR) {
                    cout << "Nourriture étoile mangée → effet TETRIS activé !" << endl;
                    check_triple_color(&snake);
                } else {
                    add_ring(&snake, eaten);            // Ajoute un anneau de couleur
                    check_triple_color(&snake);
                }
            
                add_random_food(&world);
            }
            

            last_update = now;
        }
    
        // === 3. Affichage ===
        clear_window(&window);
        draw_world(&window, &world, &world_view);
        draw_body(&window, &snake);
        draw_snake(&window, &snake);
    
        // === 4. Fermeture après game over ===
        if (gameover) {
            set_color(&window.foreground, 255, 0, 0, 255); // rouge
            draw_text(&window, "GAME OVER", 200, 350, 80); // au centre
            refresh_window(&window); // afficher le message
            SDL_Delay(2000);         // pause visible
            quit = true;             // quitter ensuite
        } else {
            refresh_window(&window); // affichage normal
        }
        
    }
    

    // === 6. Libération de la mémoire ===
    free_world_view(&world_view);
    free_world(&world);
    close_window(&window);

    return 0;
}
