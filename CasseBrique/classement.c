#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "level.h"
#include "jeu.h"
#include "constantes.h"
#include "move.h"
#include <math.h>
#include "classement.h"

/**
*   Fonctions qui gère le classement mais également son affichage
**/


//Prend une liste en caractère et là renvoit avec le pseudo du joueur rempli
liste saisieTexte(liste nouvelleCellule, SDL_Rect positionV) {
    SDL_Event eventSaisie;
    //permet de récuperer le code ASCII des lettres
    SDL_EnableUNICODE(1);


    int position = 0, continuerSaisie = 1;

    SDL_Rect positionT;
    positionT.x = 96;
    positionT.y = 200;

    while(continuerSaisie) {
        SDL_WaitEvent(&eventSaisie);
        if(eventSaisie.type == SDL_KEYDOWN){
            if(eventSaisie.key.keysym.sym == SDLK_RETURN){
                SDL_EnableUNICODE(0);
                nouvelleCellule->pseudo[position +1] = '\0';
                continuerSaisie = 0;
            } else if(eventSaisie.key.keysym.sym == SDLK_SPACE){
                SDL_EnableUNICODE(0);
                continuerSaisie = 0;
            } else if(((eventSaisie.key.keysym.unicode & 0xFF00) == 0x0000) && (position + 1 < TAILLE_MAX_PSEUDO) ) {
                nouvelleCellule->pseudo[position] = eventSaisie.key.keysym.unicode;
                afficheTexte(positionT, nouvelleCellule->pseudo[position]);
                position++;
                positionT.x += 25;
            }
        }
        if(eventSaisie.type == SDL_MOUSEBUTTONUP){
            if(eventSaisie.button.x>=positionV.x && eventSaisie.button.x<=positionV.x+233 && eventSaisie.button.y>=positionV.y && eventSaisie.button.y<=positionV.y+37){
                SDL_EnableUNICODE(0);
                nouvelleCellule->pseudo[position +1] = '\0';
                continuerSaisie = 0;
            }
        }
        SDL_Flip(SDL_GetVideoSurface());
    }

    return nouvelleCellule;
}
//Affiche l'image de demande de saisie du pseudo au joueur
liste afficheImgSaisie(liste nouvelleCellule, int score) {
    SDL_Surface *saisie = NULL;
    SDL_Surface *buttonV;


    nouvelleCellule->score = score;
    SDL_Rect position;
    SDL_Rect positionV;

    position.x = 0;
    position.y = 0;
    positionV.x = 125;
    positionV.y = 250;

    saisie = SDL_LoadBMP("images/saisie.bmp");
    buttonV = SDL_LoadBMP("images/boutonV.bmp");


    SDL_BlitSurface(saisie, NULL, SDL_GetVideoSurface(), &position);
    SDL_BlitSurface(buttonV, NULL, SDL_GetVideoSurface(), &positionV);


    SDL_Flip(SDL_GetVideoSurface());
    //Récupère le pseudo du joueur
    nouvelleCellule = saisieTexte(nouvelleCellule, positionV);

    SDL_FreeSurface(saisie);
    SDL_FreeSurface(buttonV);



    return nouvelleCellule;
}
//Affiche une lettre, en passant par paramètre son code ASCII
void afficheTexte(SDL_Rect position, int unicodevalue){
    // Le code de A est 97, comme nous avons inutialisé son image pour imglettre[0], nous enlevons la valeur de son code
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
    SDL_Flip(SDL_GetVideoSurface());

    SDL_FreeSurface(*imglettre);
}


//vérifie que le classement soit vide
int estVide(liste classement){
	return classement == NULL;
}
//Ajout de la nouvelle cellule contenant le joueur en tete de liste
liste ajouteEnTete(liste classement, liste celluleAAjouter) {
    cellule* nouvelleCellule = malloc(sizeof(cellule));

    nouvelleCellule->classement = 1;
    nouvelleCellule->score = celluleAAjouter->score;

    int position = 0;
    while(celluleAAjouter->pseudo[position] != '\0' && position < TAILLE_MAX_PSEUDO) {
        nouvelleCellule->pseudo[position] = celluleAAjouter->pseudo[position];
        position++;
    }

    nouvelleCellule->nxt = classement;

    return nouvelleCellule;
}


//Ajoute a une position donné la cellule du joueur dans la liste
liste ajoutEnPosition(liste classement, liste celluleAAjouter, int position) {
    cellule* nouvelleCellule = malloc(sizeof(cellule));
    nouvelleCellule->nxt = NULL;

    nouvelleCellule->classement = position;
    nouvelleCellule->score = celluleAAjouter->score;

    int pos = 0;
    while(celluleAAjouter->pseudo[pos] != '\0' && pos < TAILLE_MAX_PSEUDO) {
        nouvelleCellule->pseudo[pos] = celluleAAjouter->pseudo[pos];
        pos++;
    }

    nouvelleCellule->nxt = classement->nxt;

    classement->nxt = nouvelleCellule;

    return nouvelleCellule;
}
//Ajoute au classement une nouvelle cellule contenant le joueur
liste ajoutClassement(liste classement, liste nouvelleCellule) {
    int i = 1;
    cellule *premierElem = classement;
    //Si la liste est vide, alors c'est le 1er élemebt
    if(estVide(classement)) {
        premierElem = ajouteEnTete(classement, nouvelleCellule);
    }else {
        //Si le score du nouveau joueur est supérieur au 1er actuel, on place le nouveau joueur en tete de liste
        if(classement->score < nouvelleCellule->score) {
            premierElem = ajouteEnTete(classement, nouvelleCellule);
            classement = premierElem->nxt;
            i++;
        }else {
            i++;
            //Tant que le score du nouveau joueur est inférieur au score du joueur de la liste, on avance dans la liste
            while((classement != NULL) && (classement->nxt != NULL) && (classement->nxt->score > nouvelleCellule->score)){
                classement = classement->nxt;
                i++;
            }
            //On ajoute le nouveau joueur à la liste, à la position défini
            ajoutEnPosition(classement, nouvelleCellule, i);
            //On avance dans la liste
            classement = classement->nxt;
        }

        while(classement != NULL) {
            classement->classement = i;

            classement = classement->nxt;
            i++;
        }
    }

    return premierElem;
}

