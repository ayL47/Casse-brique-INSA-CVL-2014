#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"

void moveBarre(SDL_Rect *positionBarre, int direction)
{

    switch (direction)
    {
        case DROITE:
            if (positionBarre->x < 400) /* bloqué par le mur */
            {
                positionBarre->x = positionBarre->x++;
        break;
            }
            else
            {
        break;
            }
        case GAUCHE:
            if (positionBarre->x > 25) /* bloqué par le mur */
            {
                positionBarre->x = positionBarre->x--;
        break;
            }
            else
            {
        break;
            }

    }
}

void moveBall(SDL_Rect *positionBalle, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *verti, int *hori)
{
    int rebond = 0;


    positionBalle->y = positionBalle->y + *verti;


    rebond = collision(positionBalle, positionBarre, mapLevel);

    switch(rebond)
    {
        case 1:
            *verti = - *verti;
            positionBalle->y = positionBalle->y + *verti;
        break;

        case 2:
            *hori = - *hori;
            positionBalle->x = positionBalle->x + *hori;
        break;

        case 3:
            *verti= - *verti;
            positionBalle->y = positionBalle->y + *verti;
        break;

        case 4:
            *verti = - *verti;
            positionBalle->y = positionBalle->y + *verti;
           /* mapLevel[positionBalle->y+25][positionBalle->x+25] = VIDE;*/
        break;

        case 5:

        break;

    }

}

int collision(SDL_Rect *positionBalle, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR])
{
    int r = positionBalle->w/2;
    int C = positionBalle->x + r;


    if(positionBalle->y == 25) //Quand la balle touche le mur du haut
    {
        return 1;
    }
    if((positionBalle->x)== 25 || (positionBalle->x) == LARGEUR_FENETRE-25) //Quand la balle touche les murs gauches et droits
    {
        return 2;
    }
    if(positionBalle->y == positionBarre->y-25 && \
       ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +75)))
    {
        return 3;
    }
    if((positionBalle->y >= 2*TAILLE_BLOC) &&(positionBalle->y <= 10*TAILLE_BLOC)) //Si la balle est dans le bloc des briques
    {
        return 4;
    }
        if(positionBalle->y == HAUTEUR_FENETRE -25) //Quand la balle touche le mur du bas
    {
        return 5;
    }
}
