#include <vector>
#include "Affichage.hpp"


void AffichageConsole::affiche_plateau_actuel(Joueur &joueur) {
    // tableau "canvas" de caractères (assez grand pour plusieurs hex)
    vector<string> canvas(40, string(120, ' '));

    auto iterateur = joueur.get_plateau().get_iterateur_debut();
    auto iterateur_fin = joueur.get_plateau().get_iterateur_fin();

    // itere sur toute la map
    do {
        // Coordonees hexagoneales
        int q = (int) iterateur->first.x;
        int r = (int) iterateur->first.y;
        const Hexagone& h = iterateur->second;

        // coordonnées "écran" (placement en quinconce)
        int px = q * (hexW - 3) + r * ((hexW - 3) / 2);
        int py = r * (hexH - 1);

        // message centré dans 5 colonnes
        string msg = h.get_displayed_text();
        if (msg.size() > 5) msg = msg.substr(0,5); // tronque si message trop long
        int padLeft  = (5 - msg.size()) / 2;
        int padRight = 5 - msg.size() - padLeft;

        // construire chaque ligne de l’hexagone
        std::string top    = "   _ _   ";

        std::string l1     = " /" + std::to_string(h.get_hauteur()) +
                    " " + std::to_string(h.get_hauteur()) +
                    " " + std::to_string(h.get_hauteur()) + "\\ ";

        string l2 = "/" + to_string(h.get_hauteur())
                         + string(padLeft, ' ')
                         + msg
                         + string(padRight, ' ')
                         + to_string(h.get_hauteur()) + "\\";

        string l3     = "\\" + to_string(h.get_hauteur())
                             + string(5, 'X')
                             + to_string(h.get_hauteur()) + "/";

        string l4     = " \\_" + to_string(h.get_hauteur())
                             + "_" + to_string(h.get_hauteur())
                             + "_/ ";

        // dessiner dans le canvas si dans les bornes
        if (py + 4 < (int)canvas.size() && px + hexW <= (int)canvas[0].size()) {
            canvas[py+0].replace(px, hexW, top);
            canvas[py+1].replace(px, hexW, l1);
            canvas[py+2].replace(px, hexW, l2);
            canvas[py+3].replace(px, hexW, l3);
            canvas[py+4].replace(px, hexW, l4);
        }

    } while (++iterateur != iterateur_fin);

    // Affichage final
    for (auto &line : canvas) {
        std::cout << line << "\n";
    }
}