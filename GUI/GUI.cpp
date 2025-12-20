#include "GUI.hpp"

#include "../Affichage/Affichage.hpp"

// Hexagones //

HexagoneGUIObjet::HexagoneGUIObjet(const CouleursAkropolis couleur, const std::string& description, const int height,
                                   const bool doOutline[GameConstants::HEXAGON_DIRECTIONS]) :
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

ChantierQGraphicsView::ChantierQGraphicsView(QGraphicsScene *s, QWidget *p)
    : QGraphicsView(s,p) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

// QT - ECRANS //

// ABSTRACT ECRAN

AbstractEcran::AbstractEcran(QWidget* parent) : QWidget(parent) {
    // On initialise le layout  pour que tous les enfants l'aient
    mainLayout = new QVBoxLayout(this);
}

void AbstractEcran::ecranBasics(const QString& titreText, bool avecBoutonRetour) {

    // Integration du bouton retour :
    if (avecBoutonRetour) {
        QPushButton* backButton = new QPushButton();
        backButton->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
        backButton->setFixedSize(32, 32);
        mainLayout->addWidget(backButton);
        connect(backButton, &QPushButton::clicked, this, [this](){ emit backRequested(true); });
    }
    mainLayout->addStretch();
    // Ajout du titre menu :
    //mainLayout->addStretch();
    QLabel* titre = new QLabel(titreText);
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("font-size: 60px; font-weight: bold;");
    mainLayout->addWidget(titre);
    mainLayout->addSpacing(30);
}

template <typename T, typename ClassFille> void AbstractEcran::setupBoutons(T &data, ClassFille* fille) {
    // Creations des boutons:
    for (const auto& option : data) {

        QPushButton* btn = new QPushButton(option.btnTexte);
        QString style = QString("font-size: 20px; padding: 10px; background: %1; color: white;").arg(option.couleur);
        btn->setStyleSheet(style);


        mainLayout->addWidget(btn);

        // Connexion du signal :
        connect(btn, &QPushButton::clicked, fille, [fille, option]() {
            emit fille->selectionFinished(option.signalData);
        });
    }
    mainLayout->addStretch();
}


EcranSelectionSauvegarde::EcranSelectionSauvegarde() {
    // On met en place la base de l'ecran (titre & fleche retour):
    ecranBasics("AKROPOLIS", false);
    // recupere les informations relatif a l'ecran :
    auto options = MenuData::getSeletionSauvegarde();
    // Creation de tout les boutons :
    AbstractEcran::setupBoutons(options,this);
}

EcranSelectionModeDeJeu::EcranSelectionModeDeJeu() {
    ecranBasics("SELECTION MODE DE JEU", true);
    AbstractEcran::setupBoutons( MenuData::getModesDeJeu(),this);
}
EcranSelectionNombreJoueurs::EcranSelectionNombreJoueurs() {
    ecranBasics("COMBIEN DE JOUEURS?", true);
    AbstractEcran::setupBoutons(MenuData::getNbJoueurs(),this);
}
EcranDifficulteArchitechte::EcranDifficulteArchitechte() {
    ecranBasics("DIFFICULTE ILLUSTRE ARCHITECHTE", true);
    AbstractEcran::setupBoutons(MenuData::getDifficultes(),this);
}
EcranVitessePartie::EcranVitessePartie() {
    ecranBasics("SELECTION VITESSE PARTIE", true);
    AbstractEcran::setupBoutons(MenuData::getNbTours(),this);
}

// AUTRES ECRANS

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

