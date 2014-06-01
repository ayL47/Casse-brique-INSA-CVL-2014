#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

void moveBarre(SDL_Rect *positionBarre, int direction, int speed);
void moveBalle(SDL_Rect *positionBalle, Ball *ball, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR],int *newgame, int *briquesRestantes, SDL_Surface **imgchiffre, int *score, int *life);

#endif // MOVE_H_INCLUDED
