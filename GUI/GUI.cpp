#include "GUI.hpp"

#include "../Affichage/Affichage.hpp"

// Hexagones //

HexagoneGUIObjet::HexagoneGUIObjet(const CouleursAkropolis couleur, const std::string& description, const int height,
                                   const bool doOutline[6]) :
        hex(this), outline(this), text(this), hauteur(this) {
    // Construction de l'Hexagone & de l'outline
    QPolygonF points;
    QPainterPath outlinePath;
    double rayon = GUIConstants::HEX_SIZE;

    // On définit le premier point, pour l'outline
    double angle = (60*5)*(M_PI/180);
    double x = rayon * std::cos(angle);
    double y = rayon * std::sin(angle);
    QPointF currentPoint{x,y};
    outlinePath.moveTo(currentPoint);

    for (int i=0;i<6;++i) {
        angle = (60*i)*(M_PI/180);

        x = rayon * std::cos(angle);
        y = rayon * std::sin(angle);
        currentPoint = QPointF{x,y};

        // Construction de l'hexagone
        points << currentPoint;

        // Construction du contour
        if (doOutline[i]) {
            outlinePath.lineTo(currentPoint);
        }
        outlinePath.closeSubpath();
        outlinePath.moveTo(currentPoint);
    }
    hex.setPolygon(points);
    hex.setBrush(constGUI::akropolisToQTColors[couleur]); // FOND
    hex.setPen(Qt::NoPen);
    outline.setPath(outlinePath);
    hex.setPos(0,0);
    outline.setPen(QPen(constGUI::outlineColor, 2+height));
    outline.setPos(0,0);

    // Construction du texte
    text.setPlainText(QString::fromStdString(description));
    text.setDefaultTextColor(constGUI::outlineColor);
    text.setPos(-text.boundingRect().width()/2, -text.boundingRect().height());

    // Construction du texte de la hauteur
    hauteur.setPlainText(QString::number(height));
    hauteur.setDefaultTextColor(constGUI::outlineColor);
    hauteur.setPos(-hauteur.boundingRect().width()/2, 0);

    //permet reception click souris
    setAcceptHoverEvents(true);
}

// Camera Map
CameraMap::CameraMap(QGraphicsScene* scene) : QGraphicsView(scene) {

    //Retire les barres de defilement
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Zoom
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

// QT - ECRANS //

EcranTitre::EcranTitre() {
    // Mise en page verticale
    QVBoxLayout* layout = new QVBoxLayout(this);

    // TITRE
    QLabel* texte = new QLabel("AKROPOLIS");
    texte->setAlignment(Qt::AlignCenter);
    texte->setStyleSheet("font-size: 60px; font-weight: bold;");

    // Bouton start
    QPushButton* StartBouton = new QPushButton("START");
    StartBouton->setStyleSheet("font-size: 20px; padding: 10px; background: red;");

    // mise en page
    layout->addStretch();
    layout->addWidget(texte);
    layout->addSpacing(50);
    layout->addWidget(StartBouton);
    layout->addStretch();

    connect(StartBouton, &QPushButton::clicked, this, &EcranTitre::startGame);
}

EcranSelectionSauvegarde::EcranSelectionSauvegarde() {
    // Mise en page verticale
    QVBoxLayout* layout = new QVBoxLayout(this);

    // TITRE
    QLabel* texte = new QLabel("AKROPOLIS");
    texte->setAlignment(Qt::AlignCenter);
    texte->setStyleSheet("font-size: 60px; font-weight: bold;");

    // Bouton start
    QPushButton* StartBouton = new QPushButton("NOUVELLE PARTIE");
    QPushButton* LoadBouton = new QPushButton("CHARGER PARTIE");
    StartBouton->setStyleSheet("font-size: 20px; padding: 10px; background: red;");
    LoadBouton->setStyleSheet("font-size: 20px; padding: 10px; background: orange;");

    // mise en page
    layout->addStretch();
    layout->addWidget(texte);
    layout->addSpacing(50);
    layout->addWidget(StartBouton);
    layout->addWidget(LoadBouton);
    layout->addStretch();

    connect(StartBouton, &QPushButton::clicked, this, &EcranSelectionSauvegarde::selectionFinished);
    connect(LoadBouton, &QPushButton::clicked, this, &EcranSelectionSauvegarde::selectionFinished);
    connect(LoadBouton, &QPushButton::clicked, this, &EcranSelectionSauvegarde::activateChargeSauvegarde);
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

    // debug
    AffichageGUI* affichageGUI = new AffichageGUI();
    affichageGUI->setSceneMap(sceneMap);
    affichageGUI->setLabelNom(labelNom);
    affichageGUI->setLabelPierre(labelPierre);
    affichageGUI->setLabelScore(labelScore);

    JoueurSimple j{};
    j.setNomJoueur("Dimi");
    j.set_pierre(9);
    j.set_score(getScoreSimple());
    Vector2 position = Vector2(1,7);
    j.place_tuile(new TuileDepart(), position, true);
    position = Vector2(1,5);
    j.place_tuile(new TuileJeu(), position);
    position = Vector2(1,6);
    j.place_tuile(new TuileJeu(), position);
    position = Vector2(1,9);
    j.place_tuile(new TuileJeu(), position);

    affichageGUI->Affichage::affiche_joueur(j);

    // ----------------------------------------------------
    layoutGlobal->addWidget(barreInfo);
    layoutGlobal->addWidget(zoneChantier);
    layoutGlobal->addWidget(vueMap);
}


// Ecran main (gameManager) //

MainWindow::MainWindow() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    pile = new QStackedWidget();

    //initialisation de nos ecrans
    ecranTitre = new EcranTitre();
    pile->addWidget(ecranTitre);
    ecranSelectionSauvegarde = new EcranSelectionSauvegarde();
    pile->addWidget(ecranSelectionSauvegarde);
    ecranJeu = new EcranJeu();
    pile->addWidget(ecranJeu);

    // Pile
    layout->addWidget(pile);
}