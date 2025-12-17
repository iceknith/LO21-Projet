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

void CameraMap::wheelEvent(QWheelEvent *event) {
    double zoomScale = 1.05;

    if (event->angleDelta().y() > 0) {
        scale(zoomScale, zoomScale);
    } else {
        scale(1.0 / zoomScale, 1.0 / zoomScale);
    }
}

void CameraMap::mouseMoveEvent(QMouseEvent *event) {
    //QPointF position = (event->scenePosition() - frameRect().center());
    QPoint viewPos = mapFromGlobal(event->globalPosition()).toPoint();
    QPointF position = mapToScene(viewPos);
    emit mouseMoved(position);
}

void CameraMap::mousePressEvent(QMouseEvent *event) {
    QPoint viewPos = mapFromGlobal(event->globalPosition()).toPoint();
    QPointF position = mapToScene(viewPos);
    emit mousePressed(position);
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
    QPushButton* LoadBouton = new QPushButton("CHARGER DERNIERE PARTIE");
    StartBouton->setStyleSheet("font-size: 20px; padding: 10px; background: red;");
    LoadBouton->setStyleSheet("font-size: 20px; padding: 10px; background: orange;");

    // mise en page
    layout->addStretch();
    layout->addWidget(texte);
    layout->addSpacing(50);
    layout->addWidget(StartBouton);
    layout->addWidget(LoadBouton);
    layout->addStretch();

    connect(StartBouton, &QPushButton::clicked,
            this, [this](){emit selectionFinished(false);});
    connect(LoadBouton, &QPushButton::clicked,
            this, [this](){emit selectionFinished(true);});
}

EcranSelectionModeDeJeu::EcranSelectionModeDeJeu() {

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* texte  = new QLabel("SELECTION MODE DE JEU");
    texte->setStyleSheet("font-size: 60px; font-weight: bold;");
    layout->addStretch();
    layout->addWidget(texte);
    texte->setAlignment(Qt::AlignCenter);

    QPushButton* boutonSOLO = new QPushButton("SOLO");
    QPushButton* boutonMULTI = new QPushButton("MULTIJOUEUR");
    boutonSOLO->setStyleSheet("font-size: 20px; padding: 10px; background: gray;");
    boutonMULTI->setStyleSheet("font-size: 20px; padding: 10px; background: gray;");

    layout->addStretch();
    layout->addWidget(boutonSOLO);
    layout->addWidget(boutonMULTI);
    layout->addStretch();

    connect(boutonSOLO, &QPushButton::clicked,
            this, [this](){emit selectionFinished(GameMode::SOLO);});
    connect(boutonMULTI, &QPushButton::clicked,
            this, [this](){emit selectionFinished(GameMode::MULTIJOUEUR);});
}

EcranSelectionNombreJoueurs::EcranSelectionNombreJoueurs() {

    QBoxLayout* layout = new QVBoxLayout(this);
    QLabel* texte  = new QLabel("COMBIEN DE JOUEURS?");
    texte->setStyleSheet("font-size: 60px; font-weight: bold;");
    layout->addStretch();
    layout->addWidget(texte);
    texte->setAlignment(Qt::AlignCenter);


    QHBoxLayout* BouttonLayout = new QHBoxLayout(this);

    QPushButton* duo = new QPushButton("2");
    QPushButton* trio = new QPushButton("3");
    QPushButton* quatuor = new QPushButton("4");
    duo->setStyleSheet("font-size: 20px; padding: 10px; background: gray;");
    trio->setStyleSheet("font-size: 20px; padding: 10px; background: gray;");
    quatuor->setStyleSheet("font-size: 20px; padding: 10px; background: gray;");

    layout->addStretch();
    BouttonLayout->addWidget(duo);
    BouttonLayout->addWidget(trio);
    BouttonLayout->addWidget(quatuor);
    layout->addLayout(BouttonLayout);
    layout->addStretch();

    connect(duo, &QPushButton::clicked,
            this, [this](){emit selectionFinished(2);});
    connect(trio, &QPushButton::clicked,
            this, [this](){emit selectionFinished(3);});
    connect(quatuor, &QPushButton::clicked,
            this, [this](){emit selectionFinished(4);});
}

