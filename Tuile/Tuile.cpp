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
    positions_enfants[1] = Vector2(0,1);
    positions_enfants[2] = Vector2(1,0);
    enfants[0] = new Place(this, 0, CouleursAkropolis::BLANC);
    enfants[1] = new Carriere(this, 1, CouleursAkropolis::BLANC);
    enfants[2] = new Quartier(this, 2, CouleursAkropolis::BLEU);
}

TuileDepart::TuileDepart() {

    nombre_enfants = 4;
    positions_enfants[0] = Vector2(0,0);
    positions_enfants[1] = Vector2(0,1);
    positions_enfants[2] = Vector2(-1,0);
    positions_enfants[3] = Vector2(1,-1);
    enfants[0] = new Place(this, 0, CouleursAkropolis::BLEU);
    enfants[1] = new Carriere(this, 1, CouleursAkropolis::BLANC);
    enfants[2] = new Carriere(this, 2, CouleursAkropolis::BLANC);
    enfants[3] = new Carriere(this, 2, CouleursAkropolis::BLANC);

}

