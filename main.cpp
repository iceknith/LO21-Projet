// Décommenter cette ligne pour la release (pour que les tests ne s'executent pas)
// #define NDEBUG

#include <iostream>
#include "main.hpp"
#include "Tests/Tests.hpp"
using namespace std;

int main() {
    assertTests();
    // Faire un test de l'affichage
    auto j = Joueur();
    auto a = AffichageConsole();

    auto position = Vector2(0,0);
    j.place_tuile(new TuileJeuConcrete(), position);
    position = Vector2(0,2);
    j.place_tuile(new TuileJeuConcrete(), position);

    auto b = j.get_plateau().obtenir_hexagone(Vector2(0,0));
    cout << b.get_hauteur() << endl;

    a.affiche_plateau_actuel(j);

    return 0;
}