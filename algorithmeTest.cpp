#include "doctest.h"
#include "algorithme.h"
#include "terrain.h"
#include "robot.h"

TEST_CASE("Test des algorithmes de déplacement") {
    Terrain terrain;
    terrain.chargerTerrainDepuis("terrain_test.txt");

    SUBCASE("Algorithme de la Main Droite") {
        Robot robot;
        AlgoMainDroite algo(robot);
        algo.typeAlgo(terrain);

        // Suivre la position finale du robot
        std::cout << "Position finale du robot pour Main Droite : (" << robot.getX() << ", " << robot.getY() << ")" << std::endl;
        CHECK(terrain.afficherElementGrille(robot.getX(), robot.getY()) == 'A');
    }

    SUBCASE("Algorithme de Pledge") {
        Robot robot;
        AlgoPledge algo(robot);
        algo.typeAlgo(terrain);

        // Suivre la position finale du robot
        std::cout << "Position finale du robot pour Pledge : (" << robot.getX() << ", " << robot.getY() << ")" << std::endl;
        CHECK(terrain.afficherElementGrille(robot.getX(), robot.getY()) == 'A');
    }
}


