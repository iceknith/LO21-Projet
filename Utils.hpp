#ifndef LO21_PROJET_UTILS_HPP
#define LO21_PROJET_UTILS_HPP

//! Définit les couleurs des tuiles d'Akropolis
enum CouleursAkropolis {
    BLANC,
    BLEU,
    JAUNE,
    ROUGE,
    VIOLET,
    VERT
};

//! Représente un Vecteur 2D
class Vector2 {
public:
    //! La coordonée X du Vecteur
    /*! La coordonée X du Vecteur */
    float x;
    //! La coordonée Y du Vecteur
    /*! La coordonée Y du Vecteur */
    float y;

    //! Initialize un Vecteur nul
    /*! Initialize un Vecteur nul */
    Vector2() : x(0), y(0) {};
    //! Initialize un Vecteur sur l'axe des abscisses
    /*! Initialize un Vecteur sur l'axe des abscisses */
    Vector2(float x) : x(x), y(0) {};
    //! Initialize un Vecteur avec les coordonées donées
    /*! Initialize un Vecteur avec les coordonées donées */
    Vector2(float x, float y) : x(x), y(y) {};
};

#endif
