#ifndef LO21_PROJET_MAP_HPP
#define LO21_PROJET_MAP_HPP

#include "../Utils.hpp"
#include "Tuile.hpp"
#include <iostream>
#include <map>
using namespace std;

//! La classe implémentant le Plateau de jeu d'un joueur
class Plateau : public HexagoneContainer {
private:
public:
    Plateau() : HexagoneContainer() {};

    //! Retourne true si il est possible de placer tuile à la position du Vector2
    /*!
     * @param tuile La Tuile qu'on essaye de placer
     * @param position La position à laquelle on essaye de placer la Tuile
     * @return si l'emplacement est valide (check également si les condition de placement des Hexagones sont validés)
     */
    bool peut_placer(Tuile& tuile, const Vector2& position, bool forcePlacement = false);
    //! Place une tuile à des coordonées spécifiques
    /*!
     *
     * @param tuile La Tuile à placer
     * @param position La position où l'on essaye de placer la Tuile
     * @return si le placement s'est bien effectué ou non
     */
    bool placer(Tuile* tuile, const Vector2& position, bool forcePlacement = false, Joueur *joueur = nullptr);

    //! Implémentation concrète de ClassName
    string className() override {return "Plateau";}
};


#endif //LO21_PROJET_MAP_HPP
