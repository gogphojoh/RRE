//
// Created by gogphojoh on 11/6/25.
//

#include "load_media.h"

bool game_load_media(struct Game *g) {
  //Preparación para hacer que los escenarios empiecen a rotar.
    g->background = IMG_LoadTexture(g->renderer, "assets/backgrounds/black.jpg");
    g->src= (SDL_FRect){0,0,1280, 960};
    g->dst= (SDL_FRect) {0,0,1280,960};
    if (!g->background) {
        fprintf(stderr, "Error al crear el fondo del juego: %s\n", SDL_GetError());
        return false;
    }




    g->background2 = IMG_LoadTexture(g->renderer, "assets/backgrounds/black.jpg");
    g->src3= (SDL_FRect){0,0,1280, 53};
    g->dst3= (SDL_FRect) {0,0,1280,53};
    if (!g->background2) {
        fprintf(stderr, "Error al crear el fondo del juego: %s\n", SDL_GetError());
        return false;
    }

    g->background3 = IMG_LoadTexture(g->renderer, "assets/backgrounds/black.jpg");
    g->src4= (SDL_FRect){0,825,1280, 43};
    g->dst4= (SDL_FRect) {0,917,1280,43};
    if (!g->background2) {
        fprintf(stderr, "Error al crear el fondo del juego: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

