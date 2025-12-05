#ifndef LO21_PROJET_TUILE_HPP
#define LO21_PROJET_TUILE_HPP

#include <iostream>
#include "../Hexagone/Hexagone.hpp"
#include "HexagoneContainer.hpp"
#include "../Utils.hpp"


//! Le nombre maximal d'enfants par Tuile, est utilisé pour définir la taille des Tableaux de Tuile
//const int max_enfants_par_tuile = 10;

//! La classe Tuile, qui définit les tuiles de jeu.
/*!
 * La classe Tuile, qui définit les tuiles de jeu.
 */
class Tuile : public HexagoneContainer{
protected:
    //! L'identifiant unique de la prochaine tuile initialisée
    static int nextID;
    //! L'identifiant unique de la tuile
    int id;
    //! La hauteur de la tuile, une fois placée sur le terrain
    int hauteur;
public :
    Tuile();

    //! Setteur de la Hauteur. À appeler lors de la pose sur le terrain
    void set_hauteur(const int hauteur) {this->hauteur = max(hauteur, 0);}
    //! Getteur de la Hauteur
    int get_hauteur() const {return hauteur;}
    //! Getteur de l'identifiant unique de la Tuile
    int get_id() const {return id;}

    //! Surcharge de l'opérateur ==
    /*!
     * Surcharge de l'opérateur ==
     * Soit A et B deux tuiles, A == B <=> A.id == B.id
     * @param t la deuxième tuile
     * @return si this == t
     */
    bool operator==(const Tuile& t) const {return get_id() == t.get_id();}
    //! Surcharge de l'opérateur !=
    /*!
     * Surcharge de l'opérateur !=
     * Soit A et B deux tuiles, A != B <=> A.id != B.id
     * @param t la deuxième tuile
     * @return si this != t
     */
    bool operator!=(const Tuile& t) const {return get_id() != t.get_id();}
};

//! Représente une Tuile de Départ de jeu, ne peut pas être placée lors d'une partie
class TuileDepart : public Tuile {
private:
public:
    TuileDepart();
};

//! Implémentation concrète de la tuile de Jeu de base
class TuileJeu : public Tuile {
private:
    const static Vector2 positionEnfants[3];
public:
    TuileJeu();
};

#endif