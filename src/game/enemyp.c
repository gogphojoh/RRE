//
// Created by gogphojoh on 11/20/25.
//

//
// Created by gogphojoh on 11/14/25.
//

#include "enemyp.h"

//Cuando muere el enemigo es cuando el consumo de memoria se dispara.

//!Tareas pendientes:
/*
 *Los enemigos ahora mismo están completamente idos. Todos mueren a la vez o ninguno muere. Sin contar que adicionalmente el efecto de sonido de estos mismos se repite en bucle,
 *creando un efecto similar al de un latido.
 *
 *Resuelto
 */

bool enemyp_new(struct Enemyp **enemyp, SDL_Renderer *renderer) {
  *enemyp = calloc (1, sizeof (struct Enemyp));
  if (!(*enemyp)) {
    fprintf(stderr,"Error al guardar en la memoria la enemigo: %s", SDL_GetError());
    return false;
  }
  struct Enemyp *ep = *enemyp;
  ep->renderer = renderer;
  //b->next_fire_time = 0;
  if (!ep->renderer) {
    fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
    return false;
  }
  ep->surf= IMG_Load("assets/sprites/point.png");
  if (!ep->surf) {
    fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
    return false;
  }
  ep->image = SDL_CreateTextureFromSurface(ep->renderer, ep->surf);
  if (!ep->image) {
    fprintf(stderr,"Error al crear la imagen del enemigo: %s", SDL_GetError());
    return false;
  }
  SDL_GetTextureSize(ep->image,&ep->rect.w,&ep->rect.h);
  ep->quantity = SCREEN_ENEMIES;
  for (int i = 0; i < ep->quantity; i++) {
    ep->spacing += 15;
    ep->enemiesp[i].rect.x = 100 + ep->spacing;
    ep->enemiesp[i].rect.y = 100;
    ep->enemiesp[i].rect.w = ep->rect.w;
    ep->enemiesp[i].rect.h = ep->rect.h;
    ep->enemiesp[i].active = true;
    ep->enemiesp[i].x_vel = ENEMY_VEL;
    ep->enemiesp[i].y_vel = ENEMY_VEL;
  }
  // e->rect.x = 100;
  // e->rect.y = 100;

  // e->active = true;
  // e->sound_active = false;
  return true;
}
void enemyp_update(struct Enemyp *ep, struct Power *p, struct Music *m, struct Point *po) {
  //La solución final fue bastante parecida al del rectangulo, sin embargo, es un poco más compleja.

  //!!! Estudiar !!!

  for (int i = 0; i < ep->quantity; i++) {

    // if (!e->enemies[i].active && e->play_time < e->now) {
    //
    //   // spawn_enemy(e, p);
    // }



    if (ep->enemiesp[i].active == true && po->points[i].active == false) {
      po->points[i].pw_x = ep->enemiesp[i].rect.x;
      po->points[i].pw_y = ep->enemiesp[i].rect.y;
    }

    if (ep->enemiesp[i].rect.x + ep->enemiesp[i].rect.w > WINDOW_WIDTH) {
      ep->enemiesp[i].x_vel = -ENEMY_VEL;
    } else if (ep->enemiesp[i].rect.x < 0) {
      ep->enemiesp[i].x_vel = ENEMY_VEL;
    } else if (ep->enemiesp[i].rect.y < 0) {
      ep->enemiesp[i].y_vel = ENEMY_VEL;
    } else if (ep->enemiesp[i].rect.y + ep->enemiesp[i].rect.h > WINDOW_HEIGHT) {
      ep->enemiesp[i].y_vel = -ENEMY_VEL;
    } else  if (ep->enemiesp[i].active) {
      ep->enemiesp[i].rect.x += ep->x_vel + i*4;
      ep->enemiesp[i].rect.y += ep->y_vel + i;
    }
  }



  // e->rect.y = 0.01f * (e->rect.x * e->rect.x);
  // Replicar esta lógica


}
void enemyp_draw(struct Enemyp *ep) {
  for (int i = 0; i < ep->quantity; i++) {
    if (ep->enemiesp[i].active) {
      SDL_RenderTexture(ep->renderer, ep->image, NULL, &ep->enemiesp[i].rect);
    }

  }

}
void enemyp_free(struct Enemyp **enemyp) {
  if (*enemyp) {
    struct Enemyp *ep = *enemyp;
    if (ep->image) {
      SDL_DestroyTexture(ep->image);
      ep->image = NULL;
    }
    if (ep->surf) {
      SDL_DestroySurface(ep->surf);
      ep->surf = NULL;
    }
    for (int i = 0; i < ep->quantity; i++) {
      if (ep->kill) {
        MIX_DestroyAudio(ep->kill);
      }
      if (ep->track) {
        MIX_DestroyTrack(ep->track);

      }
    }


    ep->renderer = NULL;
    free(ep);
    ep = NULL;
    *enemyp = NULL;
    printf("Free Enemy. \n");

  }
}

void death_sound(struct Enemyp *ep, struct Music *m) {

  if (ep->kill ) {
    MIX_DestroyAudio(ep->kill);
    ep->kill = NULL;
  }
  if (ep->track ) {
    MIX_DestroyTrack(ep->track);
    ep->track = NULL;
  }

  ep->kill = MIX_LoadAudio(m->mixer, "music/sfx/kill.mp3", true);
  if (!ep->kill) {
    SDL_Log("Error al cargar el audio: %s", SDL_GetError());
    return ;
  }
  ep->track = MIX_CreateTrack(m->mixer);
  if (!ep->track) {
    SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
    return ;
  }


  MIX_SetTrackAudio(ep->track, ep->kill);
    MIX_PlayTrack(ep->track, 0);
  // if (e->sound_active == false) {
  //
  //   e->sound_active = true;
  //   e->play_time = e->now + 1000;
  // }else if (e->sound_active == true && e->play_time < e->now ) {
  //   e->sound_active = false;
  // }
  }



static void spawn_enemyp(struct Enemyp *ep, struct Power *p) {

  if (ep->spawn_time < ep->now) {
    if (ep->surf) SDL_DestroySurface(ep->surf);
    if (ep->image) SDL_DestroyTexture(ep->image);
    ep->surf= IMG_Load("assets/sprites/hada.png");
    if (!ep->surf) {
      fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
      return ;
    }
    ep->image = SDL_CreateTextureFromSurface(ep->renderer, ep->surf);
    ep->active = true;
  }

}