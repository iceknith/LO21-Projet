//
// Created by iceknith on 30/09/25.
//

#include "Chantier.hpp"

//Retire la tuile d'indice index du chantier pour la retourner 
Tuile* Chantier::prendre_tuile(size_t index){
    Tuile *result = tuiles[index];
    nombreTuiles--;
    for (size_t i = index; i < nombreTuiles; i++) tuiles[i] = tuiles[i+1];
    return result;
};

//Ajoute une tuile à la fin du chantier (la fin du tableau de tuiles)
void Chantier::ajouter_tuile(Tuile* tuile){
    if (nombreTuiles >= taille) {throw "Chantier plein";}

    tuiles[nombreTuiles] = tuile;
    nombreTuiles++;
};

//Ajoute plusieurs tuiles à la fin du tableau
void Chantier::ajouter_tuile(Tuile* tuile, size_t nombre){
    if (nombreTuiles >= taille) {throw "Ajout de trop de tuiles";}

    for (size_t i = 0; i < nombre; i++) {
        tuiles[nombreTuiles] = tuile;
        tuile++;
        nombreTuiles++;
    }
};