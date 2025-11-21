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
  float x_vel, y_vel;
  SDL_Texture *image;
  SDL_Surface *surf; // <- Esta fue la solución, incluir la imagen por separado en cada entidad
  int health;
  int type;
  bool active; //Define si un enemigo ya fue vencido
  // MIX_Mixer *mixer;
  // MIX_Audio *kill;
  // MIX_Track *track;
  const char *sprite; //<- Usar esta variable como forma dinámica de cambiar los sprites
};

struct Enemy {
  MIX_Mixer *mixer;
  MIX_Audio *kill;
  MIX_Track *track;
  // <- Y usar esto como switch
  // SDL_FRect rect;
  struct Power *power; // <- no es necesario tocar apartir de esto pues es universal
  struct EnemyEntity enemies[MAX_ENEMIES];
  SDL_Renderer *renderer;
  int spacing;
  int quantity;
  Uint32 next_enemy;
  //float x_vel, y_vel;
  //bool active;
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

