#ifndef LO21_PROJET_ECRANJEU_HPP
#define LO21_PROJET_ECRANJEU_HPP

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
#include <QLineEdit>
#include <QStyle>
#include <QColor>
#include "../Utils.hpp"

class AffichageGUI;
/**
 * @namespace constGUI
 * Regroupe les outils de conversion et les constantes graphiques (couleurs, styles).
 */
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

//! La classe HexagoneGUIObjet :
/*!
  La classe HexagoneGUIObjet permet d'afficher un hexagone
  Gère l'affichage du fond, du contour (outline), du type et de la hauteur.
  Herite de QGraphicsPolygonItem pour dessiner l'hexagone.
*/
class HexagoneGUIObjet : public QObject, public QGraphicsItem {
private:
    Q_OBJECT

            QGraphicsPolygonItem hex;   // La forme géométrique
    QGraphicsPathItem outline;  // Les bordures
    QGraphicsTextItem text;     // Description affichée
    QGraphicsTextItem hauteur;  // Niveau de l'hexagone

public:
    HexagoneGUIObjet(CouleursAkropolis couleur, const std::string& description, int height,
                     const bool doOutline[5]);

    QRectF boundingRect() const override {return hex.boundingRect();}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override {};
};

//! La classe CameraMap :
/*!
  La classe CameraMap permet d'interagire avec le plateau.
  Permet de zoomer avec la molette.
*/
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

//! La classe EcranJeu :
/*!
    EcranJeu: L'ecran principale où se deroule le jeu:
    Il est divisé en 3 parties: Barre information (en haut)
    Le chantier (millieu) et le plateau (bas)
*/
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


#endif //LO21_PROJET_ECRANJEU_HPP
