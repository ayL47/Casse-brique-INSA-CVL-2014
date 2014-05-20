#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"
#include <math.h>

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



void moveBall(SDL_Rect *positionBalle, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *verti, int *hori, int *life, int *continuer)
{

    positionBalle->y = positionBalle->y + *verti;
    positionBalle->x = positionBalle->x + *hori;

    double caseX = floor((double) ((positionBalle->x) / 25));
    double caseY = floor((double) ((positionBalle->y) / 25));


    switch(*hori)
    {
    case -1:
            if(mapLevel[(int) caseY][(int) caseX] == BRIQUE) // si elle touche une brique
            {
                *verti = - *verti; // on inverse la trajectoire
                positionBalle->y = positionBalle->y + *verti;
            mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
            }
            /*if((positionBalle->x)== 25 || (positionBalle->x) == LARGEUR_FENETRE-25) //Quand la balle touche les murs gauches et droits
            {
            *hori = - *hori;
            positionBalle->x = positionBalle->x + *hori;
            }*/
            //la balle touche le mur en haut
            if(mapLevel[(int) caseY][(int) caseX] == MUR)
            {
                *verti =  *verti;
                *hori = - *hori;
                positionBalle->y = positionBalle->y + *verti;
                positionBalle->x = positionBalle->x + *hori;
            }
            // la balle touche le mur en bas
            if(positionBalle->y == HAUTEUR_FENETRE -25) //Quand la balle touche le mur du bas
            {

            }
            //la balle touche la raquette
            if(positionBalle->y == positionBarre->y-25 && \
            ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +75)))
            {
                    // coté gauche
                if((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)< (positionBarre->x +25))
                {
                *verti= - *verti;
                *hori = - *hori;
                positionBalle->y = positionBalle->y + *verti;
                positionBalle->x = positionBalle->x + *hori;
                }
                if((positionBalle->x) >= (positionBarre->x+25) && (positionBalle->x)<= (positionBarre->x +75))
                {
                *verti= - *verti;
                positionBalle->y = positionBalle->y + *verti;
                }
            }
    break;

    //la balle se déplace verticalement
    case 0:
            if(mapLevel[(int) caseY][(int) caseX] == BRIQUE) // si elle touche une brique
            {
                *verti = - *verti; // on inverse la trajectoire
                positionBalle->y = positionBalle->y + *verti;
                mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
            }
            //la balle touche la raquette
            if(positionBalle->y == positionBarre->y-25 && \
            ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +75)))
            {
                // coté gauche
                if((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)< (positionBarre->x +10))
                {
                *verti= - *verti;
                *hori = -1;
                positionBalle->y = positionBalle->y + *verti;
                positionBalle->x = positionBalle->x + *hori;
                }
                //au centre
                if((positionBalle->x) >= (positionBarre->x+10) && (positionBalle->x)<= (positionBarre->x +60))
                {
                *verti= - *verti;
                positionBalle->y = positionBalle->y + *verti;
                }
                //a droite
                if((positionBalle->x+25) >= (positionBarre->x+60) && (positionBalle->x)<= (positionBarre->x +75))
                {
                *verti=  *verti;
                *hori = 1;
                positionBalle->y = positionBalle->y + *verti;
                positionBalle->x = positionBalle->x + *hori;
                }
            }
            //la balle touche le mur en haut
            if(mapLevel[(int) caseY][(int) caseX] == MUR)
            {
                if(positionBalle->y < positionBarre->y)//Quand la balle touche le mur du bas
                {
                    life--;
                    *continuer = 0;
                }
                else
                {
                *verti = - *verti;
                positionBalle->y = positionBalle->y + *verti;
                positionBalle->x = positionBalle->x + *hori;
                }
            }
            // la balle touche le mur en bas


    break;

    case 1:
            //la balle touche la raquette
            if(positionBalle->y == positionBarre->y-25 && \
            ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +75)))
            {
                // coté gauche
                if((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)< (positionBarre->x +10))
                {
                *verti= - *verti;
                *hori = -1;
                positionBalle->y = positionBalle->y + *verti;
                positionBalle->x = positionBalle->x + *hori;
                }
                if((positionBalle->x) >= (positionBarre->x+10) && (positionBalle->x)<= (positionBarre->x +60))
                {
                *verti= - *verti;
                positionBalle->y = positionBalle->y + *verti;
                }
                if((positionBalle->x+25) >= (positionBarre->x+60) && (positionBalle->x)<= (positionBarre->x +75))
                {
                *verti=  *verti;
                *hori = 1;
                positionBalle->y = positionBalle->y + *verti;
                positionBalle->x = positionBalle->x + *hori;
                }
            }
            //la balle touche le mur en haut
            if(mapLevel[(int) caseY][(int) caseX] == MUR)
            {
                *verti = - *verti;
                *hori = - *hori;
                positionBalle->y = positionBalle->y + *verti;
                positionBalle->x = positionBalle->x + *hori;
            }
    break;

    }


}
