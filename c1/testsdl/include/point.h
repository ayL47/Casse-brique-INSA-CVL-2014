#ifndef POINT_H
#define POINT_H


class Point
{
    private:
    //Les coordonnées x et y du point
    int x, y;

    //La vitesse du point
    int xVel, yVel;

    public:
    //Initialisation des variables
    Point();

    //Recupere la touche pressee et ajuste la vitesse du point
    void handle_input();

    //Montre le point sur l'ecran
    void show();
};


#endif // POINT_H
