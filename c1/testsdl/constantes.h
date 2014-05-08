#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED
#include <SDL/SDL.h>
#define OUI 1
#define NON 0
#define TAILLE_BLOC         25
#define NB_BLOCS_LARGEUR    20
#define NB_BLOCS_HAUTEUR    24
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR

enum {MUR, BRIQUE, FOND};
enum {GAUCHE, DROITE};

typedef struct        /* Gestion des événements */
{
    char key[SDLK_LAST];
} Input;

#endif // CONSTANTES_H_INCLUDED
