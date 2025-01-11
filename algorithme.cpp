#include "algorithme.h"
#include "terrain.h"
#include <thread>
#include <chrono>

Algorithme::Algorithme(Robot &r) : d_robot{r}{}

// Constructeur
AlgoMainDroite::AlgoMainDroite(Robot& r) : Algorithme(r) {}

void AlgoMainDroite::affecterPositionDebutRobot(Terrain& t) {
        d_robot.positionnerAleatoirementSur(t);
}

void AlgoMainDroite::afficherTerrainSelonType(Terrain& t, int& typeTerrain) const
{
    // Efface la console pour une meilleure visualisation
    #ifdef _WIN32
        system("cls");
        #else
        system("clear");
    #endif

    switch(typeTerrain){
        case 0 : t.afficherTerrainUnicode(d_robot.getX(), d_robot.getY(),d_robot.formeRobot()); break;
        case 1 : t.afficherTerrainASCII(d_robot.getX(), d_robot.getY(),d_robot.formeRobot()); break;
        case 2 : t.afficherTerrainSimple(d_robot.getX(), d_robot.getY(),d_robot.formeRobot()); break;
    }
}

// Implémentation spécifique pour l'affichage console
void AlgoMainDroite::typeAlgo(Terrain& t, int& typeTerrain) {
    affecterPositionDebutRobot(t);  // Place le robot au début
    
    if(!d_robot.ObstacleDevant(t)){
        while(!d_robot.ObstacleDevant(t)){
            d_robot.avance();
        afficherTerrainSelonType(t,typeTerrain);   
        std::this_thread::sleep_for(std::chrono::milliseconds(250));             
        }
    }

    // Exécution de l'algorithme
    while (t.afficherElementGrille(d_robot.getX(), d_robot.getY()) != 'A') {
        if (d_robot.ObstacleDevant(t)) {
            d_robot.tourneAGauche();
        } else if (!d_robot.ObstacleDroite(t)) {
            d_robot.tourneADroite();
            d_robot.avance();
        } else{
            d_robot.avance();
        }

        // Affiche le terrain après chaque mouvement
        afficherTerrainSelonType(t,typeTerrain);

        // Pause pour observer les mouvements (ajuster la durée si nécessaire)
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    std::cout << "Le robot a atteint la case d'arrivee !\n";
    
}

AlgoPledge::AlgoPledge(Robot& r) : Algorithme(r) {}

void AlgoPledge::affecterPositionDebutRobot(Terrain& t) {
    d_robot.positionnerAleatoirementSur(t);
}

void AlgoPledge::afficherTerrainSelonType(Terrain& t, int& typeTerrain) const
{
    // Efface la console pour une meilleure visualisation
    #ifdef _WIN32
        system("cls");
        #else
        system("clear");
    #endif
    switch(typeTerrain){
        case 0 : t.afficherTerrainUnicode(d_robot.getX(), d_robot.getY(),d_robot.formeRobot()); break;
        case 1 : t.afficherTerrainASCII(d_robot.getX(), d_robot.getY(),d_robot.formeRobot()); break;
        case 2 : t.afficherTerrainSimple(d_robot.getX(), d_robot.getY(),d_robot.formeRobot()); break;
    }
}

void AlgoPledge::typeAlgo(Terrain& t, int& typeTerrain) {
    affecterPositionDebutRobot(t);
    int compteur = 0;  // Compte les changements de direction

    // Étape 1 : Aller tout droit jusqu'au mur
    while (!d_robot.ObstacleDevant(t)) {
        d_robot.avance();
        afficherTerrainSelonType(t,typeTerrain);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));  // Ralentir l'affichage
    }

    // Étape 2 : Longer le mur en tournant à droite (ou gauche)
    while (t.afficherElementGrille(d_robot.getX(), d_robot.getY()) != 'A') {
        while (!d_robot.ObstacleDevant(t)) {
            d_robot.avance();
            afficherTerrainSelonType(t,typeTerrain);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));  // Ralentir l'affichage
        }

        do {
            // Vérifier si le robot a atteint la case d'arrivée
            if (t.afficherElementGrille(d_robot.getX(), d_robot.getY()) == 'A') {
                std::cout << "Le robot a atteint la case d'arrivee !" << std::endl;
                break;  // Fin de l'algorithme
            }

            // Rotation et déplacement du robot selon les règles de l'algorithme de Pledge
            if (d_robot.ObstacleDevant(t)) {
                d_robot.tourneAGauche();
                compteur++;  // Augmenter le compteur quand on tourne à gauche
            }
            else if (!d_robot.ObstacleDroite(t)) {
                d_robot.tourneADroite();
                compteur--;  // Diminuer le compteur quand on tourne à droite
                if (!d_robot.ObstacleDevant(t)) {
                    d_robot.avance();  // Avancer si aucune obstruction devant
                }
            }
            else {
                d_robot.avance();  // Si aucune obstruction, continuer d'avancer
            }

            afficherTerrainSelonType(t,typeTerrain);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));  // Ralentir l'affichage

        } while (compteur != 0);  // Continuer à tourner tant que le compteur n'est pas à zéro
    }

    std::cout << "Le robot a termine l'algorithme de Pledge." << std::endl;
}


