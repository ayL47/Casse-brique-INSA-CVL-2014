#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED
#include <SDL/SDL.h>

#define TAILLE_BLOC         25
#define NB_BLOCS_LARGEUR    20
#define NB_BLOCS_HAUTEUR    24
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR

enum {MUR, BRIQUE, VIDE};
enum {GAUCHE, DROITE};

typedef struct        /* Gestion des �v�nements */
{
    char key[SDLK_LAST];
} Input;

 struct Balle {
        float x; //la vitesse horizontale de la balle
        float y; //la vitesse verticale
        float k; //coefficient multiplicateur de vitesse
              }

#endif // CONSTANTES_H_INCLUDED