#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

struct Window {
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
    TTF_Font* sdl_font;
    int width;
    int height;
    SDL_Color background;
    SDL_Color foreground;
    // Textures de la tête du serpent selon la direction
    SDL_Texture* head_up;
    SDL_Texture* head_down;
    SDL_Texture* head_left;
    SDL_Texture* head_right;
    // Textures du corps du serpent selon l'anneau
    SDL_Texture* body_red;
    SDL_Texture* body_green;
    SDL_Texture* body_blue;

};

void init_window(Window* window, int width, int height, string title);
void close_window(Window* window);

void set_color(SDL_Color* dst, int r, int g, int b, int a);
void set_color(SDL_Color* dst, SDL_Color* src);
void clear_window(Window* window);
void refresh_window(Window* window);

void draw_fill_rectangle(Window* window, int x, int y, int w, int h);
SDL_Texture* load_image(Window* window, string file);
void draw_texture(Window* window, SDL_Texture* texture, int x, int y, int w, int h);
void draw_text(Window* window, string text, int x, int y, int size = 20);

#endif
