//
// Created by gogphojoh on 11/10/25.
//
#include "scroll.h"

bool scroll_new (struct Scroll **scroll, SDL_Renderer *renderer) {
    *scroll = calloc(1, sizeof(struct Scroll));
    if (*scroll == NULL) {
        fprintf(stderr, "Error al realizar Calloc al crear el escenario.\n");
        return false;
    }

    struct Scroll *s = *scroll;
    s->renderer = renderer;

    s->image = IMG_LoadTexture(s->renderer, "assets/backgrounds/playzone.jpg");
    s->src= (SDL_FRect){0,0,750, 864};
    s->dst= (SDL_FRect) {75,53,750,864};
    if (!s->image) {
      fprintf(stderr, "Error al crear el fondo del juego: %s\n", SDL_GetError());
      return false;
    }
    s->image2 = IMG_LoadTexture(s->renderer, "assets/backgrounds/test.jpg");
    s->src2= (SDL_FRect){0,0,750, 864};
    s->dst2= (SDL_FRect) {75,-864,750,864};
    if (!s->image2) {
      fprintf(stderr, "Error al crear el fondo del juego: %s\n", SDL_GetError());
      return false;
    }

    return true;

}
void scroll_free(struct Scroll **scroll) {
        if (*scroll) {
        struct Scroll *s = *scroll;
        if (s->image) {
            SDL_DestroyTexture(s->image);
            s->image = NULL;
        }
        if (s->image2) {
            SDL_DestroyTexture(s->image2);
            s->image2 = NULL;
        }
        s->renderer = NULL;
        free(s);
        s = NULL;
        *scroll = NULL;
        printf("Free Scenario. \n");

    }
}
void scroll_update(struct Scroll *s) {
    
    //Esto podría considerarse como la primera versión completa del motor.
    
    if (s->dst.y >= 960) {
        SDL_DestroyTexture(s->image);
        s->image = NULL;
    } else if (s->dst2.y > -811) { //Punto exacto de colisión entre la primera y la segunda imagen (y = -864 + 53)
        s->dst.y += 1;
    } 

    if (s->dst2.y >= 53) { //Momento exacto en el que la imagen llega a la posición correcta. (la altura 53 es la esperada para el cambio de escenarios.)

    }else{
        s->dst2.y += 1;
    }

}

void scroll_draw(const struct Scroll *s) {
    SDL_RenderTexture(s->renderer,s->image,&s->src,&s->dst);  //El gran truco del telón móvil
    SDL_RenderTexture(s->renderer,s->image2,&s->src2,&s->dst2);
    
    
}
