//
// Created by gogphojoh on 11/5/25.
//

#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "text.h"
#include "player.h"
#include "music.h"
#include "bullet.h"
#include "enemy.h"

struct Game {
    struct Music *music;
    struct Text *text;
    struct Player *player;
    struct Bullet *bullet;
    struct BulletEntity *be;
    struct Enemy *enemy;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    SDL_Event event;
    bool is_running;
    SDL_FRect src;
    SDL_FRect dst;

    int r;
};

void game_free(struct Game **game);
bool game_new (struct Game **game);
void game_run(struct Game *g);

#endif