EcranDifficulteArchitechte::EcranDifficulteArchitechte() {
    // TODO: le core du code est un copier coller de EcranSelectionNombreJoueurs -> pas super pratique, faudra qu'on change ca par la suite
    QBoxLayout* layout = new QVBoxLayout(this);
    QLabel* texte  = new QLabel("DIFFICULTE ILLUSTRE ARCHITECHTE");
    texte->setStyleSheet("font-size: 60px; font-weight: bold;");
    layout->addStretch();
    layout->addWidget(texte);
    texte->setAlignment(Qt::AlignCenter);


    QHBoxLayout* BouttonLayout = new QHBoxLayout(this);

    QPushButton* facile = new QPushButton("Hippodamos");
    QPushButton* normale = new QPushButton("Metagenes");
    QPushButton* difficile = new QPushButton("Callicrates");
    facile->setStyleSheet("font-size: 20px; padding: 10px; background: green;");
    normale->setStyleSheet("font-size: 23px; padding: 15px; background: orange;");
    difficile->setStyleSheet("font-size: 26px; padding: 10px; background: red;");

    layout->addStretch();
    BouttonLayout->addWidget(facile);
    BouttonLayout->addWidget(normale);
    BouttonLayout->addWidget(difficile);
    layout->addLayout(BouttonLayout);
    layout->addStretch();

    connect(facile, &QPushButton::clicked,
            this, [this](){emit selectionFinished(Difficulte::FACILE);});
    connect(normale, &QPushButton::clicked,
            this, [this](){emit selectionFinished(Difficulte::NORMALE);});
    connect(difficile, &QPushButton::clicked,
            this, [this](){emit selectionFinished(Difficulte::DIFFICILE);});
}

EcranChoixRegles::EcranChoixRegles() {
    // TODO: le core du code est un copier coller de EcranSelectionNombreJoueurs -> pas super pratique, faudra qu'on change ca par la suite
    QBoxLayout* layout = new QVBoxLayout(this);
    QLabel* texte  = new QLabel("REGLES DE SCORE");
    texte->setStyleSheet("font-size: 60px; font-weight: bold;");
    layout->addStretch();
    layout->addWidget(texte);
    texte->setAlignment(Qt::AlignCenter);

    QHBoxLayout* BouttonLayout = new QHBoxLayout(this);

    QPushButton* facile = new QPushButton("CLASSIQUE");
    QPushButton* normale = new QPushButton("VARIANTE");

    facile->setStyleSheet("font-size: 20px; padding: 15px; background: green;");
    normale->setStyleSheet("font-size: 20px; padding: 15px; background: orange;");

    layout->addStretch();
    BouttonLayout->addWidget(facile);
    BouttonLayout->addWidget(normale);

    layout->addLayout(BouttonLayout);
    layout->addStretch();

    connect(facile, &QPushButton::clicked,
            this, [this](){emit selectionFinished(0);});
    connect(normale, &QPushButton::clicked,
            this, [this](){emit selectionFinished(1);});
}

