#include "Jeu.hpp"

void JeuGUI::gameLoop(int argc, char **argv) {
    app = new QApplication{argc, argv};
    window = new MainWindow();
    window->resize(1200, 800);
    window->show();

    // Lancer le jeu normal
    auto launchGameLoop = [](int argc, char **argv) {return JeuGUI::getJeu()->Jeu::gameLoop(argc, argv);};
    runApp = QThread::create(launchGameLoop, argc, argv);
    runApp->start();

    // Lancer l'application graphique
    QApplication::exec();

    // Une fois que l'application graphique est finie, si l'application n'est pas finie, la forcer à finir
    if (runApp->isRunning()) runApp->terminate();
}

Jeu* JeuGUI::getJeu() {
    if (jeu == nullptr) {
        jeu = new JeuGUI();
    }
    return jeu;
}

void JeuGUI::titleScreen() {
    window->showEcran(window->getEcranTitre());
    //Attendre que le signal startgame soit émis
    QEventLoop SignalWaitLoop;
    auto c1 = QWidget::connect(window->getEcranTitre(), SIGNAL(startGame()), &SignalWaitLoop, SLOT(quit()));
    SignalWaitLoop.exec();

    QWidget::disconnect(c1);
}

bool JeuGUI::selectChargerPartie() {
    window->showEcran(window->getEcranSelectionSauvegarde());

    // Connecter le signal de séléction à une lambda expression qui changera la valeure
    bool resultat = false;
    auto c1 = QObject::connect(window->getEcranSelectionSauvegarde(),
                               &EcranSelectionSauvegarde::selectionFinished,
                               [&](bool chargeSauvegarde){resultat = chargeSauvegarde;});

    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;
    auto c2 = QWidget::connect(window->getEcranSelectionSauvegarde(),
                               SIGNAL(selectionFinished(bool))
            , &SignalWaitLoop, SLOT(quit()));
    SignalWaitLoop.exec();

    QWidget::disconnect(c1);
    QWidget::disconnect(c2);

    // Retourner la réponse de l'utilisateur
    return resultat;
}

void JeuGUI::selectGameMode() {
    window->showEcran(window->getEcranSelectionModeDeJeu());

    // Connecter le signal de séléction à une lambda expression qui changera la valeure
    auto c1 = QObject::connect(window->getEcranSelectionModeDeJeu(),
                               &EcranSelectionModeDeJeu::selectionFinished,
                               [this](GameMode modeDeJeuSelected){modeDeJeu = modeDeJeuSelected;});

    auto cBack = QObject::connect(window->getEcranSelectionModeDeJeu(),
                                  &EcranSelectionModeDeJeu::backRequested,
                                  [&](bool retour){
                                      backPressed = retour;
                                  });

    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;



    auto c2 = QWidget::connect(window->getEcranSelectionModeDeJeu(),
                               SIGNAL(selectionFinished(GameMode)),
                               &SignalWaitLoop, SLOT(quit()));

    auto c3 = QWidget::connect(window->getEcranSelectionModeDeJeu(),
                               SIGNAL(backRequested(bool)),
                               &SignalWaitLoop, SLOT(quit()));



    SignalWaitLoop.exec();
    if (modeDeJeu == GameMode::SOLO) qDebug() << "Mode de jeu: SOLO";
    else qDebug() << "Mode de jeu: MULTIJOUEUR";

    QWidget::disconnect(c1);
    QWidget::disconnect(c2);
    QWidget::disconnect(cBack);
    QWidget::disconnect(c3);
}

void JeuGUI::selectJoueurs() {
    window->showEcran(window->getEcranSelectionNombreJoueurs());
    // Connecter le signal de séléction à une lambda expression qui changera la valeure
    auto c1 = QObject::connect(window->getEcranSelectionNombreJoueurs(),
                               &EcranSelectionNombreJoueurs::selectionFinished,
                               [this](int nb){
                                   this ->nombreJoueurs = nb;
                               });

    auto cBack = QObject::connect(window->getEcranSelectionNombreJoueurs(),
                                  &EcranSelectionNombreJoueurs::backRequested,
                                  [&](bool retour){
                                      backPressed = retour;
                                  });

    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;
    auto c2 = QWidget::connect(window->getEcranSelectionNombreJoueurs(),
                               SIGNAL(selectionFinished(int)),
                               &SignalWaitLoop, SLOT(quit()));

    auto c3 = QWidget::connect(window->getEcranSelectionNombreJoueurs(),
                               SIGNAL(backRequested(bool)),
                               &SignalWaitLoop, SLOT(quit()));
    SignalWaitLoop.exec();
    qDebug() << "Partie comptant " << nombreJoueurs << "joueurs.";
    // Innitialise les nouveaux joueurs
    for (int i = 0; i < nombreJoueurs; i++) joueurs[i] = new JoueurSimple();
    QWidget::disconnect(c1);
    QWidget::disconnect(c2);
    QWidget::disconnect(cBack);
    QWidget::disconnect(c3);
}

