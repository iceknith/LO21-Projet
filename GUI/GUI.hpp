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

class AffichageGUI;


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

};

class EcranSelectionSauvegarde : public QWidget {
Q_OBJECT

public:
    EcranSelectionSauvegarde();

signals:
    void selectionFinished(bool chargeSauvegarde);
};

class EcranSelectionModeDeJeu : public QWidget {
Q_OBJECT
public:
    EcranSelectionModeDeJeu();
signals:
    void selectionFinished(GameMode modeDeJeu);
};

class EcranSelectionNombreJoueurs : public QWidget {

};

class EcranSaisieNoms : public QWidget {

};

class EcranDifficulteArchitechte : public QWidget {

};

class EcranChoixRegles : public QWidget {
    Q_OBJECT
    public:
    EcranChoixRegles() = default;
    signals:
    void reglesChoisies(bool avecVariante);
};

class EcanVictoire : public QWidget {
    Q_OBJECT
    public:
    EcanVictoire() = default;
    signals:
    void retourMenu();
};

class ChantierQGraphicsView : public QGraphicsView {
Q_OBJECT

    void mousePressEvent(QMouseEvent *event) override {if(event->button() == Qt::LeftButton) emit onClicked();}

public:
    ChantierQGraphicsView(QGraphicsScene *s, QWidget *p) : QGraphicsView(s,p) {}

signals:
    void onClicked();
};

class EcranJeu : public QWidget {

Q_OBJECT
    // Indicateurs
    QLabel* labelNom;
    QLabel* labelScore;
    QLabel* labelPierre;

    // Chantier
    QWidget* zoneChantier;
    QGraphicsScene** sceneChantier;
    QLabel** labelsChantier;

    // La Map
    CameraMap* vueMap;
    QGraphicsScene* sceneMap;
public:
    AffichageGUI* getAffichageJoueur();
    AffichageGUI** getAffichagesChantier(size_t tailleChantier);
    QLabel** getLabelsChantier() {return labelsChantier;}

    EcranJeu();
    ~EcranJeu();

signals:
    void selectionTuileFinished(int tuileSelected);
    void selectionPlacement(QPointF placement);
};


// Ecran main (gameManager) //

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
    EcanVictoire* victoire = nullptr;
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
    EcanVictoire* getEictoire() const {return victoire;}

};



#endif //LO21_PROJET_GUI_HPP