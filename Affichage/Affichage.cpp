#include <vector>
#include "Affichage.hpp"
using namespace AffichageConsoleUtils;

void AffichageConsole::affiche_plateau_actuel(Joueur &joueur) {
    // tableau "canvas" de caractères (assez grand pour plusieurs hex)
    vector<string> canvas(40, string(120, ' '));

    auto iterateur = joueur.get_plateau().get_iterateur_debut();
    auto iterateur_fin = joueur.get_plateau().get_iterateur_fin(); // recupere les hexagones du plateau via iterator

    // itere sur toute la map
    do {
        // Coordonees hexagoneales
        int q = (int) iterateur->first.x;
        int r = (int) iterateur->first.y;

        const auto * h = iterateur->second;
        if (!h) continue;

        // coordonnées "écran" (placement en quinconce)
        int px = q * (2 * hexW - 2) + (r%2) * (hexW-1);
        int py = r * (hexH - 3);

        // message centré dans 5 colonnes

        string msg =  type_to_string(h->get_type());
        // DEBUG option: afficher les coordonées
        //string msg = "("+ to_string( q)+","+ to_string(r)+")";
        if (h->get_type() == TypeHexagone::Hexagone);

        if (msg.size() > 5) msg = msg.substr(0,5); // tronque si message trop long
        int padLeft  = (5 - msg.size()) / 2;
        int padRight = 5 - msg.size() - padLeft;

        int hauteur = h->get_hauteur();


        // construire chaque ligne de l’hexagone
        string top    = "  _ _ _  ";

        string l1     = " /" + to_string(hauteur) +
                    " " + to_string(hauteur) +
                    " " + to_string(hauteur) + "\\ ";

        string l2 = "/" + to_string(hauteur)
                         + string(padLeft, ' ')
                         + msg
                         + string(padRight, ' ')
                         + to_string(hauteur) + "\\";

        string l3     = "\\" + to_string(hauteur)
                             + couleur_to_string(static_cast<CouleursAkropolis>(h->get_couleur()))
                             + to_string(hauteur) + "/";

        string l4     = " \\_" + to_string(hauteur)
                             + "_" + to_string(hauteur)
                             + "_/ ";

        // dessiner dans le canvas si dans les bornes
        if (py + 4 < (int)canvas.size() && px + hexW <= (int)canvas[0].size()) {
            /*
            canvas[py+0].replace(px, hexW, top);
            canvas[py+1].replace(px, hexW, l1);
            canvas[py+2].replace(px, hexW, l2);
            canvas[py+3].replace(px, hexW, l3);
            canvas[py+4].replace(px, hexW, l4);
             */
            replace_sauf_charactere(canvas[py+0], px, hexW, top, ' ');
            replace_sauf_charactere(canvas[py+1], px, hexW, l1, ' ');
            replace_sauf_charactere(canvas[py+2], px, hexW, l2, ' ');
            replace_sauf_charactere(canvas[py+3], px, hexW, l3, ' ');
            replace_sauf_charactere(canvas[py+4], px, hexW, l4, ' ');
        }

    } while (++iterateur != iterateur_fin);

    // Affichage final
    for (auto &line : canvas) {
        cout << line;
    }
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

string AffichageConsoleUtils::couleur_to_string(CouleursAkropolis couleur) {
    static const std::map<CouleursAkropolis, std::string> noms = {
        {BLANC, "BLANC"},
        {BLEU, "BLEU "},
        {JAUNE, "JAUNE"},
        {ROUGE, "ROUGE"},
        {VIOLET, "VILET"},// Avec un charcater en moin pour le faire rentrer dans l'hexagone
        {VERT, "VERT "}
    };

    auto it = noms.find(couleur);
    if (it != noms.end()) { return(it->second);}
    else  {return("VIDE");}
}


string AffichageConsoleUtils::type_to_string(TypeHexagone type) {
    static const std::map<TypeHexagone, std::string> noms = {
        {TypeHexagone::Hexagone, "Hexagone"},
        {TypeHexagone::Place, "Place "},
        {TypeHexagone::Carriere, "Carriere"},
        {TypeHexagone::Quartier, "Quartier"}
    };

    auto it = noms.find(type);
    if (it != noms.end()) { return(it->second);}
    else  {return("VIDE");}
}

