#ifndef ROBOT_H
#define ROBOT_H
#include "point.h"

class robot{
public:
    robot(const geom::point& position);
    geom::point position()const;
    void avance(int pas);
    void tourneAGauche();
    void tourneADroite();
private:

    geom::point d_position;
    int d_orientation; //0 = ^ ,1 = <, 2 = v, 3 = >
};
#endif // ROBOT_H
