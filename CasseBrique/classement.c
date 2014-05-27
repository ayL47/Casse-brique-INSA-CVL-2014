#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"
#include <math.h>
#include "classement.h"

void saisieTexte(Joueur *joueur) {
    SDL_Event eventSaisie;
    SDL_EnableUNICODE(1);

    int position = 0, continuerSaisie = 1;

    SDL_Rect positionT;
    positionT.x = 200;
    positionT.y = 200;

    while(continuerSaisie) {
        SDL_WaitEvent(&eventSaisie);
        if(eventSaisie.type == SDL_KEYDOWN){
            if(eventSaisie.key.keysym.sym == SDLK_RETURN){
                SDL_EnableUNICODE(0);
                continuerSaisie = 0;
            } else if(eventSaisie.key.keysym.sym == SDLK_SPACE){
                SDL_EnableUNICODE(0);
                continuerSaisie = 0;
            } else if(((eventSaisie.key.keysym.unicode & 0xFF00) == 0x0000) && (position + 1 < TAILLE_MAX_PSEUDO) ) {
                joueur->pseudo[position] = eventSaisie.key.keysym.unicode;
                joueur->pseudo[position] = '\0';
                afficheTexte(positionT, joueur->pseudo[position]);
                position++;
            }
        }

        SDL_Flip(SDL_GetVideoSurface());
    }
}

void afficheImgSaisie(int score) {
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

void afficheTexte(SDL_Rect position, int unicodevalue) {
    int lettre = unicodevalue - 97;

    if(lettre < 0) {
        return 0;
    }

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

    SDL_BlitSurface(imglettre[lettre], NULL, SDL_GetVideoSurface(), &position);
}



int estVide(liste classement) {
	return classement==NULL;
}

liste ajouteEnTete(liste classement, Joueur *player) {
    player->classement = 1;

    cellule* nouvelleCellule = malloc(sizeof(cellule));

    nouvelleCellule->joueur = player;
    nouvelleCellule->nxt = classement;

    return nouvelleCellule;
}

liste ajouteEnFin(liste classement, Joueur *player) {
    player->classement = 2;

    cellule* nouvelleCellule = malloc(sizeof(cellule));

    nouvelleCellule->joueur = player;
    nouvelleCellule->nxt = NULL;

    if(classement == NULL) {
        return nouvelleCellule;
    } else {
        cellule* temp = classement;

        while(temp->nxt != NULL) {
            temp = temp->nxt;
        }

        temp->nxt = nouvelleCellule;

        return classement;
    }
}

void ajoutEnPosition(liste classement, Joueur* player, int position) {
    int i = 0;

    player->classement = position;

    cellule* nouvelleCellule = malloc(sizeof(cellule));

    nouvelleCellule->joueur = player;
    nouvelleCellule->nxt = classement->nxt;
    classement->nxt = nouvelleCellule;

    return nouvelleCellule;
}

void insere(liste classement, Joueur* player)
{
    cellule *tmp = classement;
    if((estVide(classement))||(classement->joueur->score < player->score)){
            ajouteEnTete(classement, player);
        } else {
            //Je ne suis pas
            while((tmp->nxt!=NULL) && (tmp->nxt->joueur->score < player->score)){
                    tmp = tmp->next;
                    i++;
            }
        }
    return i;
}


void affiche(liste classement) {
    SDL_Rect positionLettre;

    int position = 0;

    positionLettre.x = 80;
    positionLettre.y = 250;

    Joueur joueurTest;
    joueurTest.pseudo[0] = 'a';
    joueurTest.pseudo[1] = 'b';
    joueurTest.score = 50;

    Joueur joueurTest2;
    joueurTest2.pseudo[0] = 'c';
    joueurTest2.pseudo[1] = 'd';
    joueurTest2.score = 60;

    classement = ajouteEnTete(classement, &joueurTest);
    classement = ajouteEnFin(classement, &joueurTest2);


    cellule *uneCellule = classement;
    Joueur joueurAAfficher;

    while(!estVide(uneCellule)) {
        joueurAAfficher = *(uneCellule->joueur);

        while(classement->joueur->pseudo[position] != '\0') {
            afficheTexte(positionLettre, classement->joueur->pseudo[position]);
            position++;
            positionLettre.x+10;
        }
        uneCellule = uneCellule->nxt; // une ligne de mon classement
        positionLettre.y+10;
    }

    SDL_Flip(SDL_GetVideoSurface());


}

void ajoutClassement(liste classement, int score){

    classement.joueur.score = score;
    afficheImgSaisie(score);




}

