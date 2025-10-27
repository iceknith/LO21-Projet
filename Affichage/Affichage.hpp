#ifndef LO21_PROJET_AFFICHAGE_HPP
#define LO21_PROJET_AFFICHAGE_HPP

#include "../Utils.hpp"
#include "../Players/Players.hpp"


class Affichage {

public:
   virtual void affiche_plateau_actuel(Joueur& joueur) {};
};

class AffichageConsole : Affichage{
    static AffichageConsole* instance;
    const int hexH = 5; // lignes
    const int hexW = 9; // colonnes

public:
    AffichageConsole() = default;

    static AffichageConsole* getInstance() {
        if (instance == nullptr) instance = new AffichageConsole();
        return instance;
    }

    void affiche_plateau_actuel(Joueur &joueur);
};

//! Ensemble de fonctions utiles à l'affichage console
namespace AffichageConsoleUtils {
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
    //! Donne la couleur en type string
    /*!
     * @param couleur la couleur dont on veut changer le type
     * @return cette meme couleur sous le type string
     */
    string couleur_to_string(CouleursAkropolis couleur);
}


#endif //LO21_PROJET_AFFICHAGE_HPP
