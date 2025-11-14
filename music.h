//
// Created by gogphojoh on 11/12/25.
//

#ifndef MUSIC_MUSIC_H
#define MUSIC_MUSIC_H

#include "main.h"

struct Music {
    MIX_Mixer *mixer;
    MIX_Audio *background;
    MIX_Track *track;
    SDL_AudioSpec *spec;
};


bool music_new (struct Music **music);
void music_free(struct Music **music);
void music_update(struct Music *m);
void music_play(const struct Music *m);

#endif //MUSIC_MUSIC_H