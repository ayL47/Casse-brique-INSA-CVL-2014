#include <stdlib.h>
#include <SDL/SDL.h>
#include "menu.h"

void initMenu() {
    SDL_Surface *buttonPlay = NULL;
    SDL_Surface *buttonIns = NULL;
    SDL_Surface *instructions = NULL;
    SDL_Surface *buttonRank = NULL;
    SDL_Surface *rank = NULL;
    SDL_Surface *buttonQuit = NULL;
    SDL_Surface *buttonBack = NULL;
    SDL_Surface *menuImg = NULL;

    buttonPlay = SDL_LoadBMP("images/boutonJ_pas_survole.bmp");
    buttonIns = SDL_LoadBMP("images/boutonIns_pas_survole.bmp");
    instructions = SDL_LoadBMP("images/Instructions.bmp");
    buttonRank = SDL_LoadBMP("images/boutonS_pas_survole.bmp");
    rank = SDL_LoadBMP("images/Scores.bmp");
    buttonQuit = SDL_LoadBMP("images/boutonQ_pas_survole.bmp");
    buttonBack = SDL_LoadBMP("images/boutonR_pas_survole.bmp");
    menuImg = SDL_LoadBMP("images/menu.bmp");

    menu(buttonPlay, buttonIns, instructions, buttonRank, rank, buttonQuit, buttonBack, menuImg);

    // Lib�re les surface
    SDL_FreeSurface(buttonPlay);
    SDL_FreeSurface(buttonQuit);
    SDL_FreeSurface(buttonIns);
    SDL_FreeSurface(buttonRank);
    SDL_FreeSurface(instructions);
    SDL_FreeSurface(rank);
    SDL_FreeSurface(buttonBack);
}

void menu(SDL_Surface *buttonPlay, SDL_Surface *buttonIns, SDL_Surface *instructions, SDL_Surface *buttonRank, SDL_Surface *rank, SDL_Surface *buttonQuit, SDL_Surface *buttonBack, SDL_Surface *menu) {
    int continuer = 1;
    SDL_Event event;

    SDL_Rect positionButtonPlay;
    SDL_Rect positionButtonIns;
    SDL_Rect position;
    SDL_Rect positionButtonRank;
    SDL_Rect positionButtonQ;
    SDL_Rect positionButtonBack;

    positionButtonPlay.x = 125;
    positionButtonPlay.y = 200;
    positionButtonIns.x = positionButtonPlay.x;
    positionButtonIns.y = positionButtonPlay.y+40;
    position.x = 0;
    position.y = 0;
    positionButtonRank.x = positionButtonPlay.x;
    positionButtonRank.y = positionButtonIns.y+40;
    positionButtonQ.x = positionButtonPlay.x;
    positionButtonQ.y = positionButtonRank.y+40;
    positionButtonBack.x = 0;
    positionButtonBack.y = 563;

    SDL_BlitSurface(menu, NULL, SDL_GetVideoSurface(), &position);
    SDL_BlitSurface(buttonPlay, NULL, SDL_GetVideoSurface(), &positionButtonPlay);
    SDL_BlitSurface(buttonIns, NULL, SDL_GetVideoSurface(), &positionButtonIns);
    SDL_BlitSurface(buttonRank, NULL, SDL_GetVideoSurface(), &positionButtonRank);
    SDL_BlitSurface(buttonQuit, NULL, SDL_GetVideoSurface(), &positionButtonQ);

    SDL_Flip(SDL_GetVideoSurface());

    while(continuer) {
        SDL_WaitEvent(&event);

        switch(event.type) {
            case SDL_MOUSEBUTTONUP:
                if(event.button.x>=positionButtonPlay.x && event.button.x<=positionButtonPlay.x+233 && event.button.y>=positionButtonPlay.y && event.button.y<=positionButtonPlay.y+37) {
                    // Si souris sur bouton jouer
                    play();
                } else if(event.button.x>=positionButtonIns.x && event.button.x<=positionButtonIns.x+233 && event.button.y>=positionButtonIns.y && event.button.y<=positionButtonIns.y+37) {
                    // Si souris sur bouton instructions
                    instruction(instructions, position, buttonBack, positionButtonBack);

                    SDL_BlitSurface(menu, NULL, SDL_GetVideoSurface(), &position);
                    SDL_BlitSurface(buttonPlay, NULL, SDL_GetVideoSurface(), &positionButtonPlay);
                    SDL_BlitSurface(buttonIns, NULL, SDL_GetVideoSurface(), &positionButtonIns);
                    SDL_BlitSurface(buttonRank, NULL, SDL_GetVideoSurface(), &positionButtonRank);
                    SDL_BlitSurface(buttonQuit, NULL, SDL_GetVideoSurface(), &positionButtonQ);

                    SDL_Flip(SDL_GetVideoSurface());
                } else if(event.button.x>=positionButtonRank.x && event.button.x<=positionButtonRank.x+233 && event.button.y>=positionButtonRank.y && event.button.y<=positionButtonRank.y+37) {
                    // Si souris sur bouton scores
                    score(rank, position, buttonBack, positionButtonBack);

                    SDL_BlitSurface(menu, NULL, SDL_GetVideoSurface(), &position);
                    SDL_BlitSurface(buttonPlay, NULL, SDL_GetVideoSurface(), &positionButtonPlay);
                    SDL_BlitSurface(buttonIns, NULL, SDL_GetVideoSurface(), &positionButtonIns);
                    SDL_BlitSurface(buttonRank, NULL, SDL_GetVideoSurface(), &positionButtonRank);
                    SDL_BlitSurface(buttonQuit, NULL, SDL_GetVideoSurface(), &positionButtonQ);

                    SDL_Flip(SDL_GetVideoSurface());
                } else if(event.button.x>=positionButtonQ.x && event.button.x<=positionButtonQ.x+233 && event.button.y>=positionButtonQ.y && event.button.y<=positionButtonQ.y+37) {
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

void instruction(SDL_Surface *instructions, SDL_Rect position, SDL_Surface *buttonBack, SDL_Rect positionButtonBack) {
    int continuer = 1;
    SDL_Event event;

    SDL_BlitSurface(instructions, NULL, SDL_GetVideoSurface(), &position);
    SDL_BlitSurface(buttonBack, NULL, SDL_GetVideoSurface(), &positionButtonBack);
    SDL_Flip(SDL_GetVideoSurface());

    while(continuer) {
        SDL_WaitEvent(&event);
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

void score(SDL_Surface *rank, SDL_Rect position, SDL_Surface *buttonBack, SDL_Rect positionButtonBack) {
    int continuer = 1;
    SDL_Event event;

    SDL_BlitSurface(rank, NULL, SDL_GetVideoSurface(), &position);
    SDL_BlitSurface(buttonBack, NULL, SDL_GetVideoSurface(), &positionButtonBack);
    SDL_Flip(SDL_GetVideoSurface());

    while (continuer) {
        SDL_WaitEvent(&event);

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
