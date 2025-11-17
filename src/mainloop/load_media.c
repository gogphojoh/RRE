//
// Created by gogphojoh on 11/6/25.
//

#include "load_media.h"

bool game_load_media(struct Game *g) {
    g->background = IMG_LoadTexture(g->renderer, "assets/backgrounds/Simple_DirectMedia_Layer,_Logo.svg");
    g->src= (SDL_FRect){0,0,738, 405};
    g->dst= (SDL_FRect) {250,250,731,405};
    if (!g->background) {
        fprintf(stderr, "Error al crear el fondo del juego: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

