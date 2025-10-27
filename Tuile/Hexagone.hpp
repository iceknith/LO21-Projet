#ifndef LO21_PROJET_HEXAGONE_HPP
#define LO21_PROJET_HEXAGONE_HPP

#include <iostream>
#include "../Utils.hpp"

// Sont définis dans d'autres fichiers en-tête, qui importent Hexagone
// on les définit de façon inline pour ne pas causer d'erreurs
class Tuile; class Joueur; class Plateau;
using namespace std;

//! La classe Hexagone : le bloc de base de Akropolis
/*!
  La classe Hexagone modelise un hexagone, qui pourra être
  placé par un Joueur sur un Plateau.
  Il s'agit d'une classe abstraite, qui est héritée par d'autres classes
  Comme Place, Carriere ou Quartier
*/
class Hexagone {
protected:
    //! La couleur de cet hexagone
    enum CouleursAkropolis couleur;
    //! La tuile qui contient l'hexagone
    Tuile* tuileParent;
    //! L'indice de cet hexagone, dans tuileParent
    int indice_tuile;

public :
    Hexagone() = default;
    Hexagone(Tuile* tuile_parent, int indice_tuile, CouleursAkropolis couleur) :
        tuileParent(tuile_parent), indice_tuile(indice_tuile), couleur(couleur)
        {};
    ~Hexagone() = default;

    //! Retourne la couleur de cet hexagone
    int get_couleur() const {return couleur;}
    //! Retourne la tuile qui contient cet hexagone
    Tuile* get_tuile() const {return tuileParent;}
    //! Retourne la position locale de cet hexagone dans la tuile
    Vector2 get_local_position() const;
    //! Retourne la hauteur de cet hexagone
    /*!
     \return La hauteur de cet hexagone, qui est obtenu à partir
     de la hauteur de la tuile qui le contient
    */
    int get_hauteur() const;
    //! Retourne l'id de cet hexagone
    /*!
     \return L'id de cet hexagone
    */
    int get_id() const;
    //! Retourne si l'hexagone peut être placé à cet endroit
    /*!
     \param map Un pointeur vers le plateau dans lequel on va vouloir placer l'hexagone
     \param position Un vecteur 2d qui donne la position à laquelle on va vouloir placer l'hexagone
     /!\ Attention /!\, cette fonction ne dit pas si l'emplacement
     est un emplacemen valide, mais elle va dire
     (à partir d'un emplacement génériquement valide), si on peut
     placer cet hexagone spécifique, à cet endroit.
     \return Si l'hexagone peut être placé à cet endroit.
    */
    bool peut_etre_placee(Plateau* map, Vector2 position) const {return true;}

    //! Fonction appelée dès que l'hexagone est recouvert
    /*!
     \param joueur_qui_recouvre un pointeur vers le Joueur qui recouvre la tuile. Est utilisé pour modifier des attributs du joueur.
     Cette fonction est appelée dès que l'hexagone est recouvert.
     Elle sert notemment à la classe Carrière à ajouter une pierre au joureur.
    */
    void quand_recouvert(Joueur* joueur_qui_recouvre) const {}

    //! Retourne le texte affichée au centre de l'hexagone affichée dans la Console
    /*!
     Retourne le texte affichée au centre de l'hexagone affichée dans la Console,
     est utilisée dans AffichageConsole.
     Et est surchargée à chaque implémentation concrète de l'Hexagone.
     \return Le texte à afficher au centre de l'hexagone dans l'affichage console
    */
    string get_displayed_text() const {return "default";};
};

//! La classe Place
/*!
  Un Hexagone qui permet d'ajouter un multiplicateur à une couleur.
*/
class Place : public Hexagone{
protected:
    //! Le nombre d'etoiles (le multiplicateur) de cette place.
    /*!
     * Permet de savoir le multiplicateur à appliquer à la fin de la partie pour le score
     */
    int etoiles;

public:
    Place() = default;
    ~Place() {std::cout<<"Place détruite";};

    //! Retourne le nombre d'étoiles
    int get_etoiles();
};

//! La classe Carriere
/*!
  Un Hexagone, qui lorsque recouvert, donne une pierre au joueur actuel
*/
class Carriere : public Hexagone{

};

//! La classe Quartier
/*!
  Un Hexagone, qui est utilisé pour scorer des points
*/
class Quartier : public Hexagone{

};


#endif //LO21_PROJET_HEXAGONE_HPP
