#include "Tuile.hpp" // hexagone.hpp est inclut dans tuile.hpp

//permet d'avoir la couleur de l'hexagone (et donc ses propriétés)
int Hexagone::get_couleur() const{

};

//permet de savoir à quelle tuile l'hexagone appartient
Tuile* Hexagone::get_tuile() const{

};

//permet de savoir la position de l'hexagone
int* Hexagone::get_local_position() const{

};

//permey de savoir si on peut
bool Hexagone::peut_etre_placee(Plateau *map, int **position) const{
    return false;
}

//permet de savoir si l'heaxgone a été recouvert (donc ne compte plus à la fin de la partie et donne +1 cube si c'est une carrière)
int Hexagone::si_recouverte(Joueur* joueur_qui_recouvre) const{

}

int Hexagone::get_hauteur() const {
    return tuileParent->get_hauteur();
}
