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
    int continuer = 1, briquesRestantes = 0, i = 0, j = 0, jeu = 0, initLevel = 0;
    int debut = 0;
    int life = 3, newgame = 0;
    int level = 1;
    int score = 0;

    loadLevel(mapLevel, level);

    /* Boucle de jeu */
    while(continuer) {

        /**
        * Initialisation de la balle; avec sa position, ainsi que la barre
        **/
        if(initLevel == 0) {
            // Initialisation de la balle
            ball.Vx = 1;
            ball.Vy = -1;

            // Initialisation position de la barre
            positionBarre.x = 215;
            positionBarre.y = 500;

            // Initialisation position de la balle
            positionBalle.x = (positionBarre.x + 25);
            positionBalle.y = (positionBarre.y - 25 - 1); // -1 Pour ne pas mettre la balle pile sur la barre
            initLevel = 1;
        }

       SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));

        /**
        * Affiche le terrain
        **/
        for(i = 0 ; i < NB_BLOCS_HAUTEUR ; i++) {
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

        // Transparence de la balle
        SDL_SetColorKey(balle, SDL_SRCCOLORKEY, SDL_MapRGB(balle->format, 255, 255, 255));

        // Blittage de la barre et de la balle
        SDL_BlitSurface(barre, NULL, SDL_GetVideoSurface(), &positionBarre);
        SDL_BlitSurface(balle, NULL, SDL_GetVideoSurface(), &positionBalle);

        //Blitage des scores
        score = 128 - briquesRestantes;
        afficheScore(score);

        //Blitage des vies
        afficheLife(life);

        // Mise a Jour de l'�cran
        SDL_Flip(SDL_GetVideoSurface());

        // Le jeu ne commence que lorsque le joueur appuie sur 'espace'
        while(jeu == 0) {
            SDL_Flip(SDL_GetVideoSurface());
            SDL_WaitEvent(&event);

            switch(event.type) {
                case SDL_QUIT:
                    jeu++;
                    continuer = 0;
                break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_SPACE:
                            jeu++;
                        break;

                        case SDLK_ESCAPE:
                            jeu++;
                            continuer = 0;
                        break;

                        default:
                        break;
                    }
                break;

                default:
                break;
            }
        }

        // Tant qu'il reste des briques
        if(briquesRestantes > 0) {
            // Mouvement balle
            moveBalle(&positionBalle, &ball, &positionBarre, mapLevel, &newgame, &briquesRestantes);

            SDL_PollEvent(&event);

            switch(event.type) {
                case SDL_QUIT:
                    continuer = 0;
                break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
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
        } else if(briquesRestantes == 0) {
            // Toutes les briques sont cass�es
            // Afficher gagner et aller au niveau suivant
            int i = 1;
            afficheWin();
            SDL_Flip(SDL_GetVideoSurface());
            while(i){
                SDL_WaitEvent(&event);
                switch(event.type) {
                    case SDL_QUIT:
                        i = 0;
                    break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym) {
                            case SDLK_RETURN:
                                i = 0;
                            break;

                            case SDLK_ESCAPE:
                                i = 0;
                            break;

                            default:
                            break;
                        }
                    break;

                    default:
                    break;
                }
            }
            level++;

            loadLevel(mapLevel, level);

            jeu = 0;
            initLevel = 0;
            life = 3;
        }
        //Si une vie a �t� perdue
        if(newgame == 1) {
            jeu = 0;
            initLevel = 0;
            newgame = 0;
            life--;
        }
        //Si toutes les vies ont �t� perdues
        if(life == 0) {
            //MAJ du nombres de vies
            afficheLife(life);

            // Afficher �cran perdu
            afficheLoose();
            SDL_Flip(SDL_GetVideoSurface());
            while(continuer){
                SDL_WaitEvent(&event);
                switch(event.type) {
                    case SDL_QUIT:
                        continuer = 0;
                    break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym) {
                            case SDLK_RETURN:
                                continuer = 0;
                            break;

                            case SDLK_ESCAPE:
                                continuer = 0;
                            break;

                            default:
                            break;
                        }
                    break;

                    default:
                    break;
                }
            }
        }
    }
}

void play() {
    int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR] = {{0}};

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

    boucleJeu(balle, barre, brique, mur, vide, mapLevel);

    SDL_FreeSurface(balle);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(vide);
}
