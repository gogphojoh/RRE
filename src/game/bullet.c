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

    for (int i = 0; i < MAX_BULLETS; i++) {

      //Iteración de balas del jugador
      b->bullets[i].surf= IMG_Load("assets/objects/bullet.png");
      if (!b->bullets[i].surf) {
        fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
        return false;
      }
      b->bullets[i].image = SDL_CreateTextureFromSurface(b->renderer, b->bullets[i].surf);
      if (!b->bullets[i].image) {
        fprintf(stderr,"Error al crear la imagen: %s", SDL_GetError());
        return false;
      }

      SDL_GetTextureSize(b->bullets[i].image,&b->rect.w,&b->rect.h);

      //Iteración de enemigos

      b->ebullets[i].surf= IMG_Load("assets/objects/ebullet.png");
      if (!b->ebullets[i].surf) {
        fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
        return false;
      }
      b->ebullets[i].image = SDL_CreateTextureFromSurface(b->renderer, b->ebullets[i].surf);
      if (!b->ebullets[i].image) {
        fprintf(stderr,"Error al crear la imagen: %s", SDL_GetError());
        return false;
      }

      SDL_GetTextureSize(b->ebullets[i].image,&b->ebullets[i].rect.w,&b->ebullets[i].rect.h);
    }

    return true;
}

//Estudiarlo
void bullet_free(struct Bullet **bullet) {

    if (*bullet) {
        struct Bullet *b = *bullet;
      for (int i = 0; i < MAX_BULLETS; i++) {
        if (b->bullets[i].image) {
          SDL_DestroyTexture(b->bullets[i].image);
          b->bullets[i].image = NULL;
        }
      }
        b->renderer = NULL;
        free(b);
        *bullet = NULL;
        printf("All bullets clear! \n");
    }
}

//Estudiar
void bullet_update(struct Bullet *b, struct Enemy *e, struct Power *p, struct Music *m, struct Player *pl, struct Text *t, struct Bomb *bo) {
    Uint32 now = SDL_GetTicks();
    e->now = SDL_GetTicks();



    for (int i = 0; i < MAX_BULLETS; i++) {
      b->bcount = i;



      if (b->keystate[SDL_SCANCODE_Z] && now >= b->next_fire_time && pl->active) {
        b->bullets[i].btype = 1;
        player_bullets(b);
        b->next_fire_time = now + BULLET_DELAY;
      }


      //Tengo que aplicar un nuevo array de balas especifico para los enemigos.
      if (e->enemies[i].active && !b->ebullets[i].active) {
        b->index = i;
        enemy_bullet(b,e);
        e->enemies[i].fire_rate = now + 500;
      }

      if (b->ebullets[i].active) {
        b->ebullets[i].rect.y += ENEMY_BULLET_VEL;
        if (b->ebullets[i].rect.y + b->ebullets[i].rect.h > WINDOW_HEIGHT) {
          b->ebullets[i].active = false;
        }

        if (pl->active && rects_collide(&b->ebullets[i].rect, &pl->rect) && now > pl->invulnerability ) {
          //e->spawn_time = e->now + 1000;
          b->ebullets[i].active = false;   // desactivar bala
          pl->active = false;// desactivar al jugador
          pl->spawn = now + 1000;
          pl->invulnerability = now + 1500;
          //Agregar sonido de muerte


        }

        if (bo->active && rects_collide(&b->ebullets[i].rect, &bo->rect) ) {
          //e->spawn_time = e->now + 1000;
          b->ebullets[i].active = false;   // desactivar bala
        }


      }

        if (b->bullets[i].active) {
            b->bullets[i].rect.y -= BULLET_VEL;
            if (b->bullets[i].rect.y + b->bullets[i].rect.h < 0) {
                b->bullets[i].active = false;
            }
          for (int j = 0; j < e->quantity; j++) {
            //lógica de disparo del enemigo.
            if (!e->enemies[j].active) continue;

            //lógica de impacto en el enemigo
            if (e->enemies[j].active && rects_collide(&b->bullets[i].rect, &e->enemies[j].rect)) {
              // e->spawn_time = e->now + 1000;
              b->bullets[i].active = false;   // desactivar bala
              e->enemies[j].health -= 10;// desactivar enemigo
              if (e->enemies[j].health < 1) {
                e->enemies[j].active = false;
                p->pows[j].active = true;
                p->pows[j].up = true;
                p->pows[j].type = e->enemies[j].type; //El enemigo y el pow ya coinciden -- Solo para la generación del power up, el sonido aun sigue fuera de lugar.
                p->pows[j].ascention = e->now + 500; //La activación del power debe coincidir con el del enemigo
                p->appear = j;
                play_sound(e,m);
              }

              // e->image = NULL;
              // SDL_DestroyTexture(e->image);// destruir textura

            }
          }

        }

      if (b->bullets[i].active) {
        b->bullets[i].rect.y -= BULLET_VEL;
        if (b->bullets[i].rect.y + b->bullets[i].rect.h < 0) {
          b->bullets[i].active = false;
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
            SDL_RenderTexture(b->renderer, b->bullets[i].image, NULL, &b->bullets[i].rect);

        }
        if (b->ebullets[i].active) {
          //printf ("He sido dibujado %d veces", i);
          SDL_RenderTexture(b->renderer, b->ebullets[i].image, NULL, &b->ebullets[i].rect);

        }
    }
}

void player_bullets (struct Bullet *b) {
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
  b->bullets[first].rect.x = b->p_x + 12;
  b->bullets[first].rect.y = b->p_y;
  b->bullets[first].rect.w = b->rect.w;
  b->bullets[first].rect.h = b->rect.h;
  b->bullets[first].active = true;
  b->bullets[first].hit = 10;


  // Bala izquierda
  b->bullets[second].rect.x = b->p_x - 6;
  b->bullets[second].rect.y = b->p_y;
  b->bullets[second].rect.w = b->rect.w;
  b->bullets[second].rect.h = b->rect.h;
  b->bullets[second].active = true;
  b->bullets[first].hit = 10;

  //Acá recién se crea un dato válido para la bala

}

void enemy_bullet (struct Bullet *b, struct Enemy *e) {
  //printf("Disparo del enemigo %d registrado! \n", b->index);
  b->ebullets[b->index].rect.x = e->enemies[b->index].rect.x;
  b->ebullets[b->index].rect.y =  e->enemies[b->index].rect.y;
  b->ebullets[b->index].rect.w = b->ebullets[b->index].rect.w;
  b->ebullets[b->index].rect.h = b->ebullets[b->index].rect.h;
  b->ebullets[b->index].active = true;


}