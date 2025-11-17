//
// Created by gogphojoh on 11/14/25.
//

#include "enemy.h"

bool enemy_new(struct Enemy **enemy, SDL_Renderer *renderer) {
  *enemy = calloc (1, sizeof (struct Enemy));
  if (!(*enemy)) {
    fprintf(stderr,"Error al guardar en la memoria la enemigo: %s", SDL_GetError());
    return false;
  }
  struct Enemy *e = *enemy;
  e->renderer = renderer;
  //b->next_fire_time = 0;
  if (!e->renderer) {
    fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
    return false;
  }
  e->surf= IMG_Load("hada.png");
  if (!e->surf) {
    fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
    return false;
  }
  e->image = SDL_CreateTextureFromSurface(e->renderer, e->surf);
  if (!e->image) {
    fprintf(stderr,"Error al crear la imagen del enemigo: %s", SDL_GetError());
    return false;
  }
  SDL_GetTextureSize(e->image,&e->rect.w,&e->rect.h);
  e->rect.x = 100;
  e->rect.y = 100;
  e->x_vel = ENEMY_VEL;
  e->y_vel = ENEMY_VEL;
  e->active = true;
  e->sound_active = false;
  return true;
}
void enemy_update(struct Enemy *e, struct Power *p, struct Music *m) {
  // printf("Posicion bala X: %f\n", e->dz_x);
  // printf("Posicion bala Y: %f\n", e->dz_y);
  // printf("Posicion enemigo X: %f\n", e->rect.x);
  // printf("Posicion enemigo Y: %f\n", e->rect.y);
  // printf("Anchura enemigo W: %f\n", e->rect.w);
  // printf("Altura enemigo H: %f\n", e->rect.h);
  // printf("Posicion de bala X: %f\n", b->rect.x);
  // printf("Posicion de bala Y: %f\n", b->rect.y);
  //La posición exacta del enemigo es TAN ridiculamente fina, que la bala JAMÁS coincidirá exactamente en su posición. Debo darle mayor margen a la bala.
  //LA SOLUCIÓN PUEDE SER EL USAR LA MISMA TECNICA DEL RECTANGULO DE TEXT.C!!!
  //!!! Estudiar !!!
  /*
  Posicion bala X: 836.000000
  Posicion bala Y: 900.000000
  Posicion enemigo X: 796.000000
  Posicion enemigo Y: 796.000000
   */
  if (!e->active) {
    play_sound(e,m);
    spawn_enemy(e, p);
  }

  e->rect.x += e->x_vel;
  e->rect.y += e->y_vel;
  if (e->active == true && p->active == false) {
    p->pw_x = e->rect.x;
    p->pw_y = e->rect.y;
  }

  // e->rect.y = 0.01f * (e->rect.x * e->rect.x);
  // Replicar esta lógica
  if (e->rect.x + e->rect.w > WINDOW_WIDTH) {
    e->x_vel = -ENEMY_VEL;
  } else if (e->rect.x < 0) {
    e->x_vel = ENEMY_VEL;
  } else if (e->rect.y < 0) {
    e->y_vel = ENEMY_VEL;
  } else if (e->rect.y + e->rect.h > WINDOW_HEIGHT) {
    e->y_vel = -ENEMY_VEL;
  }

}
void enemy_draw(struct Enemy *e) {
  SDL_RenderTexture(e->renderer, e->image, NULL, &e->rect);
}
void enemy_free(struct Enemy **enemy) {
  if (*enemy) {
    struct Enemy *e = *enemy;
    if (e->image) {
      SDL_DestroyTexture(e->image);
      e->image = NULL;
    }
    e->renderer = NULL;
    free(e);
    e = NULL;
    *enemy = NULL;
    printf("Free Enemy. \n");

  }
}

void play_sound(struct Enemy *e, struct Music *m) {

  e->kill = MIX_LoadAudio(m->mixer, "kill.mp3", true);
  if (!e->kill) {
    SDL_Log("Error al cargar el audio: %s", SDL_GetError());
    MIX_DestroyMixer(e->mixer);
    return ;
  }


  e->track = MIX_CreateTrack(m->mixer);
  if (!e->track) {
    SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
    MIX_DestroyAudio(e->kill);
    MIX_DestroyMixer(e->mixer);
    return ;
  }


  MIX_SetTrackAudio(e->track, e->kill);
  if (e->sound_active == false) {
    MIX_PlayTrack(e->track, 0);
    e->sound_active = true;
    e->play_time = e->now + 1000;
  }else if (e->sound_active == true && e->play_time < e->now ) {
    e->sound_active = false;
  }
}

static void spawn_enemy(struct Enemy *e, struct Power *p) {

  if (e->spawn_time < e->now) {
    e->surf= IMG_Load("hada.png");
    if (!e->surf) {
      fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
      return ;
    }
    e->image = SDL_CreateTextureFromSurface(e->renderer, e->surf);
    e->active = true;
  }

}