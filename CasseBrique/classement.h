#ifndef CLASSEMENT_H_INCLUDED
#define CLASSEMENT_H_INCLUDED

liste saisieTexte(liste nouvelleCellule, SDL_Rect positionV);
liste afficheImgSaisie(liste classement, int score);
void afficheTexte(SDL_Rect position, int unicodevalue);


int estVide(liste classement);
liste ajouteEnTete(liste classement, liste celluleAAjouter);

liste ajoutClassement(liste classement, liste nouvelleCellule);
void afficheClassement(liste classement, SDL_Surface **imgchiffre);
liste ajoutEnPosition(liste classement, liste celluleAAjouter, int position);
void saveJoueur();

void saveClassement(liste classement);
liste readClassement(liste classement);

void calculScore(int score, SDL_Surface **imgchiffre, int classement);



#endif // CLASSEMENT_H_INCLUDED
