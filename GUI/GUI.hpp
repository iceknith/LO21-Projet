#ifndef LO21_PROJET_GUI_HPP
#define LO21_PROJET_GUI_HPP

#include "../Tuile/Tuile.hpp"

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



class Application : public QWidget {
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


class TuileGUI : public QGraphicsItemGroup {
private:
    Tuile* tuile;
    Vector2 axialToPixel(Vector2 axial);
    std::string getHexImage(Hexagone* hex);
public:
    TuileGUI(Tuile* tuileModele);
    Tuile* getTuile() const { return tuile; }

};


#endif //LO21_PROJET_GUI_HPP