void JeuGUI::selectReglesScore() {
    window->showEcran(window->getEcranChoixRegles());
    // Connecter le signal de séléction à une lambda expression qui changera la valeure
    bool varianteCouleurs[GameConstants::scoreAmounts];
    auto c1 = QObject::connect(window->getEcranChoixRegles(),
                               &EcranChoixRegles::selectionFinished,
                               [&](const bool avecVariante[GameConstants::scoreAmounts]){
                                   for (size_t i = 0; i < GameConstants::scoreAmounts; i++) varianteCouleurs[i] = avecVariante[i];
                               });
    auto cBack = QObject::connect(window->getEcranChoixRegles(),
                                  &EcranChoixRegles::backRequested,
                                  [&](bool retour){
                                      backPressed = retour;
                                  });

    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;
    auto c2 = QWidget::connect(window->getEcranChoixRegles(),
                               SIGNAL(selectionFinished(bool)),
                               &SignalWaitLoop, SLOT(quit()));
    auto c3 = QWidget::connect(window->getEcranChoixRegles(),
                               SIGNAL(backRequested(bool)),
                               &SignalWaitLoop, SLOT(quit()));

    SignalWaitLoop.exec();

    Score* score = getScore(varianteCouleurs);

    if (modeDeJeu == GameMode::MULTIJOUEUR) {
        for (size_t i = 0; i < nombreJoueurs; i++)
            dynamic_cast<JoueurSimple*>(joueurs[i])->set_score(score);
    }
    else {
        dynamic_cast<JoueurSimple*>(joueurs[0])->set_score(score);
    }

    QWidget::disconnect(c1);
    QWidget::disconnect(cBack);
    QWidget::disconnect(c2);
    QWidget::disconnect(c3);
}

Difficulte JeuGUI::selectNiveauIllustreArchitechte() {
    Difficulte resultat = Difficulte::FACILE;
    window->showEcran(window->getEcranDifficulteArchitechte());
    // Connecter le signal de séléction à une lambda expression qui changera la valeure
    auto c1 = QObject::connect(window->getEcranDifficulteArchitechte(),
                               &EcranDifficulteArchitechte::selectionFinished,
                               [&](Difficulte difficulte){resultat = difficulte;});

    auto cBack = QObject::connect(window->getEcranDifficulteArchitechte(),
                                  &EcranDifficulteArchitechte::backRequested,
                                  [&](bool retour){
                                      backPressed = retour;
                                  });
    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;
    auto c2 = QWidget::connect(window->getEcranDifficulteArchitechte(),
                               SIGNAL(selectionFinished(Difficulte)),
                               &SignalWaitLoop, SLOT(quit()));

    auto c3 = QWidget::connect(window->getEcranDifficulteArchitechte(),
                               SIGNAL(backRequested(bool)),
                               &SignalWaitLoop, SLOT(quit()));
    SignalWaitLoop.exec();

    QWidget::disconnect(c1);
    QWidget::disconnect(c2);
    QWidget::disconnect(cBack);
    QWidget::disconnect(c3);

    return resultat;
}

