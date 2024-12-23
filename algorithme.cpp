#include "algorithme.h"
#include "terrain.h"

Algorithme::Algorithme(Robot &r) : d_robot{r}{}

AlgoMainDroite::AlgoMainDroite(Robot &r) : Algorithme{r}{}

void AlgoMainDroite::affecterPositionDebutRobot(Terrain &t) {
    int maxAttempts = 100; //on le fixe
    int attempts = 0;

    while (attempts < maxAttempts) {
        auto [x, y] = t.positionAleatoireLibrePourRobot();
        if (t.afficherElementGrille(x, y) != 'X') {
            d_robot.placerSur(x, y);
            std::cout << "Position initiale du robot pour Main droite : (" << d_robot.getX() << ", " << d_robot.getY() << ")" << std::endl;
            return;
        }
        attempts++;
    }

    std::cerr << "Erreur : Impossible de placer le robot sur une position valide !" << std::endl;
}


void AlgoMainDroite::typeAlgo(Terrain& terrain){
    affecterPositionDebutRobot(terrain);

    if(!d_robot.ObstacleDevant(terrain)){
        while(!d_robot.ObstacleDevant(terrain)){
            d_robot.avance();
        }
    }

    while(terrain.afficherElementGrille(d_robot.getX(),d_robot.getY())!='A'){
        if(d_robot.ObstacleDevant(terrain)){
            d_robot.tourneAGauche();
        }
        else if(!d_robot.ObstacleDevant(terrain)){
            while(!d_robot.ObstacleDevant(terrain) && d_robot.ObstacleDroite(terrain)){
                d_robot.avance();
            }

            if(!d_robot.ObstacleDroite(terrain)){
                d_robot.tourneADroite();
                d_robot.avance();
            }
        }
    }
    std::cout << "Le robot a atteint la case d'arrivee !" << std::endl;
    std::cout<<"Element de la grille du robot :"<<terrain.afficherElementGrille(d_robot.getX(), d_robot.getY())<<std::endl;
}

AlgoPledge::AlgoPledge(Robot &r) : Algorithme{r}{}

void AlgoPledge::affecterPositionDebutRobot(Terrain &t) {
    int maxAttempts = 100;
    int attempts = 0;

    while (attempts < maxAttempts) {
        auto [x, y] = t.positionAleatoireLibrePourRobot();
        if (t.afficherElementGrille(x, y) != 'X') {
            d_robot.placerSur(x, y);
            std::cout << "Position initiale du robot pour Pledge : (" << d_robot.getX() << ", " << d_robot.getY() << ")" << std::endl;
            return;
        }
        attempts++;
    }

    std::cerr << "Erreur : Impossible de placer le robot sur une position valide !" << std::endl;
}

void AlgoPledge::typeAlgo(Terrain& terrain){
    int compteur =0;
    affecterPositionDebutRobot(terrain);
    while(terrain.afficherElementGrille(d_robot.getX(),d_robot.getY())!='A'){

        while(!d_robot.ObstacleDevant(terrain)){
            d_robot.avance();
            //terrain.afficherTerrain(d_robot.getX(),d_robot.getY(),d_robot.formeRobot());
        }
        do{
            if(terrain.afficherElementGrille(d_robot.getX(),d_robot.getY())=='A'){
                break;
            }

            if(d_robot.ObstacleDevant(terrain)){
                d_robot.tourneAGauche();
                compteur++;
            }
            else if(!d_robot.ObstacleDroite(terrain)){
                d_robot.tourneADroite();
                compteur--;
                if(!d_robot.ObstacleDevant(terrain)){
                    d_robot.avance();
                }
            }
            else{
                d_robot.avance();
            }
            //terrain.afficherTerrain(d_robot.getX(),d_robot.getY(),d_robot.formeRobot());
        }while(compteur!=0);
    }

    std::cout << "Le robot a atteint la case d'arrivee !" << std::endl;
    std::cout<<"Element de la grille du robot :"<<terrain.afficherElementGrille(d_robot.getX(), d_robot.getY())<<std::endl;

}
