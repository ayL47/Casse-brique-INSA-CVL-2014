#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

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
        float Vx; //la vitesse horizontale de la balle
        float Vy; //la vitesse verticale
        float k; //coefficient multiplicateur de vitesse
        int x, y; //Position x et y
}Ball;

#endif // CONSTANTES_H_INCLUDED
