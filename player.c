//
// Created by gogphojoh on 11/10/25.
//
#include "player.h"
#include "bullet.h"


bool player_new (struct Player **player, SDL_Renderer *renderer) {
    *player = calloc(1, sizeof(struct Player));
    if (*player == NULL) {
        fprintf(stderr, "Error al realizar Calloc para crear al jugador.\n");
        return false;
    }

    struct Player *p = *player;

    p->renderer = renderer;

    p->image = IMG_LoadTexture(p->renderer, "marisa.png");
    if (!p->image) {
        fprintf(stderr, "Error al crear la imagen del jugador: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_GetTextureSize(p->image,&p->rect.w,&p->rect.h)) {
        fprintf(stderr, "Error al obtener las medidas de la imagen: %s\n", SDL_GetError());
        return false;
    }

    p->keystate = SDL_GetKeyboardState(NULL);


    // if (!SDL_SetTextureScaleMode(p->image, SDL_SCALEMODE_NEAREST)) {
    //     fprintf(stderr, "Error al establecer la modalidad de escalado de la textura: %s\n", SDL_GetError());
    //     return false;
    // }

    return true;
}
void player_free(struct Player **player) {

    if (*player) {
        struct Player *p = *player;
        if (p->image) {
            SDL_DestroyTexture(p->image);
            p->image = NULL;
        }
        p->renderer = NULL;
        free(p);
        p = NULL;
        *player = NULL;
        printf("Free Player. \n");

    }

}
void player_update(struct Player *p, struct Bullet *b) {
    if (p->keystate[SDL_SCANCODE_LEFT]) {
        p->rect.x -= PLAYER_VEL;
    }
    if (p->keystate[SDL_SCANCODE_RIGHT]) {
        p->rect.x += PLAYER_VEL;
    }
    if (p->keystate[SDL_SCANCODE_UP]) {
        p->rect.y -= PLAYER_VEL;
    }
    if (p->keystate[SDL_SCANCODE_DOWN]) {
        p->rect.y += PLAYER_VEL;
    }
    b->p_x = p->rect.x;
    b->p_y = p->rect.y;
}
void player_draw(const struct Player *p) {
    SDL_RenderTexture(p->renderer, p->image, NULL, &p->rect);

}