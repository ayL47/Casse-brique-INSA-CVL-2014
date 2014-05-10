#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"

void boucleJeu(SDL_Surface *balle, SDL_Surface *barre, SDL_Surface *brique, SDL_Surface *mur, SDL_Surface *vide,int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR])
{
    SDL_Rect position, positionBalle, positionBarre;
    SDL_Event event;

    int continuer = 1, briquesRestantes = 0, i = 0, j = 0, jeu = 0;

while (continuer)                                      /* Boucle de jeu */
    {
    positionBarre.x = 8;
    positionBarre.y = 19;
    positionBalle.x = 9;
    positionBalle.y = 18;
    SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
    for (i = 0 ; i < NB_BLOCS_HAUTEUR ; i++)
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
    SDL_SetColorKey(balle, SDL_SRCCOLORKEY, SDL_MapRGB(balle->format, 255, 255, 255));


    position.x = positionBarre.x * TAILLE_BLOC;
    position.y = positionBarre.y * TAILLE_BLOC;
    SDL_BlitSurface(barre, NULL, SDL_GetVideoSurface(), &position);
    position.x = positionBalle.x * TAILLE_BLOC;
    position.y = positionBalle.y * TAILLE_BLOC;
    SDL_BlitSurface(balle, NULL, SDL_GetVideoSurface(), &position);
    SDL_Flip(SDL_GetVideoSurface());

    if (jeu == 0)          /*Afin de laisser le joueur commencer : tant qu'il n'appuie pas sur espace, le jeu reste freeze en position de départ.*/
        {
            SDL_Flip(SDL_GetVideoSurface());
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_SPACE:
                            jeu++;
                            break;
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;
                        default:
                            break;
                    }
            }
        }
        SDL_PollEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT:
                        continuer = 0;
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                continuer = 0;
                                break;
                            case SDLK_RIGHT:
                                moveBarre(&positionBarre, DROITE);
                                break;
                            case SDLK_LEFT:
                                moveBarre(&positionBarre, GAUCHE);
                                break;
                            default:
                                break;
                        }
                        break;
                }


    }
}

void play()
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

