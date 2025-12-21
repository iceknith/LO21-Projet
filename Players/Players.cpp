#include "Players.hpp"
#include "../Serialization/Serialization.hpp"

void JoueurSimple::set_score(Score *score) {
    if (scoreJoueur != nullptr) free(scoreJoueur);
    scoreJoueur = score;
}

void Joueur::serialize(QVariantMap &data, SerializationContext *context) const {
    data["pierre"] = pierre;
    data["nomJoueur"] = QString::fromStdString(nomJoueur);
    data["score"] = context->serialize(scoreJoueur);

    QVariantMap plateauMap;
    plateauJoueur.serialize(plateauMap, context);
    data["plateau"] = plateauMap;
}

void Joueur::deserialize(const QVariantMap &data, SerializationContext *context) {
    pierre = data["pierre"].value<int>();
    nomJoueur = data["nomJoueur"].value<QString>().toStdString();
    scoreJoueur = dynamic_cast<Score*>(context->deserialize(data["score"]));
    plateauJoueur.deserialize(data["plateau"].value<QVariantMap>(), context);
}

Vector2 IllustreArchitecte::trouver_emplacement_tuile(Tuile &tuile) {
    bool continueRecherche = true;

    int row = -2;
    int col;
    Vector2 pos;
    while (continueRecherche) {
        row++;
        for (col = -1; col < IllustreArchitechteConsts::board_max_width; col++) {
            pos.x = col;
            pos.y = row - col/2;

            if (!plateauJoueur.hasHexagone(pos)
                && plateauJoueur.peut_placer(tuile, pos)) {
                continueRecherche = false;
                break;
            }
        }
        if (row > 100) {
            throw AkropolisException("Error: l'Illustre Architechte ne trouve pas d'emplacement");
        }
    }
    return pos;
}

Tuile* IllustreArchitecte::choisir_tuile(Chantier &chantier) {

    // On prend la première tuile que l'on peut acheter qui as une place
    size_t i;
    for (i = 0; i <= get_pierre(); i++) {
        auto tuileChantier  = chantier.get_tuile(i);

        for (auto& iter : *tuileChantier) {
            if (iter.second->get_type() == TypeHexagone::Place) {
                pierre -= i;
                return chantier.prendre_tuile(i);
            }
        }
    }

    // Si ce n'est pas le cas, on prends la première tuile du chantier
    return chantier.prendre_tuile(0);
}

void IllustreArchitecte::jouer(Chantier &chantier) {
    Tuile *tuile = choisir_tuile(chantier);
    Vector2 position = trouver_emplacement_tuile(*tuile);
    place_tuile(tuile, position);
}

IllustreArchitecte::IllustreArchitecte(Difficulte difficulte) : difficulte(difficulte) {
    switch (difficulte) {
        case Difficulte::FACILE:
            scoreJoueur = new ScoreSoloArchitecteHippodamos();
            nomJoueur = "Hippodamos";
            break;
        case Difficulte::NORMALE:
            scoreJoueur = new ScoreSoloArchitecteMetagenes();
            nomJoueur = "Métagénès";
            break;
        case Difficulte::DIFFICILE:
            scoreJoueur = new ScoreSoloArchitecteCallicrates();
            nomJoueur = "Callicratès";
            break;
        default:
            break;
    }
}

void IllustreArchitecte::serialize(QVariantMap &data, SerializationContext *context) const {
    Joueur::serialize(data, context);
    data["difficulte"] = static_cast<int>(difficulte);
}

void IllustreArchitecte::deserialize(const QVariantMap &data, SerializationContext *context) {
    Joueur::deserialize(data, context);
    difficulte = static_cast<Difficulte>(data["difficulte"].value<int>());
}
