#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

void moveBarre(SDL_Rect *positionBarre, int direction);
void moveBall(SDL_Rect *positionBalle,Ball *ball, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *Vx, int *Vy, int *newgame, int *briquesRestantes);
void moveBalle(SDL_Rect *positionBalle, Ball *ball, SDL_Rect *positionBarre, int mapLevel[][NB_BLOCS_LARGEUR], int *Vy, int *Vx,int *newgame, int *briquesRestantes);

#endif // MOVE_H_INCLUDED
