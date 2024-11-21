#ifndef ROBOT_H
#define ROBOT_H
#include "point.h"

class robot{
public:
    robot(const geom::point& position);
    int positionX()const;
    int positionY()const;
    void avance(int pas);
    void tourneAGauche();
    void tourneADroite();
private:

    int d_x,d_y;
    int d_orientation; //0 = ^ ,1 = <, 2 = v, 3 = >
};
#endif // ROBOT_H
