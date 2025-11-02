//
// Created by iceknith on 30/09/25.
//

#include "Chantier.hpp"

//Retire la tuile d'indice index du chantier pour la retourner 
Tuile Chantier::prendre_tuile(int index){
    nombreTuiles--;
    Tuile result = tuiles[index];
    tuiles[index] = tuiles[nombreTuiles];
    return result;
};

//Ajoute une tuile à la fin du chantier (la fin du tableau de tuiles)
void Chantier::ajouter_tuile(Tuile* tuile){
    tuiles[nombreTuiles] = *tuile;
    nombreTuiles++;
};

//Ajoute la tuile à l'indice index du tableau
void Chantier::ajouter_tuile(Tuile* tuile, int nombre){
    if (nombre>= taille){throw "Le nombre dépasse la taille maximale";}
    if (nombre<nombreTuiles){
        tuiles[nombreTuiles] = tuiles[nombre];
    }
    tuiles[nombre] = *tuile;
    nombreTuiles++;
};