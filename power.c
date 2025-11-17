//
// Created by gogphojoh on 11/16/25.
//
#include "power.h"

bool power_new(struct Power **power, SDL_Renderer *renderer) {
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
  p->surf= IMG_Load("power.png");
  if (!p->surf) {
    fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
    return false;
  }
  p->image = SDL_CreateTextureFromSurface(p->renderer, p->surf);
  if (!p->image) {
    fprintf(stderr,"Error al crear la imagen: %s", SDL_GetError());
    return false;
  }


  SDL_GetTextureSize(p->image,&p->rect.w,&p->rect.h);
  p->active = false;
  return true;
}
void power_update(struct Power *p, struct Enemy *e, struct Player *pl) {
  if (p->active && p->rect.y + p->rect.h < WINDOW_HEIGHT) {
    spawn_power(p, e);
    power_draw(p,e);
    p->pw_y += POWER_VEL;
    p->rect.y = p->pw_y;
  }else if (p->active && p->rect.y + p->rect.h >= WINDOW_HEIGHT) {
    p->active = false;
  }
  else if (!p->active){
    p->rect.x = p->pw_x;
    p->rect.y = p->pw_y;
  }



}
void power_draw(struct Power *p, struct Enemy *e) {
    //Establecer cooldown de hasta 1000 ms para que vuelva a ser dibujado
    if (p->active && p->rect.y + p->rect.h <= WINDOW_HEIGHT) {
      SDL_RenderTexture(p->renderer, p->image, NULL, &p->rect);
    }


}
void power_free(struct Power **power) {
  if (*power) {
    struct Power *p = *power;
    if (p->image) {
      SDL_DestroyTexture(p->image);
      p->image = NULL;
    }
    p->renderer = NULL;
    free(p);
    p = NULL;
    *power = NULL;
    printf("Free Power. \n");

  }
}
void spawn_power(struct Power *p, struct Enemy *e) {
  p->surf= IMG_Load("power.png");
  p->image = SDL_CreateTextureFromSurface(p->renderer, p->surf);
}

void power_sound(struct Power *p, struct Music *m) {
  p->now = SDL_GetTicks();
  p->power = MIX_LoadAudio(m->mixer, "power.wav", true);
  if (!p->power) {
    SDL_Log("Error al cargar el audio: %s", SDL_GetError());
    MIX_DestroyMixer(p->mixer);
    return ;
  }


  p->track = MIX_CreateTrack(m->mixer);
  if (!p->track) {
    SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
    MIX_DestroyAudio(p->power);
    MIX_DestroyMixer(p->mixer);
    return ;
  }


  MIX_SetTrackAudio(p->track, p->power);
  if (p->power_sound == false) {
    MIX_PlayTrack(p->track, 0);
    p->power_sound = true;
    p->play_time = (float) p->now + 1000;
  }else if (p->power_sound == true && p->play_time < p ->now ) {
    p->power_sound = false;
  }
}