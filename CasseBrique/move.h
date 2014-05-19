#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

void moveBarre(SDL_Rect *positionBarre, int direction);
void moveBall(SDL_Rect *positionBalle, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *verti, int *hori);


#endif // MOVE_H_INCLUDED
