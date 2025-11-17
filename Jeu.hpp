#ifndef LO21_PROJET_JEU_HPP
#define LO21_PROJET_JEU_HPP

#include <limits>
#include "Players/Players.hpp"
#include "Affichage/Affichage.hpp"
#include "Chantier/Chantier.hpp"
#include "Chantier/Deck.hpp"


namespace constJeu {
    const size_t nombreJoueursMax{4};
}

//! La classe responsable de gérer tout le cycle de vie du jeu
class Jeu {
protected:
    //! Le mode de jeu (multijoueur ou solo)
    GameMode modeDeJeu;
    //! La difficulté du jeu (mode illustre architecte)
    Difficulte difficulte;

    //! Le nombre de joueurs qui participent au jeu
    size_t nombreJoueurs;
    //! Les joueurs qui jouent dans ce jeu
    Joueur* joueurs[constJeu::nombreJoueursMax];
    //! Le deck du jeu
    /*
     * Le deck du jeu
     * Il s'agit d'un pointeur, car le deck n'est initialisé que après que les joueurs ont été séléctionnés
     */
    Deck* deck;
    //! Le chantier du jeu
    Chantier chantier;
    //! L'affichage du jeu.
    /*
     * L'affichage du jeu
     * Il s'agit d'un pointeur car on traitera avec des enfants de l'affichage
    */
    Affichage* affichage;

    // Game loop methodes

    // Initialisation des plateaux des joueurs
    void initialisePlateau();

    //! La méthode chargée de la séléction de joueurs
    virtual void selectJoueurs() {};

    //! La méthode chargée de la séléction du mode de jeu
    virtual void selectGameMode() {};
    //! La méthode chargée de la séléction d'une tuile.
    virtual Tuile* selectTuile(size_t joueur) {return nullptr;}
    //! La méthode chargée du placement d'une tuile séléctionné.
    virtual void placeTuile(size_t joueur, Tuile* tuileSelected) {};
    //! La méthode chargée de gérer l'affichage d'un tour automatique
    virtual void afficheTourAutomatique(size_t joueur) {};

    //! La méthode chargée de la gestion de la fin de partie
    virtual void finDePartie() {};

public:
    virtual void gameLoop();
};

class JeuConsole : public Jeu {
protected:
    void selectJoueurs() override;
    void selectGameMode() override;
    Tuile* selectTuile(size_t joueur) override;
    void placeTuile(size_t joueur, Tuile* tuileSelected) override;
    void afficheTourAutomatique(size_t joueur) override;
    void finDePartie() override;

    //! Affiche toutes les informations au joueur lors du placement de tuile
    void afficheJoueur(size_t joueur, Plateau& tuileSelected, Vector2& positionSelectionne);

/*
    Tuile* selectTuileIllustreArchitecte(size_t joueur) override;
    void placeTuileIllustreArchitecte(size_t joueur, Tuile* tuileSelected) override;
*/
public:
    JeuConsole();
};

class JeuGUI : public Jeu {

};



#endif
