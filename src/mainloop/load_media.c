//
// Created by gogphojoh on 11/6/25.
//

#include "load_media.h"

bool game_load_media(struct Game *g) {
    g->background = IMG_LoadTexture(g->renderer, "assets/backgrounds/black.jpg");
    g->src= (SDL_FRect){0,0,1280, 960};
    g->dst= (SDL_FRect) {0,0,1280,960};
    if (!g->background) {
        fprintf(stderr, "Error al crear el fondo del juego: %s\n", SDL_GetError());
        return false;
    }

    g->playzone = IMG_LoadTexture(g->renderer, "assets/backgrounds/playzone.jpg");
    g->src2= (SDL_FRect){0,0,750, 864};
    g->dst2= (SDL_FRect) {75,53,750,864};
    if (!g->playzone) {
      fprintf(stderr, "Error al crear el fondo del juego: %s\n", SDL_GetError());
      return false;
    }

    return true;
}

