#include <stdlib.h>
#include <SDL/SDL.h>
#include "menu.h"
#include "constantes.h"
/**
*   Fonctions qui gérent les différents éléments/images constituant notre menu
*
**/


void initMenu(liste classement) {
    /**
    * On charge les différentes images formant le menu
    **/
    SDL_Surface *buttonPlay = NULL;
    SDL_Surface *buttonIns = NULL;
    SDL_Surface *instructions = NULL;
    SDL_Surface *buttonRank = NULL;
    SDL_Surface *rank = NULL;
    SDL_Surface *buttonQuit = NULL;
    SDL_Surface *buttonBack = NULL;
    SDL_Surface *menuImg = NULL;
    SDL_Surface *buttonO = NULL;

    buttonPlay = SDL_LoadBMP("images/boutonJ_pas_survole.bmp");
    buttonIns = SDL_LoadBMP("images/boutonIns_pas_survole.bmp");
    instructions = SDL_LoadBMP("images/Instructions.bmp");
    buttonRank = SDL_LoadBMP("images/boutonS_pas_survole.bmp");
    rank = SDL_LoadBMP("images/Scores.bmp");
    buttonQuit = SDL_LoadBMP("images/boutonQ_pas_survole.bmp");
    buttonBack = SDL_LoadBMP("images/boutonR_pas_survole.bmp");
    menuImg = SDL_LoadBMP("images/menu.bmp");
    buttonO = SDL_LoadBMP("images/boutonO.bmp");

    /**
    * Initialisation du tableau content les images des chiffres, score et vie
    **/
    SDL_Surface **imgchiffre;
    imgchiffre = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*12);

    imgchiffre[0] = SDL_LoadBMP("images/0.bmp");
    imgchiffre[1] = SDL_LoadBMP("images/1.bmp");
    imgchiffre[2] = SDL_LoadBMP("images/2.bmp");
    imgchiffre[3] = SDL_LoadBMP("images/3.bmp");
    imgchiffre[4] = SDL_LoadBMP("images/4.bmp");
    imgchiffre[5] = SDL_LoadBMP("images/5.bmp");
    imgchiffre[6] = SDL_LoadBMP("images/6.bmp");
    imgchiffre[7] = SDL_LoadBMP("images/7.bmp");
    imgchiffre[8] = SDL_LoadBMP("images/8.bmp");
    imgchiffre[9] = SDL_LoadBMP("images/9.bmp");
    imgchiffre[10] = SDL_LoadBMP("images/score.bmp");
    imgchiffre[11] = SDL_LoadBMP("images/Vies.bmp");


    menu(imgchiffre, classement, buttonPlay, buttonIns, instructions, buttonRank, rank, buttonQuit, buttonBack, menuImg, buttonO);


    // Libère les surface
    SDL_FreeSurface(buttonPlay);
    SDL_FreeSurface(buttonQuit);
    SDL_FreeSurface(buttonIns);
    SDL_FreeSurface(buttonRank);
    SDL_FreeSurface(instructions);
    SDL_FreeSurface(rank);
    SDL_FreeSurface(buttonBack);
    SDL_FreeSurface(*imgchiffre);
}



