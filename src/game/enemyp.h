//
// Created by gogphojoh on 11/20/25.
//

#ifndef RRE_ENEMYP_H
#define RRE_ENEMYP_H

#include "../mainloop/main.h"
#include "bullet.h"
#include "power.h"
#include "music.h"

struct EnemypEntity {
  SDL_FRect rect; //Tamaño y forma de las multiples balas
  float x_vel, y_vel;

  bool active; //Define si una bala ya fue usada
};

struct Enemyp {
  MIX_Mixer *mixer;
  MIX_Audio *kill;
  MIX_Track *track;
  struct Power *power;
  SDL_Renderer *renderer;
  SDL_Texture *image;
  SDL_Surface *surf;
  SDL_FRect rect;
  struct EnemypEntity enemiesp[MAX_ENEMIES];
  int spacing;
  int quantity;
  Uint32 next_enemy;
  float x_vel, y_vel;
  bool active;
  bool sound_active;
  float play_time;
  Uint32 now;
  int spawn_time;
  double curve;

};

void death_sound(struct Enemyp *ep, struct Music *m);
bool enemyp_new(struct Enemyp **enemyp, SDL_Renderer *renderer);
void enemyp_update(struct Enemyp *ep,struct Power *p, struct Music *m, struct Point *po);
void enemyp_draw(struct Enemyp *ep);
void enemyp_free(struct Enemyp **enemy);
static void spawn_enemyp(struct Enemyp *ep, struct Power *p);

#endif // RRE_ENEMYP_H
