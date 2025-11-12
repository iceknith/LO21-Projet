#include <iostream>
#include "Tuile.hpp"

using namespace std;

// Initialize le nextID
int Tuile::nextID = 0;

Tuile::Tuile() {

}

bool Tuile::is_in_positions_enfants(Vector2 pos) const {
    for (int i = 0; i < nombre_enfants; i++) {
        if (positions_enfants[i] == pos) return true;
    }
    return false;
}

void Tuile::tourne_tuile(bool sens_horaire) {
    for (size_t i = 0; i < nombre_enfants; i++) {
        // Convertir les coordonées axiales en coordonées cubiques
        float q = positions_enfants[i].x;
        float r = positions_enfants[i].y;
        float s = -q-r;

        // Tourner les coordonées et reconvertir en axial
        if (sens_horaire) {
            positions_enfants[i] = Vector2(-r, -s);
        }
        else {
            positions_enfants[i] = Vector2(-s, -q);
        }
    }
}

TuileJeuConcrete::TuileJeuConcrete() {

    id = nextID++;

    nombre_enfants = 3;
    positions_enfants[0] = Vector2(0,0);
    positions_enfants[1] = Vector2(0,1);
    positions_enfants[2] = Vector2(1,0);
    int selec = rand()%100;

    for (size_t i = 0; i<3; i++) {
        if (selec >= 0 && selec <= 20) {
            enfants[i] = new Place(this, i, static_cast<CouleursAkropolis>((rand()%5)+1));
        }
        else if (selec > 20 && selec <= 60) {
            enfants[i] = new Carriere(this, i);
        }
        else {
            enfants[i] = new Quartier(this, i, static_cast<CouleursAkropolis>((rand()%5)+1));
        }
        selec = rand()%100;
    }
}

TuileDepart::TuileDepart(int identifiant) {

    id = -identifiant;

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

