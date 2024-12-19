#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "terrain.h"

//#include "EtatRobot.h"


class Robot {
private:
    int x, y;
    int d_ort;

public:
    Robot(int xInitial, int yInitial);
    Robot();
    int getX() const;
    int getY() const;
    void afficherposition (int newX, int newY)const;

    int orientation()const;
    void tourneAGauche();
    void tourneADroite();
    void Avance();
    void recupereEtat();
    
    bool ObstacleDevant(Terrain t)const;
    bool ObstacleDroite(Terrain t)const;

     

};

#endif
