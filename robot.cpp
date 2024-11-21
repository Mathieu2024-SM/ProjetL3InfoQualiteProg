#include "robot.h"

robot::robot(int x,int y):d_x{x},d_y{y},d_orientation{0}//j ai choisi une orientation au pif
{

}
int robot::positionX()const
{
    return d_x;
}
int robot::positionY()const
{
    return d_y;
}
void robot::avance(int pas)
{
    switch(d_orientation)
    {
      case 0 : d_y +=pas; break; //translation vers le haut
      case 1 : d_x -=pas; break; //translation vers le gauche
      case 2 : d_y -=pas; break; //translation vers le bas
      case 3 : d_x +=pas; break; //translation vers le droite

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
