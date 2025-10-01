#include <iostream>
#include "Tuile.hpp"

using namespace std;

// Initialize le nextID
int Tuile::nextID = 0;

Tuile::Tuile() {
    id = nextID++;
}

TuileJeuConcrete::TuileJeuConcrete() {
    nombre_enfants = 3;
    positions_enfants[0] = Vector2(0,0);
    positions_enfants[1] = Vector2(1,0);
    positions_enfants[2] = Vector2(0,1);
    enfants[0] = Hexagone(this, 0, CouleursAkropolis::BLANC);
    enfants[1] = Hexagone(this, 1, CouleursAkropolis::ROUGE);
    enfants[2] = Hexagone(this, 2, CouleursAkropolis::BLEU);
}
