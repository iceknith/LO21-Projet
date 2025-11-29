//
// Created by iceknith on 30/09/25.
//

#include "Plateau.hpp"


bool Plateau::peut_placer(Tuile &tuile, const Vector2 &position, bool forcePlacement) {
    // On peut placer si on est:
    // - Si on peut placer toutes les tuiles, à leurs positions locales
    // - Sur un niveau commun
    // - Sur plus d'une tuile

    // Définition des variables
    int hauteur = 0;
    Tuile* tuile_base = nullptr;

    if (hasHexagone(position)){
        hauteur = getHexagone(position)->get_hauteur();
        tuile_base = getHexagone(position)->get_tuile();
    }

    bool conditionTuileValidee = (tuile_base == nullptr); // Si on n'as pas de tuile, la condition d'être sur plusieurs tuiles est déjà validée

    bool asAdjacent = forcePlacement; // garde en mémoire si la condition d'adjascence est valide

    // Iteration à travers toute les positions, pour voir si elles sont légales
    for (auto iterTuile : tuile){
        Vector2 positionHex = position + iterTuile.first;

        if (hasHexagone(positionHex)){
            Hexagone* h = getHexagone(positionHex);
            // Condition hauteur
            if (hauteur != h->get_hauteur()) return false;
            // Condition Tuile - Si !conditionTuileValidee, tuile_base != nullptr
            if (!conditionTuileValidee && (h->get_tuile()) != (tuile_base)) conditionTuileValidee = true;
            // Condition Hexagone
            if (!h->peut_etre_placee(this, position)) return false;
        }
        else {
            // Condition hauteur
            if (hauteur != 0) return false;
            // On ne check pas la condition tuile, car si tuile_base, sa hauteur est au moins 1, donc la condition hauteur se déclenchera avant
        }

        if (hauteur == 0 && !asAdjacent) {
            //On regarde si notre hexagone est adjascent à une tuile lorsqu'on place à la hauteur 0
            for (int j = 0; j < 6; ++j) {
                if (hasHexagone(positionHex + adjascenceHex[j])) {
                    asAdjacent = true;
                    break;
                }
            }
        }
    }

    return conditionTuileValidee && (asAdjacent || hauteur != 0);
}

bool Plateau::placer(Tuile* tuile, const Vector2 &position, bool forcePlacement, Joueur *joueur) {
    // Si on ne peut pas placer, retourner False
    if (!peut_placer(*tuile, position, forcePlacement)) return false;

    // Changement de la hauteur de la tuile
    int hauteur = 1;
    if (hasHexagone(position)) hauteur = getHexagone(position)->get_hauteur() + 1;
    tuile->set_hauteur(hauteur);

    // Iteration à travers toute les positions, pour placer l'hexagone à cet endroit
    for (auto iterTuile : *tuile) {
        // Récupération des hexagone et de leurs positions
        Vector2 positionHex = position + iterTuile.first;

        // Appliquer la fonction quand recouvert de l'hexagone recouvert
        if (joueur != nullptr && hauteur > 1) {
            container[positionHex]->quand_recouvert(joueur);
        }

        // Placement de l'hexagone
        container[positionHex] = iterTuile.second;
    }

    // retourner True car on l'as placee
    return true;
}
