#include "Tuile.hpp" // hexagone.hpp est inclut dans tuile.hpp
#include "Hexagone.hpp"

int Hexagone::get_hauteur() const {
    return tuileParent->get_hauteur();
}

Vector2 Hexagone::get_local_position() const {
    return tuileParent->get_positions_enfants()[indice_tuile];
}
