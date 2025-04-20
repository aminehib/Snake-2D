#include <iostream>
#include <SDL2/SDL.h>
#include "window.hpp"
#include "enum.hpp"
#include "world.hpp"
#include "view.hpp"

using namespace std;

int main(int argc, char** argv) {
    // 1. Init fenêtre
    Window window;
    init_window(&window, 800, 800, "Snaketris - Test Monde");

    // 2. Init couleurs
    set_color(&window.background, 255, 255, 255, 255); // blanc
    set_color(&window.foreground, 0, 0, 0, 255);       // noir

    // 3. Init monde
    World world;
    init_world(&world, 10, 10);
    set_food(&world, 2, 2, RED);
    set_food(&world, 4, 4, GREEN);
    set_food(&world, 6, 6, BLUE);
    set_food(&world, 8, 8, STAR);

    // 4. Init textures monde
    WorldView view;
    init_world_view(&view, &window);

    // 5. Affichage
    clear_window(&window);
    draw_world(&window, &world, &view);
    refresh_window(&window);

    SDL_Delay(4000); // 4 secondes

    // 6. Nettoyage
    free_world_view(&view);
    free_world(&world);
    close_window(&window);

    return 0;
}
