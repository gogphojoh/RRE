//
// Created by gogphojoh on 11/14/25.
//

#include "enemy.h"

//Cuando muere el enemigo es cuando el consumo de memoria se dispara.

//!Tareas pendientes:
/*
 *Los enemigos ahora mismo están completamente idos. Todos mueren a la vez o ninguno muere. Sin contar que adicionalmente el efecto de sonido de estos mismos se repite en bucle,
 *creando un efecto similar al de un latido.
 *
 *Resuelto
 */

bool enemy_new(struct Enemy **enemy, SDL_Renderer *renderer) {

  *enemy = calloc (1, sizeof (struct Enemy));
  if (!(*enemy)) {
    fprintf(stderr,"Error al guardar en la memoria la enemigo: %s", SDL_GetError());
    return false;
  }
  struct Enemy *e = *enemy;
  e->renderer = renderer;
  //b->next_fire_time = 0;
  if (!e->renderer) {
    fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
    return false;
  }
  e->quantity = SCREEN_ENEMIES;
  for (int i = 0; i < e->quantity; i++) {
    printf ("Es mi iteración %d", i);
    switch (i) {
    case 6:
      e->enemies[i].type = 5; //Jefe
      break;
    case 5:
      e->enemies[i].type = 4; //Mid-jefe
      break;
    case 4:
      e->enemies[i].type = 3; //Enemigo fuerte
      break;
    case 3:
      e->enemies[i].type = 2; //hada azul
      break;
    default:
      e->enemies[i].type = 1; //hada roja
      break;
    }
    // if (i % 5 == 0) {
    //   e->enemies[i].type = 4;
    // }else if (i % 3 == 0) {
    //   e->enemies[i].type = 3;
    // } else if (i % 2 == 0 ) {
    //   e->enemies[i].type = 2;
    // } else {
    //   e->enemies[i].type = 1;
    // }
    switch (e->enemies[i].type) {
    case 1:
      e->enemies[i].sprite = "assets/sprites/hada.png";
      break;
    case 2:
      e->enemies[i].sprite = "assets/sprites/point.png";
      break;
    case 3:
      e->enemies[i].sprite = "assets/sprites/hard-fairy.png";
      break;
    case 4:
      e->enemies[i].sprite = "assets/sprites/aki_sheet.png";
      break;
    case 5:
      e->enemies[i].sprite = "assets/sprites/hina_sheet.png";
      break;
    default:
      e->enemies[i].sprite = "assets/objects/bullet.png";
    }

    e->enemies[i].surf= IMG_Load(e->enemies[i].sprite);
    if (!e->enemies[i].surf) {
      fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
      return false;
    }
    e->enemies[i].image = SDL_CreateTextureFromSurface(e->renderer, e->enemies[i].surf);
    if (!e->enemies[i].image) {
      fprintf(stderr,"Error al crear la imagen del enemigo: %s", SDL_GetError());
      return false;
    }
    //Transformar a switch
    if (e->enemies[i].type == 5 ) {
      e->enemies[i].src = (SDL_FRect){0,0,30,58};
      e->enemies[i].rect = (SDL_FRect) {0,0,30,58};
    }   else if (e->enemies[i].type == 4 ) {
      //39 w 57 h
      e->enemies[i].src = (SDL_FRect){0,0,39,57};
      e->enemies[i].rect = (SDL_FRect) {0,0,39,57};
    }else {
      SDL_GetTextureSize(e->enemies[i].image,&e->enemies[i].rect.w,&e->enemies[i].rect.h);
      e->enemies[i].src = (SDL_FRect){0,0,e->enemies[i].rect.w,e->enemies[i].rect.h};
    }


      e->spacing += 70;
      e->enemies[i].rect.x = 100 + e->spacing;
      e->enemies[i].rect.y = 100;
      e->enemies[i].rect.w = e->enemies[i].rect.w;
      e->enemies[i].rect.h = e->enemies[i].rect.h;
      e->enemies[i].active = true;

    //transformar en switch
    if (e->enemies[i].type == 5) {
      e->enemies[i].health = 2000;
    }
      else if (e->enemies[i].type == 4) {
        e->enemies[i].health = 1000;
      }else if (e->enemies[i].type == 3) {
        e->enemies[i].health = 100;
      } else {
        e->enemies[i].health = 1;
      }
      // e->dstrect = &e->enemies[i].rect;
      // e->srcrect = &e->enemies[i].src;
      e->angle = 180;
      e->flip = SDL_FLIP_VERTICAL;

      //Esta es la lógica para mover a los enemigos en la pantalla
      e->enemies[i].x_vel = ENEMY_VEL;
      e->enemies[i].y_vel = ENEMY_VEL;

  }

  // e->rect.x = 100;
  // e->rect.y = 100;

  // e->active = true;
  // e->sound_active = false;
  return true;
}
void enemy_update(struct Enemy *e, struct Power *p, struct Music *m) {
  Uint32 now = SDL_GetTicks();


  //La solución final fue bastante parecida al del rectangulo, sin embargo, es un poco más compleja.

  //!!! Estudiar !!!



  for (int i = 0; i < e->quantity; i++) {


    // if (!e->enemies[i].active && e->play_time < e->now) {
    //
    //   // spawn_enemy(e, p);
    // }

    if (e->enemies[i].type == 5 && now > e->enemies[i].frame_time) {
      e->current_enemy = i;
      hina_update(e);
      e->enemies[i].frame_time = now + 96;
    }

    if (e->enemies[i].type == 4 && now > e->enemies[i].frame_time && e->enemies[i].x_vel == 0) {
      e->current_enemy = i;
      aki_update(e);
      e->enemies[i].frame_time = now + 192; //Acá se hace el doble de tiempo por motivos de frames
    } else if (e->enemies[i].type == 4 && now > e->enemies[i].frame_time && e->enemies[i].x_vel != 0) {
      e->current_enemy = i;
      aki_left_update(e);
      e->enemies[i].frame_time = now + 192; //Acá se hace el doble de tiempo por motivos de frames
    }

    if (e->enemies[i].active == true && p->pows[i].active == false) {
      p->pows[i].pw_x = e->enemies[i].rect.x;
      p->pows[i].pw_y = e->enemies[i].rect.y;
    }

    //Y esta es la responsable de encargarse de que vayan dando tumbos por la pantalla
    e->enemies[i].rect.x += e->enemies[i].x_vel;
    e->enemies[i].rect.y += e->enemies[i].y_vel;

    if (e->enemies[i].rect.x + e->enemies[i].rect.w > WINDOW_WIDTH) {
        e->enemies[i].x_vel = -ENEMY_VEL;
    }
    else if (e->enemies[i].rect.x < 0) {
        e->enemies[i].x_vel = ENEMY_VEL;
    }

    if (e->enemies[i].rect.y + e->enemies[i].rect.h > WINDOW_HEIGHT) {
        e->enemies[i].y_vel = -ENEMY_VEL;
    }
    else if (e->enemies[i].rect.y < 0) {
        e->enemies[i].y_vel = ENEMY_VEL;
    }


  }



  // e->rect.y = 0.01f * (e->rect.x * e->rect.x);
  // Replicar esta lógica


}
void enemy_draw(struct Enemy *e) {
  for (int i = 0; i < e->quantity; i++) {
    if (e->enemies[i].active && e->enemies[i].health > 0 && e->enemies[i].x_vel >= 0) {
      SDL_RenderTexture(e->renderer, e->enemies[i].image, &e->enemies[i].src, &e->enemies[i].rect);
      //SDL_RenderTextureRotated(e->renderer, e->enemies[i].image, &e->enemies[i].src, &e->enemies[i].rect, e->angle, e->center, e->flip);
    }
    if (e->enemies[i].active && e->enemies[i].health > 0 && e->enemies[i].x_vel < 0) {
      SDL_RenderTextureRotated(e->renderer, e->enemies[i].image, &e->enemies[i].src, &e->enemies[i].rect, e->angle, e->center, e->flip);
    }
  }

}
void enemy_free(struct Enemy **enemy) {
  if (*enemy) {
    struct Enemy *e = *enemy;
    for (int i = 0; i < e->quantity; i++) {
      if (e->enemies[i].image) {
        SDL_DestroyTexture(e->enemies[i].image);
        e->enemies[i].image = NULL;
      }
      if (e->enemies[i].surf) {
        SDL_DestroySurface(e->enemies[i].surf);
        e->enemies[i].surf = NULL;
      }
      for (int i = 0; i < e->quantity; i++) {
        if (e->kill) {
          MIX_DestroyAudio(e->kill);
        }
        if (e->track) {
          MIX_DestroyTrack(e->track);

        }
      }
    }



    e->renderer = NULL;
    free(e);
    e = NULL;
    *enemy = NULL;
    printf("Free Enemy. \n");

  }
}

