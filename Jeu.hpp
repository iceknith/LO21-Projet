#ifndef LO21_PROJET_JEU_HPP
#define LO21_PROJET_JEU_HPP

#include <limits>
#include "Players/Players.hpp"
#include "Affichage/Affichage.hpp"
#include "Chantier/Chantier.hpp"
#include "Chantier/Deck.hpp"
#include "GUI/GUI.hpp"
#include <QFile>
#include <QFileInfo>
#include <QThread>


namespace constJeu {
    const size_t nombreJoueursMax{4};
    const QString saveFilePath = "save.dat";
}

//! La classe responsable de gérer tout le cycle de vie du jeu
class Jeu : public Serializable {
private:
    //! La méthode chargée de calculer les score des gagnants, la map associe score : joueur
    multimap<int, size_t> calculerScores();

protected:
    //! Jeu est un singleton
    static Jeu* jeu;
    //! Le mode de jeu (multijoueur ou solo)
    GameMode modeDeJeu = GameMode::SOLO;

    //! Le nombre de tours joués
    size_t nombreTours = 0;
    //! Le nombre maximum de tours à jouer
    size_t maxNombreTours = 0;

    //! Le nombre de joueurs qui participent au jeu
    size_t nombreJoueurs = 0;
    //! Les joueurs qui jouent dans ce jeu
    Joueur* joueurs[constJeu::nombreJoueursMax];
    //! Le joueur actuel
    size_t joueurActuel = 0;
    //! Le premier joueur
    size_t premierJoueur = 0;

    //! La tuile de depart des joueurs
    TuileDepart* tuileDepart;
    //! Le deck du jeu
    Deck deck;
    //! Le chantier du jeu
    Chantier chantier;


    // Game loop methodes

    // Initialisation des plateaux des joueurs
    void initialisePlateau();
    //! La méthode chargée d'afficher l'écran d'acceuil
    virtual void titleScreen()=0;
    //! La méthode chargée de demander à l'utilisateur si il veut charger une partie précédente
    virtual bool selectChargerPartie()=0;
    //! La méthode chargée de la séléction du mode de jeu
    virtual void selectGameMode() = 0;
    //! La méthode chargée de la séléction de joueurs
    virtual void selectJoueurs() = 0;
    //! La méthode chargée de la séléction des noms des joueurs
    virtual void selectNomsJoueurs() = 0;
    //! La méthode chargée de la séléction du niveau de l'Illustre Architechte
    virtual Difficulte selectNiveauIllustreArchitechte() = 0;
    //! La méthode chargée de la séléction des règles de score
    virtual void selectReglesScore() = 0;
    //! La méthode chargée de notifier l'affichage qu'on affiche la scène de jeu
    virtual void afficheSceneJeu() = 0;
    //! La méthode chargée de la séléction d'une tuile.
    virtual int selectTuile(size_t joueur) = 0;
    //! La méthode chargée du placement d'une tuile séléctionné.
    virtual bool placeTuile(size_t joueur, Tuile* tuileSelected) = 0;
    //! La méthode chargée de gérer l'affichage d'un tour automatique
    virtual void afficheTourAutomatique(size_t joueur) = 0;

    //! La méthode chargée de la gestion de la fin de partie
    virtual void finDePartie(multimap<int, size_t> scores) = 0;

    //! La méthode chargée de charger la dernière partie
    static void chargerPartie();
    //! La méthode chargée de sauvegarder la partie actuelle
    static void sauvegarderPartie();

    //! Implémentation concrète de la sérialisation
    void serialize(QVariantMap& data, SerializationContext* context) const override;
    //! Implémentation concrète de la désérialisation
    void deserialize(const QVariantMap& data, SerializationContext* context) override;

    Jeu() : deck(), chantier() {tuileDepart = new TuileDepart();}
public:
    ~Jeu();

    virtual void gameLoop(int argc, char *argv[]);

    //! Retourne le jeu instantié, si il existe, sinon retourne nullptr
    static Jeu* getJeu() {return jeu;}

    string className() override {return "Jeu";}
};

// JEU CONSOLE //

class JeuConsole : public Jeu {
private:
    //! L'affichage du jeu.
    /*
     * L'affichage du jeu
    */
    Affichage* affichage;

    JeuConsole();

    void titleScreen() override;
    bool selectChargerPartie() override;
    void selectGameMode() override;
    void selectJoueurs() override;
    void selectNomsJoueurs() override;
    Difficulte selectNiveauIllustreArchitechte() override;
    void selectReglesScore() override;
    void afficheSceneJeu() override {} // Cette methode n'est pas utilisee par le jeu console
    int selectTuile(size_t joueur) override;
    bool placeTuile(size_t joueur, Tuile* tuileSelected) override;
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

// JEU GUI //

class JeuGUI : public Jeu {
private:
    QApplication* app = nullptr;
    MainWindow* window = nullptr;
    QThread* runApp = nullptr;

    AffichageGUI* affichageJoueur = nullptr;
    AffichageGUI** affichageChantier = nullptr;

    JeuGUI() : Jeu() {};


    void titleScreen() override;
    bool selectChargerPartie() override;
    void selectGameMode() override;
    void selectJoueurs() override { nombreJoueurs = 2; joueurs[0]=new JoueurSimple(); joueurs[1]=new JoueurSimple(); }// Temporaire
    void selectNomsJoueurs() override {}
    Difficulte selectNiveauIllustreArchitechte() override { return Difficulte::FACILE; }// Temporaire
    void selectReglesScore() override {
        Score* score = getScoreSimple();
        for (size_t i = 0; i < nombreJoueurs; i++)
            dynamic_cast<JoueurSimple*>(joueurs[i])->set_score(score);
    }
    void afficheSceneJeu() override;
    int selectTuile(size_t joueur) override;// Temporaire
    bool placeTuile(size_t joueur, Tuile* tuileSelected) override { return true; } // Temporaire
    void afficheTourAutomatique(size_t joueur) override {}
    void finDePartie(multimap<int, size_t> scores) override {}

public:

    void gameLoop(int argc, char *argv[]) override;
    static Jeu* getJeu();
};

#endif
