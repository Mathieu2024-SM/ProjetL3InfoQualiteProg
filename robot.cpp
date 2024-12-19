#include "Robot.h"
#include <iostream>
#include <ctime>

// Constructeur

Robot::Robot(int xInitial, int yInitial)
    : x(xInitial), y(yInitial),d_ort{rand() % 4} {}

Robot::Robot(){}

// Met � jour la position du robot
void Robot::afficherposition(int newX, int newY) {
    x = newX;
    y = newY;
    std::cout << "[Robot] Position mise � jour : (" << x << ", " << y << ")" << std::endl;
}

 // Getter pour la position en X
    int Robot:: getX() const {
        return x;
    }

    // Getter pour la position en Y
    int Robot:: getY() const {
        return y;
    }


int Robot::orientation()const
{
    return d_ort;
}
void Robot::tourneAGauche()
{
    d_ort = (d_ort - 1) % 4;
}
void Robot::tourneADroite()
{
    d_ort = (d_ort + 1) % 4;
}

bool Robot::ObstacleDevant(Terrain t){
    int obstacle_X=x;
    int obstacle_Y=y;

    if(d_ort == 2){
        obstacle_Y--;
        
    }
    if(d_ort==1){
        obstacle_X++;
        
    }
    if(d_ort==0){
        obstacle_Y++;
        
    }
    if(d_ort==3){
        obstacle_X--;
        
    }
    if(t.Obstacle(obstacle_X,obstacle_Y)){
        return true;
    }else{
        return false;
    }

}
bool Robot::ObstacleDroite(Terrain t){
    int direction_simule=d_ort;
                                                   
    if(d_ort == 2){
        d_ort=3;
    }
    if(d_ort==1){
        d_ort=2;                              
    }
    if(d_ort==0){
        d_ort=1;   
    }
    
    if(d_ort==3){
        d_ort=0;                                
    }
    bool obstacle=ObstacleDevant(t);
    d_ort=direction_simule;

    return obstacle;
    
}
void robot::recupereEtat()
{
    std::cout<<d_x<<' '<<d_y<<' '<<d_pos
}
