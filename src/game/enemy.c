//
// Created by gogphojoh on 11/14/25.
//

#include "enemy.h"

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
  //¿Tendré que poner a mano el spawn de los enemigos o posteriormente podré dejar esto como algo de legado?
  //Tal vez alguna idea similar a lo que hice con los power up me permita lograr mi meta incluso.
  for (int i = 0; i < e->quantity; i++) {
    //printf ("Es mi iteración %d", i);
    switch (i) {
    case 3:
      e->enemies[i].type = 2; //hada azul
    break;
    case 4:
      e->enemies[i].type = 3; //hada verde
    break;
    case 5:
      e->enemies[i].type = 4; //Hada fuerte
    break;
    case 6:
      e->enemies[i].type = 5; //Mid-jefe
    break;
     case 7:
      e->enemies[i].type = 6; //Jefe
    break;
    default:
      e->enemies[i].type = 1; //hada roja
      break;
    }

    
    switch (e->enemies[i].type) {
    case 1:
      e->enemies[i].sprite = "assets/sprites/hada_pendeja.png";
      e->enemies[i].aura = "assets/objects/red-circle.png";
      e->enemies[i].death = "assets/objects/red.png";
      e->enemies[i].health = 1;
      break;  
    case 2:
      e->enemies[i].sprite = "assets/sprites/blue_fairy_sheet.png";
      e->enemies[i].aura = "assets/objects/blue-circle.png";
      e->enemies[i].death = "assets/objects/blue.png";
      e->enemies[i].health = 1;
      break;
    case 3:
      e->enemies[i].sprite = "assets/sprites/green-fairy-sheet.png";
      e->enemies[i].aura = "assets/objects/green-aura.png";
      e->enemies[i].death = "assets/objects/green.png";
      e->enemies[i].health = 1;
      break;
    case 4:
      e->enemies[i].sprite = "assets/sprites/white_fairy_sheet.png";
      e->enemies[i].aura = "assets/objects/red-circle.png";
      e->enemies[i].death = "assets/objects/blue.png";
      e->enemies[i].health = 100;
      break;
    case 5:
      e->enemies[i].sprite = "assets/sprites/aki_sheet.png";
      e->enemies[i].aura = "assets/objects/red-circle.png";
      e->enemies[i].death = "assets/objects/red.png";
      e->enemies[i].health = 1000;
      break;
    case 6:
      e->enemies[i].sprite = "assets/sprites/hina_sheet.png";
      e->enemies[i].aura = "assets/objects/boss-aura.png";
      e->enemies[i].death = "assets/objects/red.png";
      e->enemies[i].health = 2000;
      break;
    default:
      e->enemies[i].sprite = "assets/objects/bullet.png";
      e->enemies[i].aura = "assets/objects/red-circle.png";
      e->enemies[i].death = "assets/objects/red.png";
      e->enemies[i].health = 1;
    }


    e->enemies[i].surf= IMG_Load(e->enemies[i].sprite);
    if (!e->enemies[i].surf) {
      fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
      return false;
    }

    e->enemies[i].surf_aura = IMG_Load(e->enemies[i].aura);
    if (!e->enemies[i].surf_aura) {
      fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
      return false;
    }

    e->enemies[i].surf_death = IMG_Load(e->enemies[i].death);
    if (!e->enemies[i].surf_death) {
      fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
      return false;
    }

     e->enemies[i].surf_ring = IMG_Load(e->enemies[i].death);
    if (!e->enemies[i].surf_ring) {
      fprintf(stderr,"Error al establecer el renderer: %s", SDL_GetError());
      return false;
    }


    //SDL_SetSurfaceColorKey(e->enemies[i].surf2, true, 2000);

    //Mientras más grande el número, más opaco es. Mientras más pequeño, más transparente.
    SDL_SetSurfaceAlphaMod(e->enemies[i].surf_aura, 150);


    e->enemies[i].image = SDL_CreateTextureFromSurface(e->renderer, e->enemies[i].surf);
    if (!e->enemies[i].image) {
      fprintf(stderr,"Error al crear la imagen del enemigo: %s", SDL_GetError());
      return false;
    }

    
    e->enemies[i].image_aura = SDL_CreateTextureFromSurface(e->renderer, e->enemies[i].surf_aura);
    if (!e->enemies[i].image_aura) {
      fprintf(stderr,"Error al crear la imagen del enemigo: %s", SDL_GetError());
      return false;
    }

        
    e->enemies[i].image_death = SDL_CreateTextureFromSurface(e->renderer, e->enemies[i].surf_death);
    if (!e->enemies[i].image_death) {
      fprintf(stderr,"Error al crear la imagen del enemigo: %s", SDL_GetError());
      return false;
    }

    e->enemies[i].image_ring = SDL_CreateTextureFromSurface(e->renderer, e->enemies[i].surf_ring);
    if (!e->enemies[i].image_ring) {
      fprintf(stderr,"Error al crear la imagen del enemigo: %s", SDL_GetError());
      return false;
    }



    //SDL_SetTextureBlendMode(e->enemies[i].image2, SDL_BLENDMODE_MUL );
    
    //Interesante
    //Esto es todo lo relacionado a la apariciónd el aura y la muerte de los enemigos.
    if(e->enemies[i].type == 1 || e->enemies[i].type == 2 || e->enemies[i].type == 3 || e->enemies[i].type == 4 || e->enemies[i].type == 5)
    {

      if(e->enemies[i].type == 1 || e->enemies[i].type == 2 || e->enemies[i].type == 3 )
      {
        SDL_GetTextureSize(e->enemies[i].image_aura,&e->enemies[i].rect_aura.w,&e->enemies[i].rect_aura.h);
        e->enemies[i].src_aura = (SDL_FRect) {0,0,30,30};
        e->enemies[i].rect_aura.w = 30;
        e->enemies[i].rect_aura.h = 30;
      }else if (e->enemies[i].type == 4) {
        SDL_GetTextureSize(e->enemies[i].image_aura,&e->enemies[i].rect_aura.w,&e->enemies[i].rect_aura.h);
        e->enemies[i].src_aura = (SDL_FRect) {0,0,0,0};
        e->enemies[i].rect_aura.w = 0;
        e->enemies[i].rect_aura.h = 0;
      }

          //Medidas de la muerte
      SDL_GetTextureSize(e->enemies[i].image_death,&e->enemies[i].rect_death.w,&e->enemies[i].rect_death.h);
      e->enemies[i].src_death = (SDL_FRect){0,0,e->enemies[i].rect_death.w,e->enemies[i].rect_death.h};
        e->enemies[i].rect_death.w = e->enemies[i].rect_death.w;
        e->enemies[i].rect_death.h = e->enemies[i].rect_death.h;
      //Medidas del anillo de la muerte

      if(!(e->enemies[i].type ==  5))
      {
        SDL_GetTextureSize(e->enemies[i].image_ring,&e->enemies[i].rect_ring.w,&e->enemies[i].rect_ring.h);
        e->enemies[i].src_ring = (SDL_FRect){0,0,e->enemies[i].rect_ring.w,e->enemies[i].rect_ring.h};
        e->enemies[i].rect_ring.w = e->enemies[i].rect_ring.w/3;
        e->enemies[i].rect_ring.h = e->enemies[i].rect_ring.h;
      }else{
        SDL_GetTextureSize(e->enemies[i].image_ring,&e->enemies[i].rect_ring.w,&e->enemies[i].rect_ring.h);
        e->enemies[i].src_ring = (SDL_FRect){0,0,e->enemies[i].rect_ring.w,e->enemies[i].rect_ring.h};
        e->enemies[i].rect_ring.w = 0;
        e->enemies[i].rect_ring.h = 0;
      }

    }else{
      SDL_GetTextureSize(e->enemies[i].image_aura,&e->enemies[i].rect_aura.w,&e->enemies[i].rect_aura.h);
      e->enemies[i].src_aura = (SDL_FRect) {0,0,0,0};
      e->enemies[i].rect_aura.w = 0;
      e->enemies[i].rect_aura.h = 0;
            SDL_GetTextureSize(e->enemies[i].image_death,&e->enemies[i].rect_death.w,&e->enemies[i].rect_death.h);
      e->enemies[i].src_death = (SDL_FRect){0,0,0,0};
        e->enemies[i].rect_death.w = 0;
        e->enemies[i].rect_death.h = 0;
      //Medidas del anillo de la muerte
      SDL_GetTextureSize(e->enemies[i].image_ring,&e->enemies[i].rect_ring.w,&e->enemies[i].rect_ring.h);
      e->enemies[i].src_ring = (SDL_FRect){0,0,0,0};
        e->enemies[i].rect_ring.w = 0;
        e->enemies[i].rect_ring.h = 0;
    }

    if (e->enemies[i].type == 6) {
        SDL_GetTextureSize(e->enemies[i].image_aura,&e->enemies[i].rect_aura.w,&e->enemies[i].rect_aura.h);
        e->enemies[i].src_aura = (SDL_FRect) {0,0,130,128};
        e->enemies[i].rect_aura.w = e->enemies[i].rect_aura.w;
        e->enemies[i].rect_aura.h = e->enemies[i].rect_aura.h;
      }


    //Transformar a switch
    switch (e->enemies[i].type){
      case 1:
      //Tengo que hacer que las hadas rojas empiecen en su quinto frame, osease, en la posicion 128 x, con altura 30 y.
      e->enemies[i].src = (SDL_FRect){0,0,64,64};
      e->enemies[i].rect = (SDL_FRect) {0,0,48,48};
      break;
      case 2:
      //Tengo que hacer que las hadas rojas empiecen en su quinto frame, osease, en la posicion 128 x, con altura 30 y.
      e->enemies[i].src = (SDL_FRect){0,0,30,30};
      e->enemies[i].rect = (SDL_FRect) {0,0,30,30};
      break;
      case 3:
      //Tengo que hacer que las hadas rojas empiecen en su quinto frame, osease, en la posicion 128 x, con altura 30 y.
      e->enemies[i].src = (SDL_FRect){0,0,30,30};
      e->enemies[i].rect = (SDL_FRect) {0,0,30,30};
      break;
      case 4:
      //Tengo que hacer que las hadas blancas empiecen en su quinto frame, osease, en la posicion 256 x, con altura 30 y.
      e->enemies[i].src = (SDL_FRect){0,0,64,52};
      e->enemies[i].rect = (SDL_FRect) {0,0,64,52};
      break;
      case 5: 
        //39 w 57 h
      e->enemies[i].src = (SDL_FRect){0,0,39,57};
      e->enemies[i].rect = (SDL_FRect) {0,0,39,57};
      break;
      case 6:
      e->enemies[i].src = (SDL_FRect){0,0,30,58};
      e->enemies[i].rect = (SDL_FRect) {0,0,30,58};
      break;
      default:
      SDL_GetTextureSize(e->enemies[i].image,&e->enemies[i].rect.w,&e->enemies[i].rect.h);
      e->enemies[i].src = (SDL_FRect){0,0,e->enemies[i].rect.w,e->enemies[i].rect.h};
      break;
    }
      e->spacing += 70;
      e->enemies[i].rect.x = 100 + e->spacing;
      e->enemies[i].rect.y = 100;
      e->enemies[i].rect.w = e->enemies[i].rect.w;
      e->enemies[i].rect.h = e->enemies[i].rect.h;
      e->enemies[i].active = true;
    //transformar en switch
      e->angle = 180;
      e->flip = SDL_FLIP_VERTICAL;
      //Gira como loco la espiral. Me encanta
      e->progressive = 0;
      e->angle2 = e->progressive;
      e->flip2 = SDL_FLIP_HORIZONTAL;

      e->angle_ring = 45;
      e->flip_ring = SDL_FLIP_HORIZONTAL;
      
    e->enemies[i].rect_aura.x = e->enemies[i].rect.x; 
    e->enemies[i].rect_aura.y = e->enemies[i].rect.y;


      //Esta es la lógica para mover a los enemigos en la pantalla
      e->enemies[i].x_vel = ENEMY_VEL;
      e->enemies[i].y_vel = ENEMY_VEL;

      e->enemies[i].vanishing = 255;
      e->enemies[i].death_done = false;

  }

  for (int i = 0; i < e->quantity; i++) {
    SDL_DestroySurface (e->enemies[i].surf);
    SDL_DestroySurface (e->enemies[i].surf_aura);
    SDL_DestroySurface (e->enemies[i].surf_death);
    SDL_DestroySurface (e->enemies[i].surf_ring);
  }




  // e->rect.x = 100;
  // e->rect.y = 100;

  // e->active = true;
  // e->sound_active = false;
  return true;
}
void enemy_update(struct Enemy *e, struct Power *p, struct Music *m) {
  Uint32 now = SDL_GetTicks();



  for (int i = 0; i < e->quantity; i++) {
    //Hacer que el giro sea al impacto y no por tiempo.
      
      if(e->enemies[i].vanishing > 0 && !e->enemies[i].active){
        
        if (e->enemies[i].vanishing >= 5){
          e->enemies[i].vanishing -= 5;
        }else{ 
          e->enemies[i].vanishing = 0;
          e->enemies[i].death_done = true;
          e->enemies[i].image_death = NULL;
          e->enemies[i].image_ring = NULL;
          SDL_DestroyTexture(e->enemies[i].image_death);
          SDL_DestroyTexture(e->enemies[i].image_ring);
        }
        SDL_SetTextureAlphaMod(e->enemies[i].image_death, e->enemies[i].vanishing);
        SDL_SetTextureAlphaMod(e->enemies[i].image_ring, e->enemies[i].vanishing);
        //Muerte roja
        e->enemies[i].rect_death.w += e->enemies[i].expand;
        e->enemies[i].rect_death.h += e->enemies[i].expand;
        //Anillo que lo atraviesa
        //e->enemies[i].rect_ring.w += e->enemies[i].expand;
        e->enemies[i].rect_ring.h += e->enemies[i].expand;
        if (e->enemies[i].rect_death.w <= 64) 
        {
          e->enemies[i].expand = 3;
        }
      }else {
        //Cuestiones de difuminado, ambos usan el mismo.
        SDL_SetTextureAlphaMod(e->enemies[i].image_death, 0);
        
      }
      

    //Es momento de hacer más cosas: Ajustar el aura con los colores de hadas. Agregar los sprites de hadas, y por supuesto, ajustar sus tamaños.
    
    if(e->enemies[i].active){
      e->enemies[i].rect.x += e->enemies[i].x_vel;
      e->enemies[i].rect.y += e->enemies[i].y_vel;
    }else{
      e->enemies[i].rect.x += 0;
      e->enemies[i].rect.y += 0;
    }


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

    e->angle2 += 5;
    
    //Se supone que e->enemies[i].rect.x + e->enemies[i].rect.w/2 ajusta en el centro exacto de la figura, mientras que e->enemies[i].rect2.w/2 al obtener la mitad del rectangulo 2, lo aprovecha para ajusta en el centro geometrico. o algo así
    e->enemies[i].rect_aura.x = e->enemies[i].rect.x + e->enemies[i].rect.w/2 - e->enemies[i].rect_aura.w/2;
    e->enemies[i].rect_aura.y = e->enemies[i].rect.y + e->enemies[i].rect.h/2 - e->enemies[i].rect_aura.h/2; 
    e->enemies[i].rect_death.x = e->enemies[i].rect.x + e->enemies[i].rect.w/2 - e->enemies[i].rect_death.w/2;
    e->enemies[i].rect_death.y = e->enemies[i].rect.y + e->enemies[i].rect.h/2 - e->enemies[i].rect_death.h/2;  

    e->enemies[i].rect_ring.x = e->enemies[i].rect.x + e->enemies[i].rect.w/2 - e->enemies[i].rect_ring.w/2;
    e->enemies[i].rect_ring.y = e->enemies[i].rect.y + e->enemies[i].rect.h/2 - e->enemies[i].rect_ring.h/2;  



    //Tremenda ridiculez.
    //Encima fuga de memoria?

    //XD ESTE HIJO DE PUTA ES EL RESPONSABLE (El aura y la muerte)

    /*!!!!!  Que esto sirva de recordatorio eterno:  !!!!!
      1.Que la imagen ya no se dibuje, no signfica que está libre. Aun debes hacer DestroySurface y DestroyTexture en cada situación en la que se supone que muere.
      2.Que ya no se dibuje, no implica que no sigue incrementando, y peor aún, no significa que no está agrandandose. Esto explica por que no solo con el 
      anillo sino también con la animación de muerte crecía la memoría, por que aún se usan en la memoria las muy hijas de remil.
      3.Que el que algo ya haya sido liberado de la memoria no implica ni de broma que la GPU no esté estresada. Algo de 1000x1000 fácilmente puede dejarla:
      "Kaput".
    */

    if(!e->enemies[i].death_done){
      e->enemies[i].rect_aura.w += e->enemies[i].growing;
      e->enemies[i].rect_aura.h += e->enemies[i].growing;
    }

    if (e->enemies[i].rect_aura.w > 50 && e->enemies [i].type != 6) {
        e->enemies[i].growing = -1;
    }
    else if (e->enemies[i].rect_aura.w > 260 && e->enemies [i].type == 6){
      e->enemies[i].growing = -1;
    }
   if (e->enemies[i].rect_aura.w <= 30 && e->enemies [i].type != 6) {
        e->enemies[i].growing = 1;      
  
    }else if (e->enemies[i].rect_aura.w <= 130 && e->enemies [i].type == 6){
        e->enemies[i].growing = 1; 
    }
    //e->enemies[i].rect2.h += 10;
    // if (!e->enemies[i].active && e->play_time < e->now) {
    //
    //   // spawn_enemy(e, p);
    // }

    if (e->enemies[i].type == 6 && now > e->enemies[i].frame_time) {
      e->current_enemy = i;
      hina_update(e);
      e->enemies[i].frame_time = now + 96;
    }

    if (e->enemies[i].type == 5 && now > e->enemies[i].frame_time && e->enemies[i].x_vel == 0) {
      e->current_enemy = i;
      aki_update(e);
      e->enemies[i].frame_time = now + 192; //Acá se hace el doble de tiempo por motivos de frames
    } else if (e->enemies[i].type == 5 && now > e->enemies[i].frame_time && e->enemies[i].x_vel != 0) {
      e->current_enemy = i;
      aki_left_update(e);
      e->enemies[i].frame_time = now + 192; //Acá se hace el doble de tiempo por motivos de frames
    }

    if ((e->enemies[i].type == 1 || e->enemies[i].type == 2 || e->enemies[i].type == 3 ) && now > e->enemies[i].frame_time) {
      e->current_enemy = i;
      //red_update(e);
      e->enemies[i].frame_time = now + 192; //Acá se hace el doble de tiempo por motivos de frames
    } 

    //Este es el tema, la hada blanca al ser significativamente más grande que el resto, debo usarla en codigo con sus medidas:
    //52 de altura, 64 de anchura.
    //Posicion x = 256  del quinto frame, el frame de movimientos.

    if ((e->enemies[i].type == 4) && now > e->enemies[i].frame_time) {
      e->current_enemy = i;
      white_update(e);
      e->enemies[i].frame_time = now + 192; //Acá se hace el doble de tiempo por motivos de frames
    } 

    if (e->enemies[i].active == true && p->pows[i].active == false) {
      p->pows[i].pw_x = e->enemies[i].rect.x;
      p->pows[i].pw_y = e->enemies[i].rect.y;
    }

    //Y esta es la responsable de encargarse de que vayan dando tumbos por la pantalla

  }



  // e->rect.y = 0.01f * (e->rect.x * e->rect.x);
  // Replicar esta lógica


}
void enemy_draw(struct Enemy *e) {
  for (int i = 0; i < e->quantity; i++) {
    if (e->enemies[i].active && e->enemies[i].health > 0 && e->enemies[i].x_vel >= 0) {
      
      SDL_RenderTextureRotated(e->renderer, e->enemies[i].image_aura, &e->enemies[i].src_aura, &e->enemies[i].rect_aura, e->angle2, e->center, e->flip2);
      SDL_RenderTexture(e->renderer, e->enemies[i].image, &e->enemies[i].src, &e->enemies[i].rect);
      
    
    }
    if (e->enemies[i].active && e->enemies[i].health > 0 && e->enemies[i].x_vel < 0) {
      SDL_RenderTextureRotated(e->renderer, e->enemies[i].image_aura, &e->enemies[i].src_aura, &e->enemies[i].rect_aura, e->angle2, e->center, e->flip2);
      SDL_RenderTextureRotated(e->renderer, e->enemies[i].image, &e->enemies[i].src, &e->enemies[i].rect, e->angle, e->center, e->flip);
    }
    if(!e->enemies[i].active){
      SDL_RenderTexture(e->renderer, e->enemies[i].image_death, &e->enemies[i].src_death, &e->enemies[i].rect_death);
      SDL_RenderTextureRotated(e->renderer, e->enemies[i].image_ring, &e->enemies[i].src_ring, &e->enemies[i].rect_ring, e->enemies[i].angle_ring, e->center, e->flip_ring);
    }
  }

}
void enemy_free(struct Enemy **enemy) {
  if (*enemy) {
    struct Enemy *e = *enemy;
    for (int i = 0; i < e->quantity; i++) {
      if (e->enemies[i].image) {
        SDL_DestroyTexture(e->enemies[i].image);
        SDL_DestroyTexture(e->enemies[i].image_aura);
        SDL_DestroyTexture(e->enemies[i].image_death);
        SDL_DestroyTexture(e->enemies[i].image_ring);
        e->enemies[i].image = NULL;
       e->enemies[i].image_aura = NULL;
       e->enemies[i].image_death = NULL;
       e->enemies[i].image_ring = NULL;
      }
      if (e->enemies[i].surf) {
        SDL_DestroySurface(e->enemies[i].surf);
        SDL_DestroySurface(e->enemies[i].surf_aura);
        SDL_DestroySurface(e->enemies[i].surf_death);
        SDL_DestroySurface(e->enemies[i].surf_ring);
        e->enemies[i].surf = NULL;
        e->enemies[i].surf_aura = NULL;
        e->enemies[i].surf_death = NULL;
        e->enemies[i].surf_ring = NULL;
      }

        if (e->kill) {
          MIX_DestroyAudio(e->kill);
        }
        if (e->track) {
          MIX_DestroyTrack(e->track);

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
  //MIX_PlayAudio(m->kill_sfx, 0);
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

void red_update(struct Enemy *e) {
  //39 w 57 h
  e->enemies[e->current_enemy].frame_count += 1;
  //Hina = 30 de anchura. 58 de altura
  if (e->enemies[e->current_enemy].frame_count > 8) {
    e->enemies[e->current_enemy].frame_count = 7;
  }
  switch (e->enemies[e->current_enemy].frame_count) {
  case 1:
    e->enemies[e->current_enemy].src = (SDL_FRect){128,0,30,30};
    break;
  case 2:
    e->enemies[e->current_enemy].src = (SDL_FRect){160,0,30,30};
    break;
  case 3:
    e->enemies[e->current_enemy].src = (SDL_FRect){192,0,30,30};
    break;
  case 4:
    e->enemies[e->current_enemy].src = (SDL_FRect){192,0,30,30};
    break;
    case 5:
    e->enemies[e->current_enemy].src = (SDL_FRect){224,0,30,30};
    break;
    case 6:
    e->enemies[e->current_enemy].src = (SDL_FRect){256,0,30,30};
    break;
    case 7:
    e->enemies[e->current_enemy].src = (SDL_FRect){290,0,30,30};
    break;
      case 8:
        e->enemies[e->current_enemy].src = (SDL_FRect){352,0,30,30};
    break;
    break;
  default:
      e->enemies[e->current_enemy].src = (SDL_FRect){0,0,30,30};
    break;

  }
}

void white_update(struct Enemy *e) {
  //64 w 52 h
  e->enemies[e->current_enemy].frame_count += 1;
  //White = 64 de anchura. 52 de altura
  if (e->enemies[e->current_enemy].frame_count > 8) {
    e->enemies[e->current_enemy].frame_count = 8;
  }
  switch (e->enemies[e->current_enemy].frame_count) {
  case 1:
    e->enemies[e->current_enemy].src = (SDL_FRect){256,0,64,52};
    break;
  case 2:
    e->enemies[e->current_enemy].src = (SDL_FRect){320,0,64,52};
    break;
  case 3:
    e->enemies[e->current_enemy].src = (SDL_FRect){384,0,64,52};
    break;
  case 4:
    e->enemies[e->current_enemy].src = (SDL_FRect){448,0,64,52};
    break;
    case 5:
    e->enemies[e->current_enemy].src = (SDL_FRect){512,0,64,52};
    break;
    case 6:
    e->enemies[e->current_enemy].src = (SDL_FRect){576,0,64,52};
    break;
    case 7:
    e->enemies[e->current_enemy].src = (SDL_FRect){640,0,64,52};
    break;
    //Esta pendejada está estirada desde la imagen, no es culpa del código el que se vea así.
    case 8:
        e->enemies[e->current_enemy].src = (SDL_FRect){704,0,64,52};
    break;
  default:
      e->enemies[e->current_enemy].src = (SDL_FRect){0,0,64,52};
    break;

  }
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

//Esto es un basurero  municipal. XDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD

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

      /*
      Esto es putisima mierda. Aparentemente es incapaz de centrar como se debe, ya que esta formual primeramente compara tamaños, y desplaza, en vez de obtener el centro absoluto.
      Lo cual llega al ridiculo por que esta formula fue pensada inicialmente para conseguir el putisimo centro absoluto. Como solo toma en cuenta el agrandemiento del circulo y no del enemigo,
      este código hace cualquier cosa.
      if(!(e->enemies[i].adjust == e->enemies[i].rect2.w)) 
      {
        e->enemies[i].adjust =  (e->enemies[i].rect2.w - e->enemies[i].rect.w );
        e->enemies[i].adjust = e->enemies[i].adjust/2;
        e->enemies[i].rect2.x =  e->enemies[i].rect2.x - ((e->enemies[i].adjust));
      }

      if(!(e->enemies[i].adjusty == e->enemies[i].rect2.h)) 
      {
        e->enemies[i].adjusty =  (e->enemies[i].rect2.h - e->enemies[i].rect.h);
        e->enemies[i].adjusty = e->enemies[i].adjusty/2;
        e->enemies[i].rect2.y =  e->enemies[i].rect2.y - ((e->enemies[i].adjusty));
      }*/


    //printf ("Este es el valor: %f", (e->enemies[i].rect2.x + e->enemies[i].rect2.w));
    //printf("Este es el segundo valor: %f",e->enemies[i].rect.x + e->enemies[i].rect.w*1.40 );
    //printf ("Este es el valor: %f \n", (e->enemies[i].rect2.w ));
    //printf("Este es el segundo valor: %f \n",e->enemies[i].rect.w);
    //printf ("Este es el valor x: %f \n", (e->enemies[i].rect2.x));
    //printf("Este es el segundo valor x: %f \n",e->enemies[i].rect.x);
        /*
      if (p->pows[p->sp_index].type == 2 || p->pows[p->sp_index].type > 3) {
      // if (p->pows[p->appear].surf) SDL_DestroySurface(p->pows[p->appear].surf);
      // if (p->pows[p->appear].image) SDL_DestroyTexture(p->pows[p->appear].image);
      p->pows[p->sp_index].surf= NULL;
      p->pows[p->sp_index].image = NULL;
      p->pows[p->sp_index].object = "assets/objects/points.png";
      p->pows[p->sp_index].surf= IMG_Load(p->pows[p->sp_index].object);
      p->pows[p->sp_index].image = SDL_CreateTextureFromSurface(p->renderer, p->pows[p->sp_index].surf);
      SDL_GetTextureSize(p->pows[p->sp_index].image,&p->pows[p->sp_index].rect.w,&p->pows[p->sp_index].rect.h);
      p->pows[p->sp_index].rect.w = p->pows[p->sp_index].rect.w * 2;
      p->pows[p->sp_index].rect.h = p->pows[p->sp_index].rect.h * 1.93;
    } else if (p->pows[p->sp_index].type == 3){
      p->pows[p->sp_index].surf= NULL;
      p->pows[p->sp_index].image = NULL;
      p->pows[p->sp_index].object = "assets/objects/green-drop.png";
      p->pows[p->sp_index].surf= IMG_Load(p->pows[p->sp_index].object);
      p->pows[p->sp_index].image = SDL_CreateTextureFromSurface(p->renderer, p->pows[p->sp_index].surf);
      SDL_GetTextureSize(p->pows[p->sp_index].image,&p->pows[p->sp_index].rect.w,&p->pows[p->sp_index].rect.h);
      p->pows[p->sp_index].rect.w = p->pows[p->sp_index].rect.w * 2;
      p->pows[p->sp_index].rect.h = p->pows[p->sp_index].rect.h * 1.93;
    }*/

        // if (i % 5 == 0) {
    //   e->enemies[i].type = 4;
    // }else if (i % 3 == 0) {
    //   e->enemies[i].type = 3;
    // } else if (i % 2 == 0 ) {
    //   e->enemies[i].type = 2;
    // } else {
    //   e->enemies[i].type = 1;
    // }
