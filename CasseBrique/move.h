#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

void moveBarre(SDL_Rect *positionBarre, int direction);
void moveBalle(SDL_Rect *positionBalle, Ball *ball, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR],int *newgame, int *briquesRestantes, SDL_Surface **imgchiffre);

#endif // MOVE_H_INCLUDED
