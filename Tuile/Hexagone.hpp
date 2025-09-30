#ifndef LO21_PROJET_HEXAGONE_HPP
#define LO21_PROJET_HEXAGONE_HPP

#include <iostream>

// Sont définis dans d'autres fichiers en-tête, qui importent Hexagone
// on les définit de façon inline pour ne pas causer d'erreurs
class Tuile; class Joueur; class Plateau;
using namespace std;

class Hexagone {
protected:
    int indice_tuile;
    int couleur;
    Tuile* tuileParent;

public :
    Hexagone() = default;
    ~Hexagone() = default;

    int get_couleur() const;
    Tuile* get_tuile() const;
    int* get_local_position() const;
    int get_hauteur() const;
    bool peut_etre_placee(Plateau* map, int** position) const;
    int si_recouverte(Joueur* joueur_qui_recouvre) const;

    string get_displayed_text() const {return "default";};
};

class Place{
protected:
    int etoiles;

public:
    Place() = default;
    ~Place() {std::cout<<"Place détruite";};
    int get_etoiles();
};


#endif //LO21_PROJET_HEXAGONE_HPP
