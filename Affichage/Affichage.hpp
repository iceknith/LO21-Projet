#ifndef LO21_PROJET_AFFICHAGE_HPP
#define LO21_PROJET_AFFICHAGE_HPP

#include "../Utils.hpp"
#include "../Players/Players.hpp"


class Affichage {

public:
   virtual void affiche_plateau_actuel(Joueur& joueur);
};

class AffichageConsole : Affichage{
    static AffichageConsole* instance;
    const int hexH = 5; // lignes
    const int hexW = 9; // colonnes

    AffichageConsole() = default;

public:

    static AffichageConsole* getInstance() {
        if (instance == nullptr) instance = new AffichageConsole();
        return instance;
    }

    void affiche_plateau_actuel(Joueur &joueur);
};


#endif //LO21_PROJET_AFFICHAGE_HPP
