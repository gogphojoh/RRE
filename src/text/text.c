//
// Created by gogphojoh on 11/8/25.
//

#include "text.h"
#include "bubble.h"

bool text_new (struct Text **text, SDL_Renderer *renderer) {
        *text = calloc(1, sizeof(struct Text));
        if (*text == NULL) {
            fprintf(stderr, "Error al realizar Calloc para crear el nuevo texto.\n");
            return false;
        }

    struct Text *t = *text;

    t->renderer = renderer;



    t->score = 0;
    t->hi_score = 200;
    t->lives = 3;
    t->power_count = 0;
    t->bomb_count = 3;
    sprintf(t->text_num, "%d", t->score);
    sprintf(t->text_hiscore, "%d", t->hi_score);
    sprintf(t->player, "%d", t->lives);
    sprintf(t->power, "%d", t->power_count);
    sprintf(t->bomb, "%d", t->bomb_count);



  for (int i = 0; i < TEXT_AMOUNT; i++) {
    switch (i) {
    case 0:
      t->text[i].surf = bubble_create_text(TEXT_STR, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLUE_COLOR);
      t->text[i].rect.x = 1000;
      t->text[i].rect.y = 100;
      break;
    case 1:
      t->text[i].surf = bubble_create_text("HiScore", TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 850;
      t->text[i].rect.y = 150;
      break;
    case 2:
      t->text[i].surf = bubble_create_text(t->text_hiscore, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 1100;
      t->text[i].rect.y = 150;
      break;
    case 3:
      t->text[i].surf = bubble_create_text("Score", TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 880;
      t->text[i].rect.y = 200;
      break;
    case 4:
      t->text[i].surf = bubble_create_text(t->text_num, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 1100;
      t->text[i].rect.y = 200;
      break;
    case 5:
      t->text[i].surf = bubble_create_text("Player", TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 880;
      t->text[i].rect.y = 250;
      break;
    case 6:
      t->text[i].surf = bubble_create_text(t->player, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 1100;
      t->text[i].rect.y = 250;
      break;
    case 7:
      t->text[i].surf = bubble_create_text("Power", TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 880;
      t->text[i].rect.y = 300;
      break;
    case 8:
      t->text[i].surf = bubble_create_text(t->power, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 1100;
      t->text[i].rect.y = 300;
      break;
    case 9:
      t->text[i].surf = bubble_create_text("Bomb", TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 880;
      t->text[i].rect.y = 350;
      break;
    case 10:
      t->text[i].surf = bubble_create_text(t->bomb, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
      t->text[i].rect.x = 1100;
      t->text[i].rect.y = 350;
      break;
    default:
      t->text[i].surf = NULL;
    }

    if (!t->text[i].surf) {
      return false;
    }

    t->text[i].rect.w = (float)t->text[i].surf->w;
    t->text[i].rect.h = (float)t->text[i].surf->h;




    t->text[i].image = SDL_CreateTextureFromSurface(t->renderer, t->text[i].surf);
    SDL_DestroySurface (t->text[i].surf);
    t->text[i].surf = NULL;

    if (!t->text[i].image) {
      fprintf(stderr, "Error al cargar la imagen del texto en el juego: %s\n", SDL_GetError());
      return false;
    }

    // t->x_vel = TEXT_VEL;
    // t->y_vel = TEXT_VEL;

    if (!SDL_SetTextureScaleMode(t->text[i].image, SDL_SCALEMODE_NEAREST)) {
      fprintf(stderr, "Error al cargar la imagen del texto en el juego: %s\n", SDL_GetError());
      return false;
    }
  }


    return true;
}

void text_free(struct Text **text) {
    if (*text) {
        struct Text *t = *text;
      for (int i = 0; i < TEXT_AMOUNT; i++) {
        if (t->text[i].image) {
          SDL_DestroyTexture(t->text[i].image);
          t->text[i].image = NULL;
        }
      }


        t->renderer = NULL;
        free(t);
        t = NULL;
        *text = NULL;
        printf("Free Text. \n");

    }
}

void text_update(struct Text *t) {
    //printf("Puntuaje: %lf \n", t->score);

    //printf("Puntuaje: %lf \n", t->text_num);


    // t->rect.x += t->x_vel;
    // t->rect.y += t->y_vel;
    //
    // if (t->rect.x + t->rect.w > WINDOW_WIDTH) {
    //     t->x_vel = -TEXT_VEL;
    // }
    // else if (t->rect.x < 0) {
    //     t->x_vel = TEXT_VEL;
    // }
    //
    // if (t->rect.y + t->rect.h > WINDOW_HEIGHT) {
    //     t->y_vel = -TEXT_VEL;
    // }
    // else if (t->rect.y < 0) {
    //     t->y_vel = TEXT_VEL;
    // }
}

void score_update (struct Text *t) {
  sprintf(t->text_num, "%d", t->score);
  int i = 4;
  if (t->text[i].surf) SDL_DestroySurface(t->text[i].surf);
  if (t->text[i].image) SDL_DestroyTexture(t->text[i].image);
  t->text[i].surf = bubble_create_text(t->text_num, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
  t->text[i].rect.x = t->text[i].rect.x;
  t->text[i].rect.y = t->text[i].rect.y;
  t->text[i].rect.w = (float)t->text[i].surf->w;
  t->text[i].rect.h = (float)t->text[i].surf->h;
  t->text[i].image = SDL_CreateTextureFromSurface(t->renderer, t->text[i].surf);
  SDL_DestroySurface (t->text[i].surf);
  t->text[i].surf = NULL;
  if (t->score >= t->hi_score) {
    t->hi_score = t->score;
    sprintf(t->text_hiscore, "%d", t->hi_score);
    int i = 2;
    if (t->text[i].surf) SDL_DestroySurface(t->text[i].surf);
    if (t->text[i].image) SDL_DestroyTexture(t->text[i].image);
    t->text[i].surf = bubble_create_text(t->text_hiscore, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
    t->text[i].rect.x = t->text[i].rect.x;
    t->text[i].rect.y = t->text[i].rect.y;
    t->text[i].rect.w = (float)t->text[i].surf->w;
    t->text[i].rect.h = (float)t->text[i].surf->h;
    t->text[i].image = SDL_CreateTextureFromSurface(t->renderer, t->text[i].surf);
    SDL_DestroySurface (t->text[i].surf);
    t->text[i].surf = NULL;
  }

}

void live_update(struct Text *t) {
  sprintf(t->player, "%d", t->lives);
  int i = 6;
  if (t->text[i].surf) SDL_DestroySurface(t->text[i].surf);
  if (t->text[i].image) SDL_DestroyTexture(t->text[i].image);
  t->text[i].surf = bubble_create_text(t->player, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
  t->text[i].rect.x = t->text[i].rect.x;
  t->text[i].rect.y = t->text[i].rect.y;
  t->text[i].rect.w = (float)t->text[i].surf->w;
  t->text[i].rect.h = (float)t->text[i].surf->h;
  t->text[i].image = SDL_CreateTextureFromSurface(t->renderer, t->text[i].surf);
  SDL_DestroySurface (t->text[i].surf);
  t->text[i].surf = NULL;
}

void tpower_update(struct Text *t) {
  sprintf(t->power, "%d", t->power_count);
  int i = 8;
  if (t->text[i].surf) SDL_DestroySurface(t->text[i].surf);
  if (t->text[i].image) SDL_DestroyTexture(t->text[i].image);
  t->text[i].surf = bubble_create_text(t->power, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
  t->text[i].rect.x = t->text[i].rect.x;
  t->text[i].rect.y = t->text[i].rect.y;
  t->text[i].rect.w = (float)t->text[i].surf->w;
  t->text[i].rect.h = (float)t->text[i].surf->h;
  t->text[i].image = SDL_CreateTextureFromSurface(t->renderer, t->text[i].surf);
  SDL_DestroySurface (t->text[i].surf);
  t->text[i].surf = NULL;
}

void tbomb_update(struct Text *t) {
  sprintf(t->bomb, "%d", t->bomb_count);
  int i = 10;
  if (t->text[i].surf) SDL_DestroySurface(t->text[i].surf);
  if (t->text[i].image) SDL_DestroyTexture(t->text[i].image);
  t->text[i].surf = bubble_create_text(t->bomb, TEXT_SIZE, BUBBLE_RADIUS, WHITE_COLOR, BLACK_COLOR);
  t->text[i].rect.x = t->text[i].rect.x;
  t->text[i].rect.y = t->text[i].rect.y;
  t->text[i].rect.w = (float)t->text[i].surf->w;
  t->text[i].rect.h = (float)t->text[i].surf->h;
  t->text[i].image = SDL_CreateTextureFromSurface(t->renderer, t->text[i].surf);
  SDL_DestroySurface (t->text[i].surf);
  t->text[i].surf = NULL;
}

void text_draw(const struct Text *t) {
  for (int i = 0; i < TEXT_AMOUNT; i++) {
    SDL_RenderTexture(t->renderer, t->text[i].image, NULL, &t->text[i].rect);
  }


}




/*if (g->text_rect.x <= 0) {
    g->backwards_x = false;
}
else if (g->text_rect.x >= TEXT_LIMIT_X) {
    g->backwards_x = true;
}

g->text_rect.x += (float) (g->backwards_x ? -5 : 5);

if (g->text_rect.y <= 0) {
    g->backwards_y = false;
}
else if(g->text_rect.y >= TEXT_LIMIT_Y) {
    g->backwards_y = true;
}

g->text_rect.y += (float) (g->backwards_y ? -5 : 5);*/

//Esto es para redibujar el sprite o lo que haya salido de vuelta en la zona inicial.
//t->rect.x = WINDOW_WIDTH - t->rect.w;