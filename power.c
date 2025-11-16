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
  return true;
}
void power_update(struct Power *p, struct Enemy *e) {
  p->rect.x = p->pw_x;
  p->rect.y = p->pw_y;

}
void power_draw(struct Power *p) {
  if (p->active) {
    SDL_RenderTexture(p->renderer, p->image, NULL, &p->rect);
  }

}
void power_free(struct Power **power) {

}
void spawn_power(struct Power *p, struct Enemy *e) {
  p->surf= IMG_Load("power.png");
  p->image = SDL_CreateTextureFromSurface(p->renderer, p->surf);
}