void JeuGUI::selectNomsJoueurs() {
    int nombreChampsText;
    if (modeDeJeu == GameMode::SOLO) nombreChampsText = 1;
    else nombreChampsText = nombreJoueurs;

    // Mise à jour graphique de la page de saisie de nom, On utilise invokeMethod pour basculer sur le thread graphique le temps de la configuration
    QMetaObject::invokeMethod(qApp, [=]() {
        window->getEcranSaisieNoms()->setUpChamps(nombreChampsText);
        window->showEcran(window->getEcranSaisieNoms());
    }, Qt::BlockingQueuedConnection);
    window->showEcran(window->getEcranSaisieNoms());

    std::vector<QString> newNames;

    auto c1 = QObject::connect(window->getEcranSaisieNoms(),
                               &EcranSaisieNoms::saisieNoms,
                               [&](std::vector<QString> liste){newNames = liste; });

    auto cBack = QObject::connect(window->getEcranSaisieNoms(),
                                  &EcranSaisieNoms::backRequested,
                                  [&](bool retour){
                                      backPressed = retour;
                                  });

    QEventLoop SignalWaitLoop;
    auto c2 = QWidget::connect(window->getEcranSaisieNoms(),
                               SIGNAL(saisieNoms(std::vector<QString>)),
                               &SignalWaitLoop, SLOT(quit()));

    auto c3 = QWidget::connect(window->getEcranSaisieNoms(),
                               SIGNAL(backRequested(bool)),
                               &SignalWaitLoop, SLOT(quit()));


    SignalWaitLoop.exec();

    // Donne leurs noms à chaque joueurs
    for(size_t i = 0; i < newNames.size(); i++) {
        if(joueurs[i]) {
            if (auto player = dynamic_cast<JoueurSimple*>(joueurs[i])) {
                player->setNomJoueur(newNames[i].toStdString());
            }
        }
    }

    QObject::disconnect(c1);
    QObject::disconnect(cBack);
    QObject::disconnect(c2);
    QObject::disconnect(c3);
}

VITESSE JeuGUI::selectVitessePartie() {
    window->showEcran(window->getEcranVitessePartie());
    VITESSE v = VITESSE::NORMALE;

    // Connecter le signal de séléction à une lambda expression qui changera la valeure
    auto c1 = QObject::connect(window->getEcranVitessePartie(),
                               &EcranVitessePartie::selectionFinished,
                               [&](VITESSE vitesse){v = vitesse;});

    auto cBack = QObject::connect(window->getEcranVitessePartie(),
                                  &EcranVitessePartie::backRequested,
                                  [&](bool retour){
                                      backPressed = retour;
                                  });

    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;

    auto c2 = QWidget::connect(window->getEcranVitessePartie(),
                               SIGNAL(selectionFinished(VITESSE)),
                               &SignalWaitLoop, SLOT(quit()));

    auto c3 = QWidget::connect(window->getEcranVitessePartie(),
                               SIGNAL(backRequested(bool)),
                               &SignalWaitLoop, SLOT(quit()));

    SignalWaitLoop.exec();

    QWidget::disconnect(c1);
    QObject::disconnect(cBack);
    QWidget::disconnect(c2);
    QObject::disconnect(c3);

    return v;
}

void JeuGUI::afficheSceneJeu() {
    // Actualiser le plateau de jeu
    QMetaObject::invokeMethod(qApp, [=]() {
        window->getEcranJeu()->setUpWidgets(nombreJoueurs);
    }, Qt::QueuedConnection);

    // Attendre que l'écran de jeu soit prêt
    QEventLoop SignalWaitLoop;
    auto c2 = QWidget::connect(window->getEcranJeu(),
                               SIGNAL(ready()),
                               &SignalWaitLoop, SLOT(quit()));
    SignalWaitLoop.exec();

    window->showEcran(window->getEcranJeu());
    affichageJoueur = window->getEcranJeu()->getAffichageJoueur();
    affichageChantier = window->getEcranJeu()->getAffichagesChantier();
    affichageJoueursAdverses = window->getEcranJeu()->getAffichagesJoueursAdverses();
}

int JeuGUI::selectTuile(size_t joueur) {
    // Dessiner le plateau des joueurs et le chantier
    QMetaObject::invokeMethod(qApp, [=]() {
        // Joueur principal
        affichageJoueur->Affichage::affiche_joueur(*joueurs[joueur]);

        // Joueurs adverses
        for (size_t i = 0; i < nombreJoueurs; i++)
            if (i != joueur)
                affichageJoueursAdverses[i - (i > joueur)]->Affichage::affiche_joueur(*joueurs[i]);

        // Chantier
        size_t i = 0;
        for (auto tuile : chantier)
            affichageChantier[i++]->Affichage::affiche_container(*tuile);

        for (i; i < chantier.get_taille(); i++)
            affichageChantier[i++]->clearAffichage();

    }, Qt::QueuedConnection);

    QString text = "Tour " + QString::number(nombreTours) + "/" + QString::number(maxNombreTours);
    window->getEcranJeu()->getLabelTour()->setText(text);

    QString textControles = "Séléctionnez une tuile dans le chantier en cliquant dessus !";
    window->getEcranJeu()->getLabelRegles()->setText(textControles);

    int resultat = -1;
    auto c1 = QObject::connect(window->getEcranJeu(),
                               &EcranJeu::selectionTuileFinished,
                               [&](int tuileSelectionne){resultat = tuileSelectionne;});

    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;
    auto c2 = QWidget::connect(window->getEcranJeu(),
                               SIGNAL(selectionTuileFinished(int)),
                               &SignalWaitLoop, SLOT(quit()));

    do {
        SignalWaitLoop.exec();
    } while (resultat > joueurs[joueur]->get_pierre());

    QWidget::disconnect(c1);
    QWidget::disconnect(c2);

    return resultat;
}

