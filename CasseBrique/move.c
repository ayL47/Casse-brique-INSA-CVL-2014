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

void moveBalle(SDL_Rect *positionBalle, Ball *ball, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *Vy, int *Vx,int *newgame, int *briquesRestantes) {
    /**
    * ball->x à 1 vers la droite, -1 vers la gauche
    * ball->y à 1 descend, à -1 monte
    **/

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
        ball->Vy = newSpeedY;
    }

    if(mapLevel[(int) caseY][(int) caseXGauche] == BRIQUE) {
        // Mur à gauche
        ball->Vx = newSpeedX;

        // Suppression de la brique
        mapLevel[(int) caseY][(int) caseXGauche] = VIDE;
        *briquesRestantes--;
    } else if(mapLevel[(int) caseY][(int) caseXDroite] == BRIQUE) {
        // Mur à droite
        ball->Vx = newSpeedX;

        // Suppression de la brique
        mapLevel[(int) caseY][(int) caseXDroite] = VIDE;
        *briquesRestantes--;
    } else if(mapLevel[(int) caseYHaut][(int) caseX] == BRIQUE) {
        // Mur en haut
        ball->Vy = newSpeedY;

        // Suppression de la brique
        mapLevel[(int) caseYHaut][(int) caseX] = VIDE;
        *briquesRestantes--;
    } else if(mapLevel[(int) caseYBas][(int) caseX] == BRIQUE) {
        // Mur en bas
        ball->Vy = newSpeedY;

        // Suppression de la brique
        mapLevel[(int) caseYBas][(int) caseX] = VIDE;
        *briquesRestantes--;
    }

    positionBalle->x +=  ball->k * ball->Vx;
    positionBalle->y +=  ball->k * ball->Vy;


    /*if(ball->x == 0) {
        // La balle se déplace uniquement verticalement
        if(mapLevel[(int) caseY][(int) caseX] == BRIQUE) {
            // Inversion du déplacement en Y
            ball->y = -ball->y;

            // On enlève la brique
            mapLevel[(int) caseY][(int) caseX] = VIDE;
            *briquesRestantes--;
        } else if(mapLevel[(int) caseY][(int) caseX] == MUR) {
            // Balle touche un mur
            if(positionBalle->y > positionBarre->y) {
                *newgame = 1;
            } else {
                ball->y = - ball->y;
            }
        } else if(positionBalle->y == positionBarre->y-25 && ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x + positionBarre->w))) {
            if((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +25)) {
                // Coté gauche de la raquette
                ball->x = -1;
            }  else if((positionBalle->x) >= (positionBarre->x+50) && (positionBalle->x)<= (positionBarre->x +75)) {
                // Coté droit de la raquette
                ball->x = 1;
            } else {
                // Milieu de la raquette
            }

            ball->y = -ball->y;
        }
    } else if(ball->x == 1 && ball->y != 0) {
        // Vers la droite en montant ou descendant

        // Mur droit
        if(ball->y == 1) {
            // Balle montante
            if(mapLevel[(int) caseY+1][(int) caseX+1] == MUR) {
                ball->x = -ball->x;
            }
        } else if (ball->y == -1) {
            // Balle descendante
            if(mapLevel[(int) caseY-1][(int) caseX+1] == MUR) {
                ball->x = -ball->x;
            }
        }

        // Mur du haut
        if(mapLevel[(int) caseY+1][(int) caseX] == MUR) {
            ball->y = -ball->y;
        }

        if(mapLevel[(int) caseY][(int) caseX] == BRIQUE) {
            // Inversion du déplacement en X
            ball->x = -ball->x;

            // On enlève la brique
            mapLevel[(int) caseY][(int) caseX] = VIDE;
            *briquesRestantes--;
        }
    } else if(ball->x == -1 && ball->y != 0) {
        // Vers la gauche en montant ou descendant

        // Mur gauche
        if(ball->y == 1) {
            if(mapLevel[(int) caseY+1][(int) caseX-1] == MUR) {
                ball->x = -ball->x;
            }
        } else if (ball->y == -1) {
            if(mapLevel[(int) caseY-1][(int) caseX-1] == MUR) {
                ball->x = -ball->x;
            }
        }

        // Mur du haut
        if(mapLevel[(int) caseY+1][(int) caseX] == MUR) {
            ball->y = -ball->y;
        }

        if(mapLevel[(int) caseY][(int) caseX] == BRIQUE) {
            // Inversion du déplacement en X
            ball->x = -ball->x;

            // On enlève la brique
            mapLevel[(int) caseY][(int) caseX] = VIDE;
            *briquesRestantes--;
        }
    }

    positionBalle->x +=  ball->k * ball->x;
    positionBalle->y +=  ball->k * ball->y;*/
}

