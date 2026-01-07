//
// Created by gogphojoh on 11/10/25.
//

#ifndef SCROLL_H
#define SCROLL_H

#include "../mainloop/main.h"

struct Scroll {
    SDL_Renderer *renderer;
    SDL_Texture *image;
    SDL_FRect rect;
    SDL_FRect src;
    SDL_FRect dst;
    SDL_Texture *image2;
    SDL_FRect rect2;
    SDL_FRect src2;
    SDL_FRect dst2;
    float frame_time;
    int frame_count;
    const bool *keystate;
};

bool scroll_new (struct Scroll **scroll, SDL_Renderer *renderer);
void scroll_free(struct Scroll **scroll);
void scroll_update(struct Scroll *s);
void scroll_draw(const struct Scroll *s);

#endif