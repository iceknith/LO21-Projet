#include <iostream>
#include "Tuile.hpp"

using namespace std;

// Initialize le nextID
int Tuile::nextID = 0;

Tuile::Tuile() : HexagoneContainer() {
    id = nextID++;
}

const Vector2 TuileJeu::positionEnfants[3] = {
        Vector2(0,0),
        Vector2(1,0),
        Vector2(0,1),
};

TuileJeu::TuileJeu() : Tuile() {
    id = nextID++;

    int selec = rand()%100;
    //pour ne jamais avoir plus de 2 carrières par tuile ou plus de 1 place
    int carriere = 0;
    int place = 0;

    for (auto position : positionEnfants) {
        if (selec >= 0 && selec <= 20 && place < 1) {
            container[position] = new Place(this, position, static_cast<CouleursAkropolis>((rand()%5)+1));
            place++;
        }
        else if (selec > 20 && selec <= 60 && carriere < 2) {
            container[position] = new Carriere(this, position);
            carriere++;
        }
        else {
            container[position] = new Quartier(this, position, static_cast<CouleursAkropolis>((rand()%5)+1));
        }
        selec = rand()%100;
    }
}

TuileDepart::TuileDepart() : Tuile() {
    container[Vector2(0,0)] = new Place(this, Vector2(0,0), CouleursAkropolis::BLEU);
    container[Vector2(0,1)] = new Carriere(this, Vector2(0,1));
    container[Vector2(-1,0)] = new Carriere(this, Vector2(-1,0));
    container[Vector2(1,-1)] = new Carriere(this, Vector2(1,-1));
}

