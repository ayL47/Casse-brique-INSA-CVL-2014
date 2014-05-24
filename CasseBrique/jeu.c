#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"

void boucleJeu(SDL_Surface *balle, SDL_Surface *barre, SDL_Surface *brique, SDL_Surface *mur, SDL_Surface *vide,int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR]) {
    SDL_Rect position, positionBalle, positionBarre;
    SDL_Event event;

    Ball ball;
    ball.k = 1;
    ball.x = 1;
    ball.y = -1;
    ball.Vx = 1;
    ball.Vy = -1;

    int continuer = 1, briquesRestantes = 0, i = 0, j = 0, jeu = 0, levelLoad = 0;
    int Vy = 0, debut = 0;
    int Vx = 0;
    int life = 3, newgame = 0;
    int tempsA = 0, tempsP = 0;


    /* Boucle de jeu */
    while (continuer) {
        /*TTF_Font *police = NULL;
        SDL_Surface *texte;
        police = TTF_OpenFont("colibria.ttf", 30);
        SDL_Color couleurBlanche = {255, 255, 255};
        texte = TTF_RenderText_Blended(police, "TEUB", couleurBlanche);
        SDL_Rect positionT;
        positionT.x = 0;
        positionT.y = 0;
        SDL_BlitSurface(texte, NULL, SDL_GetVideoSurface(), &positionT);*/

        if(levelLoad == 0) {
            positionBarre.x = 215;
            positionBarre.y = 500;
            positionBalle.x = (positionBarre.x + 25);
            positionBalle.y = 474;
            levelLoad = 1;
            Vy = -1;
            Vx = 0;
        }

       SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));

        /*Rempli la carte*/
        for (i = 0 ; i < NB_BLOCS_HAUTEUR ; i++) {
            for (j = 0 ; j < NB_BLOCS_LARGEUR ; j++) {
                position.x = j * TAILLE_BLOC;
                position.y = i * TAILLE_BLOC;

                switch(mapLevel[i][j]) {
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

        /*Transparence de la balle*/
        SDL_SetColorKey(balle, SDL_SRCCOLORKEY, SDL_MapRGB(balle->format, 255, 255, 255));

        /*Blittage de la barre et de la balle*/
        SDL_BlitSurface(barre, NULL, SDL_GetVideoSurface(), &positionBarre);
        SDL_BlitSurface(balle, NULL, SDL_GetVideoSurface(), &positionBalle);

        /*Mise a Jour de l'écran*/
        SDL_Flip(SDL_GetVideoSurface());

        /*Le jeu ne commence que lorsque le joueur appuies sur 'espace'*/
        while(jeu == 0) {
            SDL_Flip(SDL_GetVideoSurface());
            SDL_WaitEvent(&event);

            switch(event.type) {
                case SDL_QUIT:
                    continuer = 0;
                break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_SPACE:
                            jeu++;
                        break;

                        case SDLK_ESCAPE:
                            continuer = 0;
                        break;

                        default:
                        break;
                    }
                break;
            }
        }

        /*Tant qu'il reste des briques*/
        if(briquesRestantes > 0) {
            /*Mouvement balle*/
            moveBalle(&positionBalle, &ball, &positionBarre, mapLevel, &Vy, &Vx, &newgame, &briquesRestantes);

            SDL_PollEvent(&event);

            switch(event.type) {
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

                default:
                break;
            }
        }
        /*Toutes les briques sont cassées*/
        else if(briquesRestantes == 0) {
        }
        if(life == 0) {
            continuer = 0;
        }

        if(newgame == 1) {
            jeu = 0;
            levelLoad = 0;
            newgame = 0;
            life--;
        }
    }
}

void play() {
    int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR] = {{0}};
    int level=1;

    SDL_Surface *balle = NULL;
    SDL_Surface *barre = NULL;
    SDL_Surface *brique = NULL;
    SDL_Surface *mur = NULL;
    SDL_Surface *vide = NULL;

    balle = SDL_LoadBMP("images/balle.bmp");
    barre = SDL_LoadBMP("images/barre.bmp");
    brique = SDL_LoadBMP("images/brique.bmp");
    mur = SDL_LoadBMP("images/mur.bmp");
    vide = SDL_LoadBMP("images/fond.bmp");

    loadLevel(mapLevel, level);
    boucleJeu(balle, barre, brique, mur, vide, mapLevel);

    SDL_FreeSurface(balle);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(vide);
}
