//
// Created by gogphojoh on 11/25/25.
//
//
// Created by gogphojoh on 11/13/25.
//

#include "bomb.h"

//MEJOR SIGUE LA LÓGICA QUE YA ESTÁ EN PLAYER.C !!!! <-no es necesario
//!Lmao, nunca olvides inicializar el bomb_new en game_new. dentro de game.c

bool bomb_collide(SDL_FRect *a, SDL_FRect *b) {
  return (a->x < b->x + b->w &&
          a->x + a->w > b->x &&
          a->y < b->y + b->h &&
          a->y + a->h > b->y);
}

bool bomb_new (struct Bomb **bomb, SDL_Renderer *renderer) {
    *bomb = calloc (1, sizeof (struct Bomb));
    if (!(*bomb)) {
        fprintf(stderr,"Error al guardar en la memoria la bala: %s", SDL_GetError());
        return false;
    }
    struct Bomb *b = *bomb;
    b->renderer = renderer;
    b->keystate = SDL_GetKeyboardState(NULL);
    if (!b->renderer) {
        fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
        return false;
    }



      //Iteración de balas del jugador
      b->surf= IMG_Load("assets/objects/spark.png");
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
void bomb_free(struct Bomb **bomb){

    if (*bomb) {
        struct Bomb *b = *bomb;
      for (int i = 0; i < MAX_BULLETS; i++) {
        if (b->image) {
          SDL_DestroyTexture(b->image);
          b->image = NULL;
        }
      }
        b->renderer = NULL;
        free(b);
        *bomb = NULL;
        printf("All bullets clear! \n");
    }
}

//Estudiar
void bomb_update(struct Bomb *b, struct Enemy *e, struct Power *p, struct Music *m, struct Bullet *bu,struct Player *pl, struct Text *t) {
    Uint32 now = SDL_GetTicks();




      if (b->keystate[SDL_SCANCODE_X] && !b->active && t->bomb_count > 0) {
        player_bombs(b, bu);
        bomb_sound(b, m);
        pl->invulnerability = now + 5000;
        b->active = true;
        b->action_time = now + BOMB_DURATION;
        t->bomb_count -= 1;
        tbomb_update(t);
      }


      //Tengo que aplicar un nuevo array de balas especifico para los enemigos.


        if (b->active) {

          b->rect.x = bu->p_x - (b->rect.w / 2) + 15;
          b->rect.y = bu->p_y - (b->rect.h);
            if (now > b->action_time) {
                b->active = false;
            }
          for (int j = 0; j < e->quantity; j++) {
            //lógica de disparo del enemigo.
            if (!e->enemies[j].active) continue;

            //lógica de impacto en el enemigo
            if (e->enemies[j].active && bomb_collide(&b->rect, &e->enemies[j].rect)) {
              // e->spawn_time = e->now + 1000;
              e->enemies[j].health -= b->hit;// desactivar enemigo
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



}

// b->rect.x = b->p_x;
// b->rect.y = b->p_y;

//Estudiar
void bomb_draw(const struct Bomb *b) {
        if (b->active) {
            SDL_RenderTexture(b->renderer, b->image, NULL, &b->rect);
        }
}

void player_bombs (struct Bomb *b, struct Bullet *bu) {

  // Bala derecha

  b->rect.w = 550;
  b->rect.h = 1000;
  b->rect.x = bu->p_x - (b->rect.w / 2) +15 ;
  b->rect.y = bu->p_y - (b->rect.h);
  b->active = true;
  b->hit = 100;



}

void bomb_sound (struct Bomb *b, struct Music *m) {

  if (b->bomb ) {
    MIX_DestroyAudio(b->bomb);
    b->bomb = NULL;
  }
  if (b->track ) {
    MIX_DestroyTrack(b->track);
    b->track = NULL;
  }

  b->bomb = MIX_LoadAudio(m->mixer, "music/sfx/spark.mp3", true);
  if (!b->bomb) {
    SDL_Log("Error al cargar el audio: %s", SDL_GetError());
    return ;
  }
  b->track = MIX_CreateTrack(m->mixer);
  if (!b->track) {
    SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
    return ;
  }


  MIX_SetTrackAudio(b->track, b->bomb);
  MIX_PlayTrack(b->track, 0);
}

