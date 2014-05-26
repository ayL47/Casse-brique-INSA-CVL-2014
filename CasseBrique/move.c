#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"
#include <math.h>
#include "classement.h"

void moveBarre(SDL_Rect *positionBarre, int direction) {
    switch (direction) {
        case DROITE:
            /* Bloqué par le mur */
            if (positionBarre->x < 400) {
                positionBarre->x = positionBarre->x++;
            }
        break;
        case GAUCHE:
            /* bloqué par le mur */
            if (positionBarre->x > 25) {
                positionBarre->x = positionBarre->x--;
            }
        break;
    }
}

void moveBalle(SDL_Rect *positionBalle, Ball *ball, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *newgame, int *briquesRestantes, SDL_Surface **imgchiffre, int *score, int *life) {
    /**
    * En X : 1 vers la droite, -1 vers la gauche
    * En Y : 1 descend, -1 monte
    **/
    //SDL_Rect position;
    double caseX = floor((double) ((positionBalle->x) / 25));
    double caseY = floor((double) ((positionBalle->y) / 25));

    int caseBalle = mapLevel[(int) caseY][(int) caseX];
    int posBalleXGauche = positionBalle->x;
    int posBalleXDroite = positionBalle->x + positionBalle->w;
    int posBalleYHaut = positionBalle->y;
    int posBalleYBas = positionBalle->y + positionBalle->h;

    double caseXGauche = floor((double) ((posBalleXGauche-1) / 25));
    double caseXDroite = floor((double) ((posBalleXDroite+1) / 25));
    double caseYHaut = floor((double) ((posBalleYHaut-1) / 25));
    double caseYBas = floor((double) ((posBalleYBas+1) / 25));

    double newSpeedX, newSpeedY;

    newSpeedX = cos(M_PI - acos(ball->Vx));
    newSpeedY = sin(-asin(ball->Vy));

    /**
    * Rebonds sur les murs
    **/
    if(mapLevel[(int) caseY][(int) caseXGauche] == MUR) {
        // Mur à gauche
        ball->Vx = newSpeedX;
    } else if(mapLevel[(int) caseY][(int) caseXDroite] == MUR) {
        // Mur à droite
        ball->Vx = newSpeedX;
    } else if(mapLevel[(int) caseYHaut][(int) caseX] == MUR) {
        // Mur en haut
        ball->Vy = newSpeedY;
    } else if(mapLevel[(int) caseYBas][(int) caseX] == MUR) {
        // Mur en bas
        *newgame = 1;
    }

    /**
    * Rebonds sur les briques
    **/
    else if(mapLevel[(int) caseY][(int) caseXGauche] == BRIQUE) {
        // Brique sur la gauche
        ball->Vx = newSpeedX;

        // Suppression de la brique
        mapLevel[(int) caseY][(int) caseXGauche] = VIDE;

        (*briquesRestantes)--;
        (*score)++;

        majScore(score, imgchiffre);
    } else if(mapLevel[(int) caseY][(int) caseXDroite] == BRIQUE) {
        // Brique sur la droite
        ball->Vx = newSpeedX;

        // Suppression de la brique
        mapLevel[(int) caseY][(int) caseXDroite] = VIDE;
        (*briquesRestantes)--;
        (*score)++;

        majScore(score, imgchiffre);
    } else if(mapLevel[(int) caseYHaut][(int) caseX] == BRIQUE) {
        // Brique sur le haut
        ball->Vy = newSpeedY;

        // Suppression de la brique
        mapLevel[(int) caseYHaut][(int) caseX] = VIDE;
        (*briquesRestantes)--;
        (*score)++;

        majScore(score, imgchiffre);
    } else if(mapLevel[(int) caseYBas][(int) caseX] == BRIQUE) {
        // Brique sur le bas
        ball->Vy = newSpeedY;

        // Suppression de la brique
        mapLevel[(int) caseYBas][(int) caseX] = VIDE;
        (*briquesRestantes)--;
        (*score)++;

        majScore(score, imgchiffre);
    }

    /**
    * Rebonds sur la raquette
    **/
    else if(posBalleYBas == positionBarre->y) {
        // Rebond raquette
        if(((positionBalle->x + positionBalle->w) >= positionBarre->x) && (positionBalle->x <= (positionBarre->x + positionBarre->w))) {
            // Rebond normal, vers le haut
            ball->Vy = newSpeedY;
        }
    }
    /**
    * Rebonds sur les briques vies
    **/
    else if(mapLevel[(int) caseY][(int) caseXGauche] == BRIQUEVIE) {
        // Brique sur la gauche
        ball->Vx = newSpeedX;

        // Suppression de la brique
        mapLevel[(int) caseY][(int) caseXGauche] = VIDE;

        (*briquesRestantes)--;
        (*score)++;
        (*life)++;

        majScore(score, imgchiffre);
    } else if(mapLevel[(int) caseY][(int) caseXDroite] == BRIQUEVIE) {
        // Brique sur la droite
        ball->Vx = newSpeedX;

        // Suppression de la brique
        mapLevel[(int) caseY][(int) caseXDroite] = VIDE;
        (*briquesRestantes)--;
        (*score)++;
        (*life)++;

        majScore(score, imgchiffre);
    } else if(mapLevel[(int) caseYHaut][(int) caseX] == BRIQUEVIE) {
        // Brique sur le haut
        ball->Vy = newSpeedY;

        // Suppression de la brique
        mapLevel[(int) caseYHaut][(int) caseX] = VIDE;
        (*briquesRestantes)--;
        (*score)++;
        (*life)++;

        majScore(score, imgchiffre);
    } else if(mapLevel[(int) caseYBas][(int) caseX] == BRIQUEVIE) {
        // Brique sur le bas
        ball->Vy = newSpeedY;

        // Suppression de la brique
        mapLevel[(int) caseYBas][(int) caseX] = VIDE;
        (*briquesRestantes)--;
        (*score)++;
        (*life)++;

        majScore(score, imgchiffre);
    }

    positionBalle->x +=  ball->Vx;
    positionBalle->y +=  ball->Vy;
}
