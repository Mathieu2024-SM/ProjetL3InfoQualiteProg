#include "doctest.h"
#include "observateur.h"

TEST_CASE("Le constructeur est valide") {
    observateur ob(5, 10, 1);
    CHECK(ob.getPositionX() == 5);
    CHECK(ob.getPositionY() == 10);
    CHECK(ob.getDirection() == 1);
}
