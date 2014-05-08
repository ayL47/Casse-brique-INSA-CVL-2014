#include <stdlib.h>
#include <stdio.h>
#include <SDL_image.h>
#define OUI 1
#define NON 0
#include "main.cpp"
#include "constantes.h"

void jouer()
{
    int carte[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR] = {{0}};
    SDL_Surface *balle = NULL;
    SDL_Surface *barre = NULL;
    SDL_Surface *brique = NULL;
    SDL_Surface *mur = NULL;
    SDL_Surface *fond = NULL;

    balle = chargerImages("balle.bmp");
    barre = chargerImages("barre.bmp");
    brique = chargerImages("brique.bmp");
    mur = chargerImages("mur.bmp");
    fond = chargerImages("fond.bmp");
    chargercarte(carte);
    boucleJeu(balle, barre, brique, mur, fond);

    SDL_FreeSurface(balle);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(fond);

}

