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

//! Définit les modes de jeu d'Akropolis
enum class GameMode {
    SOLO,
    MULTIJOUEUR
};

//! Définit les difficultées du jeu d'Akropolis en solo
enum class Difficulte {
    FACILE,
    NORMALE,
    DIFFICILE
};

namespace GameConstants {
    // Constantes de score
    const int VERT_PLACE_MULTIPLIER = 3;
    const int BLEU_VARIANTE_BONUS_THRESHOLD = 10;
    const int BLEU_VARIANTE_BONUS_MULTIPLIER = 2;
    const int ROUGE_VARIANTE_BONUS_MIN_EDGES = 3;
    const int ROUGE_VARIANTE_BONUS_MAX_EDGES = 4;
    const int ROUGE_VARIANTE_BONUS_MULTIPLIER = 2;
    const int VIOLET_VARIANTE_HAUTEUR_THRESHOLD = 1;
    const int VIOLET_VARIANTE_BONUS_MULTIPLIER = 2;
    const int JAUNE_VARIANTE_BONUS_MULTIPLIER = 2;

    // Game rules
    const int MAX_HEXAGON_NEIGHBORS = 6;
    const int HEXAGON_DIRECTIONS = 6;
    const int MAX_COULEUR = 6;
}


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
    bool operator==(const Vector2& v) const {return (x == v.x) && (y == v.y);}

    //! Surcharge de l'opérateur soustraction
    /*! Surcharge de l'opérateur soustraction
     * Soit A et B deux vecteurs : A + B = (A.X + B.X, A.y + B.y)
     */
    Vector2 operator-(const Vector2& v) const{return {x - v.x, y - v.y};}
};
// Positions de tous les voisins d'un Hexagone
static const Vector2 adjascenceHex[6]{
    Vector2(-1, 0), // Haut Gauche
    Vector2(-1, +1), // Bas Gauche
    Vector2(0, -1), // Haut Millieu
    Vector2(0, +1), // Bas Millieu
    Vector2(+1, -1), // Haut Droite
    Vector2(+1, 0) // Bas Droite
};

//Utile pour calculer facilement le score de l'illustre architecte
struct StatsCouleursSoloArchitecte {
    int quartiers[GameConstants::MAX_COULEUR] = {0};
    int places[GameConstants::MAX_COULEUR] = {0};
};


#endif
