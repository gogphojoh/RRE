//
// Created by gogphojoh on 11/8/25.
//

#ifndef TEXT_H
#define TEXT_H

#include "../mainloop/main.h"

struct TextEntity {
  SDL_Texture *image;
  SDL_FRect rect;
  SDL_Surface *surf;
  const char *text;
};

struct Text {
    SDL_Renderer *renderer;
    // SDL_Texture *image;
    // SDL_FRect rect;
  const char *text_num[64];
  const char *text_hiscore[64];
  const char *player[64];
  const char *power[64];
  struct TextEntity text[16];
  float x_vel;
  float y_vel;
  int score;
  int hi_score;
  int lives;
  int power_count;
};

bool text_new (struct Text **text, SDL_Renderer *renderer);
void text_free(struct Text **text);
void text_update(struct Text *t);
void text_draw(const struct Text *t);
void score_update(struct Text *t);
void live_update(struct Text *t);
void tpower_update(struct Text *t);

#endif //MOVING_TEXT_TEXT_H