#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "terrain.h"

//#include "EtatRobot.h"


class Robot {
private:
    int x, y;
    char d_forme;
    int d_ort;

public:
    Robot(int xInitial, int yInitial ,char forme);
    Robot();
    int getX() const;
    int getY() const;
    void afficherposition(int newX, int newY);

    int orientation()const;
    void tourneAGauche();
    void tourneADroite();
    void Avance();
    
    bool ObstacleDevant(Terrain t);
    bool ObstacleDroite(Terrain t);

     

};

#endif
