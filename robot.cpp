#include "Robot.h"
#include <iostream>
#include <ctime>
#include "terrain.h"

// Constructeurs
Robot::Robot(int xInitial, int yInitial)
    : d_x(xInitial), d_y(yInitial), d_orientation{rand() % 4}
{
    modifierFormeSelon(d_orientation);
}

Robot::Robot() : d_x(0), d_y(0), d_orientation(1), d_formeRobot(">") {}

// Destructeur
Robot::~Robot() {
    for (auto observateur : d_listeObservateurs) {
        delete observateur;
    }
    d_listeObservateurs.clear();
}

// Getters pour la position
int Robot::getX() const {
    return d_x;
}

int Robot::getY() const {
    return d_y;
}

int Robot::orientation() const {
    return d_orientation;
}

string Robot::formeRobot()const{
    return d_formeRobot;
}

std::vector<observateur*> Robot::getObservateurs() const {
    return d_listeObservateurs;
}

void Robot::recupereEtat() {
    d_listeObservateurs.push_back(new observateur(d_x, d_y, d_formeRobot));
}

// Place le robot en ses nouvelles positions
void Robot::placerSur(int newX, int newY) {
    d_x = newX;
    d_y = newY;
    recupereEtat();
}

void Robot::modifierFormeSelon(int orientation)
{
    switch(d_orientation)
    {
        case 2 : d_formeRobot = "V"; break;
        case 1 : d_formeRobot = ">"; break;
        case 0 : d_formeRobot = "^"; break;
        case 3 : d_formeRobot = "<"; break;
    }
}

void Robot::tourneAGauche() {
    d_orientation = ((d_orientation - 1) + 4) % 4;
    modifierFormeSelon(d_orientation);
    recupereEtat();
}

void Robot::tourneADroite() {
    d_orientation = (d_orientation + 1) % 4;
    modifierFormeSelon(d_orientation);
    recupereEtat();
}

void Robot::avance() {
    switch (d_orientation)
    {
        case 2: d_x++; break; //
        case 1: d_y++; break; //
        case 0: d_x--; break; //
        case 3: d_y--; break; //
    }
    modifierFormeSelon(d_orientation);
    recupereEtat();
}

bool Robot::ObstacleDevant(const Terrain& t){
    int obstacle_X = d_x;
    int obstacle_Y = d_y;

    switch (d_orientation) {
        case 2: obstacle_X++; break; //
        case 1: obstacle_Y++; break; //
        case 0: obstacle_X--; break; //
        case 3: obstacle_Y--; break; //
    }
    return t.Obstacle(obstacle_X, obstacle_Y);
}

bool Robot::ObstacleDroite(const Terrain& t) {
    int direction_conserve = d_orientation;

    switch (d_orientation) {
        case 2: d_orientation =3; break; //
        case 1: d_orientation =2; break; //
        case 0: d_orientation =1; break; //
        case 3: d_orientation =0; break; //
    }
    bool obstacle = ObstacleDevant(t);
    d_orientation = direction_conserve;

    return obstacle;
}
void Robot::positionnerAleatoirementSur(const Terrain& terrain) {
    std::srand(std::time(nullptr)); // Initialisation du générateur aléatoire
    int x, y;

    // Recherche d'une case valide (par exemple, une case libre '.')
    do {
        x = std::rand() % terrain.hauteur();
        y = std::rand() % terrain.largeur();
    } while (terrain.afficherElementGrille(x, y) != '.'); // Vérifie si la case est libre

    // Met à jour les coordonnées du robot
    d_x = x;
    d_y = y;
}
