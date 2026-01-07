//
// Created by gogphojoh on 11/5/25.
//

#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "../text/text.h"
#include "../game/player.h"
#include "../game/music.h"
#include "../game/bullet.h"
#include "../game/enemy.h"
#include "../game/power.h"
#include "../game/bomb.h"
#include "../game/scroll.h"

struct Game {
    struct Music *music;
    struct Text *text;
    struct Player *player;
    struct Bullet *bullet;
    struct BulletEntity *be;
    struct Enemy *enemy;
    struct Power *power;
    struct Enemyp *enemyp;
    struct Point *point;
    struct Bomb *bomb;
    struct Scroll *scroll;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    SDL_Texture *background2;
    SDL_Texture *background3;
    SDL_Texture *playzone;
    SDL_Event event;
    bool is_running;
    SDL_FRect src;
    SDL_FRect dst;
    SDL_FRect src2;
    SDL_FRect dst2;
    SDL_FRect src3;
    SDL_FRect dst3;
    SDL_FRect src4;
    SDL_FRect dst4;


    int r;
};

void game_free(struct Game **game);
bool game_new (struct Game **game);
void game_run(struct Game *g);

#endif
