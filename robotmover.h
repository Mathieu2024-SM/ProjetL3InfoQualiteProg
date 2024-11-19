#ifndef ROBOTMOVER_H
#define ROBOTMOVER_H
#include "robot.h"

class deplacementsRobot
{
    public:
        virtual ~deplacementsRobot() = default;
        virtual void deplaceRobot(robot& r) = 0;
};


class robotGauche : public deplacementsRobot{
    public:
        void deplaceRobot(robot& r)override;
};

class robotDroite : public deplacementsRobot{
    public:
        void deplaceRobot(robot& r)override;

};

class robotAvance : public deplacementsRobot{
    public:
        robotAvance(int pas);
        void deplaceRobot(robot& r)override;
    private:
        int d_pas;
};
#endif // ROBOTMOVER_H
