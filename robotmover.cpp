#include "robotmover.h"

void robotGauche::deplaceRobot(Robot& r)
{
    r.tourneAGauche();
     // r.recupereEtat();
}
void robotDroite::deplaceRobot(Robot& r)
{
    r.tourneADroite();
   // r.recupereEtat();
}
robotAvance::robotAvance(int pas):d_pas{pas}
{

}
void robotAvance::deplaceRobot(Robot& r)
{
    r.Avance();
     // r.recupereEtat();
}