EcranSaisieNoms::EcranSaisieNoms() {
    QBoxLayout* globalLayout = new QVBoxLayout(this);
    // Titre
    QLabel* titre  = new QLabel("Selection des noms");
    titre->setStyleSheet("font-size: 60px; font-weight: bold;");
    globalLayout->addStretch();
    globalLayout->addWidget(titre);
    titre->setAlignment(Qt::AlignCenter);

    // Champ de text modulable
    QWidget* zoneChamps = new QWidget();
    layoutChampsSaisies = new QVBoxLayout(zoneChamps);

    globalLayout->addWidget(zoneChamps);

    // Bouton valider
    QPushButton* boutonValider = new QPushButton("VALIDER");
    boutonValider->setStyleSheet("font-size: 20px; padding: 10px; background: red;");
    globalLayout->addWidget(boutonValider);
    globalLayout->addStretch();

    // Recupere les noms et les envois
    connect(boutonValider, &QPushButton::clicked, [this](){
        std::vector<QString> listeNoms;
           for (size_t i = 0; i < noms.size(); ++i) {

               QString texte = noms[i]->text();
               // si pas de nom, donne nom avec index
               if (texte.isEmpty()) texte = "Joueur " + QString::number(i+1);

               listeNoms.push_back(texte);
           }
           emit saisieNoms(listeNoms);
    });
}

void EcranSaisieNoms::setUpChamps(int nbChamps) {
    noms.clear();
    for(int i = 0; i < nbChamps; i++) {
        QLineEdit* champ = new QLineEdit();
        champ->setPlaceholderText("Nom du Joueur " + QString::number(i+1));
        champ->setStyleSheet("background-color: white; color: black; font-size: 18px;");

        layoutChampsSaisies->addWidget(champ);
        noms.push_back(champ);
    }
}

EcanVictoire::EcanVictoire() {
    // Mise en page verticale
    QVBoxLayout* layout = new QVBoxLayout(this);

    // TITRE
    QLabel* titre = new QLabel("VICTOIRE");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("font-size: 60px; font-weight: bold; color : yellow");
    // MESSAGE JOUEUR GAGNANT
    QLabel* vainqueur = new QLabel("Le joueur XXXX a gagné!"); // TODO : rendre interactif
    vainqueur->setAlignment(Qt::AlignCenter);
    vainqueur->setStyleSheet("font-size: 30px; font-weight: bold; color : orange");
    // Bouton start
    QPushButton* StartBouton = new QPushButton("RESTART?");
    StartBouton->setStyleSheet("font-size: 20px; padding: 10px; background: red;");

    // mise en page
    layout->addStretch();
    layout->addWidget(titre);
    layout->addSpacing(50);
    layout->addWidget(vainqueur);
    layout->addSpacing(50);
    layout->addWidget(StartBouton);
    layout->addStretch();

    connect(StartBouton, &QPushButton::clicked, this, &EcanVictoire::startGame);
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
    labelRegleScore = new QLabel("Regle de score: XXXXX");
    labelPierre = new QLabel("Pierres: XXXXX");

    labelNom->setStyleSheet("font-size: 20px;  color: white;");
    labelScore->setStyleSheet("font-size: 20px;  color: white;");
    labelRegleScore->setStyleSheet("font-size: 20px;  color: white;");
    labelPierre->setStyleSheet("font-size: 20px;  color: white;");
    // Mise en page
    layoutInfo->addWidget(labelNom);
    layoutInfo->addStretch();
    layoutInfo->addWidget(labelScore);
    layoutInfo->addStretch();
    layoutInfo->addWidget(labelRegleScore);
    layoutInfo->addStretch();
    layoutInfo->addWidget(labelPierre);


    // ----------------------------------------------------
    //Zone 2: chantier
    zoneChantier = new QWidget();
    zoneChantier->setFixedHeight(250);
    zoneChantier->setStyleSheet("background-color: #b0b0b0;");
    auto* layoutChantier = new QGridLayout(zoneChantier);

    sceneChantier = new QGraphicsScene*[max_tuiles_par_chantier];
    labelsChantier = new QLabel*[max_tuiles_par_chantier];
    for (int i = 0; i < max_tuiles_par_chantier; i++) {
        sceneChantier[i] = new QGraphicsScene(zoneChantier);
        auto* viewSceneChantier = new ChantierQGraphicsView(sceneChantier[i], zoneChantier);
        layoutChantier->addWidget(viewSceneChantier,  0, i);

        labelsChantier[i] = new QLabel(QString::number(i), zoneChantier);
        labelsChantier[i]->setAlignment(Qt::AlignCenter);
        layoutChantier->addWidget(labelsChantier[i],  1, i);

        connect(viewSceneChantier, &ChantierQGraphicsView::onClicked,
                this, [=](){emit selectionTuileFinished(i);});
    }


    // ----------------------------------------------------
    //zone 3: plateau

    QHBoxLayout *layoutMap = new QHBoxLayout();

    QWidget* ScorePlayers = new QWidget();



    sceneMap = new QGraphicsScene();
    vueMap = new CameraMap(sceneMap);
    connect(vueMap, &CameraMap::mouseMoved,
            this, &EcranJeu::onPlateauCameraMapMouseMoved);
    connect(vueMap, &CameraMap::mousePressed,
            this, &EcranJeu::onPlateauCameraMapMousePressed);

    
    layoutMap->addWidget(vueMap);



    // ----------------------------------------------------
    layoutGlobal->addWidget(barreInfo);
    layoutGlobal->addWidget(zoneChantier);
    layoutGlobal->addWidget(vueMap);
}

