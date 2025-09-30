#include "Tuile.hpp" // hexagone.hpp est inclut dans tuile.hpp

int Hexagone::get_couleur() const{

};

Tuile* Hexagone::get_tuile() const{

};

Vector2 Hexagone::get_local_position() const{

};

bool Hexagone::peut_etre_placee(Plateau *map, Vector2 position) const{
    return false;
}

void Hexagone::quand_recouvert(Joueur* joueur_qui_recouvre) const{

}

int Hexagone::get_hauteur() const {
    return tuileParent->get_hauteur();
}