void JeuGUI::tourneTuile(Tuile* tuile, bool sensHoraire) {
    tuile->tourne(sensHoraire);
    QPointF prevPos = window->getEcranJeu()->getSelectedTuilePosition();
    QMetaObject::invokeMethod(qApp, [=]() {
        auto newSelectedTuile = affichageJoueur->getContainerGraphicsItem(*tuile);
        newSelectedTuile->setPos(prevPos);
        window->getEcranJeu()->setSelectedTuile(newSelectedTuile);
    }, Qt::QueuedConnection);
}

bool JeuGUI::placeTuile(size_t joueur, Tuile* tuileSelected) {
    QMetaObject::invokeMethod(qApp, [=]() {
        window->getEcranJeu()->setSelectedTuile(affichageJoueur->getContainerGraphicsItem(*tuileSelected));
    }, Qt::QueuedConnection);

    QString textControles = "Placez la tuile en cliquant sur un emplacement valide.\n\nContrôles:\nQ : tourner la tuile d'un cran sur la gauche\nD : tourner la tuile d'un cran sur la droite\nR : revenir à la séléction de tuiles";
    window->getEcranJeu()->getLabelRegles()->setText(textControles);


    QEventLoop SignalWaitLoop;
    auto c1 = QWidget::connect(window->getEcranJeu(),
                               SIGNAL(selectionPlacementFinished(Vector2)),
                               &SignalWaitLoop, SLOT(quit()));


    Vector2 position;
    auto c2 = QWidget::connect(window->getEcranJeu(),
                               &EcranJeu::selectionPlacementFinished,
                               [&](Vector2 nouvellePosition){position = nouvellePosition;});

    // Fonctionalité de tourner les tuiles
    auto c3 = QWidget::connect(window->getEcranJeu(),
                               &EcranJeu::tourneSelectedTuile,
                               [&](bool sensHoraire){ tourneTuile(tuileSelected, sensHoraire);});

    // Fonctionalité de revenir en arrière
    bool forceQuit = false;
    auto c4 = QWidget::connect(window->getEcranJeu(),
                               &EcranJeu::retour,
                               [&](){ forceQuit = true;});
    auto c5 = QWidget::connect(window->getEcranJeu(),
                               SIGNAL(retour()),
                               &SignalWaitLoop, SLOT(quit()));

    do {
        SignalWaitLoop.exec();
    } while (!joueurs[joueur]->get_plateau().peut_placer(*tuileSelected, position) && !forceQuit);

    QMetaObject::invokeMethod(qApp, [=]() {
        window->getEcranJeu()->removeSelectedTuile();
    }, Qt::QueuedConnection);
    if (!forceQuit) joueurs[joueur]->place_tuile(tuileSelected, position);

    QWidget::disconnect(c1);
    QWidget::disconnect(c2);
    QWidget::disconnect(c3);
    QWidget::disconnect(c4);
    QWidget::disconnect(c5);

    return !forceQuit;
}

void JeuGUI::finDePartie(multimap<int, string> scores) {
    QMetaObject::invokeMethod(qApp, [=]() {
        window->getEcranVictoire()->setUpWidgets(scores);
    }, Qt::QueuedConnection);
    window->showEcran(window->getEcranVictoire());
}

JeuGUI::~JeuGUI() {
    delete app;
    delete window;
    delete runApp;

    delete affichageJoueur;
    for (size_t i = 0; i < nombreJoueurs + 1; i++) delete affichageChantier[i];
    delete[] affichageChantier;
    for (size_t i = 0; i < nombreJoueurs - 1; i++) delete affichageJoueursAdverses[i];
    delete[] affichageJoueursAdverses;
}