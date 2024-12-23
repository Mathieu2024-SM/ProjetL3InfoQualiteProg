#ifndef ROBOTMOVER_H
#define ROBOTMOVER_H
#include "robot.h"

class deplacementsRobot {
public:
    virtual ~deplacementsRobot() = default;
    virtual void deplaceRobot(Robot& r) = 0;
};

class robotGauche : public deplacementsRobot {
public:
    void deplaceRobot(Robot& r) override;
};

class robotDroite : public deplacementsRobot {
public:
    void deplaceRobot(Robot& r) override;
};

class robotAvance : public deplacementsRobot {
public:
    robotAvance(int pas);
    void deplaceRobot(Robot& r) override;

private:
    int d_pas;
};

#endif