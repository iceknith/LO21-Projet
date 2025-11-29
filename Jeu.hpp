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
private:
    //! La méthode chargée de calculer les score des gagnants, la map associe score : joueur
    multimap<int, size_t> calculerScores();

protected:
    //! Jeu est un singleton
    static Jeu* jeu;
    //! Le mode de jeu (multijoueur ou solo)
    GameMode modeDeJeu;

    //! Le nombre de tours joués
    size_t nombre_tours;
    //! Le nombre maximum de tours à jouer
    size_t max_nombre_tours;

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
    //! La méthode chargée de la séléction du mode de jeu
    virtual void selectGameMode() = 0;
    //! La méthode chargée de la séléction de joueurs
    virtual void selectJoueurs() = 0;
    //! La méthode chargée de la séléction du niveau de l'Illustre Architechte
    virtual Difficulte selectNiveauIllustreArchitechte() = 0;
    //! La méthode chargée de la séléction des règles de score
    virtual void selectReglesScore() = 0;
    //! La méthode chargée de la séléction d'une tuile.
    virtual Tuile* selectTuile(size_t joueur) = 0;
    //! La méthode chargée du placement d'une tuile séléctionné.
    virtual void placeTuile(size_t joueur, Tuile* tuileSelected) = 0;
    //! La méthode chargée de gérer l'affichage d'un tour automatique
    virtual void afficheTourAutomatique(size_t joueur) = 0;

    //! La méthode chargée de la gestion de la fin de partie
    virtual void finDePartie(multimap<int, size_t> scores) = 0;

    Jeu() = default;
public:
    void gameLoop();

    //! Retourne le jeu instantié, si il existe, sinon retourne nullptr
    static Jeu* getJeu() {return jeu;}
};

class JeuConsole : public Jeu {
private:
    JeuConsole();

    void selectGameMode() override;
    void selectJoueurs() override;
    Difficulte selectNiveauIllustreArchitechte() override;
    void selectReglesScore() override;
    Tuile* selectTuile(size_t joueur) override;
    void placeTuile(size_t joueur, Tuile* tuileSelected) override;
    void afficheTourAutomatique(size_t joueur) override;
    void finDePartie(multimap<int, size_t> scores) override;

    //! Affiche toutes les informations au joueur lors du placement de tuile
    void afficheJoueur(size_t joueur, Tuile& tuileSelected, Vector2& positionSelectionne);
/*
    Tuile* selectTuileIllustreArchitecte(size_t joueur) override;
    void placeTuileIllustreArchitecte(size_t joueur, Tuile* tuileSelected) override;
*/
public:
    static Jeu* getJeu();
};

class JeuGUI : public Jeu {
private:
    JeuGUI() = default;
public:
    static Jeu* getJeu();
};

#endif
