
#ifndef LO21_PROJET_GUI_HPP
#define LO21_PROJET_GUI_HPP

// JE NE SUIS PAS SUR QU'ILS SOIENT TOUS UTILES!
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QDirIterator>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QDebug>
#include <QTimer>
#include <QLineEdit>
#include <iostream>


#include "../Utils.hpp"
#include <QStackedWidget>
//#include "../HexagoneContainer/HexagoneContainer.hpp"

namespace constGUI {
    void backgroundMap(int size, QGraphicsScene* scene);

    QBrush couleurAkropolisToQt(CouleursAkropolis couleur);

    QPointF axialToPixel(int q, int r);

    Vector2 grilleToAxial(int col, int ligne, int offsetCentre) ;

    const QColor akropolisToQTColors[6] {
    Qt::white,
    Qt::blue,
    Qt::yellow,
    Qt::red,
    Qt::magenta,
    Qt::green,
    };

     const QColor outlineColor = Qt::black;
}

// Hexagones //

// Hexagone
class HexagoneGUIObjet : public QObject, public QGraphicsItem {
private:
    // QGraphicsPolygonItem --> permet de cree des polygones qu'on pourra ajouter à la QGraphicsScene
    Q_OBJECT //  obligatoire pour les siganux

    QGraphicsPolygonItem hex;
    QGraphicsPathItem outline;
    QGraphicsTextItem text;
    QGraphicsTextItem hauteur;

public:
    bool interactif = true;

    HexagoneGUIObjet(CouleursAkropolis couleur, const std::string& description, int height,
                     const bool doOutline[5]);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (interactif) {
            emit hexagoneClique();
            qDebug("heyyyyy");
        }
    }

    QRectF boundingRect() const override {return hex.boundingRect();}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override {};

    signals:
        void hexagoneClique();
};

// QGraphicsView: nous permet d' afficher tout nous hexagones et qui permet de zommer et plus ... (je reviendrais refaire aux propre tout les comms)
class CameraMap : public QGraphicsView {
protected:
    // On capture le scroll de la souris
    void wheelEvent(QWheelEvent *event) override {
        double zoomScale = 1.05;

        if (event->angleDelta().y() > 0) {
            scale(zoomScale, zoomScale);
        } else {
            scale(1.0 / zoomScale, 1.0 / zoomScale);
        }
    }
public:
    CameraMap(QGraphicsScene* scene);
};

// QT - ECRANS //

class EcranTitre : public QWidget {
    Q_OBJECT
public:
    EcranTitre();
    signals:
        void startGame();
        void loadGame();
};

class EcranSelectionModeDeJeu : public QWidget {
    Q_OBJECT
    public:
    EcranSelectionModeDeJeu();
    signals:
        void modeSolo();
        void modeMulti();
};
/*
class EcranSelectionNombreJoueurs : public QWidget {
    Q_OBJECT
    public:
    EcranSelectionNombreJoueurs();
    signals:
    void nombreJoueurs();
};

class EcranSaisieNoms : public QWidget {

};

class EcranDifficulteArchitechte : public QWidget {

};

class EcranChoixRegles : public QWidget {
    Q_OBJECT
    public:
    EcranChoixRegles();
    signals:
    void reglesChoisies(bool avecVariante);
};

class EcanVictoire : public QWidget {
    Q_OBJECT
    public:
    EcanVictoire();
    signals:
    void retourMenu();
};
*/

class EcranJeu : public QWidget {
public:
    // Indicateurs
    QLabel* labelNom;
    QLabel* labelScore;
    QLabel* labelPierre;

    // Chantier
    QWidget* zoneChantier;

    // La Map
    CameraMap* vueMap;
    QGraphicsScene* sceneMap;

    EcranJeu();
};


// Ecran main (gameManager) //

class MainWindow : public QWidget {
    Q_OBJECT
    int NbJoueurs = 0;
    int difficulte = 1;
    bool Variante = false;
public:
    QStackedWidget* pile; // Pile de Widget

    EcranTitre* titre;
    // Menus
    EcranSelectionModeDeJeu* mode_de_jeu;
    //EcranSelectionNombreJoueurs nombre_joueurs;
    //EcranSaisieNoms saisie_nom;
    //EcranChoixRegles choixRegles;
    // Gameplay
    EcranJeu* jeu;

    //EcanVictoire* victoire;



    MainWindow();
    //void mettreAJourPlateau(HexagoneContainer& plateau);
    void lancerLeJeu();
    void choixNombreJoueur();
    void choixDifficulteArchitechte();
    void choixRegles();
    void choixNoms();
};

#endif //LO21_PROJET_GUI_HPP