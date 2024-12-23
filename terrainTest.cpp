#include "doctest.h"
#include "terrain.h"

TEST_CASE("Test du constructeur et des methodes de la classe Terrain") {
    Terrain terrain(5, 10);
    SUBCASE("Construction et dimensions") {
        CHECK(terrain.hauteur() == 5);
        CHECK(terrain.largeur() == 10);
    }

    SUBCASE("Chargement d'un terrain depuis un fichier") {
        Terrain terrainVide;
        terrainVide.chargerTerrainDepuis("terrain_test.txt");
        CHECK(terrainVide.hauteur() > 0);
        CHECK(terrainVide.largeur() > 0);
    }

    SUBCASE("Sauvegarde d'un terrain dans un fichier") {
        terrain.sauverTerrainSur("terrain_save.txt");
    }

    SUBCASE("Modification et affichage d'une case") {
        terrain.modifierElementGrille(2, 2, 'X');
        terrain.sauverTerrainSur("terrain_saveTest.txt");

        CHECK(terrain.afficherElementGrille(2, 2) == 'X');
        CHECK(terrain.Obstacle(2, 2) == true);
        CHECK(terrain.Obstacle(0, 0) == false);
    }
}


TEST_CASE("Test de positionAleatoireLibrePourRobot") {
    // Terrain avec toutes les cases libres
    SUBCASE("Terrain avec toutes les cases libres") {
        Terrain terrain(5, 5); // Terrain 5x5 avec des cases vides (par défaut '.')
        auto [x, y] = terrain.positionAleatoireLibrePourRobot();
        CHECK(terrain.afficherElementGrille(x, y) != 'X'); // Vérifie que ce n'est pas un mur
    }

    // Terrain avec quelques murs
    SUBCASE("Terrain avec des murs et des cases libres") {
        Terrain terrain(5, 5);
        terrain.modifierElementGrille(0, 0, 'X');
        terrain.modifierElementGrille(1, 1, 'X');
        terrain.modifierElementGrille(2, 2, 'X');

        auto [x, y] = terrain.positionAleatoireLibrePourRobot();
        CHECK(terrain.afficherElementGrille(x, y) != 'X'); // Vérifie que ce n'est pas un mur
    }

    // Grand terrain (vérification de la performance)
    SUBCASE("Grand terrain") {
        Terrain terrain(1000, 1000); // Terrain 1000x1000
        terrain.modifierElementGrille(500, 500, 'X'); // Ajout d'un mur quelque part

        auto [x, y] = terrain.positionAleatoireLibrePourRobot();
        CHECK(terrain.afficherElementGrille(x, y) != 'X'); // Vérifie que ce n'est pas un mur
    }
}
