#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "jeu.h"
#include "level.h"
#include "constantes.h"

void jouer()
{
    int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR] = {{0}};
    int level=1;
    SDL_Surface *balle = NULL;
    SDL_Surface *barre = NULL;
    SDL_Surface *brique = NULL;
    SDL_Surface *mur = NULL;
    SDL_Surface *vide = NULL;

    balle = SDL_LoadBMP("balle.bmp");
    barre = SDL_LoadBMP("barre.bmp");
    brique = SDL_LoadBMP("brique.bmp");
    mur = SDL_LoadBMP("mur.bmp");
    vide = SDL_LoadBMP("fond.bmp");

    loadLevel(mapLevel, level);
    /*boucleJeu(balle, barre, brique, mur, vide);*/

    SDL_FreeSurface(balle);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(vide);

}

