//
// Created by iceknith on 30/09/25.
//

#include "Deck.hpp"

//Retire la tuile la plus "haute" (la dernière du tableau tuiles) du deck et la retourne
Tuile* Deck::tirer_tuile(){
    if (nombreTuiles < 1) throw "Le deck est vide";
    nombreTuiles--;
    return tuiles+nombreTuiles;
};

//Retire les x tuiles les plus "hautes" (les dernières du tableau tuiles) du deck et retourne un tableau de ces x tuiles
Tuile* Deck::tirer_tuile(int nombre_tuiles){
    if (nombreTuiles < nombre_tuiles) throw "Le deck ne contient pas assez de tuiles";
    nombreTuiles -= nombre_tuiles;
    return tuiles+nombreTuiles;
};