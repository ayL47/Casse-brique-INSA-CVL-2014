#ifndef CLASSEMENT_H_INCLUDED
#define CLASSEMENT_H_INCLUDED

void saisieTexte(Joueur *joueur);
void afficheImgSaisie(int score);
void afficheTexte(SDL_Rect position, int unicodevalue);

cellule* creerCellule(Joueur *player, int nbClass);
int estVide(liste classement);
liste ajouteEnTete(liste classement, Joueur *player);
liste ajouteEnFin(liste classement, Joueur *player);
void insere(liste classement, Joueur* player);
void affiche();

#endif // CLASSEMENT_H_INCLUDED
