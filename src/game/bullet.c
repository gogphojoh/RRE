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
      b->bullets[i].surf= IMG_Load("assets/objects/bullet_sheet.png");
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
      //printf("Esta es la anchura %f, y la altura: %f \n", b->rect.w,b->rect.h);
      b->bullets[i].src = (SDL_FRect){0,114,16,32};
      b->rect = (SDL_FRect) {0,0,16,32};
      
      //Iteración para el laser
      b->laser[i].surf= IMG_Load("assets/objects/marisa-laser.png");
      if (!b->laser[i].surf) {
        fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
        return false;
      }
      b->laser[i].image = SDL_CreateTextureFromSurface(b->renderer, b->laser[i].surf);
      if (!b->laser[i].image) {
        fprintf(stderr,"Error al crear la imagen: %s", SDL_GetError());
        return false;
      }

      SDL_GetTextureSize(b->laser[i].image,&b->laser[i].rect.w,&b->laser[i].rect.h);

      b->laser[i].src = (SDL_FRect){0,0,18,64};
      b->laser[i].rect = (SDL_FRect) {0,0,18,64};
      //b->laser[i].rect.x = -5000;
      //b->laser[i].rect.y = -5000;

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
        SDL_DestroySurface(b->bullets[i].surf);
        SDL_DestroyTexture(b->ebullets[i].image);
        SDL_DestroySurface(b->ebullets[i].surf);
          b->bullets[i].image = NULL;
          b->bullets[i].surf = NULL;
          b->ebullets[i].image = NULL;
          b->ebullets[i].surf = NULL;
          b->renderer = NULL;
        }
      }
      

        free(b);
        *bullet = NULL;
        printf("All bullets clear! \n");
    }
}

