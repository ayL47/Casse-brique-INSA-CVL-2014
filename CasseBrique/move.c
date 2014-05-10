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

void moveBall(SDL_Rect *positionBalle, int mapLevel[][NB_BLOCS_LARGEUR])
{
    /*if(mapLevel[positionBalle->y + 1][positionBalle->x] == BRIQUE)
    {
        mapLevel[positionBalle->y + 1][positionBalle->x] = VIDE;
    }*/
    positionBalle->y = positionBalle->y--;
}
