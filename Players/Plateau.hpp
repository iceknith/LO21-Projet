#ifndef LO21_PROJET_MAP_HPP
#define LO21_PROJET_MAP_HPP

#include "../Utils.hpp"
#include "../Tuile/Hexagone.hpp"
#include <iostream>
#include <map>
using namespace std;


class Plateau {
private:
    map<Vector2, Hexagone&> plateau;

public:
    Plateau() = default;
    ~Plateau() = default;
    // TODO: implémenter le destructeur de Plateau

    Hexagone& obtenir_hexagone(const Vector2& coordonees);
    bool peut_placer(const Tuile& tuileJeu, const Vector2& position);
    void placer(const Tuile& tuileJeu, const Vector2& position);

    map<Vector2, Hexagone&>::iterator get_iterateur_debut() {return plateau.begin();};
    map<Vector2, Hexagone&>::iterator get_iterateur_fin() {return plateau.end();};
};


#endif //LO21_PROJET_MAP_HPP
