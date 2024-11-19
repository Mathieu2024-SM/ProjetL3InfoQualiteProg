#include "robot.h"

robot::robot(const geom::point& position):d_position{position},d_orientation{0}//j ai choisi une orientation au pif
{

}
geom::point robot::position()const
{
    return d_position;
}
void robot::avance(int pas)
{
    switch(d_orientation)
    {
      case 0 : d_position.moveTo(0,pas); break; //translation vers le haut
      case 1 : d_position.moveTo(-pas,0); break; //translation vers le gauche
      case 2 : d_position.moveTo(0,-pas); break; //translation vers le bas
      case 3 : d_position.moveTo(pas,0); break; //translation vers le droite

      default: ;
    }
}
void robot::tourneAGauche()
{
    d_orientation = (d_orientation - 1) % 4;
}
void robot::tourneADroite()
{
    d_orientation = (d_orientation + 1) % 4;
}
