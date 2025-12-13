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



