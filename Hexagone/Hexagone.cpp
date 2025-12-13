#include "../HexagoneContainer/Tuile.hpp" // hexagone.hpp est inclut dans tuile.hpp
#include "Hexagone.hpp"
#include "../Players/Players.hpp"

int Hexagone::get_hauteur() const {
    return tuileParent->get_hauteur();
}

using namespace constAffichageConsoleHex;
const vector<string> Hexagone::affiche_console(bool highlighted) const {
    vector<string> affichage{4, ""};

    // Construction du texte central
    string centre = get_text();
    string centreL1 = "";
    string centreL2 = "";
    if (centre.size() > largeurCentre) {
        size_t effectiveSize = largeurCentre - 1;
        centreL1 = centre.substr(0, effectiveSize) + "-";
        centreL2 = "-" + centre.substr(effectiveSize, effectiveSize);
    }
    else {
        size_t diff = centre.size() - largeurCentre;
        centreL1 = centre + string(diff, ' ');
        centreL2 = string(largeurCentre, ' ');
    }

    // Construction du reste de l'affichage
    // En prenant compte des hexagones adjascents
    Vector2 locPos = get_local_position();
    string hauteurTuileTxt = to_string(get_hauteur());
    string couleurString = highlighted ? couleursConsoleHighlighted[couleur] : couleursConsole[couleur];

    // Haut Gauche
    if (get_tuile()->hasHexagone(locPos + adjascenceHex[0])) {
        affichage[1] += " " + couleurString + " ";

        // Ne pas afficher le coin si il y as une tuile en haut également
        if (get_tuile()->hasHexagone(locPos + adjascenceHex[2]))
            affichage[0] += " " + couleurString + " ";
        else
            affichage[0] += " " + couleurString + hauteurTuileTxt;
    }
    else {
        affichage[0] += "/" + couleurString + hauteurTuileTxt;
        affichage[1] += "/" + couleurString + hauteurTuileTxt;
    }
    // Bas Gauche
    if (get_tuile()->hasHexagone(locPos + adjascenceHex[1])) {
        affichage[2] += " " + couleurString + " ";

        // Ne pas afficher le coin si il y as une tuile en haut également
        if (get_tuile()->hasHexagone(locPos + adjascenceHex[3]))
            affichage[3] += " " + couleurString + " ";
        else
            affichage[3] += " " + couleurString + hauteurTuileTxt;
    }
    else {
        affichage[2] += "\\" + couleurString + hauteurTuileTxt;
        affichage[3] += "\\" + couleurString + hauteurTuileTxt;
    }
    // Haut Centre
    if (get_tuile()->hasHexagone(locPos + adjascenceHex[2])) {
        affichage[0] += "   ";
    }
    else {
        affichage[0] += "-" + hauteurTuileTxt + "-";
    }
    // Bas Centre
    if (get_tuile()->hasHexagone(locPos + adjascenceHex[3])) {
        affichage[3] += "   ";
    }
    else {
        affichage[3] += "_" + hauteurTuileTxt + "_";
    }

    // Ajout lignes centre
    affichage[1] += centreL1;
    affichage[2] += centreL2;

    // Haut Droite
    if (get_tuile()->hasHexagone(locPos + adjascenceHex[4])) {
        affichage[1] += " " + couleurConsoleOutline + " ";

        // Ne pas afficher le coin si il y as une tuile en haut également
        if (get_tuile()->hasHexagone(locPos + adjascenceHex[2]))
            affichage[0] += " " + couleurConsoleOutline + " ";
        else
            affichage[0] += hauteurTuileTxt + couleurConsoleOutline + " ";
    }
    else {
        affichage[0] += hauteurTuileTxt + couleurConsoleOutline + "\\";
        affichage[1] += hauteurTuileTxt + couleurConsoleOutline + "\\";
    }
    // Bas Droite
    if (get_tuile()->hasHexagone(locPos + adjascenceHex[5])) {
        affichage[2] += " " + couleurConsoleOutline + " ";

        // Ne pas afficher le coin si il y as une tuile en bas également
        if (get_tuile()->hasHexagone(locPos + adjascenceHex[3]))
            affichage[3] += " " + couleurConsoleOutline + " ";
        else
            affichage[3] += hauteurTuileTxt + couleurConsoleOutline + " ";
    }
    else {
        affichage[2] += hauteurTuileTxt + couleurConsoleOutline + "/";
        affichage[3] += hauteurTuileTxt + couleurConsoleOutline + "/";
    }

    return affichage;
}

void Hexagone::serialize(QVariantMap &data, SerializationContext *context) const {
    data["couleur"] = couleur;
    QVariantMap  vectData;
    localPos.serialize(vectData, context);
    data["localPos"] = vectData;
}

void Hexagone::deserialize(const QVariantMap &data, SerializationContext *context) {
    couleur = data["couleur"].value<CouleursAkropolis>();
    localPos.deserialize(data["localPos"].value<QVariantMap>(), context);
}

void Carriere::quand_recouvert(Joueur *joueur_qui_recouvre) const {
    Hexagone::quand_recouvert(joueur_qui_recouvre);

    joueur_qui_recouvre->ajouter_pierre(pierre_count);
}

void Place::serialize(QVariantMap &data, SerializationContext *context) const {
    Hexagone::serialize(data, context);
    data["etoiles"] = etoiles;
}

void Place::deserialize(const QVariantMap &data, SerializationContext *context) {
    Hexagone::deserialize(data, context);
    etoiles = data["etoiles"].value<int>();
}
