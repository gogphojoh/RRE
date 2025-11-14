//
// Created by gogphojoh on 11/10/25.
//

#ifndef PLAYER_PLAYER_H
#define PLAYER_PLAYER_H

#include "main.h"
#include "bullet.h"

struct Player {
    struct Bullet *bullet;
    SDL_Renderer *renderer;
    SDL_Texture *image;
    SDL_FRect rect;
    const bool *keystate;
};

bool player_new (struct Player **player, SDL_Renderer *renderer);
void player_free(struct Player **player);
void player_update(struct Player *p, struct Bullet *b);
void player_draw(const struct Player *p);

#endif //PLAYER_PLAYER_H