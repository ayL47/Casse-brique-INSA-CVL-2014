#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"

void boucleJeu(SDL_Surface *briqueVie, SDL_Surface *balle, SDL_Surface *barre, SDL_Surface *brique, SDL_Surface *mur, SDL_Surface *vide, int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR], SDL_Surface **imgchiffre) {
    SDL_Rect position, positionBalle, positionBarre;
    SDL_Event event;

    Ball ball;
    int continuer = 1, briquesRestantes = 0, i = 0, j = 0, jeu = 0, initLevel = 0;
    int debut = 0;
    int life = 1, newgame = 0;
    int level = 1;
    int score = 0;

    loadLevel(mapLevel, level, &briquesRestantes);

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
                        break;

                    case VIDE:
                        SDL_BlitSurface(vide, NULL, SDL_GetVideoSurface(), &position);
                        break;

                    case BRIQUEVIE:
                        SDL_BlitSurface(briqueVie, NULL, SDL_GetVideoSurface(), &position);
                        break;

                    default:
                        break;
                }
            }
        }

        // Affichage du texte score
        afficheScores(imgchiffre);

        // Affichage du texte vie
        afficheLife(imgchiffre);

        //Mise a jours des scores
        majScore(&score, imgchiffre);

        //Mise a jours des vies
        majLife(life, imgchiffre);

        // Transparence de la balle
        SDL_SetColorKey(balle, SDL_SRCCOLORKEY, SDL_MapRGB(balle->format, 255, 255, 255));

        // Blittage de la barre et de la balle
        SDL_BlitSurface(barre, NULL, SDL_GetVideoSurface(), &positionBarre);
        SDL_BlitSurface(balle, NULL, SDL_GetVideoSurface(), &positionBalle);

        // Mise à Jour de l'écran
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

        if(continuer == 1) {
            // Tant qu'il reste des briques
            if(briquesRestantes > 0) {
                // Mouvement balle
                moveBalle(&positionBalle, &ball, &positionBarre, mapLevel, &newgame, &briquesRestantes, imgchiffre, &score, &life);

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
                // Toutes les briques sont cassées
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

                loadLevel(mapLevel, level, &briquesRestantes);

                jeu = 0;
                initLevel = 0;
                life = life +3;
            }

            //Si une vie a été perdue
            if(newgame == 1) {
                jeu = 0;
                initLevel = 0;
                newgame = 0;
                life--;
            }

            //Si toutes les vies ont été perdues
            if(life == 0) {
                //MAJ du nombres de vies
                majLife(life, imgchiffre);

                // Afficher écran perdu
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
                                    afficheImgSaisie(life, score);
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
}

void play() {
    int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR] = {{0}};

    SDL_Surface *balle = NULL;
    SDL_Surface *barre = NULL;
    SDL_Surface *brique = NULL;
    SDL_Surface *mur = NULL;
    SDL_Surface *vide = NULL;
    SDL_Surface *Life = NULL;
    SDL_Surface *briqueVie = NULL;

    balle = SDL_LoadBMP("images/balle.bmp");
    barre = SDL_LoadBMP("images/barre.bmp");
    brique = SDL_LoadBMP("images/brique.bmp");
    mur = SDL_LoadBMP("images/mur.bmp");
    vide = SDL_LoadBMP("images/fond.bmp");
    briqueVie = SDL_LoadBMP("images/briqueVie.bmp");

    /**
    * Initialisation du tableau des images des chiffres et score et vie
    **/
    SDL_Surface **imgchiffre;
    imgchiffre = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*12);

    imgchiffre[0] = SDL_LoadBMP("images/0.bmp");
    imgchiffre[1] = SDL_LoadBMP("images/1.bmp");
    imgchiffre[2] = SDL_LoadBMP("images/2.bmp");
    imgchiffre[3] = SDL_LoadBMP("images/3.bmp");
    imgchiffre[4] = SDL_LoadBMP("images/4.bmp");
    imgchiffre[5] = SDL_LoadBMP("images/5.bmp");
    imgchiffre[6] = SDL_LoadBMP("images/6.bmp");
    imgchiffre[7] = SDL_LoadBMP("images/7.bmp");
    imgchiffre[8] = SDL_LoadBMP("images/8.bmp");
    imgchiffre[9] = SDL_LoadBMP("images/9.bmp");
    imgchiffre[10] = SDL_LoadBMP("images/score.bmp");
    imgchiffre[11] = SDL_LoadBMP("images/Vies.bmp");

    // Transparence des chiffres
    /*SDL_SetColorKey(imgchiffre[0], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[0]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[1], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[1]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[2], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[2]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[3], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[3]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[4], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[4]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[5], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[5]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[6], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[6]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[7], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[7]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[8], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[8]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[9], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[9]->format, 0, 0, 0));

    SDL_SetColorKey(imgchiffre[10], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[10]->format, 0, 0, 0));
    SDL_SetColorKey(imgchiffre[11], SDL_SRCCOLORKEY, SDL_MapRGB(imgchiffre[11]->format, 0, 0, 0));*/

    // Appel de la boucle de jeu
    boucleJeu(briqueVie, balle, barre, brique, mur, vide, mapLevel, imgchiffre);

    // Libération mémoire
    SDL_FreeSurface(balle);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(vide);
    SDL_FreeSurface(briqueVie);
    SDL_FreeSurface(*imgchiffre);
}
