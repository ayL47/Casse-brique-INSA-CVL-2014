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

float speed_ball(Ball ball)
{
    return ball.k * sqrt(ball.x * ball.x + ball.y * ball.y);
}


void moveBalle(SDL_Rect *positionBalle, Ball *ball, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *Vy, int *Vx,int *newgame, int *briquesRestantes)
{

    float speed = speed_ball(*ball);
    float new_speed = 0;
    float mid_paddle = (positionBarre->x + positionBarre->w /2);
    float impactX = (positionBalle->x + positionBalle->w/2) + ball->k * 1;
    float dx = mid_paddle - impactX;
    int yI = ball->y;
    double caseX = floor((double) ((positionBalle->x) / 25));
    double caseY = floor((double) ((positionBalle->y) / 25));

//deplacement uniquement verticalement
if((*Vy == 1 || *Vy == -1) && (*Vx == 0))
{
    if((mapLevel[(int) caseY][(int) caseX] == BRIQUE) &&(mapLevel[(int) caseY][(int) caseX+1] == BRIQUE))
    {
        *Vy = - *Vy; // on inverse la trajectoire
        mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
        mapLevel[(int) caseY][(int) caseX+1] = VIDE;
        *briquesRestantes-2;
    }

    // si elle touche une seule brique
    if(mapLevel[(int) caseY][(int) caseX] == BRIQUE)
    {
        *Vy = - *Vy; // on inverse la trajectoire
        mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
        *briquesRestantes--;
    }

    //la Balle touche un mur
    if(mapLevel[(int) caseY][(int) caseX] == MUR)
    {
        if(positionBalle->y > positionBarre->y)//Quand la Balle touche le mur du bas
        {
            *newgame = 1;
        }
        else
        {
            *Vy = - *Vy;

        }
    }
    //la balle touche la raquette
    if(positionBalle->y == positionBarre->y-25 && \
    ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x + positionBarre->w)))
    {
        // coté gauche
        if((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +25))
        {
            *Vy = 0;
            ball-> y = 1;
        }
        else if((positionBalle->x) >= (positionBarre->x+50) && (positionBalle->x)<= (positionBarre->x +75))
        {
            *Vy = 0;
            ball-> y = 1;
        }
        else
        {
            *Vy = -*Vy;
        }
    }
positionBalle->y -= *Vy;

}
else
{
    //la balle touche la raquette
    if(positionBalle->y == positionBarre->y-25 && \
    ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +75)))
    {
        ball->y = - ball->y;
        // coté gauche
        if((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)< (positionBarre->x +25))
        {
        ball->x = - ball->x;
        }
        //au centre
        else if((positionBalle->x) >= (positionBarre->x+25) && (positionBalle->x)<= (positionBarre->x +50))
        {
            *Vy = 1;
        }
        else if((positionBalle->x) >= (positionBarre->x+25) && (positionBalle->x)<= (positionBarre->x +75))
        {
            ball->x = ball->x;
        }

    }
    if(positionBalle->y > positionBarre->y + 50)//Quand la Balle touche le mur du bas
    {
        *newgame = 1;
        *Vy = 1;
    }
    if(mapLevel[(int) caseY][(int) caseX+1] == MUR) // mur droit
    {
        ball->x = -ball->x;
    }
    if(mapLevel[(int) caseY-1][(int) caseX] == MUR)
    {
        ball-> x = -ball->x;
    }
    if((mapLevel[(int) caseY][(int) caseX] == BRIQUE) &&(mapLevel[(int) caseY][(int) caseX+1] == BRIQUE))
    {
        ball->x = -ball->x;
        ball->y = -ball->y;
        mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
        mapLevel[(int) caseY][(int) caseX+1] = VIDE;
    }

    // si elle touche une seule brique
    else if(mapLevel[(int) caseY][(int) caseX] == BRIQUE)
    {
        ball->x = -ball->x;
        ball->y = -ball->y;
        mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
    }
    else if(mapLevel[(int) caseY+1][(int) caseX] == BRIQUE)
    {
        ball->x = -ball->x;
        ball->y = -ball->y;
        mapLevel[(int) caseY+1][(int) caseX] = VIDE; // la brique disparait
    }
        // si elle touche une seule brique
    else if(mapLevel[(int) caseY][(int) caseX+1] == BRIQUE)
    {
        ball->x = -ball->x;
        ball->y = -ball->y;
        mapLevel[(int) caseY][(int) caseX+1] = VIDE; // la brique disparait
    }

positionBalle->x +=  ball->k * ball->x;
positionBalle->y +=  ball->k * ball->y;

}
}






























/*void moveBall(SDL_Rect *positionBalle, Ball *ball, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *Vy, int *Vx,int *newgame, int *briquesRestantes)
{

    float speed = speed_ball(*ball);
    float vitesse_non_corrigee = 0;
    int k;
    float impactX = (positionBalle->x) + ball->k * 25;


    float dx = (positionBarre->x + 37.5) - impactX;


    double caseX = floor((double) ((positionBalle->x) / 25));
    double caseY = floor((double) ((positionBalle->y) / 25));
   /* positionBalle->y = positionBalle->y + *Vy;
    positionBalle->x = positionBalle->x + *Vx;*/

/*if((*Vy == 1 || *Vy == -1) && (*Vx == 0))
{

    //la Balle se déplace verticalement

            if(mapLevel[(int) caseY][(int) caseX] == BRIQUE) // si elle touche une brique
            {
                *Vy = - *Vy; // on inverse la trajectoire
                positionBalle->y = positionBalle->y + *Vy;
                mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
                *briquesRestantes--;
            }
            //la balle touche la raquette
            if(positionBalle->y == positionBarre->y-25 && \
            ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +75)))
            {
                // coté gauche
                if((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)< (positionBarre->x +10))
                {
                *Vy= - *Vy;
                *Vx = 0;
                positionBalle->y = positionBalle->y + *Vy;
                positionBalle->x = positionBalle->x + *Vx;
                }
                //au centre
                if((positionBalle->x) >= (positionBarre->x+10) && (positionBalle->x)<= (positionBarre->x +60))
                {
                *Vy= - *Vy;
                positionBalle->y = positionBalle->y + *Vy;
                }
                // coté droit
                if(ball->x * dx < 0)
                {
                    ball->y -= dx * coeff;
                    vitesse_non_corrigee = speed_ball(*ball);
                    ball->k = (speed / vitesse_non_corrigee);
                    positionBalle->x += ball->k * ball->x;
                    positionBalle->y -= ball->k * ball->y;
                }
                //a droite
               /* if((positionBalle->x+25) >= (positionBarre->x+60) && (positionBalle->x)<= (positionBarre->x +75))
                {
                *Vy=  *Vy;
                *Vx = 0;
                positionBalle->y = positionBalle->y + *Vy;
                positionBalle->x = positionBalle->x + *Vx;
                }*/
            //}
            //la positionBallee touche un mur
           /* if(mapLevel[(int) caseY][(int) caseX] == MUR)
            {
                if(positionBalle->y > positionBarre->y)//Quand la positionBallee touche le mur du bas
                {
                    *newgame = 1;
                }
                else
                {
                    *Vy = - *Vy;
                    positionBalle->y = positionBalle->y + *Vy;
                    positionBalle->x = positionBalle->x + *Vx;
                }
            }

positionBalle->y = positionBalle->y - *Vy;
positionBalle->x = positionBalle->x + *Vx;




}


}*/
