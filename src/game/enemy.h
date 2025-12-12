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
  int angle_ring;
  SDL_FRect rect; //Tamaño y forma de las multiples balas
  SDL_FRect src;
  float x_vel, y_vel;
  int growing;
  int expand;
  int vanishing;
  SDL_Texture *image;
  SDL_Surface *surf; // <- Esta fue la solución, incluir la imagen por separado en cada entidad
  SDL_Texture *image_aura;//Imagen del aura del enemigo
  SDL_Surface *surf_aura; 
  SDL_FRect rect_aura;
  SDL_FRect src_aura;
  SDL_Texture *image_death;//Imagen de la muerte del enemigo
  SDL_Surface *surf_death; 
  SDL_FRect rect_death;
  SDL_FRect src_death;
  SDL_Texture *image_ring;//Imagen del anillo de la muerte del enemigo
  SDL_Surface *surf_ring; 
  SDL_FRect rect_ring;
  SDL_FRect src_ring;
  float fire_rate;
  int health;
  int type;
  int frame_count;
  int frame_time;
  bool active; //Define si un enemigo ya fue vencido
  // MIX_Mixer *mixer;
  // MIX_Audio *kill;
  // MIX_Track *track;
  const char *sprite; //<- Usar esta variable como forma dinámica de cambiar los sprites
  const char *aura;
  const char *death;
};

struct Enemy {
  bool backwards;
  int progressive;
  double angle;
  SDL_FlipMode flip;
    double angle2;
  SDL_FlipMode flip2;
  double angle_ring;
  SDL_FlipMode flip_ring;
  const SDL_FPoint *center;
  const SDL_FRect *dstrect;
  const SDL_FRect *srcrect;
  int current_enemy;
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
void hina_update(struct Enemy *e);
void aki_update(struct Enemy *e);
void aki_left_update(struct Enemy *e);
#endif // RRE_ENEMY_H

