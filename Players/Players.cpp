#include "Players.hpp"

void Joueur::set_score(Score *score) {
    if (scoreJoueur != nullptr) free(scoreJoueur);
    scoreJoueur = score;
}

Vector2 IllustreArchitecte::trouver_emplacement_tuile(Tuile &tuile) {
    bool continueRecherche = true;
    //var parity = hex.col&1
    //var q = hex.col
    //var r = hex.row - (hex.col - parity) / 2
    int row = -2;
    int col;
    Vector2 pos;
    while (continueRecherche) {
        row++;
        for (col = -1; col < IllustreArchitechteConsts::board_max_width; col++) {
            pos.x = col;
            pos.y = row - col/2;

            if (!plateauJoueur.hexagone_existe(pos)
                && plateauJoueur.peut_placer(tuile, pos)) {
                continueRecherche = false;
                break;
            }
        }
        if (row > 100) {
            throw "Error: l'Illustre Architechte ne trouve pas d'emplacement";
        }
    }
    return pos;
}

Tuile* IllustreArchitecte::choisir_tuile(Chantier &chantier) {
    return chantier.prendre_tuile(0);
}

void IllustreArchitecte::jouer(Chantier &chantier) {
    Tuile *tuile = choisir_tuile(chantier);
    Vector2 position = trouver_emplacement_tuile(*tuile);
    cout << position.x << " " << position.y << endl;
    place_tuile(tuile, position);
}

IllustreArchitecte::IllustreArchitecte(Difficulte difficulte) : difficulte(difficulte) {
    switch (difficulte) {
        case Difficulte::FACILE:
            scoreJoueur = new ScoreSoloArchitecteHippodamos();
            break;
        case Difficulte::NORMALE:
            scoreJoueur = new ScoreSoloArchitecteMetagenes();
            break;
        case Difficulte::DIFFICILE:
            scoreJoueur = new ScoreSoloArchitecteCallicrates();
            break;
        default:
            break;
    }
}
