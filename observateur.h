#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

class observateur {
public:
    observateur(int positionX, int positionY, int direction);

    int getPositionX()const;
    int getPositionY()const;
    int getDirection()const;

    void afficheObservation() const;

private:
    int d_positionX;
    int d_positionY;
    int d_direction;
};

#endif
