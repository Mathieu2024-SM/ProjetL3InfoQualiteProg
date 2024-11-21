#include "Robot.h"
#include <iostream>
#include <ctime>

// Constructeur
Robot::Robot(int xInitial, int yInitial,char forme)
    : x(xInitial), y(yInitial),d_forme{forme},d_ort{rand() % 4} {}

// Met à jour la position du robot
void Robot::afficherposition(int newX, int newY) {
    x = newX;
    y = newY;
    std::cout << "[Robot] Position mise à jour : (" << x << ", " << y << ")" << std::endl;
}

 // Getter pour la position en X
    int Robot:: getX() const {
        return x;
    }

    // Getter pour la position en Y
    int Robot:: getY() const {
        return y;
    }


int Robot::orientation()const
{
    return d_ort;
}
void Robot::tourneAGauche()
{
    d_ort = (d_ort - 1) % 4;
}
void Robot::tourneADroite()
{
    d_ort = (d_ort + 1) % 4;
}
