
#ifndef LO21_PROJET_GUI_HPP
#define LO21_PROJET_GUI_HPP


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

#include "../Utils.hpp"
#include <QStackedWidget>
// VUE DE LA MAP
class CameraMap : public QGraphicsView {
public:

    CameraMap(QGraphicsScene* scene) : QGraphicsView(scene) {
        // this->setDragMode(QGraphicsView::ScrollHandDrag);

        //Retire les barres de defilement
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        //Zoom
        setRenderHint(QPainter::Antialiasing);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    }

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
};


class EcranTitre : public QWidget {
    Q_OBJECT
public:
    EcranTitre();

    signals:
        void startGame();
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

class MainWindow : public QWidget {
    Q_OBJECT
public:
    QStackedWidget* pile; // Pile de Widget
    EcranTitre* titre;
    EcranJeu* jeu;


    MainWindow();

    void lancerLeJeu();
};



// QGraphicsPolygonItem --> permet de cree des polygones qu'on pourra ajouter à la QGraphicsScene
class HexagonObjet :public QObject, public QGraphicsPolygonItem {
    Q_OBJECT//  obligatoire pour les siganux

public:
    CouleursAkropolis couelur = CouleursAkropolis::BLANC;
    TypeHexagone type = TypeHexagone::Hexagone;
    bool interactif = true;
    HexagonObjet();

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (interactif) {
            qDebug() << "Clic reçu sur un hexagone !";

            // emmet signal
            emit hexagoneClique();
            setBrush(Qt::green);
        }
    }

    signals:
        //
        void hexagoneClique();
};





namespace constGUI {
    void backgroundMap(int size, QGraphicsScene* scene);
}

#endif //LO21_PROJET_GUI_HPP