#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H


class observateur
{
    public:
        observateur(int positionX , int positionY , int direction );
        void afficheObservation();

    private:
        int d_positionX;
        int d_positionY;
        int d_direction;

};

#endif // OBSERVATEUR_H
