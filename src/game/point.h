//
// Created by gogphojoh on 11/20/25.
//

#ifndef RRE_POINT_H
#define RRE_POINT_H

#include "../mainloop/main.h"
#include "enemy.h"
#include "player.h"
#include "music.h"
#include "enemyp.h"

struct PointEntity {
  SDL_FRect rect; //Tamaño y forma de las multiples balas
  float pw_x, pw_y;
  bool up;
  float ascention;
  bool active; //Define si una bala ya fue usada
  bool follow;
};

struct Point {
  struct Enemy *enemy;
  SDL_Renderer *renderer;
  SDL_Texture *image;
  SDL_Surface *surf;
  SDL_FRect rect; // for width/height reference
  float pw_x, pw_y;
  bool active;
  bool follow;
  struct PointEntity points[MAX_BULLETS];
  MIX_Mixer *mixer;
  MIX_Audio *point;
  MIX_Track *track;//piscina de balas
  bool point_sound;
  float play_time;
  ///float ascention;
  Uint32 now;
  int i;
};
bool point_new(struct Point **point, SDL_Renderer *renderer, struct Enemyp *ep);
void point_update(struct Point *p, struct Enemyp *ep, struct Player *pl);
void point_draw(struct Point *p, struct Enemy *e);
void point_free(struct Point **point);
void spawn_point(struct Point *p, struct Enemy *e);
bool point_collide(SDL_FRect *a, SDL_FRect *b);
void point_sound(struct Point *p, struct Music *m);


#endif // RRE_POINT_H
