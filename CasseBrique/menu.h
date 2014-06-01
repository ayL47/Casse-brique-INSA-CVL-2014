#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "constantes.h"

void initMenu(liste classement);
void menu(SDL_Surface **imgchiffre, liste classement, SDL_Surface *buttonPlay, SDL_Surface *buttonIns, SDL_Surface *instructions, SDL_Surface *buttonRank, SDL_Surface *rank, SDL_Surface *buttonQuit, SDL_Surface *buttonBack, SDL_Surface *menu, SDL_Surface *buttonO);
void score(SDL_Surface **imgchiffre, liste classement, SDL_Surface *rank, SDL_Rect position, SDL_Surface *buttonBack, SDL_Rect positionButtonBack);
void instruction(SDL_Surface *instructions, SDL_Rect position, SDL_Surface *buttonBack, SDL_Rect positionButtonBack);
int option(SDL_Rect position, SDL_Surface *buttonBack, SDL_Rect positionButtonBack);
int option(SDL_Rect position, SDL_Surface *buttonBack, SDL_Rect positionButtonBack);

#endif // MENU_H_INCLUDED
