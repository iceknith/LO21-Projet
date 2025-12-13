
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

#include "../Utils.hpp"




// QGraphicsPolygonItem --> permet de cree des polygones qu'on pourra ajouter à la QGraphicsScene
class HexagonObjet :public QObject, public QGraphicsPolygonItem {
    Q_OBJECT//  obligatoire pour les siganux

public:
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





class Application : public QWidget {

    QGraphicsPolygonItem *HexagonItemA;


    //Q_OBJECT // TODO: gestion interactions
    // Tous les éléments present dans la fenetre de jeu
    //zone 1
    QGraphicsView *vueChantier;
    QLabel *currentPlayerLabel;
    //zone 2
    QGraphicsView *scenePlateau;
    QLabel *ImageLabel;
    QLabel *labelPierres;
public:
    Application();
};



namespace constGUI {
    void backgroundMap(int size, QGraphicsScene* scene);
}

#endif //LO21_PROJET_GUI_HPP