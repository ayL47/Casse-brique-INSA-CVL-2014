#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"

/**
* Affichage des différents composant de la fenetre jeux: les scores, les vies
* Ainsi que les images si le joueur remporte,perd la partie ou met le jeu en pause
**/


//Affichage du texte: score
void afficheScores(SDL_Surface **imgchiffre){
    SDL_Rect positionScore;
    positionScore.x = 50;
    positionScore.y = -1;

    SDL_BlitSurface(imgchiffre[10], NULL, SDL_GetVideoSurface(), &positionScore);
}

//Affiche les chiffres passés par paramètre à la position donnée
void blitChiffre(int value, SDL_Surface **imgchiffre, SDL_Rect *position) {
    SDL_BlitSurface(imgchiffre[value], NULL, SDL_GetVideoSurface(), position);
}

//Mise à jours de l'affichage des scores
void majScore(int score, SDL_Surface **imgchiffre) {
    SDL_Rect positionChiffreC, positionChiffreD, positionChiffreU;

    positionChiffreC.x = 110;
    positionChiffreC.y = 0;
    positionChiffreD.x = positionChiffreC.x + 25;
    positionChiffreD.y = positionChiffreC.y;
    positionChiffreU.x = positionChiffreD.x + 25;
    positionChiffreU.y = positionChiffreC.y;
    //c pour les centaines du scores
    //d pour les disaines du score, %10 = modulo 10 -> récupère le chiffre le plus à droite
    //u pour les unités
    int c = score/100;
    int d = (score/10)%10;
    int u = (score%10);

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
    //Charge image perdu
    perdu = SDL_LoadBMP("images/Perdu.bmp");
    //On rend transparent le fond blanc
    SDL_SetColorKey(perdu, SDL_SRCCOLORKEY, SDL_MapRGB(perdu->format, 255, 255, 255));
    //On colle notre image
    SDL_BlitSurface(perdu, NULL, SDL_GetVideoSurface(), &position);
}

//Affiche 'victoire' si niveau passé
void afficheWin(){
    SDL_Rect position;

    position.x = 25;
    position.y = HAUTEUR_FENETRE/2;

    SDL_Surface *win = NULL;
    //Charge image gagné
    win = SDL_LoadBMP("images/Victoire.bmp");
    //On rend transparent le fond blanc
    SDL_SetColorKey(win, SDL_SRCCOLORKEY, SDL_MapRGB(win->format, 255, 255, 255));
    //On colle notre image
    SDL_BlitSurface(win, NULL, SDL_GetVideoSurface(), &position);
}

//Affichage du texte: Vies
void afficheLife(SDL_Surface **imgchiffre) {
    SDL_Rect positionLife;
    //On définit la position
    positionLife.x = 370;
    positionLife.y = -1;
    //On colle notre image
    SDL_BlitSurface(imgchiffre[11], NULL, SDL_GetVideoSurface(), &positionLife);
}

//Mise a jours de l'affichage du nombre de vies
void majLife (int life, SDL_Surface **imgchiffre){
    SDL_Rect positionNbLife;
    //On définit la position
    positionNbLife.x = 410;
    positionNbLife.y = 0;
    //On colle notre image
    blitChiffre(life, imgchiffre, &positionNbLife);
}


