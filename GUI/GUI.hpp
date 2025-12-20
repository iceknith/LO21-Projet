#ifndef LO21_PROJET_GUI_HPP
#define LO21_PROJET_GUI_HPP

#include "EcranJeu.hpp"

#include <QStackedWidget>
#include "MenusDatas.hpp"

// QT - ECRANS //

//! La classe AbstractEcran :
/*!
  La classe AbstractEcran est la classe de base pour tous les menus basique du jeu (titre + n boutons).
*/
class AbstractEcran : public QWidget {
    Q_OBJECT
protected:
    QVBoxLayout* mainLayout;
    // Configure le titre et le layout de base.
    void ecranBasics(const QString& titre, bool avecBoutonRetour = false);
    // Genere dynamiquement les boutons à partir d'un conteneur de donnée.
    template <typename T, typename ClassFille> void setupBoutons(T &data, ClassFille* fille);
public:
    AbstractEcran(QWidget* parent = nullptr);
    signals:
        void backRequested(bool); // Signal commun pour le retour
};
//! Classes filles :
/*!
  Chaqu'une represente un etat du menu (selection difficulté, nombre de joueurs...).
*/
class EcranSelectionSauvegarde : public AbstractEcran {
    Q_OBJECT
public:
    EcranSelectionSauvegarde();

    signals:
        void selectionFinished(bool chargeSauvegarde);
};
class EcranSelectionModeDeJeu : public AbstractEcran {
    Q_OBJECT
public:
    EcranSelectionModeDeJeu();
    signals:
        void selectionFinished(GameMode modeDeJeu);

};
class EcranSelectionNombreJoueurs : public AbstractEcran {
    Q_OBJECT
    public:
    EcranSelectionNombreJoueurs();
    signals:
        void selectionFinished(int nombreDeJoueurs);
};
class EcranDifficulteArchitechte : public AbstractEcran {
    Q_OBJECT
        public:
    EcranDifficulteArchitechte();
    signals:
    void selectionFinished(Difficulte difficulte);

};
class EcranVitessePartie : public AbstractEcran {
    Q_OBJECT
        public:
    EcranVitessePartie();
    signals:
        void selectionFinished(VITESSE vitesse);
};

//! La classe EcranTitre :
/*!
  Ecran titre du jeu avec bouton start.
*/
class EcranTitre : public QWidget {
    Q_OBJECT

public:
    EcranTitre();

    signals:
        void startGame();
};
//! La classe EcranSaisieNoms :
/*!
  Ecran selection des noms de chaque joueur.
*/
class EcranSaisieNoms : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* layoutChampsSaisies;
    std::vector<QLineEdit*> noms;
public:
    EcranSaisieNoms();
    // Pour poser le bon nombre de champs de texts
    void setUpChamps(int nbChamps);

    signals:
    void saisieNoms(std::vector<QString> noms);

};
//! La classe EcranChoixRegles :
/*!
  TODO :
*/
class EcranChoixRegles : public QWidget {
    Q_OBJECT
    QPushButton* boutons[GameConstants::scoreAmounts];

    public:
    EcranChoixRegles();
    signals:
    void selectionFinished(bool varianteCouleurs[GameConstants::scoreAmounts]);
};
//! La classe EcranVictoire :
/*!
  La classe EcranVictoire implemente l'ecran titre du jeu avec un bouton start.
*/
class EcranVictoire : public QWidget {
    Q_OBJECT
    public:
    EcranVictoire() ;
    signals:
    void startGame();
};


// Ecran main (gameManager) //

//! La classe MainWindow :
/*!
    MainWindow: Gestionnaire des fenetres.
    Utilise une pile (QStackedWidget) et permet de basculer entre les ecrans du jeu.
*/
class MainWindow : public QWidget {
    Q_OBJECT

    QStackedWidget* pile; // Pile de Widget
    // Menus
    EcranTitre* ecranTitre;
    EcranSelectionSauvegarde* ecranSelectionSauvegarde;
    EcranSelectionModeDeJeu* ecranSelectionModeDeJeu;
    EcranSelectionNombreJoueurs* ecranSelectionNombreJoueurs;
    EcranDifficulteArchitechte* ecranDifficulteArchitechte;
    EcranSaisieNoms* ecranSaisieNoms;
    EcranChoixRegles* ecranChoixRegles;
    // Gameplay
    EcranJeu* ecranJeu = nullptr;
    EcranVictoire* victoire = nullptr;
public:
    MainWindow();
    void showEcran(QWidget* ecran) {pile->setCurrentWidget(ecran);};

    EcranTitre* getEcranTitre() const {return ecranTitre;}
    EcranSelectionSauvegarde* getEcranSelectionSauvegarde() const {return ecranSelectionSauvegarde;}
    EcranSelectionModeDeJeu* getEcranSelectionModeDeJeu() const {return ecranSelectionModeDeJeu;}
    EcranSelectionNombreJoueurs* getEcranSelectionNombreJoueurs() const {return ecranSelectionNombreJoueurs;}
    EcranDifficulteArchitechte* getEcranDifficulteArchitechte() const {return ecranDifficulteArchitechte;}
    EcranSaisieNoms* getEcranSaisieNoms() const {return ecranSaisieNoms;}
    EcranChoixRegles* getEcranChoixRegles() const {return ecranChoixRegles;}
    EcranJeu* getEcranJeu() const {return ecranJeu;}
    EcranVictoire* getEcranVictoire() const {return victoire;}

};

#endif //LO21_PROJET_GUI_HPP