#include "game.h"
#include "init_sdl.h"
#include "load_media.h"

void game_events(struct Game *g);
void game_draw(struct Game *g);
void game_update(struct Game *g);
void game_render_color(struct Game *g);

bool game_new (struct Game **game) {
  *game = calloc(1, sizeof(struct Game));
  if (*game == NULL) {
    fprintf(stderr, "Error al realizar Calloc para crear el juego.\n");
    return false;
  }
  struct Game *g = *game;

  if (!game_init_sdl(g)) {
    return false;
  }
  if (!game_load_media(g)) {
    return false;
  }

  if (!text_new(&g->text, g->renderer)) {
    return false;
  }

  if (!player_new(&g->player, g->renderer)) {
    return false;
  }
  if (!bullet_new(&g->bullet, g->renderer)) {
    return false;
  }
  if (!music_new(&g->music)) {
    return false;
  }
  if (!enemy_new(&g->enemy, g->renderer)) {
    return false;
  }
  if (!power_new(&g->power,g->renderer, g->enemy)) {
    return false;
  }


    g->is_running = true;
    srand((unsigned)time(NULL));

    return true;
}

// Esta función cierra todo lo que se abrió
void game_free(struct Game **game) {
    if (*game) {
        struct Game *g = *game;

        if (g->player) {
            player_free(&g->player);

        }
        if (g->text) {
            text_free(&g->text);
        }
        if (g->background) {
            SDL_DestroyTexture(g->background);
            g->background = NULL;
        }
        if (g->renderer) {
            SDL_DestroyRenderer(g->renderer);
            g->renderer = NULL;
        }

        if (g->window) {
            SDL_DestroyWindow(g->window);
            g->window = NULL;
        }
        if (g->music) {
            music_free(&g->music);
        }
        if (g->bullet) {
            bullet_free(&g->bullet);
        }
        if (g->enemy) {
          enemy_free(&g->enemy);
        }
        if (g->power) {
          power_free(&g->power);
        }
        MIX_Quit();
        TTF_Quit();
        SDL_Quit(); // Cierra SDL
        free(g);
        g = NULL;
        *game = NULL;
        printf("All clean!");
    }
}

void game_render_color (struct Game *g) {
    SDL_SetRenderDrawColor(g->renderer, (Uint8)rand() % 256, (Uint8)rand() % 256,(Uint8)rand() % 256,255);
}



// void bullet_movement(struct Game *g) {
//     g->bullet_rect.y -= 15;
//     if (g->keystate[SDL_SCANCODE_Z]) {
//             g->bullet_rect.x = (g->player_rect.x);
//             g->bullet_rect.y = (g->player_rect.y);
//     }
// }

void game_events(struct Game *g) {
    g->r = rand() % 10; //0 a 9
    while (SDL_PollEvent(&g->event)) {
        switch (g->event.type) {
            case SDL_EVENT_QUIT:
                g->is_running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                switch (g->event.key.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        g->is_running = false;
                        break;
                case SDL_SCANCODE_SPACE:
                        game_render_color(g);
                        break;
                case SDL_SCANCODE_BACKSPACE:
                        if (g->r == 4) {
                            SDL_DestroyTexture(g->background);
                            g->background = IMG_LoadTexture(g->renderer,"assets/backgrounds/chancho.png");
                            g->src = (SDL_FRect) {0,0,2851,2390};
                            g->dst = (SDL_FRect) {250,150,713,598 };
                        }
                        else {
                            SDL_DestroyTexture(g->background);
                            g->background = IMG_LoadTexture(g->renderer,"assets/backgrounds/C_Logo.png");
                            g->src = (SDL_FRect) {0,0,360,405};
                            g->dst = (SDL_FRect) {450,250,360,405 };
                        }
                        break;
                case SDL_SCANCODE_RETURN:
                        if (g->r == 4) {
                            SDL_DestroyTexture(g->background);
                            g->background = IMG_LoadTexture(g->renderer,"assets/backgrounds/chancho.png");
                            g->src = (SDL_FRect) {0,0,2851,2390};
                            g->dst = (SDL_FRect) {250,150,713,598 };
                        }else {
                            SDL_DestroyTexture(g->background);
                            g->background = IMG_LoadTexture(g->renderer,"assets/backgrounds/Simple_DirectMedia_Layer,_Logo.svg");
                            g->src= (SDL_FRect){0,0,738, 405};
                            g->dst= (SDL_FRect) {250,250,731,405};
                        }
                        break;
                default:
                        //SDL_DestroyTexture(g->background);
                        break;
                }

                break;
            default:
                break;
        }

    }
}

void game_update(struct Game *g) {
    text_update(g->text);
    player_update(g->player,g->bullet, g->power, g->music, g->enemy);
    power_update(g->power, g->enemy, g->player);
    enemy_update(g->enemy, g->power, g->music);
    bullet_update(g->bullet, g->enemy, g->power, g->music);
    music_update(g->music);
}

void game_draw(struct Game *g) {
  //SDL_SetRenderDrawColor(g->renderer, 74, 18, 59, 255);
  SDL_RenderClear(g->renderer);
  // Color de la pantalla (Rojo, Verde, Azul, Opacidad)
  SDL_RenderTexture(g->renderer,g->background,&g->src,&g->dst);
  text_draw(g->text);
  player_draw(g->player);
  bullet_draw(g->bullet);
  power_draw(g->power, g->enemy);
    enemy_draw(g->enemy);
    // Limpia la pantalla con ese color
    // Muestra el resultado en pantalla
    SDL_RenderPresent(g->renderer);
}



// Aquí se dibuja la pantalla
void game_run(struct Game *g) {
    music_play(g->music);
    // if (!music_new(&g->music)) {
    //     return;
    // }
    while (g->is_running){
        game_events(g);
        game_update(g);
        game_draw(g);
        //text_movement(g);
        // Pausa de 0.016 segundos para dejar ver la ventana
        SDL_Delay(16);

    }
}
