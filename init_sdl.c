//
// Created by gogphojoh on 11/6/25.
//
#include "init_sdl.h"

bool game_init_sdl(struct Game *g) {
    // Inicia SDL
    if (!SDL_Init(SDL_FLAGS)) {
        fprintf(stderr, "Error al iniciar SDL3: %s\n", SDL_GetError());
        return false;
    }

    if (!TTF_Init()) {
        fprintf(stderr, "Error al iniciar SDL3_ttf: %s\n", SDL_GetError());
        return false;
    }

    if (!MIX_Init()) {
        fprintf(stderr, "Error al iniciar SDL3_mixer: %s\n", SDL_GetError());
        return false;
    }

    // Crea la ventana
    g->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!g->window) {
        fprintf(stderr, "Error al crear ventana: %s\n", SDL_GetError());
        return false;
    }

    // Crea el "pincel" para dibujar en la ventana
    g->renderer = SDL_CreateRenderer(g->window, NULL);
    if (!g->renderer) {
        fprintf(stderr, "Error al crear renderer: %s\n", SDL_GetError());
        return false;
    }


    SDL_Surface *icon_surf =  (IMG_Load("Logo.png"));
    if (!icon_surf) {
        fprintf(stderr, "Error cargando el icono de la pantalla: %s\n", SDL_GetError());
        return false;
    }
    if (!SDL_SetWindowIcon(g->window, icon_surf)) {
        fprintf(stderr, "Error al establecer el icono de la pantalla: %s\n", SDL_GetError());
        SDL_DestroySurface(icon_surf);
        return false;
    }

    SDL_DestroySurface(icon_surf);

    return true;
}