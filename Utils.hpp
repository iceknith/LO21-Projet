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
//! Définit les types des hexagones d'Akropolis
enum class TypeHexagone {
    Hexagone,
    Place,
    Carriere,
    Quartier
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

    //! Surcharge l'operateur inférieur à, pour qu'il puisse être utilisé comme clé dans une map
    /*!
     * Surcharge l'operateur inférieur à, pour qu'il puisse être utilisé comme clé dans une map
     * Soit A et B deux vecteurs, A < B <=> (A.y < B.y) || (A.y == B.y && A.x < B.x)
    */
    bool operator<(const Vector2 v) const{return (y < v.y) || (y == v.y && x < v.x);}
    //! Surcharge de l'opérateur addition
    /*! Surcharge de l'opérateur addition
     * Soit A et B deux vecteurs : A + B = (A.X + B.X, A.y + B.y)
     */
    Vector2 operator+(const Vector2& v) const{return {x + v.x, y + v.y};}
    //! Surcharge l'operateur égale à, pour pouvoir comparer deux Vector2
    /*!
     * Surcharge l'operateur égale à, pour pouvoir comparer deux Vector2
     * Soit A et B deux vecteurs, A == B <=> (A.y == B.y) || (A.y == B.y)
    */
    bool operator==(const Vector2& v) const {
        return (x == v.x) && (y == v.y);
    }

};

// position de tout les voisions locals d'un Hexagone
static const Vector2 PositionContourHexagone[6] = { {0,1}, {1,0}, {1,-1}, {0,-1},{-1,0},{-1,1}};

#endif