void play_sound(struct Enemy *e, struct Music *m) {

  if (e->kill ) {
    MIX_DestroyAudio(e->kill);
    e->kill = NULL;
  }
  if (e->track ) {
    MIX_DestroyTrack(e->track);
    e->track = NULL;
  }

  e->kill = MIX_LoadAudio(m->mixer, "music/sfx/kill.mp3", true);
  if (!e->kill) {
    SDL_Log("Error al cargar el audio: %s", SDL_GetError());
    return ;
  }
  e->track = MIX_CreateTrack(m->mixer);
  if (!e->track) {
    SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
    return ;
  }


  MIX_SetTrackAudio(e->track, e->kill);
    MIX_PlayTrack(e->track, 0);
  // if (e->sound_active == false) {
  //
  //   e->sound_active = true;
  //   e->play_time = e->now + 1000;
  // }else if (e->sound_active == true && e->play_time < e->now ) {
  //   e->sound_active = false;
  // }
  }

void hina_update(struct Enemy *e) {

  e->enemies[e->current_enemy].frame_count += 1;
  //Hina = 30 de anchura. 58 de altura
  if (e->enemies[e->current_enemy].frame_count > 9) {
    e->enemies[e->current_enemy].frame_count = 2;
  }
  switch (e->enemies[e->current_enemy].frame_count) {
    //48 pixeles de altura.
  case 1:
    e->enemies[e->current_enemy].src = (SDL_FRect){0,0,30,58};
    break;
  case 2:
    e->enemies[e->current_enemy].src = (SDL_FRect){0,64,30,58};
    break;
  case 3:
    e->enemies[e->current_enemy].src = (SDL_FRect){64,64,30,58};
    break;
  case 4:
    e->enemies[e->current_enemy].src = (SDL_FRect){128,64,30,58};
    break;
  case 5:
    e->enemies[e->current_enemy].src = (SDL_FRect){192,64,30,58};
    break;
  case 6:
    e->enemies[e->current_enemy].src = (SDL_FRect){0,128,30,58};
    break;
  case 7:
    e->enemies[e->current_enemy].src = (SDL_FRect){64,128,30,58};
    break;
  case 8:
    e->enemies[e->current_enemy].src = (SDL_FRect){128,128,30,58};
    break;
  case 9:
    e->enemies[e->current_enemy].src = (SDL_FRect){192,128,30,58};
    break;
  default:
    e->enemies[e->current_enemy].src = (SDL_FRect){0,0,30,58};
    break;
  }
}

