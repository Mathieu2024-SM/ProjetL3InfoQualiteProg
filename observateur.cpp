#include "observateur.h"
#include <iostream>

observateur::observateur(int positionX, int positionY, string direction)
    : d_positionX{positionX}, d_positionY{positionY}, d_direction{direction} {}

int observateur::getPositionX() const
{
    return d_positionX;
}

int observateur::getPositionY() const
{
    return d_positionY;
}

string observateur::getDirection() const
{
    return d_direction;
}

void observateur::afficheObservation() const {
    std::cout << "Position du robot : (" << d_positionX << ", " << d_positionY << ")"
              << " Direction: " << d_direction << std::endl;
}
