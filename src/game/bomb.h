//
// Created by gogphojoh on 11/25/25.
//

#ifndef RRE_BOMB_H
#define RRE_BOMB_H

#include "../mainloop/main.h"
#include "enemy.h"
#include "power.h"
#include "music.h"

struct Bomb{
  MIX_Mixer *mixer;
  MIX_Audio *bomb;
  MIX_Track *track;
  SDL_Renderer *renderer;
  SDL_Texture *image;
  SDL_Surface *surf;
  SDL_FRect rect;
  bool active;
  float action_time;
  const bool *keystate;
  float pv;
  int hit;

};

bool bomb_new (struct Bomb **bomb, SDL_Renderer *renderer);
void bomb_free(struct Bomb **bomb);
void bomb_update(struct Bomb *b, struct Enemy *e, struct Power *p, struct Music *m, struct Bullet *bu, struct Player *pl, struct Text *t);
void bomb_draw(const struct Bomb *b);
void player_bombs (struct Bomb *b, struct Bullet *bu);
void bomb_sound (struct Bomb *b, struct Music *m);


#endif // RRE_BOMB_H
