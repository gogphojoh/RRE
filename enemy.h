//
// Created by gogphojoh on 11/14/25.
//

#ifndef RRE_ENEMY_H
#define RRE_ENEMY_H

#include "main.h"
#include "bullet.h"
#include "power.h"

struct Enemy {
  struct Power *power;
  SDL_Renderer *renderer;
  SDL_Texture *image;
  SDL_Surface *surf;
  SDL_FRect rect;
  float x_vel, y_vel;
  bool active;
  Uint32 now;
  int spawn_time;
  double curve;
};

bool enemy_new(struct Enemy **enemy, SDL_Renderer *renderer);
void enemy_update(struct Enemy *e,struct Power *p);
void enemy_draw(struct Enemy *e);
void enemy_free(struct Enemy **enemy);
static void spawn_enemy(struct Enemy *e);

#endif // RRE_ENEMY_H

