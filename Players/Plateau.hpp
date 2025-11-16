#ifndef LO21_PROJET_MAP_HPP
#define LO21_PROJET_MAP_HPP

#include "../Utils.hpp"
#include "../Tuile/Tuile.hpp"
#include <iostream>
#include <map>
using namespace std;

//! La classe implémentant le Plateau de jeu d'un joueur
class Plateau {
private:
    //! La map associant une coordonée vectorielle à un hexagone.
    map<Vector2, Hexagone*> plateau;

public:
    Plateau() = default;
    ~Plateau() = default;
    //! TODO: implémenter le destructeur de Plateau

    //! Retourne si il existe un hexagone aux coordonées entreées
    /*!
     * Retourne si il existe un hexagone aux coordonées entreées
     * @param coordonees les coordonées du potentiel hexagone
     * @return un booléen qui indique si l'hexagone existe ou non
     */
    bool hexagone_existe(const Vector2& coordonees) {return plateau.find(coordonees) != plateau.end();}
    //! Retourne l'hexagone aux coordonées du Vector2
    /*!
     * @param coordonees le Vector2 des coordonées de l'hexagone recherché
     * @return l'hexagone à ces coordonées
     */
    Hexagone* obtenir_hexagone(const Vector2& coordonees) {return plateau.at(coordonees);}
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
    bool placer(Tuile* tuile, const Vector2& position, bool forcePlacement = false);

    //! Retourne un itérateur sur le plateau, mis au début de celui-ci
    map<Vector2, Hexagone*>::iterator get_iterateur_debut() {return plateau.begin();};
    //! Retourne un itérateur sur le plateau, mis à la fin de celui-ci
    map<Vector2, Hexagone*>::iterator get_iterateur_fin() {return plateau.end();};
};


#endif //LO21_PROJET_MAP_HPP
