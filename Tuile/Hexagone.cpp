#include "Tuile.hpp" // hexagone.hpp est inclut dans tuile.hpp
#include "Hexagone.hpp"

int Hexagone::get_hauteur() const {
    return tuileParent->get_hauteur();
}

int Hexagone::get_id() const {
    return indice_tuile;
}

Vector2 Hexagone::get_local_position() const {
    return tuileParent->get_positions_enfants()[indice_tuile];
}

using namespace constAffichageConsoleHex;
const vector<string> Hexagone::affiche_console() const {
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

    // Haut Gauche
    if (get_tuile()->is_in_positions_enfants(locPos + adjascence[0])) {
        affichage[1] += " " + couleursConsole[couleur] + " ";

        // Ne pas afficher le coin si il y as une tuile en haut également
        if (get_tuile()->is_in_positions_enfants(locPos + adjascence[2]))
            affichage[0] += " " + couleursConsole[couleur] + " ";
        else
            affichage[0] += " " + couleursConsole[couleur] + hauteurTuileTxt;
    }
    else {
        affichage[0] += "/" + couleursConsole[couleur] + hauteurTuileTxt;
        affichage[1] += "/" + couleursConsole[couleur] + hauteurTuileTxt;
    }
    // Bas Gauche
    if (get_tuile()->is_in_positions_enfants(locPos + adjascence[1])) {
        affichage[2] += " " + couleursConsole[couleur] + " ";

        // Ne pas afficher le coin si il y as une tuile en haut également
        if (get_tuile()->is_in_positions_enfants(locPos + adjascence[3]))
            affichage[3] += " " + couleursConsole[couleur] + " ";
        else
            affichage[3] += " " + couleursConsole[couleur] + hauteurTuileTxt;
    }
    else {
        affichage[2] += "\\" + couleursConsole[couleur] + hauteurTuileTxt;
        affichage[3] += "\\" + couleursConsole[couleur] + hauteurTuileTxt;
    }
    // Haut Centre
    if (get_tuile()->is_in_positions_enfants(locPos + adjascence[2])) {
        affichage[0] += "   ";
    }
    else {
        affichage[0] += "-" + hauteurTuileTxt + "-";
    }
    // Bas Centre
    if (get_tuile()->is_in_positions_enfants(locPos + adjascence[3])) {
        affichage[3] += "   ";
    }
    else {
        affichage[3] += "_" + hauteurTuileTxt + "_";
    }

    // Ajout lignes centre
    affichage[1] += centreL1;
    affichage[2] += centreL2;

    // Haut Droite
    if (get_tuile()->is_in_positions_enfants(locPos + adjascence[4])) {
        affichage[1] += " " + couleursConsole[BLANC] + " ";

        // Ne pas afficher le coin si il y as une tuile en haut également
        if (get_tuile()->is_in_positions_enfants(locPos + adjascence[2]))
            affichage[0] += " " + couleursConsole[BLANC] + " ";
        else
            affichage[0] += hauteurTuileTxt + couleursConsole[BLANC] + " ";
    }
    else {
        affichage[0] += hauteurTuileTxt + couleursConsole[BLANC] + "\\";
        affichage[1] += hauteurTuileTxt + couleursConsole[BLANC] + "\\";
    }
    // Bas Droite
    if (get_tuile()->is_in_positions_enfants(locPos + adjascence[5])) {
        affichage[2] += " " + couleursConsole[BLANC] + " ";

        // Ne pas afficher le coin si il y as une tuile en bas également
        if (get_tuile()->is_in_positions_enfants(locPos + adjascence[3]))
            affichage[3] += " " + couleursConsole[BLANC] + " ";
        else
            affichage[3] += hauteurTuileTxt + couleursConsole[BLANC] + " ";
    }
    else {
        affichage[2] += hauteurTuileTxt + couleursConsole[BLANC] + "/";
        affichage[3] += hauteurTuileTxt + couleursConsole[BLANC] + "/";
    }

    return affichage;
}
