#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"

/**
* Fonctions gérant le jeux
**/

int boucleJeu(SDL_Surface *briqueDouble, SDL_Surface *briqueVie, SDL_Surface *balle, SDL_Surface *barre, SDL_Surface *brique, SDL_Surface *mur, SDL_Surface *vide, int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR], SDL_Surface **imgchiffre, int speed) {
    SDL_Rect position, positionBalle, positionBarre;
    SDL_Event event;

    Ball ball;
    int continuer = 1, briquesRestantes = 0, i = 0, j = 0, jeu = 0, initLevel = 0, gagner = 0;
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

            gagner = 0;
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

                    case BRIQUEDOUBLE:
                        SDL_BlitSurface(briqueDouble, NULL, SDL_GetVideoSurface(), &position);

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
        majScore(score, imgchiffre);

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

            while(SDL_PollEvent(&event)) {
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
                               moveBarre(&positionBarre, DROITE, speed);
                            break;

                            case SDLK_LEFT:
                                moveBarre(&positionBarre, GAUCHE, speed);
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
                i = 1;
                afficheWin();
                SDL_Flip(SDL_GetVideoSurface());

                while(i){
                    while(SDL_PollEvent(&event)) {
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
                }
                //On augmente de 1 le niveau
                level++;
                //Tant que le niveau est inférieur au niveau maximun
                if(level <= LEVEL_MAX) {
                    //On charge le nouveaux niveaux
                    loadLevel(mapLevel, level, &briquesRestantes);
                    //On re initialise initLevel pour changer les valeurs du tableau mapLevel en briques, mur, ou vide
                    //On met jeu à 0 pour attendre que le joueur appuie sur espace pour lancer le jeu
                    //On donne 3 vie suplémentaires au joueur
                    jeu = 0;
                    initLevel = 0;
                    life = life +3;
                } else {
                    continuer = 0;
                    gagner = 1;
                }
            }

            //Si une vie a été perdue
            if(newgame == 1) {
                //On met jeu à 0 pour attendre que le joueur appuie sur espace pour lancer le jeu
                //Le joueur perd une vie
                //On remet a 0 la variable newgame pour une nouvelle partie
                jeu = 0;
                initLevel = 0;
                newgame = 0;
                life--;
            }

            //Si toutes les vies ont été perdues
            if(life == 0) {
                //MAJ du nombres de vies
                majLife(life, imgchiffre);

                // Affiche écran perdu
                afficheLoose();
                //Mise à jours de l'écran
                SDL_Flip(SDL_GetVideoSurface());
                i = 1;

                while(i){
                    while(SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_QUIT:
                                i = 0;
                                continuer = 0;
                            break;

                            case SDL_KEYDOWN:
                                switch(event.key.keysym.sym) {
                                    case SDLK_RETURN:
                                        i = 0;
                                        continuer = 0;
                                    break;

                                    case SDLK_ESCAPE:
                                        i = 0;
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

            if(gagner == 1) {
                i = 1;

                while(i){
                    while(SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_QUIT:
                                i = 0;
                                continuer = 0;
                            break;

                            case SDL_KEYDOWN:
                                switch(event.key.keysym.sym) {
                                    case SDLK_RETURN:
                                        i = 0;
                                        continuer = 0;
                                    break;

                                    case SDLK_ESCAPE:
                                        i = 0;
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
    return score;
}

liste play(liste classement, SDL_Surface **imgchiffre, int speed) {
    int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR] = {{0}};
    SDL_Surface *balle = NULL;
    SDL_Surface *barre = NULL;
    SDL_Surface *brique = NULL;
    SDL_Surface *mur = NULL;
    SDL_Surface *vide = NULL;
    SDL_Surface *Life = NULL;
    SDL_Surface *briqueVie = NULL;
    SDL_Surface *briqueDouble = NULL;

    balle = SDL_LoadBMP("images/balle.bmp");
    barre = SDL_LoadBMP("images/barre.bmp");
    brique = SDL_LoadBMP("images/brique.bmp");
    mur = SDL_LoadBMP("images/mur.bmp");
    vide = SDL_LoadBMP("images/fond.bmp");
    briqueVie = SDL_LoadBMP("images/briqueVie.bmp");
    briqueDouble = SDL_LoadBMP("images/briquedouble.bmp");

    /**
    * Initialisation du tableau des images des chiffres et score et vie
    **/
    /*SDL_Surface **imgchiffre;
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
    imgchiffre[11] = SDL_LoadBMP("images/Vies.bmp");*/


    // Appel de la boucle de jeu
    int score = boucleJeu(briqueDouble, briqueVie, balle, barre, brique, mur, vide, mapLevel, imgchiffre, speed);

    // Enregistre le joueur
    cellule* nouvelleCellule = malloc(sizeof(cellule));
    nouvelleCellule->nxt = NULL;

    nouvelleCellule = afficheImgSaisie(nouvelleCellule, score);

    //Ajout du joueur au classement
    classement = ajoutClassement(classement, nouvelleCellule);

    // Sauvegarde du classement
    saveClassement(classement);


    // Libération mémoire
    SDL_FreeSurface(balle);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(vide);
    SDL_FreeSurface(briqueVie);
    //SDL_FreeSurface(*imgchiffre);
    SDL_FreeSurface(briqueDouble);

    return classement;
}

