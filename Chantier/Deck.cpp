//
// Created by iceknith on 30/09/25.
//

#include "Deck.hpp"
#include "../Serialization/Serialization.hpp"

Deck::Deck(int nombre_joueurs) {
    setNombreJoueurs(nombre_joueurs);
};

Deck::~Deck() {
    for(size_t i = 0; i < taille; i++) delete tuiles[i];
    delete[] tuiles;
}

void Deck::setNombreJoueurs(int nombre_joueurs) {
    for(size_t i = 0; i < taille; i++) delete tuiles[i];
    delete[] tuiles;

    if (nombre_joueurs == 1) {
        taille = 23;
    }
    else if (nombre_joueurs == 2) {
        taille = 36;
    }
    else if (nombre_joueurs == 3) {
        taille = 49;
    }
    else {
        taille = 61;
    }

    nombreTuiles = taille;

    tuiles = new TuileJeu*[taille];
    for(size_t i = 0; i < taille; i++) tuiles[i] = new TuileJeu();
}

//Retire la tuile la plus "haute" (la dernière du tableau tuiles) du deck et la retourne
TuileJeu* Deck::tirer_tuile(){
    if (nombreTuiles < 1) throw "Le deck est vide";
    nombreTuiles--;
    return tuiles[nombreTuiles];
};

//Retire les x tuiles les plus "hautes" (les dernières du tableau tuiles) du deck et retourne un tableau de ces x tuiles
TuileJeu** Deck::tirer_tuiles(size_t nombre_tuiles){
    if (nombreTuiles < nombre_tuiles) throw "Le deck ne contient pas assez de tuiles";
    nombreTuiles -= nombre_tuiles;
    return tuiles + nombreTuiles;
}

void Deck::serialize(QVariantMap &data, SerializationContext *context) const {
    data["taille"] = static_cast<qsizetype>(taille);
    data["nombreTuiles"] = static_cast<qsizetype>(nombreTuiles);
    for(size_t i = 0; i < taille; i++)
        data[QString::number(i)] = context->serialize(tuiles[i]);
}

void Deck::deserialize(const QVariantMap &data, SerializationContext *context) {
    // On supprime toutes les vielles tuiles
    for(size_t i = 0; i < taille; i++) delete tuiles[i];
    delete[] tuiles;

    taille = data["taille"].value<int>();
    nombreTuiles = data["nombreTuiles"].value<int>();

    tuiles = new TuileJeu*[taille];
    for(size_t i = 0; i < taille; i++)
        tuiles[i] = dynamic_cast<TuileJeu*>(context->deserialize(data[QString::number(i)]));
}

