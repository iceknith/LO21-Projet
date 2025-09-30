#include <iostream>
#include "Tuile.hpp"

using namespace std;

//permet de préciser la hauteur de la tuile quand cette dernière est placée sur le terrain
void Tuile::set_hauteur(int hauteur){

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

//permet de savoir le multiplicateur à appliquer à la fin de la partie pour le score
int Place::get_etoiles(){

};
