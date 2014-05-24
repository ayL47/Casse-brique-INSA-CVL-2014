#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED
#include <SDL/SDL.h>

#define TAILLE_BLOC         25
#define NB_BLOCS_LARGEUR    20
#define NB_BLOCS_HAUTEUR    24
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
#define coeff 0.2
#define Mur_D LARGEUR_FENETRE-TAILLE_BLOC
#define BALLE_D positionBalle.x+TAILLE_BLOC

enum {MUR, BRIQUE, VIDE};
enum {GAUCHE, DROITE};

typedef struct        /* Gestion des événements */
{
    char key[SDLK_LAST];
} Input;

 typedef struct
 {
        double Vx; //la vitesse horizontale de la balle
        double Vy; //la vitesse verticale
        float k; //coefficient multiplicateur de vitesse
        float Ax; // Angle X
        float Ay; // Angle y
        int x, y; //Position x et y
} Ball;

#endif // CONSTANTES_H_INCLUDED
