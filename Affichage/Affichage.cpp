#include "Affichage.hpp"
using namespace constAffichageConsoleHex;
using namespace AffichageConsoleUtils;

// L'affichage se fera sous la forme
//  /1 1 1\
// /1 Mar-1\
// \1-ché 1/3 3 3\
//  \1 1 1/3Carr-3\
//  /2 2 2\3-iere3/
// /2Place2\3 3 3/
// \2     2/
//  \2 2 2/

// Ou (si dans une tuile unie)
//  /1 1 1\
// /1 Mar-1\
// \1-ché   1 1 1\
//  \1      Carr-1\
//  /1      -iere1/
// /1Place  1 1 1/
// \1     1/
//  \1 1 1/

void AffichageConsole::affiche_plateau_actuel(Joueur &joueur) {

    // trouve les bornes de l'affichage
    const auto iterateur_debut = joueur.get_plateau().get_iterateur_debut();
    const auto iterateur_fin = joueur.get_plateau().get_iterateur_fin();

    Vector2 posInit = axialToScreen(iterateur_debut->first);
    Vector2 posFin = posInit;

    for (auto iterateur = iterateur_debut; iterateur != iterateur_fin; iterateur++) {
        Vector2 pos = axialToScreen(iterateur->first);

        if (pos.x < posInit.x) posInit.x = pos.x;
        else if (pos.x > posFin.x) posFin.x = pos.x;

        if (pos.y < posInit.y) posInit.y = pos.y;
        else if (pos.y > posFin.y) posFin.y = pos.y;
    }

    // tableau "canvas" de caractères (assez grand pour plusieurs hex)
    size_t largeur = (posFin.x - posInit.x) + largeurHex;
    size_t hauteur = (posFin.y - posInit.y) + hauteurHex;
    vector<string> canvas(hauteur, string(largeur, ' '));

    // Initialisation des valeurs du tableau, et insertion de balises de couleurs, pour assurer un alignement
    string emptyLineB{};
    string emptyLineS{" "};
    for (int i = 0; i < largeur/emptyHexLineB.size(); i++) {
        emptyLineB += emptyHexLineB;
        emptyLineS += emptyHexLineS;
    }

    int parite = (largeur/largeurHex)%2;
    for (int i = 0; i < hauteur; i += 1) {
        // Si la parite est à 0, alors les petites lignes sont aux indices 0 et 3, sinon ils sont aux indices 1 et 2.
        if (i%4 == parite || i%4 == 3 - parite) canvas[i] = emptyLineS;
        else canvas[i] = emptyLineB;
    }

    for (auto iterateur = iterateur_debut; iterateur != iterateur_fin; iterateur++) {
        Vector2 pos = axialToScreen(iterateur->first) - posInit;
        vector<string> affichageHex = iterateur->second->affiche_console();


        canvas[pos.y].replace(pos.x+decalagePetiteLigne, affichageHex[0].size(), affichageHex[0]);
        canvas[pos.y+1].replace(pos.x, affichageHex[1].size(), affichageHex[1]);
        canvas[pos.y+2].replace(pos.x, affichageHex[2].size(), affichageHex[2]);
        canvas[pos.y+3].replace(pos.x+decalagePetiteLigne, affichageHex[3].size(), affichageHex[3]);
    }

    // Affichage final
    for (auto &line : canvas) {
        cout << line << endl;
    }
}

Vector2 AffichageConsoleUtils::axialToScreen(Vector2 v) {
    float col = v.x / 2 * largeurHex;
    float ligne = (v.y + v.x / 2) * hauteurHex;
    return Vector2{col, ligne};
}

void AffichageConsoleUtils::replace_sauf_charactere(string &text_original, size_t pos, size_t len,
                                                    const std::string &text_nouveau, char charactere_non_remplace)  {
    size_t endSize = min(text_original.length(), pos + min(len, text_nouveau.size()));
    for (size_t i = pos; i < endSize; i++){
        if (text_nouveau[i - pos] != charactere_non_remplace){
            text_original[i] = text_nouveau[i - pos];
        }
    }
}
