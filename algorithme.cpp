#include "algorithme.h"



Algorithme::Algorithme(Robot r){
    this->d_robot=r;
}
void AlgorithmeMainDroite::typeAlgo(){

    while(d_robot.d_terrain.getGrille(d_robot.getX(),d_robot.getY())!='S'){
        if(d_robot.isObstacleDevant()){
            d_robot.turnLeft();

        }
        if(!d_robot.isObstacleDevant()){
            while(!d_robot.isObstacleDevant()){
                d_robot.forward();
            }
        }
        if(!d_robot.isObstacleDroite()){
            d_robot.turnRight();
        }
        d_robot.forward();
    }
}
