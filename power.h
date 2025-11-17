//
// Created by gogphojoh on 11/16/25.
//

#ifndef RRE_POWER_H
#define RRE_POWER_H

#include "main.h"
#include "enemy.h"
#include "player.h"
#include "music.h"

struct PowerEntity {
  SDL_FRect rect; //Tamaño y forma de las multiples balas
  bool active; //Define si una bala ya fue usada
};

struct Power {
  struct Enemy *enemy;
  SDL_Renderer *renderer;
  SDL_Texture *image;
  SDL_Surface *surf;
  SDL_FRect rect; // for width/height reference
  float pw_x, pw_y;
  bool active;
  struct PowerEntity bullets[MAX_BULLETS];
  MIX_Mixer *mixer;
  MIX_Audio *power;
  MIX_Track *track;//piscina de balas
  bool power_sound;
  float play_time;
  Uint32 now;
  int i;
};
bool power_new(struct Power **power, SDL_Renderer *renderer);
void power_update(struct Power *p, struct Enemy *e, struct Player *pl);
void power_draw(struct Power *p, struct Enemy *e);
void power_free(struct Power **power);
void spawn_power(struct Power *p, struct Enemy *e);
bool power_collide(SDL_FRect *a, SDL_FRect *b);
void power_sound(struct Power *p, struct Music *m);


#endif // RRE_POWER_H
