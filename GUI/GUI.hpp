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
#include <Qstyle>
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
    Q_OBJECT
protected:
    // On capture le scroll de la souris
    void wheelEvent(QWheelEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;


public:
    CameraMap(QGraphicsScene* scene);

signals:
    void mouseMoved(QPointF mousePos);
    void mousePressed(QPointF mousePos);
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
    void backRequested(bool retour);
};

class EcranSelectionNombreJoueurs : public QWidget {
    Q_OBJECT
    public:
    EcranSelectionNombreJoueurs();
    signals:
        void selectionFinished(int nombreDeJoueurs);
        void backRequested(bool retour);
};


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

class EcranDifficulteArchitechte : public QWidget {
    Q_OBJECT
        public:
    EcranDifficulteArchitechte();
    signals:
    void selectionFinished(Difficulte difficulte);
    void backRequested(bool retour);
};

class EcranChoixRegles : public QWidget {
    Q_OBJECT
    public:
    EcranChoixRegles();
    signals:
    void selectionFinished(bool avecVariante);
};

class EcanVictoire : public QWidget {
    Q_OBJECT
    public:
    EcanVictoire() ;
    signals:
    void startGame();
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
    QLabel* labelRegleScore;
    QLabel* labelPierre;

    // Chantier
    QWidget* zoneChantier;
    QGraphicsScene** sceneChantier;
    QLabel** labelsChantier;

    //Autres Joueurs
    QLabel* labelJ1;
    QLabel* labelJ2;
    QLabel* labelJ3;
    QLabel* labelJ4;
    QLabel* labelJ5;


    QLabel* labelRegles;
    // La Map
    CameraMap* vueMap;
    QGraphicsScene* sceneMap;

    // La tuile séléctionnée
    QGraphicsItemGroup* selectedTuile = nullptr;

    void onPlateauCameraMapMouseMoved(QPointF mousePos);
    void onPlateauCameraMapMousePressed(QPointF mousePos);
    void keyPressEvent(QKeyEvent *event) override;

public:
    AffichageGUI* getAffichageJoueur();
    AffichageGUI** getAffichagesChantier(size_t tailleChantier);
    QLabel** getLabelsChantier() const {return labelsChantier;}
    void setSelectedTuile(QGraphicsItemGroup* newSelectedTuile);
    QPointF getSelectedTuilePosition() const {return selectedTuile->pos();};
    void removeSelectedTuile() {delete selectedTuile; selectedTuile = nullptr;}

    EcranJeu();
    ~EcranJeu() override;

signals:
    void selectionTuileFinished(int tuileSelected);
    void selectionPlacementFinished(Vector2 placement);
    void tourneSelectedTuile(bool sensHoraire);
    void retour();
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
    EcanVictoire* getEcranVictoire() const {return victoire;}

};



#endif //LO21_PROJET_GUI_HPP