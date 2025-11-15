//
// Created by gogphojoh on 11/13/25.
//

#include "bullet.h"
#include "player.h"

//MEJOR SIGUE LA LÓGICA QUE YA ESTÁ EN PLAYER.C !!!! <-no es necesario
//!Lmao, nunca olvides inicializar el bullet_new en game_new. dentro de game.c

bool rects_collide(SDL_FRect *a, SDL_FRect *b) {
  return (a->x < b->x + b->w &&
          a->x + a->w > b->x &&
          a->y < b->y + b->h &&
          a->y + a->h > b->y);
}




bool bullet_new (struct Bullet **bullet, SDL_Renderer *renderer) {
    *bullet = calloc (1, sizeof (struct Bullet));
    if (!(*bullet)) {
        fprintf(stderr,"Error al guardar en la memoria la bala: %s", SDL_GetError());
        return false;
    }
    struct Bullet *b = *bullet;
    b->renderer = renderer;
    b->keystate = SDL_GetKeyboardState(NULL);
    b->next_fire_time = 0;
    if (!b->renderer) {
        fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
        return false;
    }
    b->surf= IMG_Load("bullet.png");
    if (!b->surf) {
        fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
        return false;
    }
    b->image = SDL_CreateTextureFromSurface(b->renderer, b->surf);
    if (!b->image) {
        fprintf(stderr,"Error al crear la imagen: %s", SDL_GetError());
        return false;
    }

    SDL_GetTextureSize(b->image,&b->rect.w,&b->rect.h);
    return true;
}

//Estudiarlo
static void spawn_bullet(struct Bullet *b, struct Enemy *e) {
    int first = -1;
    int second = -1;

    // Busca dos slots libres
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!b->bullets[i].active) {
            if (first == -1) first = i;
            else {
                second = i;
                break;
            }
        }
    }

    // Si no hay suficientes slots, no dispares
    if (first == -1 || second == -1) return;

    // Bala derecha
    b->bullets[first].rect.x = b->p_x + 6;
    b->bullets[first].rect.y = b->p_y;
    b->bullets[first].rect.w = b->rect.w;
    b->bullets[first].rect.h = b->rect.h;
    b->bullets[first].active = true;


    // Bala izquierda
    b->bullets[second].rect.x = b->p_x - 6;
    b->bullets[second].rect.y = b->p_y;
    b->bullets[second].rect.w = b->rect.w;
    b->bullets[second].rect.h = b->rect.h;
    b->bullets[second].active = true;

    //Acá recién se crea un dato válido para la bala


}

void bullet_free(struct Bullet **bullet) {
    if (*bullet) {
        struct Bullet *b = *bullet;
        if (b->image) {
            SDL_DestroyTexture(b->image);
            b->image = NULL;
        }
        b->renderer = NULL;
        free(b);
        *bullet = NULL;
        printf("All bullets clear! \n");
    }
}

//Estudiar
void bullet_update(struct Bullet *b, struct Enemy *e) {
    Uint32 now = SDL_GetTicks();

    if (b->keystate[SDL_SCANCODE_Z] && now >= b->next_fire_time) {
        spawn_bullet(b,e);
        b->next_fire_time = now + BULLET_DELAY;
    }

    for (int i = 0; i < MAX_BULLETS; i++) {

        if (b->bullets[i].active) {
            b->bullets[i].rect.y -= BULLET_VEL;
            if (b->bullets[i].rect.y + b->bullets[i].rect.h < 0) {
                b->bullets[i].active = false;
            }
            if (e->active && rects_collide(&b->bullets[i].rect, &e->rect)) {
              b->bullets[i].active = false;   // desactivar bala
              e->active = false;              // desactivar enemigo
              SDL_DestroyTexture(e->image);   // destruir textura
            }
        }


    }
}

// b->rect.x = b->p_x;
// b->rect.y = b->p_y;

//Estudiar
void bullet_draw (struct Bullet *b) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (b->bullets[i].active) {
            SDL_RenderTexture(b->renderer, b->image, NULL, &b->bullets[i].rect);

        }
    }
}
