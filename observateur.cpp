#include "observateur.h"
#include <iostream>

observateur::observateur(int x, int y, int direction)
    : d_x{x}, d_y{y}, d_direction{direction}
{}

void observateur::afficheobservation() {
    std::cout << "Position du robot : (" << d_x << ", " << d_y << ")"
              << " Direction: " << d_direction << std::endl;
}
