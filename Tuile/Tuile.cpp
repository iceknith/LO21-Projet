#include <iostream>
#include "Tuile.hpp"

using namespace std;

// Initialize le nextID
int Tuile::nextID = 0;

Tuile::Tuile() {
    id = nextID++;
}

bool Tuile::is_in_positions_enfants(Vector2 pos) const {
    for (int i = 0; i < nombre_enfants; i++) {
        if (positions_enfants[i] == pos) return true;
    }
    return false;
}

TuileJeuConcrete::TuileJeuConcrete() {
    nombre_enfants = 3;
    positions_enfants[0] = Vector2(0,0);
    positions_enfants[1] = Vector2(0,1);
    positions_enfants[2] = Vector2(1,0);
    enfants[0] = new Place(this, 0, CouleursAkropolis::VERT);
    enfants[1] = new Carriere(this, 1);
    enfants[2] = new Quartier(this, 2, CouleursAkropolis::BLEU);
}

TuileDepart::TuileDepart() {

    nombre_enfants = 4;
    positions_enfants[0] = Vector2(0,0);
    positions_enfants[1] = Vector2(0,1);
    positions_enfants[2] = Vector2(-1,0);
    positions_enfants[3] = Vector2(1,-1);
    enfants[0] = new Place(this, 0, CouleursAkropolis::ROUGE);
    enfants[1] = new Carriere(this, 1);
    enfants[2] = new Quartier(this, 2, CouleursAkropolis::VIOLET);
    enfants[3] = new Carriere(this, 3);
}