void menu(SDL_Surface **imgchiffre, liste classement, SDL_Surface *buttonPlay, SDL_Surface *buttonIns, SDL_Surface *instructions, SDL_Surface *buttonRank, SDL_Surface *rank, SDL_Surface *buttonQuit, SDL_Surface *buttonBack, SDL_Surface *menu, SDL_Surface *buttonO) {
    int continuer = 1;
    int speed = 1;
    SDL_Event event;

    // Nous définissons la position des boutons
    SDL_Rect positionButtonPlay;
    SDL_Rect positionButtonIns;
    SDL_Rect position;
    SDL_Rect positionButtonRank;
    SDL_Rect positionButtonQ;
    SDL_Rect positionButtonBack;
    SDL_Rect positionButtonO;

    positionButtonPlay.x = 125;
    positionButtonPlay.y = 200;
    positionButtonIns.x = positionButtonPlay.x;
    positionButtonIns.y = positionButtonPlay.y + 40;
    position.x = 0;
    position.y = 0;
    positionButtonRank.x = positionButtonPlay.x;
    positionButtonRank.y = positionButtonIns.y + 40;
    positionButtonO.x = positionButtonPlay.x;
    positionButtonO.y = positionButtonRank.y + 40;
    positionButtonQ.x = positionButtonPlay.x;
    positionButtonQ.y = positionButtonO.y + 40;
    positionButtonBack.x = 0;
    positionButtonBack.y = 563;

    //Nous les affichons
    SDL_BlitSurface(menu, NULL, SDL_GetVideoSurface(), &position);
    SDL_BlitSurface(buttonPlay, NULL, SDL_GetVideoSurface(), &positionButtonPlay);
    SDL_BlitSurface(buttonIns, NULL, SDL_GetVideoSurface(), &positionButtonIns);
    SDL_BlitSurface(buttonRank, NULL, SDL_GetVideoSurface(), &positionButtonRank);
    SDL_BlitSurface(buttonO, NULL, SDL_GetVideoSurface(), &positionButtonO);
    SDL_BlitSurface(buttonQuit, NULL, SDL_GetVideoSurface(), &positionButtonQ);

    //Nous mettons à jours notre écran pour que le blittage des boutons soit pris en compte
    SDL_Flip(SDL_GetVideoSurface());

    while(continuer) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_MOUSEBUTTONUP:
                    if(event.button.x>=positionButtonPlay.x && event.button.x<=positionButtonPlay.x+233 && event.button.y>=positionButtonPlay.y && event.button.y<=positionButtonPlay.y+37) {
                        // Si souris sur bouton jouer, appel de la fonction play
                        classement = play(classement, imgchiffre, speed);

                        SDL_BlitSurface(menu, NULL, SDL_GetVideoSurface(), &position);
                        SDL_BlitSurface(buttonPlay, NULL, SDL_GetVideoSurface(), &positionButtonPlay);
                        SDL_BlitSurface(buttonIns, NULL, SDL_GetVideoSurface(), &positionButtonIns);
                        SDL_BlitSurface(buttonRank, NULL, SDL_GetVideoSurface(), &positionButtonRank);
                        SDL_BlitSurface(buttonO, NULL, SDL_GetVideoSurface(), &positionButtonO);
                        SDL_BlitSurface(buttonQuit, NULL, SDL_GetVideoSurface(), &positionButtonQ);

                        SDL_Flip(SDL_GetVideoSurface());
                    } else if(event.button.x>=positionButtonIns.x && event.button.x<=positionButtonIns.x+233 && event.button.y>=positionButtonIns.y && event.button.y<=positionButtonIns.y+37) {
                        // Si souris sur bouton instructions
                        instruction(instructions, position, buttonBack, positionButtonBack);

                        SDL_BlitSurface(menu, NULL, SDL_GetVideoSurface(), &position);
                        SDL_BlitSurface(buttonPlay, NULL, SDL_GetVideoSurface(), &positionButtonPlay);
                        SDL_BlitSurface(buttonIns, NULL, SDL_GetVideoSurface(), &positionButtonIns);
                        SDL_BlitSurface(buttonRank, NULL, SDL_GetVideoSurface(), &positionButtonRank);
                        SDL_BlitSurface(buttonO, NULL, SDL_GetVideoSurface(), &positionButtonO);
                        SDL_BlitSurface(buttonQuit, NULL, SDL_GetVideoSurface(), &positionButtonQ);

                        SDL_Flip(SDL_GetVideoSurface());
                    } else if(event.button.x>=positionButtonRank.x && event.button.x<=positionButtonRank.x+233 && event.button.y>=positionButtonRank.y && event.button.y<=positionButtonRank.y+37) {
                        // Si souris sur bouton scores
                        score(imgchiffre, classement, rank, position, buttonBack, positionButtonBack);

                        SDL_BlitSurface(menu, NULL, SDL_GetVideoSurface(), &position);
                        SDL_BlitSurface(buttonPlay, NULL, SDL_GetVideoSurface(), &positionButtonPlay);
                        SDL_BlitSurface(buttonIns, NULL, SDL_GetVideoSurface(), &positionButtonIns);
                        SDL_BlitSurface(buttonRank, NULL, SDL_GetVideoSurface(), &positionButtonRank);
                        SDL_BlitSurface(buttonO, NULL, SDL_GetVideoSurface(), &positionButtonO);
                        SDL_BlitSurface(buttonQuit, NULL, SDL_GetVideoSurface(), &positionButtonQ);

                        SDL_Flip(SDL_GetVideoSurface());
                    } else if(event.button.x>=positionButtonO.x && event.button.x<=positionButtonO.x+233 && event.button.y>=positionButtonO.y && event.button.y<=positionButtonO.y+37) {
                        // Si souris sur bouton option
                        speed = option(position, buttonBack, positionButtonBack);

                        SDL_BlitSurface(menu, NULL, SDL_GetVideoSurface(), &position);
                        SDL_BlitSurface(buttonPlay, NULL, SDL_GetVideoSurface(), &positionButtonPlay);
                        SDL_BlitSurface(buttonIns, NULL, SDL_GetVideoSurface(), &positionButtonIns);
                        SDL_BlitSurface(buttonRank, NULL, SDL_GetVideoSurface(), &positionButtonRank);
                        SDL_BlitSurface(buttonO, NULL, SDL_GetVideoSurface(), &positionButtonO);
                        SDL_BlitSurface(buttonQuit, NULL, SDL_GetVideoSurface(), &positionButtonQ);
                        SDL_Flip(SDL_GetVideoSurface());
                    }else if(event.button.x>=positionButtonQ.x && event.button.x<=positionButtonQ.x+233 && event.button.y>=positionButtonQ.y && event.button.y<=positionButtonQ.y+37) {
                        // Si souris sur bouton quitter
                        continuer = 0;
                    }
                break;
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        continuer = 0;
                    }
                break;
            }
        }
    }
}

