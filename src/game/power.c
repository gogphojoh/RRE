//
// Created by gogphojoh on 11/16/25.
//
#include "power.h"

//Problemas con el seguimiento al jugador y con el dibujado de posiciones distintas.
//!La primera vez que tomas un power, sin importar el enemigo, se reproducen ambos audios. Interesante, ¿No?

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

  for (int i = 0; i < e->quantity; i++) {
    //Por algún motivo este ternario lo soluciona todo???
    //Al parecer p->pows[i].type se estaba estableciendo mal y fue el culpable todo este condenado tiempo
    p->pows[i].type = 1;
    p->pows[i].type = (i%2 == 0) ? 1:2;
    // switch (p->pows[i].type) {
    // case 1 :
    //   p->pows[i].object = "assets/objects/power.png";
    //   break;
    // case 2:
    //   p->pows[i].object = "assets/objects/points.png";
    //   break;
    // default:
    //   p->pows[i].object = "assets/objects/bullets.png";
    //
    // }

    p->pows[i].object = "assets/objects/points.png";
    p->pows[i].surf= IMG_Load(p->pows[i].object);
    if (!p->pows[i].surf) {
      fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
      return false;
    }
    p->pows[i].image = SDL_CreateTextureFromSurface(p->renderer, p->pows[i].surf);
    if (!p->pows[i].image) {
      fprintf(stderr,"Error al crear la imagen: %s", SDL_GetError());
      return false;
    }



    for (int i = 0; i < e->quantity; i++) {
      p->pows[i].active = false;
      //Tienes que definir todos los parametros, sobre todo si son objetos de arrays que se dibujan varias veces.
      SDL_GetTextureSize(p->pows[i].image,&p->pows[i].rect.w,&p->pows[i].rect.h);
    }

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
        SDL_RenderTexture(p->renderer, p->pows[i].image, NULL, &p->pows[i].rect);
      }
    }



}
void power_free(struct Power **power, struct Enemy *e) {
  if (*power) {
    struct Power *p = *power;
    for (int i = 0; i < e->quantity; i++ ) {
      if (p->pows[i].image) {
        SDL_DestroyTexture(p->pows[i].image);
        p->pows[i].image = NULL;
      }
      if (p->pows[i].surf) {
        SDL_DestroySurface(p->pows[i].surf);
        p->pows[i].surf = NULL;
      }
      if (p->pows[i].power) {
        MIX_DestroyAudio(p->pows[i].power);
      }
      if (p->pows[i].track) {
        MIX_DestroyTrack(p->pows[i].track);
      }
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
  for (int i = 0; i < e->quantity; i++ ) {
    if (p->pows[i].surf) SDL_DestroySurface(p->pows[i].surf);
    if (p->pows[i].image) SDL_DestroyTexture(p->pows[i].image);
    switch (p->pows[i].type) {
    case 1:
      p->pows[i].object = "assets/objects/power.png";
      break;
    case 2:
      p->pows[i].object = "assets/objects/points.png";
      break;
    default:
      p->pows[i].object = "assets/objects/bullet.png";
      break;
    }
    p->pows[i].surf= IMG_Load(p->pows[i].object);
    p->pows[i].image = SDL_CreateTextureFromSurface(p->renderer, p->pows[i].surf);
  }

}

//Cuando se cargan todos los audios, rompen los timpanos por que el mismo audio se reproduce una cantidad infinita de veces, lo que hace que te dañen los timpanos
void power_sound(struct Power *p, struct Music *m, struct Enemy *e) {

  p->now = SDL_GetTicks();
  for (int i = 0; i < e->quantity; i++) {
    if (p->pows[i].power ) {
      MIX_DestroyAudio(p->pows[i].power);
      p->pows[i].power = NULL;
    }
    if (p->pows[i].track) {
      MIX_DestroyTrack(p->pows[i].track);
      p->pows[i].track = NULL;
    }
    switch (p->pows[i].type) {
    case 1:
      p->pows[i].music = "music/sfx/power.mp3";
      break;
    case 2:
      p->pows[i].music = "music/sfx/point.mp3";
      break;
    case 3:
      p->pows[i].music = "music/sfx/bullet.wav";

    }


    p->pows[i].power = MIX_LoadAudio(m->mixer, p->pows[i].music, true);
    if (!p->pows[i].power) {
      SDL_Log("Error al cargar el audio: %s", SDL_GetError());
      MIX_DestroyMixer(p->mixer);
      return ;
    }


    p->pows[i].track = MIX_CreateTrack(m->mixer);
    if (!p->pows[i].track) {
      SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
      MIX_DestroyAudio(p->pows[i].power);
      p->pows[i].power = NULL;
      return ;
    }

    //Revisar como volver independiente esta sección para cada objeto
    MIX_SetTrackAudio(p->pows[i].track, p->pows[i].power);
    //Esta condicional no se cumple siempre.
    //El problema podría deberse a que el comprobante de sonido es universal y no un objeto como habría de esperar.
    if (p->pows[i].power_sound == false) {
      p->i++;
      printf("Esto pasó! %d veces", p->i);
      MIX_PlayTrack(p->pows[i].track, 0);
      p->pows[i].power_sound = true;
      p->play_time = (float) p->now + 100;
    }

  }

}