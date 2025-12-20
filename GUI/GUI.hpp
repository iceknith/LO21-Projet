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
#include <QStyle>
#include <iostream>
#include <QColor>

#include "../Utils.hpp"
#include <QStackedWidget>

class AffichageGUI;


namespace constGUI {
    void backgroundMap(int size, QGraphicsScene* scene);

    QBrush couleurAkropolisToQt(CouleursAkropolis couleur);

    QPointF axialToPixel(int q, int r);

    Vector2 grilleToAxial(int col, int ligne, int offsetCentre) ;

    const QColor akropolisToQTColors[6] {
    QColor(193,229,234),//white
    QColor(59,119,166),//blue
    QColor(243,194,32),//yellow
    QColor(181,65,49),//red
    QColor(97,64,122),//magenta
    QColor(86,190,68),//green
    };

    const QColor outlineColor = QColor(46,44,59);//black
    const QString chantierStyleSheet = "background-color: #343638;";
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
    HexagoneGUIObjet(CouleursAkropolis couleur, const std::string& description, int height,
                     const bool doOutline[5]);

    QRectF boundingRect() const override {return hex.boundingRect();}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override {};
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

class ChantierQGraphicsView : public QGraphicsView {
Q_OBJECT

    void mousePressEvent(QMouseEvent *event) override {if(event->button() == Qt::LeftButton) emit onClicked();}

public:
    ChantierQGraphicsView(QGraphicsScene *s, QWidget *p);

signals:
    void onClicked();
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

class EcranJeu : public QWidget {

Q_OBJECT
    size_t nombreJoueurs = 0;

    // Indicateurs Joueur principal
    QLabel* labelNom;
    QLabel* labelScore;
    QLabel* labelRegleScore;
    QLabel* labelPierre;

    // Chantier
    QWidget* zoneChantier;
    QGraphicsScene** sceneChantier;
    QLabel** labelsChantier;

    // La Map
    QWidget* plateau;
    CameraMap* vueMap;
    QGraphicsScene* sceneMap;
    QWidget* infoJoueurs;

    // Autres joueurs
    QLabel** labelNomJoueurs;
    QLabel** labelScoreJoueurs;
    QLabel** labelPierreJoueurs;
    QGraphicsScene** sceneMapJoueurs;


    QLabel* labelRegles;

    // La tuile séléctionnée
    QGraphicsItemGroup* selectedTuile = nullptr;

    void onPlateauCameraMapMouseMoved(QPointF mousePos);
    void onPlateauCameraMapMousePressed(QPointF mousePos);
    void keyPressEvent(QKeyEvent *event) override;

public:
    AffichageGUI* getAffichageJoueur();
    AffichageGUI** getAffichagesChantier();
    AffichageGUI** getAffichagesJoueursAdverses();
    QLabel** getLabelsChantier() const {return labelsChantier;}

    void setUpWidgets(size_t playerCount);

    void setSelectedTuile(QGraphicsItemGroup* newSelectedTuile);
    QPointF getSelectedTuilePosition() const {return selectedTuile->pos();};
    void removeSelectedTuile() {delete selectedTuile; selectedTuile = nullptr;}

    EcranJeu();
    ~EcranJeu() override;

signals:
    void ready();
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