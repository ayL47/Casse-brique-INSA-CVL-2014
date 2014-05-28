#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"

//Affichage du texte: score
void afficheScores(SDL_Surface **imgchiffre){
    SDL_Rect positionScore;
    positionScore.x = 50;
    positionScore.y = -1;

    SDL_BlitSurface(imgchiffre[10], NULL, SDL_GetVideoSurface(), &positionScore);
}


void blitChiffre(int value, SDL_Surface **imgchiffre, SDL_Rect *position) {
    SDL_BlitSurface(imgchiffre[value], NULL, SDL_GetVideoSurface(), position);
}

//Mise à jours de l'affichage des scores
void majScore(int *score, SDL_Surface **imgchiffre) {
    SDL_Rect positionChiffreC, positionChiffreD, positionChiffreU;

    positionChiffreC.x = 110;
    positionChiffreC.y = 0;
    positionChiffreD.x = positionChiffreC.x + 25;
    positionChiffreD.y = positionChiffreC.y;
    positionChiffreU.x = positionChiffreD.x + 25;
    positionChiffreU.y = positionChiffreC.y;

    int c = *score/100;
    int d = (*score/10)%10;
    int u = (*score%10);

    blitChiffre(c, imgchiffre, &positionChiffreC);
    blitChiffre(d, imgchiffre, &positionChiffreD);
    blitChiffre(u, imgchiffre, &positionChiffreU);

}

//Affiche 'perdue' si plus de vies
void afficheLoose(){
    SDL_Rect position;

    position.x = 25;
    position.y = HAUTEUR_FENETRE/2;

    SDL_Surface *perdu = NULL;

    perdu = SDL_LoadBMP("images/Perdu.bmp");

    SDL_SetColorKey(perdu, SDL_SRCCOLORKEY, SDL_MapRGB(perdu->format, 255, 255, 255));

    SDL_BlitSurface(perdu, NULL, SDL_GetVideoSurface(), &position);

}

//Affiche 'victoire' si niveau passé
void afficheWin(){
    SDL_Rect position;

    position.x = 25;
    position.y = HAUTEUR_FENETRE/2;

    SDL_Surface *win = NULL;

    win = SDL_LoadBMP("images/Victoire.bmp");

    SDL_SetColorKey(win, SDL_SRCCOLORKEY, SDL_MapRGB(win->format, 255, 255, 255));

    SDL_BlitSurface(win, NULL, SDL_GetVideoSurface(), &position);

}

//Affichage du texte: Vies
void afficheLife(SDL_Surface **imgchiffre) {
    SDL_Rect positionLife;

    positionLife.x = 370;
    positionLife.y = -1;

    SDL_BlitSurface(imgchiffre[11], NULL, SDL_GetVideoSurface(), &positionLife);
}

//Mise a jours de l'affichage du nombre de vies
void majLife (int life, SDL_Surface **imgchiffre){
    SDL_Rect positionNbLife;

    positionNbLife.x = 410;
    positionNbLife.y = 0;

    blitChiffre(life, imgchiffre, &positionNbLife);

}
