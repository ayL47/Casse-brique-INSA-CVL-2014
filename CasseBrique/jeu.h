#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include "constantes.h"

liste play(liste classement, SDL_Surface **imgchiffre, int speed);
int boucleJeu(SDL_Surface *briqueDouble, SDL_Surface *briqueVie, SDL_Surface *balle, SDL_Surface *barre, SDL_Surface *brique, SDL_Surface *mur, SDL_Surface *vide,int mapLevel[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR], SDL_Surface **imgchiffre, int speed);

#endif // JEU_H_INCLUDED
