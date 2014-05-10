#include <stdlib.h>
#include <SDL/SDL.h>
#include "constantes.h"
#include "jeu.h"

int main(int argc, char *argv[])
{

    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(":: Casse brique ::", NULL);
    menu();
    /*play();*/
    close();

    return 0;
}

void close(void)
{

    SDL_Quit(); /* Fermeture SDL */

}

void menu()
{
    int continuer = 1;
    SDL_Event event;

    SDL_Surface *buttonPlay = NULL;
    SDL_Surface *buttonIns = NULL;
    SDL_Surface *instructions = NULL;
    SDL_Rect positionButtonPlay;
    SDL_Rect positionButtonIns;
    SDL_Rect positionInstruction;

    buttonPlay = SDL_LoadBMP("boutonJ_pas_survole.bmp");
    buttonIns = SDL_LoadBMP("boutonIns_pas_survole.bmp");
    instructions = SDL_LoadBMP("Instructions.bmp");


    positionButtonPlay.x=125;
    positionButtonPlay.y=200;
    positionButtonIns.x=125;
    positionButtonIns.y=240;
    positionInstruction.x=0;
    positionInstruction.y=0;

    SDL_BlitSurface(buttonPlay, NULL, SDL_GetVideoSurface(), &positionButtonPlay);
    SDL_BlitSurface(buttonIns, NULL, SDL_GetVideoSurface(), &positionButtonIns);

    SDL_Flip(SDL_GetVideoSurface());

    while(continuer)
    {
                SDL_WaitEvent(&event); /// attente d'un event
        switch(event.type)
        {
            case SDL_MOUSEBUTTONUP:
                if (event.button.x>=positionButtonPlay.x && event.button.x<=positionButtonPlay.x+233 && event.button.y>=positionButtonPlay.y && event.button.y<=positionButtonPlay.y+37)
                {
                    play();
                }
                if (event.button.x>=positionButtonIns.x && event.button.x<=positionButtonIns.x+233 && event.button.y>=positionButtonIns.y && event.button.y<=positionButtonIns.y+37)
                {
                    SDL_BlitSurface(instructions, NULL, SDL_GetVideoSurface(), &positionInstruction);
                    SDL_Flip(SDL_GetVideoSurface());
                }
                /*if (event.button.x>=posCredits.x && event.button.x<=posCredits.x+LONGUEUR && event.button.y>=posCredits.y && event.button.y<=posCredits.y+LARGEUR)
                {
                    credits(ecran);
                }*/
                else
                {
                    continuer = 1;
                }
                break;
            case SDL_QUIT: /// si type = SDL_QUIT
                continuer = 0;
                break;
            case SDL_KEYDOWN: /// si type = TOUCHE APPUYE
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /// si touche = ECHAP
                        continuer = 0;
                        break;
                }

            break;
        }
    }





    SDL_FreeSurface(buttonPlay);
}


/*int main(int argc, char *argv[])
{
    SDL_Surface *ecran, *raquette;
    SDL_Rect positionR;
    int continuer=OUI;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    ecran=SDL_SetVideoMode(800, 600, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    Uint32 blanc=SDL_MapRGB(ecran->format, 255, 255, 255);
    SDL_FillRect(ecran, NULL, blanc);
    raquette=SDL_LoadBMP("raquette.bmp");
    SDL_WM_SetCaption(":: Casse brique ::",NULL);
    positionR.x=350;
    positionR.y=500;
    SDL_EnableKeyRepeat(5,5);
    /*Afficher(ecran,brique,table,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR);
    while(continuer==OUI)
    {
        SDL_PollEvent(&event);
        if(event.type==SDL_QUIT)
        {
            continuer=NON;
        }
        else if(event.type==SDL_KEYDOWN)
        {
            if(event.key.keysym.sym==SDLK_ESCAPE)
            {
                continuer=NON;
            }
            else if(event.key.keysym.sym==SDLK_LEFT)
            {
                if(positionR.x>150)
                {positionR.x=positionR.x -1;}
            }
            else if(event.key.keysym.sym==SDLK_RIGHT)
            {
                if(positionR.x<550)
                {positionR.x=positionR.x +1;}
            }
        }
    SDL_FillRect(ecran, NULL, blanc);
    SDL_BlitSurface(raquette,NULL,ecran,&positionR);
    SDL_Flip(ecran);
    }
    SDL_FreeSurface(raquette);
    return 0;
}*/
