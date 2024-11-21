#ifndef ALGORITHME_H
#define ALGORITHME_H
#include "Robot.h"



class Algorithme{
    private:
        Robot d_robot;
    public:
        virtual ~Algorithme=default;
        Algorithme(Robot r); 
        virtual void typeAlgo()=0;
        
};

class AlgoMainDroite : public Algorithme{
    public:
        void typeAlgo()override;
};

class AlgoPledge : public Algorithme{
    public:
        void typeAlgo()override;
};








#endif
