#include "robotmover.h"

void robotGauche::deplaceRobot(robot& r)
{
    r.tourneAGauche();
}
void robotDroite::deplaceRobot(robot& r)
{
    r.tourneADroite();
}
robotAvance::robotAvance(int pas):d_pas{pas}
{

}
void robotAvance::deplaceRobot(robot& r)
{
    r.avance(d_pas);
}
