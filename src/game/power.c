//
// Created by gogphojoh on 11/16/25.
//
#include "power.h"

//Problemas con el seguimiento al jugador y con el dibujado de posiciones distintas.

bool power_new(struct Power **power, SDL_Renderer *renderer, struct Enemy *e) {
  *power = calloc (1, sizeof (struct Power));
  if (!(*power)) {
    fprintf(stderr,"Error al guardar en la memoria la bala: %s", SDL_GetError());
    return false;
  }
  struct Power *p = *power;
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



  for (int i = 0; i < e->quantity; i++) {
    p->pows[i].active = false;
    //Tienes que definir todos los parametros, sobre todo si son objetos de arrays que se dibujan varias veces.
    SDL_GetTextureSize(p->image,&p->pows[i].rect.w,&p->pows[i].rect.h);
  }

  return true;
}
void power_update(struct Power *p, struct Enemy *e, struct Player *pl) {
  //Conseguir que el Power suba brevemente

  for (int i = 0; i < e->quantity; i++) {

    if (p->pows[i].active && p->pows[i].rect.y + p->pows[i].rect.h < WINDOW_HEIGHT && !(pl->rect.y + pl->rect.h <= ( (float) WINDOW_HEIGHT/ 5)) && e->now > p->pows[i].ascention ) {
      // printf("estoy bajando. \n");
      p->pows[i].up = false;
      spawn_power(p, e);
      power_draw(p,e);
      p->pows[i].pw_y += POWER_VEL;
      p->pows[i].rect.y = p->pows[i].pw_y;

    } else if (p->pows[i].active && p->pows[i].ascention > e->now && p->pows[i].up == true) {
      // printf("Estoy levitando \n");
      //La condicional inferior se estaba activando antes que esta, por lo que el movimiento continuaba, más no el dibujado. Este solo se reactivaba
      //Gracias a la condicional superior.
      spawn_power(p, e);
      power_draw(p,e);
      p->pows[i].pw_y -= POWER_VEL;
      p->pows[i].rect.y = p->pows[i].pw_y;
    }
    else if (p->pows[i].active && p->pows[i].rect.y + p->pows[i].rect.h >= WINDOW_HEIGHT) {
      p->pows[i].active = false;
    }
    if ((p->pows[i].active && (p->pows[i].rect.y + p->pows[i].rect.h < WINDOW_HEIGHT) && pl->rect.y + pl->rect.h <= ( (float) WINDOW_HEIGHT/ 5))) {
      printf("Seguimiento al jugador activado");
      p->pows[i].follow = true;
      //Hacer una transición suave
    }
    if (p->pows[i].follow) {
      if (p->pows[i].rect.x < pl->rect.x ) {
        p->pows[i].rect.x +=10;
      }
      else if (p->pows[i].rect.x > pl->rect.x) {
        p->pows[i].rect.x -=10;
      } else if (p->pows[i].rect.x == pl->rect.x) {

      }
      if (p->pows[i].rect.y < pl->rect.y ) {
        p->pows[i].rect.y +=10;
      }
      else if (p->pows[i].rect.y > pl->rect.y) {
        p->pows[i].rect.y -=10;
      }
      p->pows[i].pw_x = p->pows[i].rect.x;
      p->pows[i].pw_y = p->pows[i].rect.y;
    }
    else if (!p->pows[i].active){
      p->pows[i].rect.x = p->pows[i].pw_x;
      p->pows[i].rect.y = p->pows[i].pw_y;
      // printf("Esta es mi posición X: %f \n", p->pows[i].rect.x);
      // printf("Esta es mi posición Y: %f \n", p->pows[i].rect.y);
    }
  }




}
void power_draw(struct Power *p, struct Enemy *e) {
    //Establecer cooldown de hasta 1000 ms para que vuelva a ser dibujado
    for (int i = 0; i < e->quantity; i++) {
      if (p->pows[i].active && p->pows[i].rect.y + p->pows[i].rect.h <= WINDOW_HEIGHT) {
        SDL_RenderTexture(p->renderer, p->image, NULL, &p->pows[i].rect);
      }
    }



}
void power_free(struct Power **power) {
  if (*power) {
    struct Power *p = *power;
    if (p->image) {
      SDL_DestroyTexture(p->image);
      p->image = NULL;
    }
    if (p->surf) {
      SDL_DestroySurface(p->surf);
      p->surf = NULL;
    }
    if (p->power) {
      MIX_DestroyAudio(p->power);
    }
    if (p->track) {
      MIX_DestroyTrack(p->track);
    }
    p->renderer = NULL;
    free(p);
    p = NULL;
    *power = NULL;
    printf("Free Power. \n");

  }
}
void spawn_power(struct Power *p, struct Enemy *e) {
  //Posible problema de consumo excesivo de CPU
  if (p->surf) SDL_DestroySurface(p->surf);
  if (p->image) SDL_DestroyTexture(p->image);
  p->surf= IMG_Load("assets/objects/power.png");
  p->image = SDL_CreateTextureFromSurface(p->renderer, p->surf);
}

void power_sound(struct Power *p, struct Music *m) {
  if (p->power ) {
    MIX_DestroyAudio(p->power);
    p->power = NULL;
  }
  if (p->track) {
    MIX_DestroyTrack(p->track);
    p->track = NULL;
  }
  p->now = SDL_GetTicks();
  p->power = MIX_LoadAudio(m->mixer, "music/sfx/power.wav", true);
  if (!p->power) {
    SDL_Log("Error al cargar el audio: %s", SDL_GetError());
    MIX_DestroyMixer(p->mixer);
    return ;
  }


  p->track = MIX_CreateTrack(m->mixer);
  if (!p->track) {
    SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
    MIX_DestroyAudio(p->power);
    p->power = NULL;
    return ;
  }

//Revisar como volver independiente esta sección para cada objeto
  MIX_SetTrackAudio(p->track, p->power);
  //Esta condicional no se cumple siempre.
  if (p->power_sound == false) {
    p->i++;
    printf("Esto pasó! %d veces", p->i);
    MIX_PlayTrack(p->track, 0);
    p->power_sound = true;
    p->play_time = (float) p->now + 500;
  }
}