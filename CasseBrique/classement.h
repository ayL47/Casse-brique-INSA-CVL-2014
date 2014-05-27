#ifndef CLASSEMENT_H_INCLUDED
#define CLASSEMENT_H_INCLUDED

void saisieTexte(Joueur *joueur);
void afficheImgSaisie(Joueur *joueur);
void afficheTexte(SDL_Rect position, int unicodevalue);

cellule* creerCellule(Joueur *player, int nbClass);
int estVide(liste classement);
liste ajouteEnTete(liste classement, Joueur *player);
liste ajouteEnFin(liste classement, Joueur *player);
void insere(liste classement, Joueur* player);
void affiche(liste classement);
void ajoutEnPosition(liste classement, Joueur* player, int position)

#endif // CLASSEMENT_H_INCLUDED
