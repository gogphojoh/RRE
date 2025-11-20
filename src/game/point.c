//
// Created by gogphojoh on 11/16/25.
//
#include "point.h"

//Problemas con el seguimiento al jugador y con el dibujado de posiciones distintas.

bool point_new(struct Point **point, SDL_Renderer *renderer, struct Enemyp *ep) {
  *point = calloc (1, sizeof (struct Point));
  if (!(*point)) {
    fprintf(stderr,"Error al guardar en la memoria la bala: %s", SDL_GetError());
    return false;
  }
  struct Point *p = *point;
  p->renderer = renderer;
  if (!p->renderer) {
    fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
    return false;
  }
  p->surf= IMG_Load("assets/objects/power.png");
  if (!p->surf) {
    fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
    return false;
  }
  p->image = SDL_CreateTextureFromSurface(p->renderer, p->surf);
  if (!p->image) {
    fprintf(stderr,"Error al crear la imagen: %s", SDL_GetError());
    return false;
  }



  for (int i = 0; i < ep->quantity; i++) {
    p->points[i].active = false;
    //Tienes que definir todos los parametros, sobre todo si son objetos de arrays que se dibujan varias veces.
    SDL_GetTextureSize(p->image,&p->points[i].rect.w,&p->points[i].rect.h);
  }

  return true;
}
void  point_update(struct Point *p, struct Enemyp *ep, struct Player *pl) {
  //Conseguir que el Power suba brevemente

  for (int i = 0; i < ep->quantity; i++) {

    if (p->points[i].active && p->points[i].rect.y + p->points[i].rect.h < WINDOW_HEIGHT && !(pl->rect.y + pl->rect.h <= ( (float) WINDOW_HEIGHT/ 5)) && ep->now > p->points[i].ascention ) {
      // printf("estoy bajando. \n");
      p->points[i].up = false;
      spawn_point(p, ep);
      point_draw(p,ep);
      p->points[i].pw_y += POWER_VEL;
      p->points[i].rect.y = p->points[i].pw_y;

    } else if (p->points[i].active && p->points[i].ascention > ep->now && p->points[i].up == true) {
      // printf("Estoy levitando \n");
      //La condicional inferior se estaba activando antes que esta, por lo que el movimiento continuaba, más no el dibujado. Este solo se reactivaba
      //Gracias a la condicional superior.
      spawn_point(p, ep);
      point_draw(p,ep);
      p->points[i].pw_y -= POWER_VEL;
      p->points[i].rect.y = p->points[i].pw_y;
    }
    else if (p->points[i].active && p->points[i].rect.y + p->points[i].rect.h >= WINDOW_HEIGHT) {
      p->points[i].active = false;
    }
    if ((p->points[i].active && (p->points[i].rect.y + p->points[i].rect.h < WINDOW_HEIGHT) && pl->rect.y + pl->rect.h <= ( (float) WINDOW_HEIGHT/ 5))) {
      printf("Seguimiento al jugador activado");
      p->points[i].follow = true;
      //Hacer una transición suave
    }
    if (p->points[i].follow) {
      if (p->points[i].rect.x < pl->rect.x ) {
        p->points[i].rect.x +=10;
      }
      else if (p->points[i].rect.x > pl->rect.x) {
        p->points[i].rect.x -=10;
      } else if (p->points[i].rect.x == pl->rect.x) {

      }
      if (p->points[i].rect.y < pl->rect.y ) {
        p->points[i].rect.y +=10;
      }
      else if (p->points[i].rect.y > pl->rect.y) {
        p->points[i].rect.y -=10;
      }
      p->points[i].pw_x = p->points[i].rect.x;
      p->points[i].pw_y = p->points[i].rect.y;
    }
    else if (!p->points[i].active){
      p->points[i].rect.x = p->points[i].pw_x;
      p->points[i].rect.y = p->points[i].pw_y;
      // printf("Esta es mi posición X: %f \n", p->pows[i].rect.x);
      // printf("Esta es mi posición Y: %f \n", p->pows[i].rect.y);
    }
  }




}
void point_draw(struct Point *p, struct Enemy *e) {
    //Establecer cooldown de hasta 1000 ms para que vuelva a ser dibujado
    for (int i = 0; i < e->quantity; i++) {
      if (p->points[i].active && p->points[i].rect.y + p->points[i].rect.h <= WINDOW_HEIGHT) {
        SDL_RenderTexture(p->renderer, p->image, NULL, &p->points[i].rect);
      }
    }



}
void point_free(struct Point **point) {
  if (*point) {
    struct Point *p = *point;
    if (p->image) {
      SDL_DestroyTexture(p->image);
      p->image = NULL;
    }
    if (p->surf) {
      SDL_DestroySurface(p->surf);
      p->surf = NULL;
    }
    if (p->point) {
      MIX_DestroyAudio(p->point);
    }
    if (p->track) {
      MIX_DestroyTrack(p->track);
    }
    p->renderer = NULL;
    free(p);
    p = NULL;
    *point = NULL;
    printf("Free Power. \n");

  }
}
void spawn_point(struct Point *p, struct Enemy *e) {
  //Posible problema de consumo excesivo de CPU
  if (p->surf) SDL_DestroySurface(p->surf);
  if (p->image) SDL_DestroyTexture(p->image);
  p->surf= IMG_Load("assets/objects/points.png");
  p->image = SDL_CreateTextureFromSurface(p->renderer, p->surf);
}

void point_sound(struct Point *p, struct Music *m) {
  if (p->point ) {
    MIX_DestroyAudio(p->point);
    p->point = NULL;
  }
  if (p->track) {
    MIX_DestroyTrack(p->track);
    p->track = NULL;
  }
  p->now = SDL_GetTicks();
  p->point = MIX_LoadAudio(m->mixer, "music/sfx/point.wav", true);
  if (!p->point) {
    SDL_Log("Error al cargar el audio: %s", SDL_GetError());
    MIX_DestroyMixer(p->mixer);
    return ;
  }


  p->track = MIX_CreateTrack(m->mixer);
  if (!p->track) {
    SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
    MIX_DestroyAudio(p->point);
    p->point = NULL;
    return ;
  }


  MIX_SetTrackAudio(p->track, p->point);
  //Esta condicional no se cumple siempre.
  if (p->point_sound == false) {
    p->i++;
    printf("Esto pasó! %d veces", p->i);
    MIX_PlayTrack(p->track, 0);
    p->point_sound = true;
    p->play_time = (float) p->now + 500;
  }
}