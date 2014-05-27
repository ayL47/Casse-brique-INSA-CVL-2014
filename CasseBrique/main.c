#include <stdlib.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "jeu.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    //TTF_Init();
    SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(":: Casse-briques ::", NULL);

    liste classement = NULL;
    // Affichage du menu
    initMenu(classement);

    // Fermeture SDL
    close();

    return 0;
}

void close(void) {
    // TTF_Quit();

    // Fermeture SDL
    SDL_Quit();
}
