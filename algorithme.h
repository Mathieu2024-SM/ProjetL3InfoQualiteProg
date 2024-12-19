#ifndef ALGORITHME_H
#define ALGORITHME_H
#include "Robot.h"



class Algorithme{
    private:
        Robot d_robot;
    public:
        virtual ~Algorithme()=default;
        Algorithme(Robot r); 
        virtual void typeAlgo(const Terrain& t)=0;
        
};


//////////////////////////////////////////////////
////////////////// CLASSE FILLE //////////////////
//////////////////////////////////////////////////


class AlgoMainDroite : public Algorithme{
    public:
        void typeAlgo(const Terrain& t)override;
};

class AlgoPledge : public Algorithme{
    public:
        void typeAlgo(const Terrain& t)override;
};








#endif
