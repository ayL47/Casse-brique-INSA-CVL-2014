#include <stdlib.h>
#include <SDL/SDL.h>

#include "jeu.h"

int main(int argc, char *argv[])
{
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption(":: Casse brique ::", NULL);
    jouer();
    system("pause");
    return 0;
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
