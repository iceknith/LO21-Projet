// Décommenter cette ligne pour la release (pour que les tests ne s'executent pas)
// #define NDEBUG

#include "main.hpp"
#include "Tests/Tests.hpp"
using namespace std;

int main() {
    assertTests();

    /*
    // Faire un test de l'affichage
    auto j = Joueur();
    auto a = AffichageConsole();

    auto position = Vector2(0,0);

    position = Vector2(0,0);
    j.place_tuile(new TuileJeuConcrete(), position);

    position = Vector2(1,7);
    j.place_tuile(new TuileDepart(), position);

    position = Vector2(1,3);
    j.place_tuile(new TuileJeuConcrete(), position);
    */

    JeuConsole jeu{};
    jeu.gameLoop();

    return 0;
}