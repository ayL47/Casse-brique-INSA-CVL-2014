#ifndef CLASSEMENT_H_INCLUDED
#define CLASSEMENT_H_INCLUDED

void saisieTexte(Joueur *joueur);
void afficheImgSaisie(Joueur *joueur, int score);
void afficheTexte(SDL_Rect position, int unicodevalue);

cellule* creerCellule(Joueur *player, int nbClass);
int estVide(liste classement);
liste ajouteEnTete(liste classement, Joueur *player);
liste ajouteEnFin(liste classement, Joueur *player);
int insere(liste classement, Joueur *player);
void affiche(liste classement);
liste ajoutEnPosition(liste classement, Joueur* player, int position);
void saveJoueur();
void saveClassement(liste classement);


#endif // CLASSEMENT_H_INCLUDED
