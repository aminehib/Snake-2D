#include <fstream>
#include "snake.hpp"
#include "world.hpp"

using namespace std;

void save_game(Snake* s, World* w, string filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Erreur ouverture fichier sauvegarde." << endl;
        return;
    }

    file << s->x << " " << s->y << " " << s->dir << "\n";

    Ring* current = s->tail;
    while (current) {
        file << "R " << current->x << " " << current->y << " " << current->food << "\n";
        current = current->next;
    }

    for (int y = 0; y < w->height; ++y) {
        for (int x = 0; x < w->width; ++x) {
            FoodType f = get_food(w, x, y);
            if (f != NONE) {
                file << "F " << x << " " << y << " " << f << "\n";
            }
        }
    }

    file.close();
}