//Estudiar
void bullet_update(struct Bullet *b, struct Enemy *e, struct Power *p, struct Music *m, struct Player *pl, struct Text *t, struct Bomb *bo) {
    Uint32 now = SDL_GetTicks();
    e->now = SDL_GetTicks();
    //Desactivar laser luego de un tiempo.
    if(now > b->time_active || !pl->active){
    for (int i = 0; i < 128; i++)
    {
      b->laser[i].active = false;
      b->laser[i].rect.x = -5000;
      b->laser[i].rect.y = -5000;
      SDL_DestroyTexture(b->laser[i].image);
      SDL_DestroySurface(b->laser[i].surf);
      b->laser[i].surf= NULL;
      b->laser[i].image = NULL;
    }
    }else{
    for (int i = 0; i < 16; i++)
    {
      //Revisar si puedo hacer que el rayo se vea menos raro. y hacer que se mueva.
      b->laser[0].rect.w = b->laser[0].rect.w;
      b->laser[0].rect.h = b->laser[0].rect.h;
      b->laser[0].rect.x = (b->p_x + b->p_w/2) - 7;
      b->laser[0].rect.y =  b->p_y - b->laser[0].rect.h;
      b->laser[i].rect.x = (b->p_x + b->p_w/2) - 7;
      b->laser[i].rect.y = b->laser[0].rect.y - (i * 64);
    }
      /*
      b->laser[1].rect.x = (b->p_x + b->p_w/2) - 7;
      b->laser[1].rect.y =  b->p_y - b->laser[1].rect.h;
      b->laser[2].rect.x = (b->p_x + b->p_w/2) - 28;
      b->laser[2].rect.y =  b->p_y - b->laser[2].rect.h;
      b->laser[3].rect.x = (b->p_x + b->p_w/2)+ 14;
      b->laser[3].rect.y =  b->p_y - b->laser[3].rect.h;*/
    }


    for (int i = 0; i < MAX_BULLETS; i++) {
      b->bcount = i;
      if (b->bullets[i].impact && now > b->bullets[i].frame_time) {
        b->current_bullet = i;
        bullet_animation(b);
        b->bullets[i].frame_time = now + 7;
      }

    if (now > b->laser[i].frame_time) {
      b->current_laser = i;
      laser_animation(b);
      b->laser[i].frame_time = now + 32;
    }


      //Reacomodarlo para que el laser sea constante.
      if (b->keystate[SDL_SCANCODE_Z] && now >= b->next_fire_time && pl->active) {
        b->bullets[i].btype = 1;
        player_bullets(b);
        player_laser(b, t);
        b->next_fire_time = now + BULLET_DELAY;
        b->time_active = now + LASER_TTL;
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

        if (b->bullets[i].active && !b->bullets[i].impact) {
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
              // if (b->bullets[i].active = true) {
              //   b->current_bullet = i;
              //   bullet_animation(b);
              //   b->bullets[i].frame_time = now + 96;
              // }
                // desactivar bala
              e->enemies[j].angle_ring =  rand() %  340;
              b->bullets[i].impact = true;
              e->enemies[j].health -= 10;// desactivar enemigo
              if (e->enemies[j].health < 1) {
                SDL_DestroyTexture(e->enemies[j].image);
                SDL_DestroyTexture(e->enemies[j].image_aura);
                e->enemies[j].image = NULL;
                e->enemies[j].image_aura = NULL;
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

      if (b->bullets[i].active && !b->bullets[i].impact) {
        b->bullets[i].rect.y -= BULLET_VEL;
        if (b->bullets[i].rect.y + b->bullets[i].rect.h < 0) {
          b->bullets[i].active = false;
        }

      }

      for (int j = 0; j < e->quantity; j++) {
      //lógica de disparo del enemigo.
      if (!e->enemies[j].active) continue;

      //lógica de impacto de laser en el enemigo
      if (e->enemies[j].active && rects_collide(&b->laser[i].rect, &e->enemies[j].rect) && b->time_active > now && b->laser[i].active ) {
        e->enemies[j].angle_ring =  rand() %  340;
        e->enemies[j].health -= 10;// desactivar enemigo
        if (e->enemies[j].health < 1) {
          SDL_DestroyTexture(e->enemies[j].image);
          SDL_DestroyTexture(e->enemies[j].image_aura);
          e->enemies[j].image = NULL;
          e->enemies[j].image_aura = NULL;
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
void bullet_draw (struct Bullet *b) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (b->bullets[i].active) {
            SDL_RenderTexture(b->renderer, b->bullets[i].image, &b->bullets[i].src, &b->bullets[i].rect);

        }

        if (b->laser[i].active) {
            SDL_RenderTexture(b->renderer, b->laser[i].image, &b->laser[i].src, &b->laser[i].rect);

        }
        if (b->ebullets[i].active) {
          //printf ("He sido dibujado %d veces", i);
          SDL_RenderTexture(b->renderer, b->ebullets[i].image, NULL, &b->ebullets[i].rect);

        }
    }
}

void player_laser (struct Bullet *b, struct Text *t) {
  if(t->power_count >= 2){
    if(b->laser[0].surf == NULL){
    b->laser[0].surf= IMG_Load("assets/objects/marisa-laser.png");
    b->laser[0].image = SDL_CreateTextureFromSurface(b->renderer, b->laser[0].surf);
    SDL_GetTextureSize(b->laser[0].image,&b->laser[0].rect.w,&b->laser[0].rect.h);
    //Acá debo probar modificar los rayos de marisa.
    b->laser[0].src = (SDL_FRect){0,0,18,64};
    b->laser[0].rect = (SDL_FRect) {0,0,18,64};
    }

    b->laser[0].rect.w = b->laser[0].rect.w;
    b->laser[0].rect.h = b->laser[0].rect.h;
    b->laser[0].rect.x = (b->p_x + b->p_w/2) - 7;
    b->laser[0].rect.y =  b->p_y - b->laser[0].rect.h;
    b->laser[0].active = true;
    for (int i = 1; i < 32; i++)
    {
      if(b->laser[i].surf == NULL){
      b->laser[i].surf= IMG_Load("assets/objects/marisa-laser.png");
      b->laser[i].image = SDL_CreateTextureFromSurface(b->renderer, b->laser[i].surf);
      SDL_GetTextureSize(b->laser[i].image,&b->laser[i].rect.w,&b->laser[i].rect.h);
      //Acá debo probar modificar los rayos de marisa.
      b->laser[i].src = (SDL_FRect){0,0,18,64};
      b->laser[i].rect = (SDL_FRect) {0,0,18,64};
      }

      b->laser[i].rect.w = b->laser[i].rect.w;
      b->laser[i].rect.h = b->laser[i].rect.h;
      b->laser[i].rect.x = (b->p_x + b->p_w/2) - 7;
      b->laser[i].rect.y = b->laser[0].rect.y - (i * 64);
      b->laser[i].active = true;
    }

    

  }

  /*

    if(t->power_count >= 4){
    if(b->laser[2].surf == NULL){
    b->laser[2].surf= IMG_Load("assets/objects/marisa-laser.png");
    b->laser[2].image = SDL_CreateTextureFromSurface(b->renderer, b->laser[2].surf);
    SDL_GetTextureSize(b->laser[2].image,&b->laser[2].rect.w,&b->laser[2].rect.h);
    b->laser[2].src = (SDL_FRect){0,0,18,1000};
    b->laser[2].rect = (SDL_FRect) {0,0,18,1000};
    }

    b->laser[2].rect.w = b->laser[2].rect.w;
    b->laser[2].rect.h = b->laser[2].rect.h;
    b->laser[2].rect.x = (b->p_x + b->p_w/2) - 28;
    b->laser[2].rect.y =  b->p_y - b->laser[2].rect.h;
    b->laser[2].active = true;

  }

  if(t->power_count >= 5){
    if(b->laser[3].surf == NULL){
    b->laser[3].surf= IMG_Load("assets/objects/marisa-laser.png");
    b->laser[3].image = SDL_CreateTextureFromSurface(b->renderer, b->laser[3].surf);
    SDL_GetTextureSize(b->laser[3].image,&b->laser[3].rect.w,&b->laser[3].rect.h);
    b->laser[3].src = (SDL_FRect){0,0,18,1000};
    b->laser[3].rect = (SDL_FRect) {0,0,18,1000};
    }

    b->laser[3].rect.w = b->laser[3].rect.w;
    b->laser[3].rect.h = b->laser[3].rect.h;
    b->laser[3].rect.x = (b->p_x + b->p_w/2) + 14;
    b->laser[3].rect.y =  b->p_y - b->laser[3].rect.h;
    b->laser[3].active = true;

  }*/


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
  b->bullets[first].rect.x = b->p_x + 30;
  b->bullets[first].rect.y = b->p_y;
  b->bullets[first].rect.w = b->rect.w;
  b->bullets[first].rect.h = b->rect.h;
  b->bullets[first].active = true;
  b->bullets[first].hit = 10;
  b->bullets[first].src = (SDL_FRect){0,114,16,32};


  // Bala izquierda
  b->bullets[second].rect.x = b->p_x + 7;
  b->bullets[second].rect.y = b->p_y;
  b->bullets[second].rect.w = b->rect.w;
  b->bullets[second].rect.h = b->rect.h;
  b->bullets[second].active = true;
  b->bullets[second].hit = 10;
  b->bullets[second].src = (SDL_FRect){0,114,16,32};

  //Acá recién se crea un dato válido para la bala

}

void bullet_animation (struct Bullet *b) {
   b->bullets[b->current_bullet].frame_count += 1;
   if (b->bullets[b->current_bullet].frame_count > 4) {
     b->bullets[b->current_bullet].active = false;
     b->bullets[b->current_bullet].impact = false;
     b->bullets[b->current_bullet].frame_count = 0;
   }
  //Hina = 30 de anchura. 58 de altura
    switch (b->bullets[b->current_bullet].frame_count) {
      //48 pixeles de altura.
    case 1:
      b->bullets[b->current_bullet].src = (SDL_FRect){0,114,16,32};
      break;
    case 2:
      b->bullets[b->current_bullet].src = (SDL_FRect){0,80,16,32};
      break;
    case 3:
      b->bullets[b->current_bullet].src = (SDL_FRect){0,48,16,32};
      break;
    case 4:
      b->bullets[b->current_bullet].src = (SDL_FRect){0,16,16,32};
      break;
    default:
      b->bullets[b->current_bullet].src = (SDL_FRect){0,0,16,32};
      break;
    }


}

void laser_animation (struct Bullet *b) {
   b->laser[b->current_laser].frame_count += 1;
   if (b->laser[b->current_laser].frame_count > 4) {
     b->laser[b->current_laser].frame_count = 1;
   }
  //Hina = 30 de anchura. 58 de altura
    switch (b->laser[b->current_laser].frame_count) {
      //48 pixeles de altura.
    case 1:
      b->laser[b->current_laser].src = (SDL_FRect){0,192,18,64};
      break;
    case 2:
      b->laser[b->current_laser].src = (SDL_FRect){0,128,18,64};
      break;
    case 3:
      b->laser[b->current_laser].src = (SDL_FRect){0,64,18,64};
      break;
    case 4:
      b->laser[b->current_laser].src = (SDL_FRect){0,0,18,64};
      break;
    default:
      b->laser[b->current_laser].src = (SDL_FRect){0,0,18,64};
      break;
    }


}


void enemy_bullet (struct Bullet *b, struct Enemy *e) {
  //printf("Disparo del enemigo %d registrado! \n", b->index);
  b->ebullets[b->index].rect.x = e->enemies[b->index].rect.x;
  b->ebullets[b->index].rect.y =  e->enemies[b->index].rect.y;
  b->ebullets[b->index].rect.w = b->ebullets[b->index].rect.w;
  b->ebullets[b->index].rect.h = b->ebullets[b->index].rect.h;
  b->ebullets[b->index].active = true;


}

      /*
      b->laser[1].active = false;
      b->laser[1].rect.x = -5000;
      b->laser[1].rect.y = -5000;
      SDL_DestroyTexture(b->laser[1].image);
      SDL_DestroySurface(b->laser[1].surf);
      b->laser[1].surf= NULL;
      b->laser[1].image = NULL;
      b->laser[2].active = false;
      b->laser[2].rect.x = -5000;
      b->laser[2].rect.y = -5000;
      SDL_DestroyTexture(b->laser[2].image);
      SDL_DestroySurface(b->laser[2].surf);
      b->laser[2].surf= NULL;
      b->laser[2].image = NULL;
      b->laser[3].active = false;
      b->laser[3].rect.x = -5000;
      b->laser[3].rect.y = -5000;
      SDL_DestroyTexture(b->laser[3].image);
      SDL_DestroySurface(b->laser[3].surf);
      b->laser[3].surf= NULL;
      b->laser[3].image = NULL;*/