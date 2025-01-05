#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

#include<string>

using std::string;

class observateur {
public:
    observateur(int positionX, int positionY, string direction);

    int getPositionX()const;
    int getPositionY()const;
    string getDirection()const;

    void afficheObservation() const;

private:
    int d_positionX;
    int d_positionY;
    string d_direction;
};

#endif
