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

    SDL_Event eventSaisie;
    SDL_EnableUNICODE(1);

    int position = 0, continuerSaisie = 1;
    int nb = 0;
    while(continuerSaisie) {
        SDL_WaitEvent(&eventSaisie);
        if(eventSaisie.type == SDL_KEYDOWN){
            if(eventSaisie.key.keysym.sym == SDLK_RETURN){
                SDL_EnableUNICODE(0);
                continuerSaisie = 0;
            }
            else if(eventSaisie.key.keysym.sym == SDLK_SPACE){
                SDL_EnableUNICODE(0);
                continuerSaisie = 0;
            }
            else if(((eventSaisie.key.keysym.unicode & 0xFF00) == 0x0000) && (position + 1 < TAILLE_MAX_PSEUDO) ) {
                joueur->pseudo[position] = eventSaisie.key.keysym.unicode;
                position++;
                joueur->pseudo[position] = '\0';
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

    int b =0;
    b = joueur.pseudo[nb -1] - 97; // 97 est le code de 'a'

    SDL_Rect position;

    position.x = 80 + nb*10;
    position.y = 170;

    SDL_Surface **imglettre;
    imglettre = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*26);

    imglettre[0] = SDL_LoadBMP("images/lettres/a.bmp");
    imglettre[1] = SDL_LoadBMP("images/lettres/b.bmp");
    imglettre[2] = SDL_LoadBMP("images/lettres/c.bmp");
    imglettre[3] = SDL_LoadBMP("images/lettres/d.bmp");
    imglettre[4] = SDL_LoadBMP("images/lettres/e.bmp");
    imglettre[5] = SDL_LoadBMP("images/lettres/f.bmp");
    imglettre[6] = SDL_LoadBMP("images/lettres/g.bmp");
    imglettre[7] = SDL_LoadBMP("images/lettres/h.bmp");
    imglettre[8] = SDL_LoadBMP("images/lettres/i.bmp");
    imglettre[9] = SDL_LoadBMP("images/lettres/j.bmp");
    imglettre[10] = SDL_LoadBMP("images/lettres/k.bmp");
    imglettre[11] = SDL_LoadBMP("images/lettres/l.bmp");
    imglettre[12] = SDL_LoadBMP("images/lettres/m.bmp");
    imglettre[13] = SDL_LoadBMP("images/lettres/n.bmp");
    imglettre[14] = SDL_LoadBMP("images/lettres/o.bmp");
    imglettre[15] = SDL_LoadBMP("images/lettres/p.bmp");
    imglettre[16] = SDL_LoadBMP("images/lettres/q.bmp");
    imglettre[17] = SDL_LoadBMP("images/lettres/r.bmp");
    imglettre[18] = SDL_LoadBMP("images/lettres/s.bmp");
    imglettre[19] = SDL_LoadBMP("images/lettres/t.bmp");
    imglettre[20] = SDL_LoadBMP("images/lettres/u.bmp");
    imglettre[21] = SDL_LoadBMP("images/lettres/v.bmp");
    imglettre[22] = SDL_LoadBMP("images/lettres/w.bmp");
    imglettre[23] = SDL_LoadBMP("images/lettres/x.bmp");
    imglettre[24] = SDL_LoadBMP("images/lettres/y.bmp");
    imglettre[25] = SDL_LoadBMP("images/lettres/z.bmp");

    SDL_BlitSurface(imglettre[b], NULL, SDL_GetVideoSurface(), &position);

}

void initListe(Liste* maListe){
    *maListe = NULL;
}

Liste creerCellule(Joueur *player, int i){
    Liste cell;
    cell = (Liste) malloc(sizeof(cellule));
    cell->joueur = player;
    cell->joueur->score = player->score;
    cell->nxt = NULL;
    cell->joueur->classement = i;
    return cell;
}

int estVide(Liste maListe){
	return maListe==NULL;
}

void ajouteEnTete(Liste* maListe,Joueur *player){
    Liste uneListe = creerCellule(player, 1);
    uneListe->nxt = *maListe;
    *maListe = uneListe;
}

void insere(Liste* maListe,Joueur* player){
    Liste uneListe, aux;
    int i = 0;
    uneListe = *maListe;
        if((estVide(uneListe))||(uneListe->joueur->score < player->score)){
            ajouteEnTete(maListe, player);
        }else{
            //Je ne suis pas
            while((uneListe->nxt!=NULL) && (uneListe->nxt->joueur->score < player->score)){
                    uneListe  = uneListe->nxt;
                    i++;
            }
            aux = creerCellule(player, i);
            aux->nxt = uneListe->nxt;
            uneListe->nxt = aux;
        }
}

void affiche(){
    Liste maListe;
    char a;
    (maListe->joueur)->pseudo[1] = a;
    Joueur* test = maListe->joueur;
    int i = 1;
    if(!estVide(maListe)){
        while (maListe != NULL){
            for(i = 0; i<TAILLE_MAX_PSEUDO; i++){
                //Probleme ici, afficheTexte, veux un joueur, mais maliste.joueur c'est un *Joueur ...
                afficheTexte(*test, i);
            }
            maListe = maListe->nxt;
            }
    }
}

