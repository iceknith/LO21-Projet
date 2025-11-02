#ifndef LO21_PROJET_DECK_HPP
#define LO21_PROJET_DECK_HPP

#include "../Tuile/Tuile.hpp"

const int max_tuiles_dans_deck = 61;

class Deck {
private:
    //! La taille maximale du Deck (est dépendante du nombre de joueurs)
    int taille;
    //! le nombre de tuiles actuellement dans le Deck
    int nombreTuiles;
    //! Le tableau enregistrant toutes les tuiles sur tout le Deck
    Tuile tuiles[max_tuiles_dans_deck];
public:
    //! Initialise le Deck selon le nombre de joueurs.
    Deck(int nombre_joueurs);
    //! Getteur de la taille maximale du Deck
    int get_taille() {return taille;};
    //! Getteur du nombre de tuiles
    int get_nombre_tuiles(){return nombreTuiles;};
    //! Tire la tuile la plus en haut du deck
    Tuile tirer_tuile();
    //! Tire les x tuiles les plus en haut du deck
    Tuile* tirer_tuile(int nombre_tuiles);
};


#endif
