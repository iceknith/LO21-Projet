#include "vuepartie.h"
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QLCDNumber>
#include "..\..\LO21-Projet\Jeu.hpp"

VuePartie::VuePartie(QWidget * parent): QWidget{parent}{
    this->Deck = new QLabel{"Deck"};

    this->nbTuilesDeck = new QProgressBar{};
    this->nbTuilesDeck->setRange(
        0, static_cast<int>(Deck::get_taille());
    this->nbTuilesDeck->setTextVisible(false);
    this->Chantier = new QLabel{"Chantier"};
    this->Joueur1 = new QLabel{"Partie du Joueur 1"};
    this->layoutInformations = new QHBoxLayout{};
    this->layoutInformations->addWidget(Deck);
    this->layoutInformations->addWidget(nbTuilesDeck);
    this->layoutInformations->addWidget(score);
    this->layoutInformations->addWidget(scoreJoueur);
    switch (Jeu::nombreJoueurs){
        case Jeu::nombreJoueurs == 1 :
            this->Architecte = new QLabel{"Partie de l'Illustre Architecte"};
        case Jeu::nombreJoueurs == 2:
            this->Joueur2 = new QLabel{"Partie du Joueur 2"};

        case Jeu::nombreJoueurs == 3:
            this->Joueur2 = new QLabel{"Partie du Joueur 2"};
            this->Joueur3 = new QLabel{"Partie du Joueur 3"};
        case Jeu::nombreJoueurs == 4:
            this->Joueur2 = new QLabel{"Partie du Joueur 2"};
            this->Joueur3 = new QLabel{"Partie du Joueur 3"};
            this->Joueur4 = new QLabel{"Partie du Joueur 4"};
    }
}

void VuePartie::fillTuile() {
    std::size_t i{};
    for (const auto & tuile : Chantier::get_taille()) {
        this->vuetuiles[i]->setTuile(tuile);
        i += 1;
    }

    while (i < Chantier::get_taille()) {
        this->vuetuiles[i]->setNoTuile();
        i += 1;
    }
}