EcranChoixRegles::EcranChoixRegles() {
    // TODO: CHECKBOX DES REGLES
    QBoxLayout* layout = new QVBoxLayout(this);
    QLabel* titre  = new QLabel("CHOIX DES REGLES");
    titre->setStyleSheet("font-size: 60px; font-weight: bold;");
    QLabel* text  = new QLabel("Selectionnez les regles variante à appliquer...");
    text->setStyleSheet("font-size: 20px; font-weight: bold;");
    layout->addStretch();
    layout->addWidget(titre);
    titre->setAlignment(Qt::AlignCenter);

    QHBoxLayout* BouttonLayout = new QHBoxLayout(this);

    QPushButton* facile = new QPushButton("CLASSIQUE");
    QPushButton* normale = new QPushButton("VARIANTE");

    facile->setStyleSheet("font-size: 20px; padding: 10px; background: green;");
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

// Ecran saisie de noms

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

// Ecran de jeu

EcranJeu::EcranJeu() {
    // Layout Principal (Vertical)
    auto* layoutGlobal = new QVBoxLayout(this);
    layoutGlobal->setContentsMargins(0,0,0,0);
    layoutGlobal->setSpacing(0);

    // Zone 1: barre d'infos
    auto* barreInfo = new QWidget();
    barreInfo->setFixedHeight(50);
    barreInfo->setStyleSheet("background-color: #333; color: white;");

    auto* layoutInfo = new QHBoxLayout(barreInfo);

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
    zoneChantier->setFixedHeight(200);
    zoneChantier->setStyleSheet(constGUI::chantierStyleSheet);

    // ----------------------------------------------------
    //zone 3: plateau
    plateau = new QWidget();
    infoJoueurs = new QWidget();

    sceneMap = new QGraphicsScene();
    vueMap = new CameraMap(sceneMap);
    connect(vueMap, &CameraMap::mouseMoved,
            this, &EcranJeu::onPlateauCameraMapMouseMoved);
    connect(vueMap, &CameraMap::mousePressed,
            this, &EcranJeu::onPlateauCameraMapMousePressed);

    labelRegles = new QLabel("VOICI LES REGLES ET LES CONTROLES\n blabla\n blabla");

    auto* layoutMap = new QHBoxLayout(plateau);

    layoutMap->addWidget(infoJoueurs, 1);
    layoutMap->addWidget(vueMap, 6);
    layoutMap->addWidget(labelRegles, 1);

    // ----------------------------------------------------
    layoutGlobal->addWidget(barreInfo);
    layoutGlobal->addWidget(zoneChantier);
    layoutGlobal->addWidget(plateau);
}

EcranJeu::~EcranJeu() {
    delete labelNom;
    delete labelScore;
    delete labelRegleScore;
    delete labelPierre;

    delete zoneChantier;

    for (int i = 0; i < nombreJoueurs+1; i++) {
        delete sceneChantier[i];
        delete labelsChantier[i];
    }
    delete sceneChantier;
    delete labelsChantier;

    for (int i = 0; i < nombreJoueurs-1; i++) {
        delete labelNomJoueurs[i];
        delete labelScoreJoueurs[i];
        delete labelPierreJoueurs[i];
        delete sceneMapJoueurs[i];
    }
    delete labelNomJoueurs;
    delete labelScoreJoueurs;
    delete labelPierreJoueurs;
    delete sceneMapJoueurs;

    delete vueMap;
    delete sceneMap;
    delete infoJoueurs;

    delete selectedTuile;

    delete labelRegles;
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

AffichageGUI **EcranJeu::getAffichagesChantier() {
    auto result = new AffichageGUI*[nombreJoueurs+1];
    for (size_t i = 0; i < nombreJoueurs+1; i++)
        result[i] = new AffichageGUI(sceneChantier[i]);
    return result;
}

AffichageGUI **EcranJeu::getAffichagesJoueursAdverses() {
    auto result = new AffichageGUI*[nombreJoueurs-1];
    for (size_t i = 0; i < nombreJoueurs-1; i++)
        result[i] = new AffichageGUI(sceneMapJoueurs[i], labelNomJoueurs[i], labelScoreJoueurs[i], labelPierreJoueurs[i]);
    return result;
}

void EcranJeu::setUpWidgets(size_t playerCount) {
    nombreJoueurs = playerCount;

    //Setup chantier
    auto* layoutChantier = new QGridLayout(zoneChantier);
    sceneChantier = new QGraphicsScene*[nombreJoueurs+1];
    labelsChantier = new QLabel*[nombreJoueurs+1];
    for (int i = 0; i < nombreJoueurs+1; i++) {
        sceneChantier[i] = new QGraphicsScene(zoneChantier);
        auto* viewSceneChantier = new ChantierQGraphicsView(sceneChantier[i], zoneChantier);
        layoutChantier->addWidget(viewSceneChantier,  0, i);

        labelsChantier[i] = new QLabel(QString::number(i), zoneChantier);
        labelsChantier[i]->setAlignment(Qt::AlignCenter);
        layoutChantier->addWidget(labelsChantier[i],  1, i);

        connect(viewSceneChantier, &ChantierQGraphicsView::onClicked,
                this, [=](){emit selectionTuileFinished(i);});
        // Faire en sorte que le chantier soit toujours à la bonne taille
        connect(sceneChantier[i], &QGraphicsScene::sceneRectChanged,
                viewSceneChantier,
                [viewSceneChantier](){
                        viewSceneChantier->fitInView(viewSceneChantier->sceneRect(),
                                                     Qt::KeepAspectRatio);
                    }
        );
    }

    //Setup preview autres joueurs
    auto* layoutPlayers = new QGridLayout(infoJoueurs);
    labelNomJoueurs = new QLabel*[nombreJoueurs-1];
    labelScoreJoueurs = new QLabel*[nombreJoueurs-1];
    labelPierreJoueurs = new QLabel*[nombreJoueurs-1];
    sceneMapJoueurs = new QGraphicsScene*[nombreJoueurs-1];
    for (int i = 0; i < nombreJoueurs-1; i++) {
        labelNomJoueurs[i] = new QLabel();
        labelScoreJoueurs[i] = new QLabel();
        labelPierreJoueurs[i] = new QLabel();
        sceneMapJoueurs[i] = new QGraphicsScene();
        auto vueMapJoueur = new CameraMap(sceneMapJoueurs[i]);

        labelNomJoueurs[i]->setAlignment(Qt::AlignCenter);
        labelScoreJoueurs[i]->setAlignment(Qt::AlignCenter);
        labelPierreJoueurs[i]->setAlignment(Qt::AlignCenter);

        layoutPlayers->addWidget(labelNomJoueurs[i],  2*i, 0);
        layoutPlayers->addWidget(labelScoreJoueurs[i],  2*i, 1);
        layoutPlayers->addWidget(labelPierreJoueurs[i],  2*i, 2);
        layoutPlayers->addWidget(vueMapJoueur,  2*i+1, 0, 1, 3);
    }

    emit ready();
}

void EcranJeu::setSelectedTuile(QGraphicsItemGroup *newSelectedTuile) {
    removeSelectedTuile();
    selectedTuile = newSelectedTuile;
    sceneMap->addItem(selectedTuile);
}

EcranVictoire::EcranVictoire() {
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

    connect(StartBouton, &QPushButton::clicked, this, &EcranVictoire::startGame);
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

    victoire = new EcranVictoire();
    pile->addWidget(victoire);

    // Pile
    layout->addWidget(pile);
    
}