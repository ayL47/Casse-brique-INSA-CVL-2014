#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"

void afficheScore(int score){
SDL_Rect positionScore, positionChiffreC, positionChiffreD, positionChiffreU;

positionScore.x = 75;
positionScore.y = 0;
positionChiffreC.x = 125;
positionChiffreC.y = 3;
positionChiffreD.x = positionChiffreC.x + 10;
positionChiffreD.y = positionChiffreC.y;
positionChiffreU.x = positionChiffreD.x + 10;
positionChiffreU.y = positionChiffreC.y;

SDL_Surface *sCore = NULL;
SDL_Surface *S0 = NULL;
SDL_Surface *S1 = NULL;
SDL_Surface *S2 = NULL;
SDL_Surface *S3 = NULL;
SDL_Surface *S4 = NULL;
SDL_Surface *S5 = NULL;
SDL_Surface *S6 = NULL;
SDL_Surface *S7 = NULL;
SDL_Surface *S8 = NULL;
SDL_Surface *S9 = NULL;


sCore = SDL_LoadBMP("images/score.bmp");
S0 = SDL_LoadBMP("images/0.bmp");
S1 = SDL_LoadBMP("images/1.bmp");
S2 = SDL_LoadBMP("images/2.bmp");
S3 = SDL_LoadBMP("images/3.bmp");
S4 = SDL_LoadBMP("images/4.bmp");
S5 = SDL_LoadBMP("images/5.bmp");
S6 = SDL_LoadBMP("images/6.bmp");
S7 = SDL_LoadBMP("images/7.bmp");
S8 = SDL_LoadBMP("images/8.bmp");
S9 = SDL_LoadBMP("images/9.bmp");

SDL_SetColorKey(sCore, SDL_SRCCOLORKEY, SDL_MapRGB(sCore->format, 0, 0, 0));
SDL_SetColorKey(S0, SDL_SRCCOLORKEY, SDL_MapRGB(S0->format, 0, 0, 0));
SDL_SetColorKey(S1, SDL_SRCCOLORKEY, SDL_MapRGB(S1->format, 0, 0, 0));
SDL_SetColorKey(S2, SDL_SRCCOLORKEY, SDL_MapRGB(S2->format, 0, 0, 0));
SDL_SetColorKey(S3, SDL_SRCCOLORKEY, SDL_MapRGB(S3->format, 0, 0, 0));
SDL_SetColorKey(S4, SDL_SRCCOLORKEY, SDL_MapRGB(S4->format, 0, 0, 0));
SDL_SetColorKey(S5, SDL_SRCCOLORKEY, SDL_MapRGB(S5->format, 0, 0, 0));
SDL_SetColorKey(S6, SDL_SRCCOLORKEY, SDL_MapRGB(S6->format, 0, 0, 0));
SDL_SetColorKey(S7, SDL_SRCCOLORKEY, SDL_MapRGB(S7->format, 0, 0, 0));
SDL_SetColorKey(S8, SDL_SRCCOLORKEY, SDL_MapRGB(S8->format, 0, 0, 0));
SDL_SetColorKey(S9, SDL_SRCCOLORKEY, SDL_MapRGB(S9->format, 0, 0, 0));


SDL_BlitSurface(sCore, NULL, SDL_GetVideoSurface(), &positionScore);

int c = score/100;
int d = (score/10)%10;
int u = (score%10);

    switch(c){
        case 0:
            SDL_BlitSurface(S0, NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;

        case 1:
            SDL_BlitSurface(S1, NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;

        case 2:
            SDL_BlitSurface(S2, NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;

        case 3:
            SDL_BlitSurface(S3, NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;

        case 4:
            SDL_BlitSurface(S4, NULL, SDL_GetVideoSurface(), &positionChiffreC);
        break;
    }
    switch(d){
        case 0:
            SDL_BlitSurface(S0, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 1:
            SDL_BlitSurface(S1, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 2:
            SDL_BlitSurface(S2, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 3:
            SDL_BlitSurface(S3, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 4:
            SDL_BlitSurface(S4, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;
        case 5:
            SDL_BlitSurface(S5, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 6:
            SDL_BlitSurface(S6, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 7:
            SDL_BlitSurface(S7, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 8:
            SDL_BlitSurface(S8, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;

        case 9:
            SDL_BlitSurface(S9, NULL, SDL_GetVideoSurface(), &positionChiffreD);
        break;
    }
    switch(u){
        case 0:
            SDL_BlitSurface(S0, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 1:
            SDL_BlitSurface(S1, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 2:
            SDL_BlitSurface(S2, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 3:
            SDL_BlitSurface(S3, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 4:
            SDL_BlitSurface(S4, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;
        case 5:
            SDL_BlitSurface(S5, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 6:
            SDL_BlitSurface(S6, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 7:
            SDL_BlitSurface(S7, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 8:
            SDL_BlitSurface(S8, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;

        case 9:
            SDL_BlitSurface(S9, NULL, SDL_GetVideoSurface(), &positionChiffreU);
        break;
    }
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

void afficheLife (int life){
SDL_Rect positionLife, positionNbLife;

positionLife.x = 375;
positionLife.y = 0;
positionNbLife.x = 420;
positionNbLife.y = 2;

SDL_Surface *Life = NULL;
SDL_Surface *S0 = NULL;
SDL_Surface *S1 = NULL;
SDL_Surface *S2 = NULL;
SDL_Surface *S3 = NULL;
SDL_Surface *S4 = NULL;

Life = SDL_LoadBMP("images/Vies.bmp");
S0 = SDL_LoadBMP("images/0.bmp");
S1 = SDL_LoadBMP("images/1.bmp");
S2 = SDL_LoadBMP("images/2.bmp");
S3 = SDL_LoadBMP("images/3.bmp");
S4 = SDL_LoadBMP("images/4.bmp");

SDL_SetColorKey(Life, SDL_SRCCOLORKEY, SDL_MapRGB(Life->format, 0, 0, 0));
SDL_SetColorKey(S0, SDL_SRCCOLORKEY, SDL_MapRGB(S0->format, 0, 0, 0));
SDL_SetColorKey(S1, SDL_SRCCOLORKEY, SDL_MapRGB(S1->format, 0, 0, 0));
SDL_SetColorKey(S2, SDL_SRCCOLORKEY, SDL_MapRGB(S2->format, 0, 0, 0));
SDL_SetColorKey(S3, SDL_SRCCOLORKEY, SDL_MapRGB(S3->format, 0, 0, 0));
SDL_SetColorKey(S4, SDL_SRCCOLORKEY, SDL_MapRGB(S4->format, 0, 0, 0));

SDL_BlitSurface(Life, NULL, SDL_GetVideoSurface(), &positionLife);


    switch(life){
        case 0:
            SDL_BlitSurface(S0, NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;

        case 1:
            SDL_BlitSurface(S1, NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;

        case 2:
            SDL_BlitSurface(S2, NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;

        case 3:
            SDL_BlitSurface(S3, NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;

        case 4:
            SDL_BlitSurface(S4, NULL, SDL_GetVideoSurface(), &positionNbLife);
        break;







    }
}