/*void moveBalle(SDL_Rect *positionBalle, Ball *ball, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *Vy, int *Vx,int *newgame, int *briquesRestantes) {
    float speed = speed_ball(*ball);
    float new_speed = 0;
    float mid_paddle = (positionBarre->x + positionBarre->w /2);
    float impactX = (positionBalle->x + positionBalle->w/2) + ball->k * 1;
    float dx = mid_paddle - impactX;
    int yI = ball->y;
    double caseX = floor((double) ((positionBalle->x) / 25));
    double caseY = floor((double) ((positionBalle->y) / 25));

    //deplacement uniquement verticalement
    if((*Vy == 1 || *Vy == -1) && (*Vx == 0)) {
        if((mapLevel[(int) caseY][(int) caseX] == BRIQUE) &&(mapLevel[(int) caseY][(int) caseX+1] == BRIQUE)) {
            *Vy = - *Vy; // on inverse la trajectoire
            mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
            mapLevel[(int) caseY][(int) caseX+1] = VIDE;
            *briquesRestantes-2;
        }

        // si elle touche une seule brique
        if(mapLevel[(int) caseY][(int) caseX] == BRIQUE) {
            *Vy = - *Vy; // on inverse la trajectoire
            mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
            *briquesRestantes--;
        }

        //la Balle touche un mur
        if(mapLevel[(int) caseY][(int) caseX] == MUR) {
            //Quand la Balle touche le mur du bas
            if(positionBalle->y > positionBarre->y) {
                *newgame = 1;
            } else {
                *Vy = - *Vy;

            }
        }

        //la balle touche la raquette
        if(positionBalle->y == positionBarre->y-25 && \
        ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x + positionBarre->w))) {
            // coté gauche
            if((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +25)) {
                *Vy = 0;
                ball->y = 1;
                ball->x = -1;
            }  else if((positionBalle->x) >= (positionBarre->x+50) && (positionBalle->x)<= (positionBarre->x +75)) {
                *Vy = 0;
                ball->y = 1;
                ball->x = 1;
            } else {
                *Vy = -*Vy;
            }
        }

        positionBalle->y -= *Vy;
    } else {
        //la balle touche la raquette
        if(positionBalle->y == positionBarre->y-25 && \
        ((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)<= (positionBarre->x +75))) {
            ball->y = - ball->y;
            // coté gauche
            if((positionBalle->x+25) >= (positionBarre->x) && (positionBalle->x)< (positionBarre->x +25)) {
                ball->x = ball->x;
            }
            //au centre
            else if((positionBalle->x) >= (positionBarre->x+25) && (positionBalle->x)<= (positionBarre->x +50)) {
                *Vy = 1;
            } else if((positionBalle->x) >= (positionBarre->x+25) && (positionBalle->x)<= (positionBarre->x +75)) {
                ball->x = ball->x;
            }
        }

        //Quand la Balle touche le mur du bas
        if(positionBalle->y > positionBarre->y + 50) {
            *newgame = 1;
            *Vy = 1;
        }

        // Mur droit
        if(mapLevel[(int) caseY][(int) caseX+1] == MUR) {
            ball->x = -ball->x;
        }

        // Mur gauche
        if(mapLevel[(int) caseY-1][(int) caseX] == MUR) {
            ball->x = -ball->x;
        }

        if((mapLevel[(int) caseY][(int) caseX] == BRIQUE) && (mapLevel[(int) caseY][(int) caseX+1] == BRIQUE)) {
            ball->x = -ball->x;
            ball->y = -ball->y;
            mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
            mapLevel[(int) caseY][(int) caseX+1] = VIDE;
        }
        // si elle touche une seule brique
        else if(mapLevel[(int) caseY][(int) caseX] == BRIQUE) {
            ball->x = -ball->x;
            ball->y = -ball->y;
            mapLevel[(int) caseY][(int) caseX] = VIDE; // la brique disparait
        } else if(mapLevel[(int) caseY+1][(int) caseX] == BRIQUE) {
            ball->x = -ball->x;
            ball->y = -ball->y;
            mapLevel[(int) caseY+1][(int) caseX] = VIDE; // la brique disparait
        }
        // si elle touche une seule brique
        else if(mapLevel[(int) caseY][(int) caseX+1] == BRIQUE) {
            ball->x = -ball->x;
            ball->y = -ball->y;
            mapLevel[(int) caseY][(int) caseX+1] = VIDE; // la brique disparait
        }

        positionBalle->x +=  ball->k * ball->x;
        positionBalle->y +=  ball->k * ball->y;
    }
}*/






























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
