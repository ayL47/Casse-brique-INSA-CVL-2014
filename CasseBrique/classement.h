#ifndef CLASSEMENT_H_INCLUDED
#define CLASSEMENT_H_INCLUDED

liste saisieTexte(liste classement);
liste afficheImgSaisie(liste classement, int score);
void afficheTexte(SDL_Rect position, int unicodevalue);

cellule* creerCellule(Joueur *player, int nbClass);
int estVide(liste classement);
liste ajouteEnTete(liste classement, liste celluleAAjouter);
liste ajouteEnFin(liste classement, Joueur *player);
liste ajoutClassement(liste classement, liste nouvelleCellule);
void afficheClassement(liste classement, SDL_Surface **imgchiffre);
liste ajoutEnPosition(liste classement, liste celluleAAjouter, int position);
void saveJoueur();
void saveClassement(liste classement);



#endif // CLASSEMENT_H_INCLUDED