void aki_update(struct Enemy *e) {
  //39 w 57 h
  e->enemies[e->current_enemy].frame_count += 1;
  //Hina = 30 de anchura. 58 de altura
  if (e->enemies[e->current_enemy].frame_count > 4) {
    e->enemies[e->current_enemy].frame_count = 1;
  }
  switch (e->enemies[e->current_enemy].frame_count) {
  case 1:
    e->enemies[e->current_enemy].src = (SDL_FRect){0,0,39,57};
    break;
  case 2:
    e->enemies[e->current_enemy].src = (SDL_FRect){64,0,39,57};
    break;
  case 3:
    e->enemies[e->current_enemy].src = (SDL_FRect){128,0,39,57};
    break;
  case 4:
    e->enemies[e->current_enemy].src = (SDL_FRect){192,0,39,57};
    break;
  default:
    e->enemies[e->current_enemy].src = (SDL_FRect){0,0,39,57};
    break;
  }
}

void aki_left_update(struct Enemy *e) {
  //39 w 57 h
  e->enemies[e->current_enemy].frame_count += 1;
  //Hina = 30 de anchura. 58 de altura
  if (e->enemies[e->current_enemy].frame_count > 4) {
    e->enemies[e->current_enemy].frame_count = 4;
  }
  switch (e->enemies[e->current_enemy].frame_count) {
  case 1:
    e->enemies[e->current_enemy].src = (SDL_FRect){0,64,39,57};
    break;
  case 2:
    e->enemies[e->current_enemy].src = (SDL_FRect){64,64,39,57};
    break;
  case 3:
    e->enemies[e->current_enemy].src = (SDL_FRect){128,64,39,57};
    break;
  case 4:
    e->enemies[e->current_enemy].src = (SDL_FRect){192,64,39,57};
    break;
  default:
    e->enemies[e->current_enemy].src = (SDL_FRect){0,64,39,57};
    break;
  }
}



static void spawn_enemy(struct Enemy *e, struct Power *p) {

  // if (e->spawn_time < e->now) {
  //   if (e->surf) SDL_DestroySurface(e->surf);
  //   if (e->image) SDL_DestroyTexture(e->image);
  //   e->surf= IMG_Load("assets/sprites/hada.png");
  //   if (!e->surf) {
  //     fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
  //     return ;
  //   }
  //   e->image = SDL_CreateTextureFromSurface(e->renderer, e->surf);
  //   e->active = true;
  // }

}

// if (e->enemies[i].rect.x + e->enemies[i].rect.w > WINDOW_WIDTH) {
//   e->enemies[i].x_vel = -ENEMY_VEL;
// } else if (e->enemies[i].rect.x < 0) {
//   e->enemies[i].x_vel = ENEMY_VEL;
// } else if (e->enemies[i].rect.y < 0) {
//   e->enemies[i].y_vel = ENEMY_VEL;
// } else if (e->enemies[i].rect.y + e->enemies[i].rect.h > WINDOW_HEIGHT) {
//   e->enemies[i].y_vel = -ENEMY_VEL;
// } else  if (e->enemies[i].active) {
//   e->enemies[i].rect.x += e->enemies[i].x_vel + i*3;
//   e->enemies[i].rect.y += e->enemies[i].y_vel + i*3;
// }