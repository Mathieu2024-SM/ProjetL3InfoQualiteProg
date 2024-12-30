#include "doctest.h"
#include "robot.h"
#include "observateur.h"
#include "terrain.h"

TEST_CASE("[robot] Test du constructeur du robot") {
    SUBCASE("Le constructeur du robot avec ses coord et sa forme est correct"){
        int x {5}, y {5};

        Robot r{x,y};
        REQUIRE (r.getX() == x);
        REQUIRE (r.getY() == y);
    }
    SUBCASE("L'orientation du robot est entre 0 et 3"){
        Robot r{1,5};
        REQUIRE (r.orientation() >= 0);
        REQUIRE (r.orientation() <= 3);
    }

}

// Fonction utilitaire pour tester les rotations
void testRotation(Robot& r, int expectedOrientation, char d) {
    if(d == 'g')
        r.tourneAGauche();
    else
        r.tourneADroite();
    CHECK(r.orientation() == expectedOrientation);
}

TEST_CASE("[robot] Tests des rotations du robot") {
    Robot r{1, 5};
    int expectedOrientation;

    SUBCASE("Rotation à gauche") {
        expectedOrientation = (r.orientation() + 3) % 4; // Rotation anti-horaire
        testRotation(r,expectedOrientation,'g');
    }

    SUBCASE("Rotation à droite") {
        expectedOrientation = (r.orientation() + 1) % 4; // Rotation horaire
        testRotation(r,expectedOrientation,'d');
    }
}


// Fonction utilitaire pour tester l'avancement
void testAvancerRobot(Robot& r, Terrain& t, int orientation, int expectedX, int expectedY) {
    // Réinitialiser l'orientation pour correspondre
    while (r.orientation() != orientation) {
        r.tourneADroite(); // Tourner jusqu'à l'orientation souhaitée
    }

    r.avance(); // Faire avancer le robot

    // Vérifier la position
    CHECK(r.getX() == expectedX);
    CHECK(r.getY() == expectedY);
}

TEST_CASE("Test de la méthode avance")
{
    Terrain terrain(10, 10); // Terrain vide pour les tests
    Robot r(5, 5); // Position initiale au centre

    // Orientation Nord
    SUBCASE("Orientation Nord") {
        testAvancerRobot(r, terrain, 0, 4, 5); // X diminue
    }

    // Orientation Est
    SUBCASE("Orientation Est") {
        testAvancerRobot(r, terrain, 1, 5, 6); // Y augmente
    }

    // Orientation Sud
    SUBCASE("Orientation Sud") {
        testAvancerRobot(r, terrain, 2, 6, 5); // X augmente
    }

    // Orientation Ouest
    SUBCASE("Orientation Ouest") {
        testAvancerRobot(r, terrain, 3, 5, 4); // Y diminue
    }
}

TEST_CASE("L'affichage de l'orientation est correct")
{
    Robot r;
    int orientation = r.orientation();
    r.modifierFormeSelon(orientation);
    CHECK(r.formeRobot() == ">");
}

void testObservations(const Robot &r)
{
    observateur* ob = new observateur(r.getX(),r.getY(), r.orientation());

    CHECK(r.getX() == ob->getPositionX());
    CHECK(r.getY() == ob->getPositionY());
    CHECK(r.orientation() == ob->getDirection());

}

TEST_CASE("Les differentes observations sont bien retenu"){

    int startX = 5, startY = 5;
    Robot r(startX, startY);

    SUBCASE("Lorsque le robot avance"){
        r.avance();
        testObservations(r);
    }
    SUBCASE("Lorsque le robot tourne a droite"){
        r.tourneADroite();
        testObservations(r);
    }
    SUBCASE("Lorsque le robot tourne a gauche"){
        r.tourneAGauche();
        testObservations(r);
    }

}