EcranJeu::~EcranJeu() {
    delete labelNom;
    delete labelScore;
    delete labelRegleScore;
    delete labelPierre;

    delete zoneChantier;

    for (int i = 0; i < max_tuiles_par_chantier; i++) {
        delete sceneChantier[i];
        delete labelsChantier[i];
    }

    delete vueMap;
    delete sceneMap;

    delete selectedTuile;


}

void EcranJeu::onPlateauCameraMapMouseMoved(QPointF mousePos) {
    if (selectedTuile == nullptr) return;
    selectedTuile->setPos(
                constAffichageGraphiqueHex::axialToScreen(
                        constAffichageGraphiqueHex::screenToAxial(mousePos)
                )
            );
}

void EcranJeu::onPlateauCameraMapMousePressed(QPointF mousePos) {
    if (selectedTuile == nullptr) return;
    selectionPlacementFinished(constAffichageGraphiqueHex::screenToAxial(mousePos));
};

void EcranJeu::keyPressEvent(QKeyEvent *event) {
    if (selectedTuile == nullptr) return;

    if (event->key() == Qt::Key::Key_Q) emit tourneSelectedTuile(true);
    else if (event->key() == Qt::Key::Key_D) emit tourneSelectedTuile(false);
    else if (event->key() == Qt::Key::Key_R) emit retour();
}

AffichageGUI *EcranJeu::getAffichageJoueur() {
    return new AffichageGUI(sceneMap, labelNom, labelScore, labelPierre);
}

AffichageGUI **EcranJeu::getAffichagesChantier(size_t tailleChantier) {
    auto result = new AffichageGUI*[tailleChantier];
    for (size_t i = 0; i < tailleChantier; i++)
        result[i] = new AffichageGUI(sceneChantier[i]);
    return result;
}

void EcranJeu::setSelectedTuile(QGraphicsItemGroup *newSelectedTuile) {
    removeSelectedTuile();
    selectedTuile = newSelectedTuile;
    sceneMap->addItem(selectedTuile);
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
    ecranSelectionModeDeJeu = new EcranSelectionModeDeJeu();
    pile->addWidget(ecranSelectionModeDeJeu);
    ecranSelectionNombreJoueurs = new EcranSelectionNombreJoueurs();
    pile->addWidget(ecranSelectionNombreJoueurs);
    ecranSaisieNoms = new EcranSaisieNoms();
    pile->addWidget(ecranSaisieNoms);
    ecranDifficulteArchitechte = new EcranDifficulteArchitechte();
    pile->addWidget(ecranDifficulteArchitechte);
    ecranChoixRegles = new EcranChoixRegles();
    pile->addWidget(ecranChoixRegles);

    ecranJeu = new EcranJeu();
    pile->addWidget(ecranJeu);

    // Pile
    layout->addWidget(pile);
}