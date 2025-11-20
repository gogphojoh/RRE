#include "main.h"
#include "game.h"

// Declaración de funciones
// Esta función prepara SDL, crea la ventana y el entorno para dibujar

// Función principal: arranca, ejecuta y cierra el programa

/*
 *Gog, Tienes que saber que cuando se escribió este código solo dos personas sabían que hacía:
 *Dios
 *Y yo.
 *Y me temo que yo no tengo ni idea de como funciona.
 *Toma este contador para tomar las horas desperidiadas tratando de hacer funcionar a RED REPUBLIC ENGINE:
 *32 hrs <- Por ahora.
 */
int main(void) {


    bool exit_status = EXIT_FAILURE;
    struct Game *game = NULL;



    if (game_new(&game)) {
        game_run(game);
        exit_status = EXIT_SUCCESS;
    }
    printf("main game: %p\n", game);
    game_free(&game);
    return exit_status;
}