//
// Created by gogphojoh on 11/14/25.
//

#include "enemy.h"

//Cuando muere el enemigo es cuando el consumo de memoria se dispara.

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
  //La solución final fue bastante parecida al del rectangulo, sin embargo, es un poco más compleja.

  //!!! Estudiar !!!
  if (!e->active && e->play_time < e->now) {
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
    if (e->surf) {
      SDL_DestroySurface(e->surf);
      e->surf = NULL;
    }
    if (e->kill) {
      MIX_DestroyAudio(e->kill);
      e->kill = NULL;
    }
    if (e->track) {
      MIX_DestroyTrack(e->track);
      e->track = NULL;
    }

    e->renderer = NULL;
    free(e);
    e = NULL;
    *enemy = NULL;
    printf("Free Enemy. \n");

  }
}

void play_sound(struct Enemy *e, struct Music *m) {
  if (e->kill ) {
    MIX_DestroyAudio(e->kill);
    e->kill = NULL;
  }
  if (e->track ) {
    MIX_DestroyTrack(e->track);
    e->track = NULL;
  }

  e->kill = MIX_LoadAudio(m->mixer, "kill.mp3", true);
  if (!e->kill) {
    SDL_Log("Error al cargar el audio: %s", SDL_GetError());
    return ;
  }
  e->track = MIX_CreateTrack(m->mixer);
  if (!e->track) {
    SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
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
    if (e->surf) SDL_DestroySurface(e->surf);
    if (e->image) SDL_DestroyTexture(e->image);
    e->surf= IMG_Load("hada.png");
    if (!e->surf) {
      fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
      return ;
    }
    e->image = SDL_CreateTextureFromSurface(e->renderer, e->surf);
    e->active = true;
  }

}