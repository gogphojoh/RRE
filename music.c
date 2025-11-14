//
// Created by gogphojoh on 11/12/25.
//

#include "music.h"

bool music_new (struct Music **music) {

    *music = calloc(1, sizeof(struct Music));
    if (*music == NULL) {
        fprintf(stderr, "Error al realizar Calloc para crear la música del juego.\n");
        return false;
    }
    struct Music *m = *music;


    // Create a mixer device (this opens an SDL_AudioDevice internally)
    m->mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!m->mixer) {
        SDL_Log("Error al crear el dispositivo de mezcla: %s", SDL_GetError());
        return false;
    }


    m->background = MIX_LoadAudio(m->mixer, "china.mp3", true);
    if (!m->background) {
        SDL_Log("Error al cargar el audio: %s", SDL_GetError());
        MIX_DestroyMixer(m->mixer);
        return false;
    }


    m->track = MIX_CreateTrack(m->mixer);
    if (!m->track) {
        SDL_Log("Error al cargar la música en el canal de sonido: %s", SDL_GetError());
        MIX_DestroyAudio(m->background);
        MIX_DestroyMixer(m->mixer);
        return false;
    }


    MIX_SetTrackAudio(m->track, m->background);

    return true;
}
void music_free(struct Music **music) {
    if (*music) {
        struct Music *m = *music;


        if (m->background) {
            MIX_DestroyAudio(m->background);
        }

        if (m->track) {
            MIX_DestroyTrack(m->track);
        }
        if (m->mixer) {
            MIX_DestroyMixer(m->mixer);
        }


        free(m);


        *music = NULL;
        printf("Free Music. \n");
    }
}

 void music_update(struct Music *m) {

}
 void music_play(const struct Music *m) {
    if (!m) return;

    if (!MIX_PlayTrack(m->track, -1)) {  // -1 = loop forever
        SDL_Log("Failed to play track: %s", SDL_GetError());
    }
}