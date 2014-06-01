#include <stdlib.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "jeu.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    //Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(":: Casse-briques - INSA-CVL - 2014 ::", NULL);

    // Mise à 0 du classement
    liste classement = NULL;

    // On charge le classement précédement établi
    classement = readClassement(classement);

    //On initialise notre menu
    initMenu(classement);

    // Appel de la fonction de fermeture de la SDL
    close();

    return 0;
}

void close(void) {
    // Fermeture SDL
    SDL_Quit();
}
