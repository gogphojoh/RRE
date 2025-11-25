//
// Created by gogphojoh on 11/10/25.
//

#ifndef PLAYER_PLAYER_H
#define PLAYER_PLAYER_H

#include "../mainloop/main.h"
#include "bullet.h"
#include "../text/text.h"


struct Player {
    struct Bullet *bullet;
    MIX_Mixer *mixer;
    MIX_Audio *death;
    MIX_Track *track;
    float spawn;
    SDL_Renderer *renderer;
    SDL_Texture *image;
    SDL_FRect rect;
    bool active;
    bool sound_played;
    float invulnerability;
    const bool *keystate;
  float pv;
};

bool player_new (struct Player **player, SDL_Renderer *renderer);
void player_free(struct Player **player);
void player_update(struct Player *p, struct Bullet *b, struct Power *pw, struct Music *m, struct Enemy *e, struct Text *t);
void player_draw(const struct Player *p);
void player_death (struct Player *p, struct Music *m);

#endif //PLAYER_PLAYER_H