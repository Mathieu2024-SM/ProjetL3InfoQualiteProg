#ifndef ALGORITHME_H
#define ALGORITHME_H
#include "Robot.h"



class Algorithme{
    public:
        virtual ~Algorithme()=default;
        virtual void typeAlgo(const Terrain& t,robot &r)=0;   
};


//////////////////////////////////////////////////
////////////////// CLASSE FILLE //////////////////
//////////////////////////////////////////////////


class AlgoMainDroite : public Algorithme{
    public:
        void typeAlgo(const Terrain& t,robot &r)override;
};

class AlgoPledge : public Algorithme{
    public:
        void typeAlgo(const Terrain& t,robot &r)override;
};








#endif