//Affiche le classement
void afficheClassement(liste classement, SDL_Surface **imgchiffre) {
    SDL_Rect positionLettre, positionScore, positionClassement;

    int position = 0;

    positionLettre.x = 110;
    positionLettre.y = 152;
    positionClassement.x = 50;
    positionClassement.y = 150;

    cellule *uneCellule = classement;
    int scorejoueur;
    int classementJoueur;

    while(!estVide(uneCellule)) {
        while(uneCellule->pseudo[position] != '\0' && position < TAILLE_MAX_PSEUDO) {
            //Tant qu'il y a des lettres dans le pseudo, on affiche la lettre, ce qui donne le pseudo entré
            afficheTexte(positionLettre, uneCellule->pseudo[position]);
            //On avance de 1 la position dans le tableau de char contenant le pseudo
            position++;
            positionLettre.x += 25;
        }
        //On récupère le score du joueur
        scorejoueur = uneCellule->score;
        //On récupère le classement du joueur
        classementJoueur = uneCellule->classement;
        //On affiche le score du joueur
        calculScore(scorejoueur, imgchiffre, classementJoueur);

        //On affiche le classement du joueur
        blitChiffre(classementJoueur, imgchiffre, &positionClassement);
        //On avance dans la liste
        uneCellule = uneCellule->nxt;
        positionLettre.y += 25;
        position = 0;
        positionLettre.x = 110;
        positionClassement.y += 25;
    }

    SDL_Flip(SDL_GetVideoSurface());
}

/*void saveJoueur(Joueur *joueur){
    FILE *fichier = NULL;
    char strClassement[501] = {0};
    char *aLine = NULL, *aPlayer = NULL;
    char pseudo[TAILLE_MAX_PSEUDO];
    int score = 0, i = 0;

    fichier = fopen("classement.txt", "r+");
    fprintf(fichier, "Classement \t Pseudo \t Score \n");
    fprintf(fichier, "%d \t\t %s \t\t %d \n", joueur->classement, joueur->pseudo, joueur->score);
    fclose(fichier);
}*/

//Sauvegarde du classement dans un fichier .txt
void saveClassement(liste classement){
    FILE *fichier = NULL;
    cellule *uneCellule = classement;

    fichier = fopen("classement.txt", "r+");
    //fprintf(fichier, "Classement \t Pseudo \t Score \n");
    while(uneCellule != NULL){
        fprintf(fichier, "%d\n%s\n%d\n", uneCellule->classement, uneCellule->pseudo, uneCellule->score);
        uneCellule = uneCellule->nxt;
    }
    fclose(fichier);
}

//On lit le classement sauvegardé dans le fichier .txt
void readClassement(liste classement){
    FILE *fichier = NULL;
    int i = 0;
    int b, c;
    char str1[3]="", str2[20]="", str3[3]="";
    cellule player;
    char pseudo[20];
    cellule* nouvelleCellule = malloc(sizeof(cellule));
    nouvelleCellule->nxt = NULL;

    fichier = fopen("classement.txt", "r");
    while (fichier != NULL) {
            fgets(str1, 3, fichier);
            int a = atoi(str1);
            nouvelleCellule->classement = a;
            b = nouvelleCellule->classement;
            fgets(str2, 20, fichier);
            while (str2[i] != '\n'){
                nouvelleCellule->pseudo[i] = str2[i];
                i++;
            }
            fgets(str3, 5, fichier);
            c = atoi(str3);
            nouvelleCellule->score = c;
            i = 0;
            classement = ajoutClassement(classement, nouvelleCellule);
            nouvelleCellule = nouvelleCellule->nxt;
    }

    fclose(fichier);
}


//On calcul et affiche le score
void calculScore(int score, SDL_Surface **imgchiffre, int classement) {
    SDL_Rect positionChiffreC, positionChiffreD, positionChiffreU;

    positionChiffreC.x = 350;
    positionChiffreC.y = 150 + (classement-1) * 25;
    positionChiffreD.x = positionChiffreC.x + 25;
    positionChiffreD.y = positionChiffreC.y ;
    positionChiffreU.x = positionChiffreD.x + 25;
    positionChiffreU.y = positionChiffreC.y ;
    //c pour centaine
    //d pour disaine, %10 donne le chiffre le plus à droite
    //u unité
    int c = score/100;
    int d = (score/10)%10;
    int u = (score%10);
    //On colle les chiffres a la position désirée
    blitChiffre(c, imgchiffre, &positionChiffreC);
    blitChiffre(d, imgchiffre, &positionChiffreD);
    blitChiffre(u, imgchiffre, &positionChiffreU);
}
