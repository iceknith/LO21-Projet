#include "GUI.hpp"




Application::Application() {



    //initialisation, QVBoxLayout --> pour gerer l'emplacement de tous nos prochains elements (verticalement)
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(0,0,0,0); // Colle aux bords

    // ============================================================
    // ZONE 1 : PLAYER ID + CHANTIER
    // composé de zoneHaut (QWidget) et LayoutHaut (QHBoxLayout)
    QWidget *zoneHaut = new QWidget();
    zoneHaut->setStyleSheet("background-color: #b0b0b0;");
    // QHBoxLayout pour gerer l'emplacement de tous nos prochains elements en haut de la fenetre (verticalement)
    QHBoxLayout *layoutHaut = new QHBoxLayout(zoneHaut);

    // Nom des joueurs
    currentPlayerLabel = new QLabel("<b>Joueur : </b> XX");
    currentPlayerLabel->setStyleSheet("font-size: 30px; color: orange;");

    // Le Chantier
    vueChantier = new QGraphicsView();
    QGraphicsScene *sceneChantier = new QGraphicsScene(); // On stocke la scène dans une variable pour l'utiliser
    vueChantier->setScene(sceneChantier);
    vueChantier->setStyleSheet("background: white;");



    layoutHaut->addWidget(currentPlayerLabel);
    layoutHaut->addWidget(vueChantier, 2);

    // ajout au widget principale
    layoutPrincipal->addWidget(zoneHaut, 2);

    // ============================================================
    // ZONE 2 : stats & buttuns + map hexagones
    // composé de zoneBas (QWidget) et layoutBas(QHBoxLayout)
    QWidget *zoneBas = new QWidget();
    QHBoxLayout *layoutBas = new QHBoxLayout(zoneBas);
    layoutBas->setContentsMargins(0,0,0,0);

    // Panneau Latéral (Stats + Boutons)
    QGroupBox *panneauStats = new QGroupBox("Informations");
    panneauStats->setStyleSheet("background-color: grey;");
    QVBoxLayout *layoutStats = new QVBoxLayout(panneauStats);



    // Affichage map hexagonale
    scenePlateau = new QGraphicsView();
    scenePlateau ->setScene(new QGraphicsScene());
    scenePlateau ->setStyleSheet("background: black;");



    layoutBas ->addWidget(panneauStats,2);
    layoutBas ->addWidget(scenePlateau,8);
    layoutPrincipal->addWidget(zoneBas, 4);

}

HexagonObjet::HexagonObjet(){
    QPolygonF points;
    double rayon = GUIConstants::HEX_SIZE;

    for (int i=0;i<6;++i) {
        double angle = (60*i)*(M_PI/180);

        double x = rayon * std::cos(angle);
        double y = rayon * std::sin(angle);

        points << QPointF(x, y);
    }
    this->setPolygon(points);

    // Apparance
    this->setBrush(QBrush(Qt::lightGray)); // FOND
    this->setPen(QPen(Qt::gray,3));// CONTOURS

    //permet reception click souris
    setAcceptHoverEvents(true);
}

void constGUI::backgroundMap(int size, QGraphicsScene* scene) {
    double rayon = GUIConstants::HEX_SIZE;


    double hauteur = rayon * std::sqrt(3.0);
    double largeur = rayon * 1.5;



    double ecartVertical = hauteur;

    for (int ligne = 0; ligne < size; ++ligne) {
        for (int col = 0; col < size; ++col) {

            HexagonObjet* hex = new HexagonObjet();

            // Calcul des positions
            double x = col * largeur;
            double y = ligne * ecartVertical;

            // Decalage (QUINCONCE)
            if (col % 2 != 0) {
                y += hauteur / 2.0;
            }

            hex->setPos(x, y);
            scene->addItem(hex);
        }
    }
}