void instruction(SDL_Surface *instructions, SDL_Rect position, SDL_Surface *buttonBack, SDL_Rect positionButtonBack) {
    int continuer = 1;
    SDL_Event event;

    SDL_BlitSurface(instructions, NULL, SDL_GetVideoSurface(), &position);
    SDL_BlitSurface(buttonBack, NULL, SDL_GetVideoSurface(), &positionButtonBack);
    SDL_Flip(SDL_GetVideoSurface());

    while(continuer) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_MOUSEBUTTONUP:
                    if(event.button.x>=positionButtonBack.x && event.button.x<=positionButtonBack.x+233 && event.button.y>=positionButtonBack.y && event.button.y<=positionButtonBack.y+37) {
                        // Si souris sur bouton retour
                        continuer = 0;
                    }
                break;
                case SDL_QUIT:
                    continuer = 0;
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        continuer = 0;
                    }
                break;
            }
        }
    }
}

void score(SDL_Surface **imgchiffre, liste classement, SDL_Surface *rank, SDL_Rect position, SDL_Surface *buttonBack, SDL_Rect positionButtonBack) {
    int bContinuer = 1;
    SDL_Event event;

    SDL_BlitSurface(rank, NULL, SDL_GetVideoSurface(), &position);
    SDL_BlitSurface(buttonBack, NULL, SDL_GetVideoSurface(), &positionButtonBack);
    SDL_Flip(SDL_GetVideoSurface());

   // readClassement(classement);
    afficheClassement(classement, imgchiffre);


    while(bContinuer) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_MOUSEBUTTONUP:
                    if(event.button.x>=positionButtonBack.x && event.button.x<=positionButtonBack.x+233 && event.button.y>=positionButtonBack.y && event.button.y<=positionButtonBack.y+37) {
                       // Si souris sur bouton retour
                       bContinuer = 0;
                       return 0;
                    }
                break;
                case SDL_QUIT:
                    bContinuer = 0;
                       return 0;
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        bContinuer = 0;
                       return 0;
                    }
                break;
            }
        }
    }
}

int option(SDL_Rect position, SDL_Surface *buttonBack, SDL_Rect positionButtonBack){
    SDL_Surface *option, *buttonL, *buttonH;

    SDL_Rect positionButtonL;
    SDL_Rect positionButtonH;

    positionButtonH.x = 125;
    positionButtonH.y = 200;
    positionButtonL.x = 125;
    positionButtonL.y = positionButtonH.y + 37;

    option = SDL_LoadBMP("images/option.bmp");
    buttonL = SDL_LoadBMP("images/buttonL.bmp");
    buttonH = SDL_LoadBMP("images/buttonH.bmp");

    int continuer = 1;
    SDL_Event event;


    SDL_BlitSurface(option, NULL, SDL_GetVideoSurface(), &position);
    SDL_BlitSurface(buttonH, NULL, SDL_GetVideoSurface(), &positionButtonH);
    SDL_BlitSurface(buttonL, NULL, SDL_GetVideoSurface(), &positionButtonL);
    SDL_BlitSurface(buttonBack, NULL, SDL_GetVideoSurface(), &positionButtonBack);
    SDL_Flip(SDL_GetVideoSurface());

    while(continuer) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_MOUSEBUTTONUP:
                    if(event.button.x>=positionButtonBack.x && event.button.x<=positionButtonBack.x+233 && event.button.y>=positionButtonBack.y && event.button.y<=positionButtonBack.y+37) {
                        // Si souris sur bouton retour
                        return 1;
                        continuer = 0;
                    }if(event.button.x>=positionButtonL.x && event.button.x<=positionButtonL.x+233 && event.button.y>=positionButtonL.y && event.button.y<=positionButtonL.y+37){
                        //choix vitesse lente
                        return 1;
                        continuer = 0;
                    }if(event.button.x>=positionButtonH.x && event.button.x<=positionButtonH.x+233 && event.button.y>=positionButtonH.y && event.button.y<=positionButtonH.y+37){
                        //choix vitesse lente
                        return 2;
                        continuer = 0;
                    }
                break;
                case SDL_QUIT:
                    return 1;
                    continuer = 0;
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        return 1;
                        continuer = 0;
                    }
                break;
            }
        }
    }

    SDL_FreeSurface(option);
    SDL_FreeSurface(buttonH);
    SDL_FreeSurface(buttonL);
}
