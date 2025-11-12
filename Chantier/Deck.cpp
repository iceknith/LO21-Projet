//
// Created by iceknith on 30/09/25.
//

#include "Deck.hpp"

//Retire la tuile la plus "haute" (la dernière du tableau tuiles) du deck et la retourne
Tuile* Deck::tirer_tuile(){
    nombreTuiles--;
    return tuiles+nombreTuiles;
};

//Retire les x tuiles les plus "hautes" (les dernières du tableau tuiles) du deck et retourne un tableau de ces x tuiles
Tuile* Deck::tirer_tuile(int nombre_tuiles){
    Tuile result[nombre_tuiles];
    int i =0;
    while (nombre_tuiles>0){
        result[i] = *tirer_tuile();
        nombre_tuiles--;
    }
    return result;
};