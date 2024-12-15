#include "algorithme.h"
#include "terrain.h"


Algorithme::Algorithme(Robot r){
    this->d_robot=r;
}
void AlgoMainDroite::typeAlgo(Terrain terrain){

    while(terrain.afficherElementGrille(d_robot.getX(),d_robot.getY())!='A'){
        if(d_robot.ObstacleDevant(terrain)){
            d_robot.tourneAGauche();

        }
        if(!d_robot.ObstacleDevant(terrain)){
            while(!d_robot.ObstacleDevant(terrain)){
                d_robot.Avance();
            }
        }
        if(!d_robot.ObstacleDroite(terrain)){
            d_robot.tourneADroite();
        }
        d_robot.Avance();
    }
}


void AlgoPledge::typeAlgo(Terrain terrain){
    int compteur =0;
    while(terrain.afficherElementGrille(d_robot.getX(),d_robot.getY())!='A'){
        
        while(!d_robot.ObstacleDevant(terrain)){
            d_robot.Avance();
        }
        do{
            
            if(d_robot.ObstacleDevant(terrain)){
                d_robot.tourneAGauche();
                compteur++;
            }
            else if(!d_robot.ObstacleDroite(terrain)){
                d_robot.tourneADroite();
                compteur--;
                if(!d_robot.ObstacleDevant(terrain)){
                    d_robot.Avance();
                }         
            }
            else{
                d_robot.Avance();
            }
        }while(compteur!=0);      
    }
}