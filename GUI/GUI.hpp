
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
#include <math.h>
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

#include "../Utils.hpp"
#include <QStackedWidget>
#include "../HexagoneContainer/HexagoneContainer.hpp"

// Hexagones //

// Hexagone
class HexagonObjet :public QObject, public QGraphicsPolygonItem {
    // QGraphicsPolygonItem --> permet de cree des polygones qu'on pourra ajouter à la QGraphicsScene
    Q_OBJECT //  obligatoire pour les siganux
public:
    bool interactif = true;
    HexagonObjet();

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (interactif) {
            qDebug() << "Hexagone";
            emit hexagoneClique();
            setBrush(Qt::green);
        }
    }
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
};

class EcranSaisieNoms : public QWidget {

};

class EcranChoixRegles : public QWidget {

};


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

    EcranJeu(); // Constructeur
};

// Ecran main (gameManager) //

class MainWindow : public QWidget {
    Q_OBJECT
public:
    QStackedWidget* pile; // Pile de Widget
    EcranTitre* titre;
    EcranJeu* jeu;


    MainWindow();
    void mettreAJourPlateau(HexagoneContainer& plateau);
    void lancerLeJeu();
};








namespace constGUI {
    void backgroundMap(int size, QGraphicsScene* scene);

    QBrush couleurAkropolisToQt(CouleursAkropolis couleur);

    QPointF axialToPixel(int q, int r);

    Vector2 grilleToAxial(int col, int ligne, int offsetCentre) ;
}

#endif //LO21_PROJET_GUI_HPP