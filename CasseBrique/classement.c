#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"
#include <math.h>
#include "classement.h"

void saisieTexte(Joueur *joueur){

    SDL_Event eventSaisie; // tu crée une variable d'evenements .
    SDL_EnableUNICODE(1);  // Cette ligne permet d'activer l'UNICODE, c'est a dire que les caracteres speciaux sont acceptés

    int position = 0, continuerSaisie = 1; // pour continuer la saisie et position permet de se repéré dans le tableau (pour pas supprimer une ancienne entrée)
    int nb = 0;
    while(continuerSaisie) // La boucle (pour que des que le joueur appuis sur le clavier, il se passe un evenement
    {
        SDL_WaitEvent(&eventSaisie);
        if(eventSaisie.type == SDL_KEYDOWN)
        {
            if(eventSaisie.key.keysym.sym == SDLK_BACKSPACE) // Si il appuis sur la touche retour arriere...
            {
                position--; // ... on  recule le curseur de 1 (comme un editeur de texte)
                joueur->pseudo[position] = '\0'; // Efface l'ancienne saisie
            }
            if(eventSaisie.key.keysym.sym == SDLK_RETURN)
            {
                SDL_EnableUNICODE(0); // Si il appuis sur entrée , on desactive l'UNICODE
                continuerSaisie = 0; // On quitte la boucle
            }
            if(((eventSaisie.key.keysym.unicode & 0xFF00) == 0x0000) && (position + 1 < TAILLE_MAX_PSEUDO) ) // ça je n'est pas trop compris, mais le deuxieme argument et que si le curseur n'est pas a la fin du tableau ...
            {
                joueur->pseudo[position] = eventSaisie.key.keysym.unicode; // on enregistre la touche appuyée dans le tableau à la position du curseur
                position++; // on avance le curseur de 1 (pour évité de supprimé l'ancienne entrée de l'utilisateur
                joueur->pseudo[position] = '\0'; // ...et on vide cette' nouvelle case pour la prochaine entrée.
                nb++;
                afficheTexte(*joueur, nb);
            }
        }
        SDL_Flip(SDL_GetVideoSurface());
    }
}

void afficheImgSaisie (int life, int score){

    Joueur joueur;
    joueur.score = score;

    SDL_Surface *saisie = NULL;

    SDL_Rect position;

    position.x = 0;
    position.y = 0;

    saisie = SDL_LoadBMP("images/saisie.bmp");

    SDL_BlitSurface(saisie, NULL, SDL_GetVideoSurface(), &position);

    SDL_Flip(SDL_GetVideoSurface());
    saisieTexte(&joueur);

}

void afficheTexte (Joueur joueur, int nb){

    int i = 0, j = 0, b =0;
    b = joueur.pseudo[nb -1] - 97;

    SDL_Rect position;

    position.x = 80 + nb*10;
    position.y = 170;

    SDL_Surface **imglettre;
    imglettre = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*26);

    imglettre[0] = SDL_LoadBMP("images/a.bmp");
    imglettre[1] = SDL_LoadBMP("images/b.bmp");
    imglettre[2] = SDL_LoadBMP("images/c.bmp");


    SDL_BlitSurface(imglettre[b], NULL, SDL_GetVideoSurface(), &position);

}
