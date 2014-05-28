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
    //test d'ajout classement

    /*Joueur *joueurTest;
    joueurTest->pseudo[0] = 'a';
    joueurTest->pseudo[1] = 'b';
    joueurTest->score = 50;
    joueurTest->classement = 1;

    Joueur *joueurTest2;
    joueurTest2->pseudo[0] = 'c';
    joueurTest2->pseudo[1] = 'd';
    joueurTest2->score = 60;
    joueurTest2->classement = 3;


    ajoutClassement(classement, joueurTest);
    ajoutClassement(classement, joueurTest2);
    saveClassement(classement);*/
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
