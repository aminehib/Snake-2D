#include "window.hpp"
#include <iostream>

void init_window(Window* window, int width, int height, string title) {
    // Initialisation de SDL pour la vidéo
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Erreur SDL_Init: " << SDL_GetError() << endl;
        SDL_Quit();
    }

    // Initialisation de SDL_TTF pour afficher du texte
    if (TTF_Init() < 0) {
        cerr << "Erreur TTF_Init: " << TTF_GetError() << endl;
        SDL_Quit();
    }

    // Enregistrement des dimensions de la fenêtre
    window->width = width;
    window->height = height;

    // Création de la fenêtre et du renderer SDL
    if (SDL_CreateWindowAndRenderer(width, height, 0, &window->sdl_window, &window->sdl_renderer) < 0) {
        cerr << "Erreur création fenêtre/rendu: " << SDL_GetError() << endl;
        SDL_Quit();
    }

    // Définir le titre de la fenêtre
    SDL_SetWindowTitle(window->sdl_window, title.c_str());

    // Chargement de la police
    window->sdl_font = TTF_OpenFont("VeraMono.ttf", 20);
    if (window->sdl_font == nullptr) {
        cerr << "Erreur chargement police: " << TTF_GetError() << endl;
        SDL_Quit();
    }

    window->sdl_font_big = TTF_OpenFont("VeraMono.ttf", 80);
    if (!window->sdl_font_big) {
        cerr << "Erreur chargement police (60) : " << TTF_GetError() << endl;
    }

    // === Têtes du serpent : ouvertes
    window->head_open_up    = load_image(window, "img/head_open_up.png");
    window->head_open_down  = load_image(window, "img/head_open_down.png");
    window->head_open_left  = load_image(window, "img/head_open_left.png");
    window->head_open_right = load_image(window, "img/head_open_right.png");

    // === Têtes du serpent : fermées
    window->head_close_up    = load_image(window, "img/head_close_up.png");
    window->head_close_down  = load_image(window, "img/head_close_down.png");
    window->head_close_left  = load_image(window, "img/head_close_left.png");
    window->head_close_right = load_image(window, "img/head_close_right.png");

    // === Corps du serpent
    window->body_red   = load_image(window, "img/body_red.png");
    window->body_green = load_image(window, "img/body_green.png");
    window->body_blue  = load_image(window, "img/body_blue.png");
}




void close_window(Window* window) {
    // Libération de la police
    TTF_CloseFont(window->sdl_font);
    TTF_CloseFont(window->sdl_font_big);

    // Libération des textures des têtes (ouverte et fermée)
    SDL_DestroyTexture(window->head_open_up);
    SDL_DestroyTexture(window->head_open_down);
    SDL_DestroyTexture(window->head_open_left);
    SDL_DestroyTexture(window->head_open_right);

    SDL_DestroyTexture(window->head_close_up);
    SDL_DestroyTexture(window->head_close_down);
    SDL_DestroyTexture(window->head_close_left);
    SDL_DestroyTexture(window->head_close_right);

    // Libération des textures du corps
    SDL_DestroyTexture(window->body_red);
    SDL_DestroyTexture(window->body_green);
    SDL_DestroyTexture(window->body_blue);

    // Libération du renderer et de la fenêtre
    SDL_DestroyRenderer(window->sdl_renderer);
    SDL_DestroyWindow(window->sdl_window);

    // Arrêt de SDL_TTF et SDL
    TTF_Quit();
    SDL_Quit();
}


void set_color(SDL_Color* dst, int r, int g, int b, int a) {
    dst->r = r;
    dst->g = g;
    dst->b = b;
    dst->a = a;
}

void set_color(SDL_Color* dst, SDL_Color* src) {
    *dst = *src;
}

void clear_window(Window* window) {
    SDL_SetRenderDrawColor(window->sdl_renderer,
                           window->background.r,
                           window->background.g,
                           window->background.b,
                           window->background.a);
    SDL_RenderClear(window->sdl_renderer);
}

void refresh_window(Window* window) {
    SDL_RenderPresent(window->sdl_renderer);
}

void draw_fill_rectangle(Window* window, int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(window->sdl_renderer,
                           window->foreground.r,
                           window->foreground.g,
                           window->foreground.b,
                           window->foreground.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(window->sdl_renderer, &rect);
}

SDL_Texture* load_image(Window* window, string file) {
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface) {
        cerr << "Erreur IMG_Load : " << IMG_GetError() << endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        cerr << "Erreur création texture : " << SDL_GetError() << endl;
        return nullptr;
    }
    return texture;
}

void draw_texture(Window* window, SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(window->sdl_renderer, texture, NULL, &dest);
}

void draw_text(Window* window, string text, int x, int y, int size) {
    TTF_Font* font = nullptr;

    if (size >= 60) {
        font = window->sdl_font_big;
    } else {
        font = window->sdl_font;
    }

    if (!font) {
        cerr << "Erreur : police non chargée pour taille " << size << endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Shaded(font, text.c_str(),
                                                 window->foreground, window->background);
    if (!surface) {
        cerr << "Erreur surface TTF : " << TTF_GetError() << endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        cerr << "Erreur texture TTF : " << SDL_GetError() << endl;
        return;
    }

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    draw_texture(window, texture, x, y, w, h);
    SDL_DestroyTexture(texture);
}
