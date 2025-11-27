//
// Created by gogphojoh on 11/10/25.
//
#include "player.h"
#include "bullet.h"

bool power_collide(SDL_FRect *a, SDL_FRect *b) {
  return (a->x < b->x + b->w &&
          a->x + a->w > b->x &&
          a->y < b->y + b->h &&
          a->y + a->h > b->y);
}

bool player_new (struct Player **player, SDL_Renderer *renderer) {
    *player = calloc(1, sizeof(struct Player));
    if (*player == NULL) {
        fprintf(stderr, "Error al realizar Calloc para crear al jugador.\n");
        return false;
    }

    struct Player *p = *player;

    p->renderer = renderer;

    p->image = IMG_LoadTexture(p->renderer, "assets/sprites/marisa_idle.png");
    if (!p->image) {
        fprintf(stderr, "Error al crear la imagen del jugador: %s\n", SDL_GetError());
        return false;
    }

    // if (!SDL_GetTextureSize(p->image,&p->rect.w,&p->rect.h)) {
    //     fprintf(stderr, "Error al obtener las medidas de la imagen: %s\n", SDL_GetError());
    //     return false;
    // }

    p->src = (SDL_FRect){0,0,26,44};
    p->rect = (SDL_FRect) {500,500,26,44};

    p->keystate = SDL_GetKeyboardState(NULL);
    p->pv = PLAYER_VEL;
    p->active = true;

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
void player_update(struct Player *p, struct Bullet *b, struct Power *pw, struct Music *m, struct Enemy *e, struct Text *t, struct Bomb *bo) {
  Uint32 now = SDL_GetTicks();




  if (p->active) {
    if (now > p->frame_time) {
      //De momento el switch parece ser la cosa más potable por ahora.
      animation_update(p);
      p->frame_time = now + 96;
    }

    p->sound_played = false;
    if (p->keystate[SDL_SCANCODE_LEFT]) {
      p->rect.x -= p->pv;
    }
    if (p->keystate[SDL_SCANCODE_RIGHT]) {
      p->rect.x += p->pv;
    }
    if (p->keystate[SDL_SCANCODE_UP]) {
      p->rect.y -= p->pv;
    }
    if (p->keystate[SDL_SCANCODE_DOWN]) {
      p->rect.y += p->pv;
    }
    if ((p->keystate[SDL_SCANCODE_LSHIFT ]) || p->keystate[SDL_SCANCODE_RSHIFT]) {
      p->pv = FOCUS_VEL;
    }else if (bo->active) {
      p->pv = BOMB_VEL;
    }
    else{
      p->pv = PLAYER_VEL;
    }
    for (int i = 0; i < e->quantity; i++) {
      if (pw->pows[i].active && power_collide(&p->rect, &pw->pows[i].rect)) {
        if (pw->pows[i].power_sound == true ) {
          pw->pows[i].power_sound = false;
        }
        pw->grab = i;
        power_sound(pw, m,e,t);
        pw->pows[i].active = false;// desactivar power
        pw->pows[i].follow = false;
        // SDL_DestroyTexture(pw->image);
        // pw->image = NULL;
      }
      b->p_x = p->rect.x;
      b->p_y = p->rect.y;
      b->p_x = p->rect.x;
      b->p_y = p->rect.y;
    }

  }
  if (!p->active & !p->sound_played){
    player_death(p,m);
    t->lives -= 1;
    live_update(t);
  }
  if (!p->active &&  now >= p->spawn && t->lives > 0) {
    p->active = true;
  }

}
void player_draw(const struct Player *p) {
  if (p->active) {
    SDL_RenderTexture(p->renderer, p->image, &p->src, &p->rect);
  }



}

void player_death (struct Player *p, struct Music *m) {

  if (p->death ) {
    MIX_DestroyAudio(p->death);
    p->death = NULL;
  }
  if (p->track ) {
    MIX_DestroyTrack(p->track);
    p->track = NULL;
  }

  p->death = MIX_LoadAudio(m->mixer, "music/sfx/dead.mp3", true);
  if (!p->death) {
    SDL_Log("Error al cargar el audio: %s", SDL_GetError());
    return ;
  }
  p->track = MIX_CreateTrack(m->mixer);
  if (!p->track) {
    SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
    return ;
  }


  MIX_SetTrackAudio(p->track, p->death);
  MIX_PlayTrack(p->track, 0);
  p->sound_played = true;
}

void animation_update (struct Player *p) {
  p->frame_count += 1;
  if (p->frame_count > 8) {
    p->frame_count = 1;
  }
  switch (p->frame_count) {
  case 1:
    p->src = (SDL_FRect){0,0,26,44};
    break;
  case 2:
    p->src = (SDL_FRect){32,0,26,44};
    break;
  case 3:
    p->src = (SDL_FRect){64,0,26,44};
    break;
  case 4:
    p->src = (SDL_FRect){96,0,26,44};
    break;
  case 5:
    p->src = (SDL_FRect){128,0,26,44};
    break;
  case 6:
    p->src = (SDL_FRect){160,0,26,44};
    break;
  case 7:
    p->src = (SDL_FRect){192,0,26,44};
    break;
  case 8:
    p->src = (SDL_FRect){224,0,26,44};
    break;
  default:
    p->src = (SDL_FRect){0,0,26,44};
    break;
  }
}