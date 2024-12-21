#include "observateur.h"
#include <iostream>

observateur::observateur(int positionX, int positionY, int direction)
    : d_positionX{positionX}, d_positionY{positionY}, d_direction{direction}
{}

void observateur::afficheobservation() {
    std::cout << "Position du robot : (" << d_positionX << ", " << d_positionY << ")"
              << " Direction: " << d_direction << std::endl;
}
