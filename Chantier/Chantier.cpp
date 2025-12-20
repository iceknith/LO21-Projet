//
// Created by iceknith on 30/09/25.
//

#include "Chantier.hpp"
#include "../Serialization/Serialization.hpp"

//Retire la tuile d'indice index du chantier pour la retourner 
Tuile* Chantier::prendre_tuile(size_t index){
    Tuile *result = tuiles[index];
    nombreTuiles--;
    for (size_t i = index; i < nombreTuiles; i++) tuiles[i] = tuiles[i+1];
    return result;
};

//Ajoute une tuile à la fin du chantier (la fin du tableau de tuiles)
void Chantier::ajouter_tuile(TuileJeu* tuile){
    if (nombreTuiles >= taille) {throw AkropolisException ("Chantier plein");}

    tuiles[nombreTuiles] = tuile;
    nombreTuiles++;
};

//Ajoute plusieurs tuiles à la fin du tableau
void Chantier::ajouter_tuile(TuileJeu** tuile, size_t nombre){
    if (nombreTuiles >= taille) {throw AkropolisException ("Ajout de trop de tuiles");}

    for (size_t i = 0; i < nombre; i++) {
        tuiles[nombreTuiles] = tuile[i];
        nombreTuiles++;
    }
}

void Chantier::serialize(QVariantMap &data, SerializationContext *context) const {
    data["taille"] = static_cast<qsizetype>(taille);
    data["nombreTuiles"] = static_cast<qsizetype>(nombreTuiles);
    int i = 0;
    for(auto tuile : tuiles)
        data[QString::number(i++)] = context->serialize(tuile);
}

void Chantier::deserialize(const QVariantMap &data, SerializationContext *context) {
    taille = static_cast<size_t>(data["taille"].value<qsizetype>());
    nombreTuiles = static_cast<size_t>(data["nombreTuiles"].value<qsizetype>());
    for(int i = 0; i < nombreTuiles; i++)
        tuiles[i] = dynamic_cast<TuileJeu*>(context->deserialize(data[QString::number(i)]));
};
