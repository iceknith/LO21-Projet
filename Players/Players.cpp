#include "Players.hpp"

Joueur::Joueur() {
    plateauJoueur = Plateau();
}

Vector2 IllustreArchitecte::trouver_emplacement_tuile(Tuile &tuile) {
    bool continueRecherche = true;
    float y = 0;
    Vector2 pos{0,0};
    while (continueRecherche) {
        for (pos.x = 0; pos.x < IllustreArchitechteConsts::board_max_width; pos.x++) {
            continueRecherche = !plateauJoueur.peut_placer(tuile, pos);
            if (!continueRecherche) break;
        }
        pos.y++;
        if (pos.y > 100) {
            throw "Error: l'Illustre Architechte ne trouve pas d'emplacement";
        }
    }
    return pos;
}

Tuile* IllustreArchitecte::choisir_tuile(Chantier chantier) {
    return chantier.prendre_tuile(0);
}

void IllustreArchitecte::jouer(Chantier chantier) {
    Tuile *tuile = choisir_tuile(chantier);
    Vector2 position = trouver_emplacement_tuile(*tuile);
    place_tuile(tuile, position);
}
