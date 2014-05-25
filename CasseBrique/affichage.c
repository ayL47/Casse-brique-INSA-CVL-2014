#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"

void afficheScores(SDL_Surface **imgchiffre){
    SDL_Rect positionScore;
    positionScore.x = 75;
    positionScore.y = 0;

    SDL_BlitSurface(imgchiffre[10], NULL, SDL_GetVideoSurface(), &positionScore);
}

void blitChiffre(int value, SDL_Surface **imgchiffre, SDL_Rect *position) {
    SDL_BlitSurface(imgchiffre[value], NULL, SDL_GetVideoSurface(), position);
}

void majScore(int *score, SDL_Surface **imgchiffre) {
    SDL_Rect positionChiffreC, positionChiffreD, positionChiffreU;

    positionChiffreC.x = 125;
    positionChiffreC.y = 3;
    positionChiffreD.x = positionChiffreC.x + 10;
    positionChiffreD.y = positionChiffreC.y;
    positionChiffreU.x = positionChiffreD.x + 10;
    positionChiffreU.y = positionChiffreC.y;

    int c = *score/100;
    int d = (*score/10)%10;
    int u = (*score%10);

    blitChiffre(c, imgchiffre, &positionChiffreC);
    blitChiffre(d, imgchiffre, &positionChiffreD);
    blitChiffre(u, imgchiffre, &positionChiffreU);

    /*switch(c){
        case 0:
            SDL_BlitSurface(imgchiffre[0], NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;

        case 1:
            SDL_BlitSurface(imgchiffre[1], NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;

        case 2:
            SDL_BlitSurface(imgchiffre[2], NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;

        case 3:
            SDL_BlitSurface(imgchiffre[3], NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;

        case 4:
            SDL_BlitSurface(imgchiffre[4], NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;
    }

    switch(d){
        case 0:
            SDL_BlitSurface(imgchiffre[0], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 1:
            SDL_BlitSurface(imgchiffre[1], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 2:
            SDL_BlitSurface(imgchiffre[2], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 3:
            SDL_BlitSurface(imgchiffre[3], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 4:
            SDL_BlitSurface(imgchiffre[4], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;
        case 5:
            SDL_BlitSurface(imgchiffre[5], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 6:
            SDL_BlitSurface(imgchiffre[6], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 7:
            SDL_BlitSurface(imgchiffre[7], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 8:
            SDL_BlitSurface(imgchiffre[8], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 9:
            SDL_BlitSurface(imgchiffre[9], NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;
    }

    switch(u){
        case 0:
            SDL_BlitSurface(imgchiffre[0], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 1:
            SDL_BlitSurface(imgchiffre[1], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 2:
            SDL_BlitSurface(imgchiffre[2], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 3:
            SDL_BlitSurface(imgchiffre[3], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 4:
            SDL_BlitSurface(imgchiffre[4], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;
        case 5:
            SDL_BlitSurface(imgchiffre[5], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 6:
            SDL_BlitSurface(imgchiffre[6], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 7:
            SDL_BlitSurface(imgchiffre[7], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 8:
            SDL_BlitSurface(imgchiffre[8], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 9:
            SDL_BlitSurface(imgchiffre[9], NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;
    }*/
}


void afficheLoose(){
    SDL_Rect position;

    position.x = 25;
    position.y = HAUTEUR_FENETRE/2;

    SDL_Surface *perdu = NULL;

    perdu = SDL_LoadBMP("images/Perdu.bmp");

    SDL_SetColorKey(perdu, SDL_SRCCOLORKEY, SDL_MapRGB(perdu->format, 255, 255, 255));

    SDL_BlitSurface(perdu, NULL, SDL_GetVideoSurface(), &position);

}

void afficheWin(){
    SDL_Rect position;

    position.x = 25;
    position.y = HAUTEUR_FENETRE/2;

    SDL_Surface *win = NULL;

    win = SDL_LoadBMP("images/Victoire.bmp");

    SDL_SetColorKey(win, SDL_SRCCOLORKEY, SDL_MapRGB(win->format, 255, 255, 255));

    SDL_BlitSurface(win, NULL, SDL_GetVideoSurface(), &position);

}

void afficheLife(SDL_Surface **imgchiffre) {
    SDL_Rect positionLife;
    positionLife.x = 375;
    positionLife.y = 0;

    SDL_BlitSurface(imgchiffre[11], NULL, SDL_GetVideoSurface(), &positionLife);
}


void majLife (int life, SDL_Surface **imgchiffre){
    SDL_Rect positionNbLife;

    positionNbLife.x = 420;
    positionNbLife.y = 2;


    switch(life){
        case 0:
            SDL_BlitSurface(imgchiffre[0], NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;

        case 1:
            SDL_BlitSurface(imgchiffre[1], NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;

        case 2:
            SDL_BlitSurface(imgchiffre[2], NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;

        case 3:
            SDL_BlitSurface(imgchiffre[3], NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;

        case 4:
            SDL_BlitSurface(imgchiffre[4], NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;
    }
}
