//
// Created by gogphojoh on 11/14/25.
//

#ifndef RRE_ENEMY_H
#define RRE_ENEMY_H

#include "../mainloop/main.h"
#include "bullet.h"
#include "power.h"
#include "music.h"

struct EnemyEntity {
  SDL_FRect rect; //Tamaño y forma de las multiples balas
  MIX_Mixer *mixer;
  MIX_Audio *kill;
  MIX_Track *track;
  bool active; //Define si una bala ya fue usada
};

struct Enemy {
  struct Power *power;
  SDL_Renderer *renderer;
  SDL_Texture *image;
  SDL_Surface *surf;
  SDL_FRect rect;
  struct EnemyEntity enemies[MAX_ENEMIES];
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

void play_sound(struct Enemy *e, struct Music *m);
bool enemy_new(struct Enemy **enemy, SDL_Renderer *renderer);
void enemy_update(struct Enemy *e,struct Power *p, struct Music *m);
void enemy_draw(struct Enemy *e);
void enemy_free(struct Enemy **enemy);
static void spawn_enemy(struct Enemy *e, struct Power *p);

#endif // RRE_ENEMY_H

