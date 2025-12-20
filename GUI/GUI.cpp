#include "GUI.hpp"

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
    QLabel* texte  = new QLabel("CHOIX DES VARIANTES DE SCORE");
    texte->setStyleSheet("font-size: 60px; font-weight: bold;");
    layout->addStretch();
    layout->addWidget(texte);
    texte->setAlignment(Qt::AlignCenter);

    auto* boutonLayout = new QGridLayout(this);

    for (size_t i = 0; i < GameConstants::scoreAmounts; i++) {

        auto* label = new QLabel(QString::fromStdString(GameConstants::nomScoresInOrder[i]));
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-size: 25px; color: " + constGUI::akropolisToQTColors[i+1].name() + ";");
        boutonLayout->addWidget(label, 0, i);

        boutons[i] = new QPushButton("NORMAL");
        boutons[i]->setStyleSheet("font-size: 15px; padding: 15px; background: green;");
        boutons[i]->setCheckable(true);
        boutons[i]->setChecked(false);
        connect(boutons[i], &QPushButton::clicked,
                [b = boutons[i]](bool checked) {
            if (checked) {
                b->setStyleSheet("font-size: 15px; padding: 15px; background: orange;");
                b->setText("VARIANTE");
            }
            else {
                b->setStyleSheet("font-size: 15px; padding: 15px; background: green;");
                b->setText("NORMAL");
            }
        });
        boutonLayout->addWidget(boutons[i], 1, i);
    }

    layout->addStretch();
    auto boutonValider = new QPushButton("VALIDER");
    boutonValider->setStyleSheet("font-size: 20px; padding: 20px; background: red;");
    boutonLayout->addWidget(boutonValider, 3, 0, 1, GameConstants::scoreAmounts);

    layout->addLayout(boutonLayout);
    layout->addStretch();

    connect(boutonValider, &QPushButton::clicked,
            this,
            [this](){
                    bool varianteCouleurs[GameConstants::scoreAmounts];
                    for (size_t i = 0; i < GameConstants::scoreAmounts; i++)
                        varianteCouleurs[i] = boutons[i]->isChecked();
                    emit selectionFinished(varianteCouleurs);
            });
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

EcranVictoire::EcranVictoire() {
    // Mise en page verticale
    layout = new QVBoxLayout(this);

    // TITRE
    QLabel* titre = new QLabel("VICTOIRE");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("font-size: 60px; font-weight: bold; color : yellow");

    // mise en page
    layout->addStretch();
    layout->addWidget(titre);
    layout->addSpacing(50);
}

void EcranVictoire::setUpWidgets(std::multimap<int, std::string> scores) {

    size_t i = 0;
    for (auto scoreIterator = scores.rbegin(); scoreIterator != scores.rend(); scoreIterator++) {
        i++;
        QString placeSuffixe = i == 1 ? "er" : "ème";
        QString text = QString::number(i) + placeSuffixe + ": " + QString::fromStdString(scoreIterator->second)
                + " avec " + QString::number(scoreIterator->first) + " points";
        QString color;
        switch (i) {
            case 1: color = "gold"; break;
            case 2: color = "silver"; break;
            case 3: color = "bronze"; break;
            default: color = "white"; break;
        }

        QLabel* resultat = new QLabel(text);
        resultat->setAlignment(Qt::AlignCenter);
        resultat->setStyleSheet("font-size: 30px; font-weight: bold; color : " + color + ";");
        layout->addWidget(resultat);
        layout->addSpacing(50);
    }
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
    ecranVitessePartie = new EcranVitessePartie();
    pile->addWidget(ecranVitessePartie);

    ecranJeu = new EcranJeu();
    pile->addWidget(ecranJeu);

    victoire = new EcranVictoire();
    pile->addWidget(victoire);

    // Pile
    layout->addWidget(pile);
    
}