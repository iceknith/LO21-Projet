#ifndef LO21_PROJET_TUILE_HPP
#define LO21_PROJET_TUILE_HPP

#include <iostream>
#include "Hexagone.hpp"
#include "../Utils.hpp"

class Tuile {
protected:
    int hauteur;
    Hexagone* enfants;
    Vector2* positions_enfants;
    int nombre_enfant;

public :
    Tuile() = default;
    ~Tuile() {std::cout<<"Tuile détruite";};
    void set_hauteur(int hauteur);

    //permet d'avoir la hauteur de la tuile quand cette dernière est placée sur le terrain
    int get_hauteur() const {return hauteur;}
    Hexagone* get_enfants();
    int** get_positions_enfants ();
    int get_nombre_enfant ();
};

#endif