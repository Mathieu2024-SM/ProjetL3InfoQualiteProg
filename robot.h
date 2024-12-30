#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "observateur.h"
#include <vector>
#include <string>

using std::string;

class Terrain;

class Robot {
private:
    int d_x, d_y;
    int d_orientation;
    string d_formeRobot;
    std::vector<observateur*> d_listeObservateurs;

public:
    Robot(int xInitial, int yInitial);
    Robot();
	~Robot(); // Destructeur pour gérer la mémoire des observateurs

    int getX() const;
    int getY() const;
    int orientation() const;
    std::vector<observateur*> getObservateurs() const;
    string formeRobot() const;

    void placerSur(int newX, int newY);
    void modifierFormeSelon(int orientation);

    void tourneAGauche();
    void tourneADroite();
    void avance();

    void recupereEtat();

    bool ObstacleDevant(const Terrain& t);
    bool ObstacleDroite(const Terrain& t);
    void positionnerAleatoirementSur(const Terrain& terrain);

};

#endif
