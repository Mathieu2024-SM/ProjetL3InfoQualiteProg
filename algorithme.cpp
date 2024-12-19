#include "algorithme.h"
#include "terrain.h"



void AlgoMainDroite::typeAlgo(const Terrain& t,robot &r){

    while(terrain.afficherElementGrille(r.getX(),r.getY())!='A'){
        if(r.ObstacleDevant(t)){
            r.tourneAGauche();

        }
        if(!r.ObstacleDevant(t)){
            while(!r.ObstacleDevant(t)){
                r.Avance();
            }
        }
        if(!r.ObstacleDroite(t)){
            r.tourneADroite();
        }
        r.Avance();
    }
}


void AlgoPledge::typeAlgo(const Terrain& t,robot &r){
    int compteur =0;
    while(t.afficherElementGrille(r.getX(),r.getY())!='A'){
        
        while(!r.ObstacleDevant(t)){
            r.Avance();
        }
        do{
            
            if(r.ObstacleDevant(t)){
                r.tourneAGauche();
                compteur++;
            }
            else if(!r.ObstacleDroite(t)){
                r.tourneADroite();
                compteur--;
                if(!r.ObstacleDevant(t)){
                    r.Avance();
                }         
            }
            else{
                r.Avance();
            }
        }while(compteur!=0);      
    }
}
