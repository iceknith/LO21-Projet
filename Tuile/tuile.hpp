#ifndef LO21_PROJET_TUILE_HPP
#define LO21_PROJET_TUILE_HPP
#include <iostream>
class Map; class Joueur;

class Tuile {
    int hauteur;
    Hexagone* enfants;
    int* positions_enfants[2];
    int nombre_enfant;
    public :
    Tuile() = default;
    ~Tuile() {std::cout<<"Tuile détruite";};
    void set_hauteur(int hauteur);
    int get_hauteur();
    Hexagone* get_enfants();
    int** get_positions_enfants ();
    int get_nombre_enfant ();
};

class Hexagone {
    int indice_tuile;
    int couleur;
    Tuile* tuileParent;
    public :
    Hexagone() = default;
    ~Hexagone() {std::cout<<"Hexagone détruit";};
    int get_couleur();
    Tuile* get_tuile();
    int** get_local_position();
    bool peut_etre_remplace(Map* map, int** position);
    int si_recouverte(Joueur* joueur_qui_recouvre);
};

class Place{
    int etoiles;
    public:
    Place() = default;
    ~Place() {std::cout<<"Place détruite";};
    int get_etoiles();
};

#endif