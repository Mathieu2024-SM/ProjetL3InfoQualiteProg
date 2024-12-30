#ifndef ALGORITHME_H
#define ALGORITHME_H
#include "Robot.h"

class Algorithme {
public:
    virtual ~Algorithme() = default;
    Algorithme(Robot &r);
    virtual void affecterPositionDebutRobot(Terrain& t) = 0;
    virtual void afficherTerrainSelonType(Terrain& t, int& typeTerrain)const = 0;
    virtual void typeAlgo(Terrain& t, int& typeTerrain) = 0;

protected:
    Robot& d_robot;
};

class AlgoMainDroite : public Algorithme {
public:
    AlgoMainDroite(Robot& r);
    void affecterPositionDebutRobot(Terrain& t) override;
    void afficherTerrainSelonType(Terrain& t, int& typeTerrain)const override;
    void typeAlgo(Terrain& t, int& typeTerrain) override;
};

class AlgoPledge : public Algorithme {
public:
    AlgoPledge(Robot &r);
    void affecterPositionDebutRobot(Terrain& t) override;
    void afficherTerrainSelonType(Terrain& t, int& typeTerrain)const override;
    void typeAlgo(Terrain& t, int& typeTerrain) override;
};

#endif
