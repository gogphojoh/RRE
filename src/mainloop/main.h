//
// Created by gogphojoh on 11/5/25.
//

#ifndef MAIN_H
#define MAIN_H


// Librerías necesarias para usar SDL y otras funciones básicas
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL3_image/SDL_image.h>
#include <time.h>
#include <math.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
// Indicamos que usaremos la parte de video de SDL (para mostrar ventanas)
#define SDL_FLAGS (SDL_INIT_VIDEO | SDL_INIT_AUDIO)

//#define MIX_FLAGS MIX_INIT_OGG


// Datos de la ventana
#define WINDOW_TITLE "Red Republic Engine"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
#define TEXT_SIZE 40
#define WHITE_COLOR (SDL_Color) {255,255,255,255}
#define BLUE_COLOR (SDL_Color) {137,180,250,255}
#define BLACK_COLOR (SDL_Color) {0,0,0,0}
#define BUBBLE_RADIUS 2
#define TEXT_STR "NORMAL"
#define TEXT_AMOUNT 9
#define TEXT_VEL 5
#define M_PI 3.14159265358979323846
#define PLAYER_VEL 7
#define FOCUS_VEL 3
#define BULLET_VEL 15
#define ENEMY_BULLET_VEL 5
#define MAX_BULLETS 128
#define MAX_ENEMIES 128
#define SCREEN_ENEMIES 7;
#define BULLET_DELAY 50
#define ENEMY_VEL 4
#define POWER_VEL 3

#endif