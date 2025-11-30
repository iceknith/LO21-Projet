
#include "GUI.hpp"
#include "../Utils.hpp"

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



    // ---------------------------------------------------------
    // <!> exemple hardcoder <!>

    Tuile* t1 = new TuileJeuConcrete();
    Tuile* t2 = new TuileJeuConcrete();
    Tuile* t3 = new TuileJeuConcrete();
    TuileGUI* item1 = new TuileGUI(t1);
    TuileGUI* item2 = new TuileGUI(t2);
    TuileGUI* item3 = new TuileGUI(t3);

    item1->setPos(-300, 0);
    item2->setPos(0, 0);
    item3->setPos(300, 0);

    sceneChantier->addItem(item1);
    sceneChantier->addItem(item2);
    sceneChantier->addItem(item3);
    // ---------------------------------------------------------



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

    layoutStats->addWidget(new QLabel("Pierres: XXX"));
    layoutStats->addWidget(new QLabel("Score Totale: XXX"));
    layoutStats->addWidget(new QLabel("Score rouge = XXX"));
    layoutStats->addWidget(new QLabel("Score bleu = XXX"));
    layoutStats->addWidget(new QLabel("Score jaune = XXX"));
    layoutStats->addWidget(new QLabel("Score violet = XXX"));
    layoutStats->addWidget(new QLabel("Score vert = XXX"));
    layoutStats->addStretch(); // Pousse les boutons vers le bas
    layoutStats->addWidget(new QPushButton("Passer le tour"));
    layoutStats->addWidget(new QPushButton("Quitter"));


    // Affichage map hexagonale
    scenePlateau = new QGraphicsView();
    scenePlateau ->setScene(new QGraphicsScene());
    scenePlateau ->setStyleSheet("background: black;");



    layoutBas ->addWidget(panneauStats,2);
    layoutBas ->addWidget(scenePlateau,8);
    layoutPrincipal->addWidget(zoneBas, 4);
}

// VUE HEXAGONE

// <!> Recherche & Développement <!>

const int HEX_SIZE = 100;

TuileGUI::TuileGUI(Tuile* tuile){
    this->tuile = tuile;

    Hexagone** enfants = this->tuile->get_enfants();
    Vector2* positions = this->tuile->get_positions_enfants();
    int nombre = this->tuile->get_nombre_enfant();

    for (int i = 0; i < nombre; i++) {

        Hexagone* hex = enfants[i];
        Vector2 postion = positions[i];

        std::string ImagePath = getHexImage(hex);
        QPixmap image(QString::fromStdString(ImagePath));

        image = image.scaled(HEX_SIZE, HEX_SIZE);

        QGraphicsPixmapItem* pixamItem = new QGraphicsPixmapItem(image);

        Vector2 posEcran = axialToPixel(postion);

        float x = posEcran.x - (HEX_SIZE / 2);
        float y = posEcran.y - (HEX_SIZE / 2);
        pixamItem->setPos(x, y);

        this->addToGroup(pixamItem);
    }
}

std::string TuileGUI::getHexImage(Hexagone* hex) {
    // TODO Logique pour trouver l'image
    if (hex->get_type()==TypeHexagone::Carriere)return ":/Ressources/hexagone_vide.png";
    else if (hex->get_type()==TypeHexagone::Place)return ":/Ressources/place.png";
    else return ":/Ressources/hexagone_bleu.png";
}


Vector2 TuileGUI::axialToPixel(Vector2 v) {
    float posX = (v.x * HEX_SIZE * 0.75);
    float posY = (v.y * HEX_SIZE) + (v.x * HEX_SIZE * 0.5);

    return Vector2(posX, posY);
}



