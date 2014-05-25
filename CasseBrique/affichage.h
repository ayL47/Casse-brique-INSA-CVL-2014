#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

void afficheScores(SDL_Surface **imgchiffre);
void blitChiffre(int value, SDL_Surface **imgchiffre, SDL_Rect *position);
void majScore(int *score, SDL_Surface **imgchiffre);
void afficheLoose();
void afficheWin();
void majLife(int life, SDL_Surface **imgchiffre;
void afficheLife(SDL_Surface **imgchiffre);

#endif // AFFICHAGE_H_INCLUDED
