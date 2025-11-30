#ifndef VUEPARTIE_H
#define VUEPARTIE_H

#include <QWidget>
#include <vector>
#include "Jeu.hpp"

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QProgressBar;
class QLCDNumber;
class VueCarte;

class VuePartie : public QWidget, public Jeu {
    Q_OBJECT
public:
    explicit VuePartie(QWidget * parent = nullptr);
private:
    void fillTuile();
    QLabel * score;                 // texte "Score"
    QLCDNumber * scoreJoueur;       // affichage du score
    QLabel * Deck;                // texte "Deck"
    QProgressBar * nbTuilesDeck;  // progression de la pioche
    QLabel * Chantier;              //texte "Chantier"
    QLabel * Joueur1;                   //texte "Partie du joueur 1"
    QLabel * Joueur2;                   //texte "Partie du joueur 2"
    QLabel * Joueur3;                   //texte "Partie du joueur 3"
    QLabel * Joueur4;                   //texte "Partie du joueur 4"
    QLabel * Architecte;                   //texte "Partie de l'Illustre Architecte"
    QHBoxLayout * layoutInformations;
    vector<VueTuile *> vuetuiles;
private slots:
    // slots qui gère les clics sur les cartes
    void TuileClique(VueTuile * vt);
};

#endif // VUEPARTIE_H


