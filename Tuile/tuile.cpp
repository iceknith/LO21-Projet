#include <iostream>
#include "tuile.hpp"
using namespace std;

//permet de préciser la hauteur de la tuile quand cette dernière est placée sur le terrain
void Tuile::set_hauteur(int hauteur){

};

//permet d'avoir la hauteur de la tuile quand cette dernière est placée sur le terrain
int Tuile::get_hauteur(){

};

//permet de savoir quels sont les hexagones qui composent la tuile
Hexagone* Tuile::get_enfants(){

};

//permet de savoir où les hexagones sont positionnés sur le terrain (et donc en même temps la tuile)
int** Tuile::get_positions_enfants (){

};

//permet de savoir combien d'hexagones composent la tuile (si on souhaite ajouter des formes différentes que celle du jeu de base)
int Tuile::get_nombre_enfant (){

};

//permet d'avoir la couleur de l'hexagone (et donc ses propriétés)
int Hexagone::get_couleur(){

};

//permet de savoir à quelle tuile l'hexagone appartient
Tuile* Hexagone::get_tuile(){

};

//permet de savoir la position de l'hexagone
int** Hexagone::get_local_position(){

};

//
bool Hexagone::peut_etre_remplace(Map* map, int** position){

};

//permet de savoir si l'heaxgone a été recouvert (donc ne compte plus à la fin de la partie et donne +1 cube si c'est une carrière)
int Hexagone::si_recouverte(Joueur* joueur_qui_recouvre){

};

//permet de savoir le multiplicateur à appliquer à la fin de la partie pour le score
int Place::get_etoiles(){

};
