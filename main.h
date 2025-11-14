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
#define SDL_FLAGS SDL_INIT_VIDEO
//#define MIX_FLAGS MIX_INIT_OGG


// Datos de la ventana
#define WINDOW_TITLE "Red Republic Engine"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
#define TEXT_SIZE 80
#define WHITE_COLOR (SDL_Color) {255,255,255,255}
#define BLUE_COLOR (SDL_Color) {137,180,250,255}
#define BUBBLE_RADIUS 15
#define TEXT_STR "Prueba"
#define TEXT_LIMIT_X 1020
#define TEXT_LIMIT_Y 880
#define TEXT_VEL 5
#define M_PI 3.14159265358979323846
#define PLAYER_VEL 5
#define BULLET_VEL 15
#define MAX_BULLETS 128
#define BULLET_DELAY 50

#endif