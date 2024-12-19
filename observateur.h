#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H


class observateur
{
    public:
        observateur(int x , int y , int direction );
        void afficheobservation();




    private:
        int d_x;
        int d_y;
        int d_direction;

};

#endif // OBSERVATEUR_H
