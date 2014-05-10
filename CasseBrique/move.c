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
        case DROITE: /* barre vers la droite */
            if (positionBarre < 800) /* afin d'être bloqué par le mur */
            {
                positionBarre->x++;
                break;
            }
            else
            {
                break;
            }
        case GAUCHE: /* barre vers la gauche */
            if (positionBarre > 0) /* afin d'être bloqué par le mur */
            {
                positionBarre->x--;
                break;
            }
            else
            {
                break;
            }

    }
}
