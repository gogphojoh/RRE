//
// Created by gogphojoh on 11/13/25.
//

#ifndef MUSIC_BULLET_H
#define MUSIC_BULLET_H

#include "main.h"

struct BulletEntity {
    SDL_FRect rect; //Tamaño y forma de las multiples balas
    bool active; //Define si una bala ya fue usada
};

struct Bullet {
    SDL_Renderer *renderer;
    SDL_Texture *image;
    SDL_Surface *surf;
    SDL_FRect rect; // for width/height reference
    const bool *keystate;
    float p_x, p_y;
    struct BulletEntity bullets[MAX_BULLETS]; //piscina de balas
    Uint32 next_fire_time;
};
bool bullet_new(struct Bullet **bullet, SDL_Renderer *renderer);
void bullet_update(struct Bullet *b);
void bullet_draw(struct Bullet *b);
void bullet_free(struct Bullet **bullet);
static void spawn_bullet(struct Bullet *b);

#endif //MUSIC_BULLET_H