#ifndef ALGORITHME_H
#define ALGORITHME_H
#include "Robot.h"

class Algorithme {
public:
    virtual ~Algorithme() = default;
    Algorithme(Robot &r);
    virtual void affecterPositionDebutRobot(Terrain& t) = 0;
    virtual void typeAlgo(Terrain& t) = 0;

protected:
    Robot& d_robot;
};

class AlgoMainDroite : public Algorithme {
public:
    AlgoMainDroite(Robot& r);
    void affecterPositionDebutRobot(Terrain& t) override;
    void typeAlgo(Terrain& t) override;
};

class AlgoPledge : public Algorithme {
public:
    AlgoPledge(Robot &r);
    void affecterPositionDebutRobot(Terrain& t) override;
    void typeAlgo(Terrain& t) override;
};

#endif
