//
// Created by iceknith on 30/09/25.
//

#include "Plateau.hpp"


bool Plateau::peut_placer(Tuile &tuile, const Vector2 &position) {
    // On peut placer si on est:
    // - Si on peut placer toutes les tuiles, à leurs positions locales
    // - Sur un niveau commun
    // - Sur plus d'une tuile
    //! TODO implémenter une condition, qui regarde si on est adjascente à une tuile lorsqu'on place à la hauteur 0

    // Définition des variables
    int hauteur = 0;
    Tuile* tuile_base = nullptr;

    if (hexagone_existe(position)){
        hauteur = obtenir_hexagone(position).get_hauteur();
        tuile_base = obtenir_hexagone(position).get_tuile();
    }

    bool conditionTuileValidee = (tuile_base == nullptr); // Si on n'as pas de tuile, la condition d'être sur plusieurs tuiles est déjà validée

    int adjacent =0;// compte le nombre d'hexagone adjacent a notre position
    static const Vector2 PositionContourHexagone[6] = { {0,1}, {0,2}, {0,-1}, {0,-2},{1,1},{1,-1}}; // position de tout les voisions locals


    // Iteration à travers toute les positions, pour voir si elles sont légales
    for (int i = 0; i < tuile.get_nombre_enfant(); i++){
        Vector2 positionLocaleHex = tuile.get_positions_enfants()[i];
        Vector2 positionHex = position + positionLocaleHex;

        if (hexagone_existe(positionHex)){
            Hexagone h = obtenir_hexagone(positionHex);
            // Condition hauteur
            if (hauteur != h.get_hauteur()) return false;
            // Condition Tuile - Si !conditionTuileValidee, tuile_base != nullptr
            if (!conditionTuileValidee && (*h.get_tuile()) != (*tuile_base)) conditionTuileValidee = true;
            // Condition Hexagone
            if (!h.peut_etre_placee(this, position)) return false;
        }
        else {
            // Condition hauteur
            if (hauteur != 0) return false;
            // On ne check pas la condition tuile, car si tuile_base, sa hauteur est au moins 1, donc la condition hauteur se déclenchera avant
        }
        //On regarde si notre hexagone est adjascente à une tuile lorsqu'on place à la hauteur 0

        for (int j = 0; j < 6; ++j) {
            if (plateau.find(positionHex + PositionContourHexagone[j]) != plateau.end()) {
                ++adjacent;
            }
        }
    }

    // Si hexagone sans adjacent et n'est pas la premiere tuile alors mauvais placement
    if (adjacent ==0) {
        if (tuile.get_id()!=0) {
            return true;  // WARNING: supposement juste mais il semble avoir un probleme dans comment on a codé la map
        }
    }

    return conditionTuileValidee;
}

bool Plateau::placer(Tuile* tuile, const Vector2 &position) {
    // Si on ne peut pas placer, retourner False
    if (!peut_placer(*tuile, position)) return false;

    // Changement de la hauteur de la tuile
    int hauteur = 1;
    if (hexagone_existe(position)) hauteur = obtenir_hexagone(position).get_hauteur() + 1;
    tuile->set_hauteur(hauteur);

    // Iteration à travers toute les positions, pour voir si elles sont légales
    for (int i = 0; i < tuile->get_nombre_enfant(); i++) {
        // Récupération des hexagone et de leurs positions
        Hexagone hex = tuile->get_enfants()[i];
        Vector2 positionLocaleHex = tuile->get_positions_enfants()[i];
        Vector2 positionHex = position + positionLocaleHex;

        // Placement de l'hexagone
        plateau[positionHex] = hex;
    }

    // Sinon, retourner True
    return true;
}

