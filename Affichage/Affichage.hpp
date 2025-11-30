#ifndef LO21_PROJET_AFFICHAGE_HPP
#define LO21_PROJET_AFFICHAGE_HPP

#include "../Utils.hpp"
#include "../Players/Players.hpp"
#include "../GUI/GUI.hpp"
#include <vector>

// Affichage //

class Affichage {

protected:
    virtual void affiche_joueur_actuel(Joueur& joueur, bool selectHexagone, Vector2 selectedHexagone) {};
    virtual void affiche_plateau_actuel(Plateau& plateau, bool selectHexagone, Vector2 selectedHexagone) {};

public:
    void affiche_plateau_actuel(Plateau& plateau) {affiche_plateau_actuel(plateau, false, Vector2());};
    void affiche_plateau_actuel(Plateau& plateau, Vector2 selectedHexagone) {affiche_plateau_actuel(plateau, true, selectedHexagone);};
    void affiche_joueur_actuel(Joueur& joueur) {affiche_joueur_actuel(joueur, false, Vector2());};
    void affiche_joueur_actuel(Joueur& joueur, Vector2 selectedHexagone) {affiche_joueur_actuel(joueur, true, selectedHexagone);};
};

// Affichage console //

class AffichageConsole : public Affichage{
    static AffichageConsole* instance;
    const int hexH = 5; // lignes
    const int hexW = 9; // colonnes

protected:
    void affiche_joueur_actuel(Joueur& joueur, bool selectHexagone, Vector2 selectedHexagone) override;
    void affiche_plateau_actuel(Plateau& plateau, bool selectHexagone, Vector2 selectedHexagone) override;

public:
    AffichageConsole() = default;

    static AffichageConsole* getInstance() {
        if (instance == nullptr) instance = new AffichageConsole();
        return instance;
    }

};

//! Ensemble de fonctions utiles à l'affichage console
namespace constAffichageConsoleHex {
    //! Implémente replace, sauf qu'il 'skip' les charactères identiques à charactere_non_remplace
    /*!
     *
     * @param text_original Le texte d'où on va remplacer des choses
     * @param pos La position du remplacement
     * @param len La taille du remplacement
     * @param text_nouveau Le texte avec lequel on remplace
     * @param charactere_non_remplace Le charactère qui ne remplacera pas le texte_original
     */
    void replace_sauf_charactere(string& text_original, size_t pos, size_t len,
                                 const string& text_nouveau, char charactere_non_remplace);

    //! Convertion entre les coordonées axiales et les coordonées de l'écran
    Vector2 axialToScreen (Vector2 v);
}

// Affichage graphique //

class AffichageGUI : public Affichage {
    Application* fenetre;

public:
    AffichageGUI();

protected:
    void affiche_plateau_actuel(Plateau& plateau, bool selectHexagone, Vector2 selectedHexagone) override;
    void affiche_joueur_actuel(Joueur& joueur, bool selectHexagone, Vector2 selectedHexagone) override;
};

//! Ensemble de fonctions utiles à l'affichage graphique
namespace constAffichageGUI {
    void debugTextures();
}



#endif //LO21_PROJET_AFFICHAGE_HPP
