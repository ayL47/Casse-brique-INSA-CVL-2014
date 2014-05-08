#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "level.h"
#include "jeu.h"
#include "constantes.h"

void boucleJeu(SDL_Surface *balle, SDL_Surface *barre, SDL_Surface *brique, SDL_Surface *mur, SDL_Surface *vide,int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR])
{
    SDL_Rect position, positionBalle, positionBarre, positionBrique;
    SDL_Event event;

    int continuer = 1, briquesRestantes = 0, i = 0, j = 0;

    positionBarre.x = 8;
    positionBarre.y = 19;
    positionBalle.x = 8;
    positionBalle.y = 18;
    SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
    for (i = 0 ; i < NB_BLOCS_HAUTEUR ; i++)                    /* Blittage des briques */
    {
        for (j = 0 ; j < NB_BLOCS_LARGEUR ; j++)
        {
            position.x = j * TAILLE_BLOC;
            position.y = i * TAILLE_BLOC;

            switch(mapLevel[i][j])
            {
                case MUR:
                    SDL_BlitSurface(mur, NULL, SDL_GetVideoSurface(), &position);
                    break;
                case BRIQUE:
                    SDL_BlitSurface(brique, NULL, SDL_GetVideoSurface(), &position);
                    briquesRestantes++;
                    break;
                case VIDE:
                    SDL_BlitSurface(vide, NULL, SDL_GetVideoSurface(), &position);
                    break;
                default:
                    break;

            }
        }
    }

    SDL_Flip(SDL_GetVideoSurface());

}


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
    boucleJeu(balle, barre, brique, mur, vide, mapLevel);

    SDL_FreeSurface(balle);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(vide);

}

