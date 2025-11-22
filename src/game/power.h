//
// Created by gogphojoh on 11/16/25.
//

#ifndef RRE_POWER_H
#define RRE_POWER_H

#include "../mainloop/main.h"
#include "enemy.h"
#include "player.h"
#include "music.h"

struct PowerEntity {
  SDL_FRect rect; //Tamaño y forma de las multiples balas
  SDL_Texture *image;
  SDL_Surface *surf;
  int type;
  float pw_x, pw_y;
  bool up;
  const char *object;
  const char *music;
  float ascention;
  bool active; //Define si una bala ya fue usada
  bool follow;

  MIX_Track *track;
  MIX_Audio *power;
  bool power_sound;
};

struct Power {
  int grab;
  int appear;
  struct Enemy *enemy;
  SDL_Renderer *renderer;
  MIX_Mixer *mixer;
  //SDL_FRect rect; // for width/height reference
  float pw_x, pw_y;
  // bool active;
  bool follow;
  struct PowerEntity pows[MAX_BULLETS];
  float play_time;
  ///float ascention;
  Uint32 now;
  int i;
};
bool power_new(struct Power **power, SDL_Renderer *renderer, struct Enemy *e);
void power_update(struct Power *p, struct Enemy *e, struct Player *pl);
void power_draw(struct Power *p, struct Enemy *e);
void power_free(struct Power **power, struct Enemy *e);
void spawn_power(struct Power *p, struct Enemy *e);
bool power_collide(SDL_FRect *a, SDL_FRect *b);
void power_sound(struct Power *p, struct Music *m, struct Enemy *e);


#endif // RRE_POWER_H
