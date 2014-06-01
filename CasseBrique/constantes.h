#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED
#include <SDL/SDL.h>

#define TAILLE_BLOC         25
#define NB_BLOCS_LARGEUR    20
#define NB_BLOCS_HAUTEUR    24
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
#define TAILLE_MAX_PSEUDO   20
#define LEVEL_MAX   4

enum {MUR, BRIQUE, VIDE, BRIQUEVIE, BRIQUEDOUBLE};
enum {GAUCHE, DROITE};



 typedef struct{
        double Vx; // Vitesse horizontale de la balle
        double Vy; // Vitesse verticale
} Ball;



typedef struct cellule cellule;
struct cellule {
    int classement;
    int score;
    char pseudo[TAILLE_MAX_PSEUDO];
    struct cellule *nxt;
};

typedef cellule* liste;

#endif // CONSTANTES_H_INCLUDED
