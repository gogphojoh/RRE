//
// Created by gogphojoh on 11/13/25.
//

#ifndef MUSIC_BULLET_H
#define MUSIC_BULLET_H

#include "../mainloop/main.h"
#include "enemy.h"

struct BulletEntity {
    SDL_FRect rect; //Tamaño y forma de las multiples balas
    int hit;
    SDL_Texture *image;
    SDL_Surface *surf;
    int btype;
    bool active; //Define si una bala ya fue usada
};

struct EnemyBulletEntity {
  SDL_FRect rect; //Tamaño y forma de las multiples balas
  int hit;
  SDL_Texture *image;
  SDL_Surface *surf;
  int btype;
  bool active; //Define si una bala ya fue usada
};

struct Bullet {
    struct Enemy *enemy;
    struct Enemyp *enemyp;
    SDL_Renderer *renderer;
    SDL_FRect rect; // for width/height reference
    const bool *keystate;
    float p_x, p_y;
    int index;
    int bcount;
    struct BulletEntity bullets[MAX_BULLETS]; //piscina de balas
    struct EnemyBulletEntity ebullets[MAX_BULLETS];
    Uint32 next_fire_time;
};
bool bullet_new(struct Bullet **bullet, SDL_Renderer *renderer);
void bullet_update(struct Bullet *b, struct Enemy *e, struct Power *p, struct Music *m, struct Player *pl);
void bullet_draw(struct Bullet *b);
void bullet_free(struct Bullet **bullet);
void player_bullets (struct Bullet *b);
static void spawn_bullet(struct Bullet *b, struct Enemy *e);
static void enemy_bullet(struct Bullet *b, struct Enemy *e);
bool rects_collide(SDL_FRect *a, SDL_FRect *b);

#endif //MUSIC_BULLET_H