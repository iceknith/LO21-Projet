#include "GUI.hpp"




EcranTitre::EcranTitre() {
    // Mise en page verticale
    QVBoxLayout* layout = new QVBoxLayout(this);

    // TITRE
    QLabel* texte = new QLabel("AKROPOLIS");
    texte->setAlignment(Qt::AlignCenter);
    texte->setStyleSheet("font-size: 60px; font-weight: bold;");

    // Bouton start
    QPushButton* bouton = new QPushButton("PLAY");
    bouton->setStyleSheet("font-size: 20px; padding: 10px; background: orange;");

    // mise en page
    layout->addStretch();
    layout->addWidget(texte);
    layout->addSpacing(20);
    layout->addWidget(bouton);
    layout->addStretch();

    // Quand on clique sur le bouton => émet le signal "clickSurJouer"
    connect(bouton, &QPushButton::clicked, this, &EcranTitre::startGame);
}

EcranJeu::EcranJeu() {
// Layout Principal (Vertical)
    QVBoxLayout* layoutGlobal = new QVBoxLayout(this);
    layoutGlobal->setContentsMargins(0,0,0,0);
    layoutGlobal->setSpacing(0);

    // Zone 1: barre d'infos
    QWidget* barreInfo = new QWidget();
    barreInfo->setFixedHeight(50);
    barreInfo->setStyleSheet("background-color: #333; color: white;");

    QHBoxLayout* layoutInfo = new QHBoxLayout(barreInfo);

    labelNom = new QLabel("Joueur: XXXX");
    labelScore = new QLabel("Score actuelle: XXXXX");
    labelPierre = new QLabel("Pierres: XXXXX");


    layoutInfo->addWidget(labelNom);
    layoutInfo->addStretch(); // Pousse les éléments pour les écarter
    layoutInfo->addWidget(labelScore);
    layoutInfo->addStretch();
    layoutInfo->addWidget(labelPierre);

    // ----------------------------------------------------
    //Zone 2: chantier
    zoneChantier = new QWidget();
    zoneChantier->setFixedHeight(200);
    zoneChantier->setStyleSheet("background-color: #b0b0b0; border-bottom: 3px solid black;");

    QLabel* lblTemp = new QLabel("EMPLACEMENT DU CHANTIER", zoneChantier);
    lblTemp->move(20, 60); // Juste pour repérer la zone

    // ----------------------------------------------------
    //zone 3: plateau

    sceneMap = new QGraphicsScene();
    vueMap = new CameraMap(sceneMap);
    constGUI::backgroundMap(10, sceneMap);


    // ----------------------------------------------------
    layoutGlobal->addWidget(barreInfo);
    layoutGlobal->addWidget(zoneChantier);
    layoutGlobal->addWidget(vueMap);
}


MainWindow::MainWindow() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    // Pile
    pile = new QStackedWidget();

    // innitialisation de nos deux ecran
    titre = new EcranTitre();
    jeu = new EcranJeu();

    pile->addWidget(titre);
    pile->addWidget(jeu);

    //affiche la pile
    layout->addWidget(pile);

    pile->setCurrentWidget(titre);

    connect(titre, &EcranTitre::startGame, this, &MainWindow::lancerLeJeu);
}

void MainWindow::lancerLeJeu() {
    qDebug() << "Changement d'écran -> Jeu !";
    // On tourne la page : on affiche l'écran jeu
    pile->setCurrentWidget(jeu);
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
