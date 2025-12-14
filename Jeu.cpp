#include "Jeu.hpp"
#include "Serialization/Serialization.hpp"

// Jeu //

Jeu* Jeu::jeu = nullptr;

void Jeu::gameLoop(int argc, char *argv[]) {
    titleScreen();

    // Si on charge une partie existante
    QFileInfo saveFileInfo{constJeu::saveFilePath};
    if (saveFileInfo.exists() && saveFileInfo.isFile() && selectChargerPartie()) chargerPartie();
    // Sinon, on fait la configuration de la partie
    else {
        selectGameMode();
        if (modeDeJeu == GameMode::MULTIJOUEUR){
            selectJoueurs();
            srand(time(NULL));
            premierJoueur = rand()%nombreJoueurs;
        }
            // Le joueur 0 sera arbitrairement l'utilisateur et le joueur 1 sera l'illustre architecte.
        else {
            nombreJoueurs = 2;
            joueurs[0] = new JoueurSimple();
            joueurs[1] = new IllustreArchitecte(selectNiveauIllustreArchitechte());
            premierJoueur = 0;
        }
        selectNomsJoueurs();
        joueurActuel = premierJoueur;

        initialisePlateau();

        // Initialisation de la règle de score
        selectReglesScore();

        // Initialisation du nombre de pierres
        for (size_t i = 0; i<nombreJoueurs; i++) {
            joueurs[(joueurActuel+i)%nombreJoueurs]->set_pierre(i+1);
        }
        deck.setNombreJoueurs(modeDeJeu == GameMode::SOLO ? 1 : nombreJoueurs);
        chantier.set_nombre_joueurs(nombreJoueurs);

        nombreTours = 1;
        maxNombreTours = deck.get_taille() / (chantier.get_taille() - 1);

        int diff = chantier.get_taille()-chantier.get_nombre_tuiles();

        if (diff > 0 && deck.get_nombre_tuiles() >= diff) {
            chantier.ajouter_tuile(deck.tirer_tuiles(diff), diff);
        }
    }

    while (chantier.get_nombre_tuiles() > 1) {
        sauvegarderPartie();
        // Joueur manuel
        if (!joueurs[joueurActuel]->get_joue_tout_seul())
        {
            bool placementConfirme = false;
            while (!placementConfirme) {
                int tuileIndx = selectTuile(joueurActuel);

                // Si on as décidé de quitter le jeu
                if (tuileIndx == -1) return;

                // Prendre la tuile séléctionné
                Tuile* tuileSelected = chantier.get_tuile(tuileIndx);
                placementConfirme = placeTuile(joueurActuel, tuileSelected);
                joueurs[joueurActuel]->ajouter_pierre(-tuileIndx);

                // Si le placement est confirmé, enlever la tuile du chantier
                if (placementConfirme) {
                    chantier.prendre_tuile(tuileIndx);
                }
                // Si le placement est annulé, rajouter le nombre de pierres qu'on as eneve au joueur
                else {
                    joueurs[joueurActuel]->ajouter_pierre(tuileIndx);
                }
            }
        }

        // Illustre architechte
        else {
            joueurs[joueurActuel]->jouer(chantier);
            afficheTourAutomatique(joueurActuel);
        }
        //___________
        joueurActuel = (joueurActuel + 1)%nombreJoueurs;
        nombreTours += joueurActuel == premierJoueur;

        if (joueurActuel == premierJoueur) {
            int diff = chantier.get_taille()-chantier.get_nombre_tuiles();

            if (diff > 0 && deck.get_nombre_tuiles() >= diff) {
                chantier.ajouter_tuile(deck.tirer_tuiles(diff), diff);
            }
        }
    }

    finDePartie(calculerScores());
}

void Jeu::initialisePlateau() {
    Vector2 positionNulle{0,0};
    for (size_t i = 0; i < nombreJoueurs; i++) {
        joueurs[i]->place_tuile(tuileDepart, positionNulle, true);
    }
}

multimap<int, size_t> Jeu::calculerScores() {
    multimap<int, size_t> scores{};
    for (size_t i = 0; i < nombreJoueurs; i++) scores.insert(make_pair(joueurs[i]->get_score(), i));
    return scores;
}

Jeu::~Jeu() {
    delete tuileDepart;
    delete affichage;
}

void Jeu::serialize(QVariantMap &data, SerializationContext *context) const {
    data["modeDeJeu"] = static_cast<int>(modeDeJeu);
    data["nombreTours"] = static_cast<qsizetype>(nombreTours);
    data["maxNombreTours"] = static_cast<qsizetype>(maxNombreTours);
    data["nombreJoueurs"] = static_cast<qsizetype>(nombreJoueurs);
    data["joueurActuel"] = static_cast<qsizetype>(joueurActuel);
    data["premierJoueur"] = static_cast<qsizetype>(premierJoueur);

    // On commence par le deck, vu que c'est lui qui est responsable de toutes les tuilesJeu
    QVariantMap deckData;
    deck.serialize(deckData, context);
    data["deck"] = deckData;

    // Ensuite, en deuxième, on sérialize la tuile de départ
    data["tuileDepart"] = context->serialize(tuileDepart);

    // Finalement, on peut faire les autres dans l'ordre qu'on veut
    for (size_t i = 0; i < nombreJoueurs; i++)
        data[QString::number(i)] = context->serialize(joueurs[i]);

    QVariantMap chantierData;
    chantier.serialize(chantierData, context);
    data["chantier"] = chantierData;
}

void Jeu::deserialize(const QVariantMap &data, SerializationContext *context) {
    // Supprimer les joueurs précédents
    for (size_t i = 0; i < nombreJoueurs; i++) delete joueurs[i];

    modeDeJeu = static_cast<GameMode>(data["modeDeJeu"].value<int>());
    nombreTours = static_cast<size_t>(data["nombreTours"].value<qsizetype>());
    maxNombreTours = static_cast<size_t>(data["maxNombreTours"].value<qsizetype>());
    nombreJoueurs = static_cast<size_t>(data["nombreJoueurs"].value<qsizetype>());
    joueurActuel = static_cast<size_t>(data["joueurActuel"].value<qsizetype>());
    premierJoueur = static_cast<size_t>(data["premierJoueur"].value<qsizetype>());

    // On commence par le deck, vu que c'est lui qui est responsable de toutes les tuilesJeu
    deck.deserialize(data["deck"].value<QVariantMap>(), context);

    // Ensuite, en deuxième, on sérialize la tuile de départ
    delete tuileDepart;
    tuileDepart = dynamic_cast<TuileDepart*>(context->deserialize(data["tuileDepart"]));

    // Finalement, on peut faire les autres dans l'ordre qu'on veut
    for (auto joueur : joueurs) delete joueur;
    for (int i = 0; i < nombreJoueurs; i++)
        joueurs[i] = dynamic_cast<Joueur*>(context->deserialize(data[QString::number(i)]));

    chantier.deserialize(data["chantier"].value<QVariantMap>(), context);
}

void Jeu::chargerPartie() {
    SerializationContext s{};
    QFile file{constJeu::saveFilePath};
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> s;
        file.close();
    }
    // Sinon dire qu'on as pas réussi à ouvrir le fichier
    else throw exception();
    // Deserialiser le jeu (stocké à l'indice 0)
    s.deserialize(0);
}

void Jeu::sauvegarderPartie() {
    SerializationContext s{};
    QFile file{constJeu::saveFilePath};
    // Sérialiser le Jeu (qu'on stockera donc à l'indice 0)
    s.serialize(getJeu());
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << s;
        file.close();
    }
    // Sinon dire qu'on as pas réussi à ouvrir le fichier
    else throw exception();
}

// Jeu console //

JeuConsole::JeuConsole() : Jeu() {
    affichage = AffichageConsole::getInstance();
}

void JeuConsole::selectGameMode()  {
    int choix =0;
    cout << "\033[0;97mSOLO ( 1 ) / MULTI ( 2 )?"
        << endl << "\033[0;37m-> \033[0;97m";
    cin >> choix;

    while (cin.fail() || choix <= 0 || choix > 2) {
        cout << "\033[1;31m --> gamemode inexistant !"
            << endl << "\033[0;37m-> \033[0;97m";
        // Enlève l'état d'erreur
        cin.clear();
        // Ignore les "mauvais" charactères
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choix;

    }
    modeDeJeu = static_cast<GameMode>(choix -1);

    if (modeDeJeu == GameMode::MULTIJOUEUR) { return;}
    // choix difficulté
    cout << "\033[0;36mVous avez selectionner le mode solo, vous allez affronter l'illustre architechte! " << endl;
}

void JeuConsole::selectJoueurs() {
    cout << "\033[0;97mCombien de joueurs joueront à cette partie ?"
        << endl << "\033[0;37m-> \033[0;97m";
    cin >> nombreJoueurs;

    while (cin.fail() || nombreJoueurs < 2 || nombreJoueurs > 4) {
        cout << "\033[1;31mLe nombre de joueur doit être un entier entre 2 et 4 !"
            << endl << "\033[0;37m-> \033[0;97m";
        // Enlève l'état d'erreur
        cin.clear();
        // Ignore les "mauvais" charactères
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> nombreJoueurs;
    }

    cout << "\033[0;36mCette partie se déroulera à " << nombreJoueurs << " joueurs" << endl;

    for (int i = 0; i < nombreJoueurs; i++) joueurs[i] = new JoueurSimple();
}

void JeuConsole::selectNomsJoueurs() {
    for (size_t i = 0; i < (modeDeJeu == GameMode::SOLO ? 1 : nombreJoueurs); i++) {
        string nomJoueur;
        string placeSuffixe = i == 0 ? "er" : "ème";
        cout << "\033[0;97mQuel est le nom du " << i+1 << placeSuffixe << " joueur ?"
             << endl << "\033[0;37m-> \033[0;97m";
        cin >> nomJoueur;

        while (cin.fail()) {
            cout << "\033[1;31mErreur, veuillez réessayer !"
                 << endl << "\033[0;37m-> \033[0;97m";
            // Enlève l'état d'erreur
            cin.clear();
            // Ignore les "mauvais" charactères
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> nomJoueur;
        }

        dynamic_cast<JoueurSimple*>(joueurs[i])->setNomJoueur(nomJoueur);
    }
}

Difficulte JeuConsole::selectNiveauIllustreArchitechte() {
    int choix;
    cout << "\033[0;97m - FACILE ( 1 ) / NORMALE ( 2 ) / DIFFICILE (3)?"
         << endl << "\033[0;37m-> \033[0;97m";
    cin >> choix;

    while (cin.fail() || choix <= 0 || choix > 3) {
        cout << "\033[1;31m --> difficulté  inexistante !"
             << endl << "\033[0;37m-> \033[0;97m";
        // Enlève l'état d'erreur
        cin.clear();
        // Ignore les "mauvais" charactères
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choix;
    }
    auto difficulte = static_cast<Difficulte>(choix-1);
    switch (difficulte){
        case Difficulte::FACILE:
            cout << "\033[0;32mFacile\033[0;97m: vous aller affronter Hippodamos, c'est un maitre du BLABLABLABLA"<< endl;
            break;
        case Difficulte::NORMALE:
            cout << "\033[0;33mNormale\033[0;97m: bon courage avec Metagenes"<< endl;
            break;
        case Difficulte::DIFFICILE:
            cout << "\033[0;31mDifficile\033[0;97m: vous n'aurez aucune chance face à Callicrates, balbalbal comment ses regles fonctionnent"<< endl;
            break;
        default:
            cout << "\033[1;31mErreur : difficulté inconnue ..." << endl;
            break;
    }
    return difficulte;
}

void JeuConsole::selectReglesScore() {
    string choixRegles;
    cout << "\033[0;97mAvec quelles règles de score voulez-vous jouer ?" << endl
        << "SIMPLE ( s ) / VARIANTE ( v )"
         << endl << "\033[0;37m-> \033[0;97m";
    cin >> choixRegles;

    while (cin.fail() || (choixRegles != "s" && choixRegles != "v")) {
        cout << "\033[1;31mLes règles ne peuvent que être: SIMPLE ( s ) / AVANCÉES ( a ) !"
             << endl << "\033[0;37m-> \033[0;97m";
        // Enlève l'état d'erreur
        cin.clear();
        // Ignore les "mauvais" charactères
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choixRegles;
    }

    Score* score;
    if (choixRegles == "s") {
        cout << "\033[0;36mCette partie se déroulera avec les règles de score simple" << endl;
        score = getScoreSimple();
    }
    else if (choixRegles == "v") {
        cout << "\033[0;36mCette partie se déroulera avec les règles de score de la variante" << endl;
        score = getScoreVariante();
    }
    else {
        cout << "\033[1;31mErreur, règles de score inconnues !" << endl;
    }

    if (modeDeJeu == GameMode::SOLO)
        dynamic_cast<JoueurSimple*>(joueurs[0])->set_score(score);
    else
        for (size_t i = 0; i < nombreJoueurs; i++)
            dynamic_cast<JoueurSimple*>(joueurs[i])->set_score(score);
}

int JeuConsole::selectTuile(size_t joueur) {
    int output;
    Vector2 positionNulle{0,0};

    cout << "\033[0;36m------------------" << endl
         << "--- Tour " << (nombreTours < 10 ? "0" : "") << nombreTours << "/" << maxNombreTours << " ---" << endl
        << "------------------" << endl << endl;

    int i = 0;
    for (auto iter : chantier) {
        // Définition du plateau pour la tuile
        cout<<"\033[0;97mTuile n°"<<i+1<< " (cout en pierre = "<< i << ") : "<<endl;
        i++;
        affichage->affiche_container(*iter);
    }
    cout<<"\033[0;97m\n Votre plateau :" <<endl;
    affichage->affiche_joueur(*joueurs[joueur]);

    cout << "\033[0;97m" << joueurs[joueur]->getNomJoueur() <<" quelle tuile voulez vous selectionner ?" << endl;
    cout << "\033[0;37m( -1 ) pour quitter le programme et sauvegarder la partie." << endl;
    cout << "\033[0;37m-> \033[0;97m";
    cin >> output;

    while (output <= 0 || output > chantier.get_nombre_tuiles() || (output-1 > joueurs[joueur]->get_pierre()) || cin.fail()) {
        // Si l'utilisateur souhaite quitter le programme
        if (output == -1) return output;
        // Sinon, gérer l'erreur de la façon appropriée
        if (output <= 0 || output > chantier.get_nombre_tuiles()){
            cout << "\033[1;31mLa valeur doit etre entre "<< 1 <<" et " << chantier.get_nombre_tuiles() << endl;
        }
        else if (output-1 > joueurs[joueur]->get_pierre()) {
            cout << "\033[1;31mVous n'avez pas assez de pierre pour prendre cette tuile !" << endl;
        }

        cout << "\033[0;37m-> \033[0;97m";

        // Enlève l'état d'erreur
        cin.clear();
        // Ignore les "mauvais" charactères
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cin >> output;
    }

    return output-1;
}

bool JeuConsole::placeTuile(size_t joueur, Tuile* tuileSelected) {
    cout << "\033[0;36m------------------" << endl
         << "--- Tour " << (nombreTours < 10 ? "0" : "") << nombreTours << "/" << maxNombreTours << " ---" << endl
         << "------------------" << endl;

    Vector2 positionSelectionne{0,0};

    // Définition du plateau pour la tuile
    Vector2 positionNulle{0,0};

    afficheJoueur(joueur, *tuileSelected, positionSelectionne);
    cout << "\033[0;37mPour afficher les commandes disponibles, tapez help" << endl;

    string output;
    while (true) {
        cout << "\033[0;37m-> \033[0;97m";
        cin >> output;

        if (output == "help") {
            cout << "\033[0;97mActuellement, vous devez séléctionner une case où placer votre tuile." << endl
                << "Vous avez un curseur, qui séléctionne un emplacement pour palcer votre tuile." << endl
                << endl
                << "Voici la liste des commandes disponibles:" << endl
                << "\033[1mr\033[0m  : Revient à la séléction de tuiles" << endl
                << "\033[1mtg\033[0m  : Tourne la tuile d'un cran sur la gauche" << endl
                << "\033[1mtd\033[0m  : Tourne la tuile d'un cran sur la droite" << endl
                << "\033[1mmh\033[0m  : Bouge le curseur en haut" << endl
                << "\033[1mmhg\033[0m : Bouge le curseur en haut à gauche" << endl
                << "\033[1mmhd\033[0m : Bouge le curseur en haut à droite" << endl
                << "\033[1mmb\033[0m  : Bouge le curseur en bas" << endl
                << "\033[1mmbg\033[0m : Bouge le curseur en bas à gauche" << endl
                << "\033[1mmbd\033[0m : Bouge le curseur en bas à droite" << endl
                << "\033[1mp\033[0m   : Tente de placer la tuile à l'emplacement du curseur" << endl
                ;
        }
        else if (output == "r") {
            return false;
        }
        else if (output == "tg" || output == "td") {
            tuileSelected->tourne(output == "tg");
            afficheJoueur(joueur, *tuileSelected, positionSelectionne);
        }
        else if (output == "mh") {
            positionSelectionne.y += -1;
            afficheJoueur(joueur, *tuileSelected, positionSelectionne);
        }
        else if (output == "mhg") {
            positionSelectionne.x += -1;
            afficheJoueur(joueur, *tuileSelected, positionSelectionne);
        }
        else if (output == "mhd") {
            positionSelectionne.x += 1;
            positionSelectionne.y += -1;
            afficheJoueur(joueur, *tuileSelected, positionSelectionne);
        }
        else if (output == "mb") {
            positionSelectionne.y += 1;
            afficheJoueur(joueur, *tuileSelected, positionSelectionne);
        }
        else if (output == "mbg") {
            positionSelectionne.x += -1;
            positionSelectionne.y += 1;
            afficheJoueur(joueur, *tuileSelected, positionSelectionne);
        }
        else if (output == "mbd") {
            positionSelectionne.x += 1;
            afficheJoueur(joueur, *tuileSelected, positionSelectionne);
        }
        else if (output == "p") {
            if (joueurs[joueur]->get_plateau().peut_placer(*tuileSelected, positionSelectionne)) {
                cout << "\033[1;32mPosition valide :" << endl;

                Joueur *tempJoueur = joueurs[joueur];
                tempJoueur->place_tuile(tuileSelected, positionSelectionne);
                affichage->affiche_joueur(*tempJoueur);

                cout << "\033[0;97mTapez \033[1;32my\033[0;97m pour confirmer ce placement !" << endl
                    << "\033[0;37m-> \033[0;97m";
                cin >> output;
                if (output == "y") {
                    cout << "\033[1;32mPlacement validé !" << endl;
                    joueurs[joueur]->place_tuile(tuileSelected, positionSelectionne);
                    return true;
                }
                else {
                    cout << "\033[0;37mPlacement annulé" << endl;
                    afficheJoueur(joueur, *tuileSelected, positionSelectionne);
                }
            }
            else {
                cout << "\033[1;31mPosition invalide !" << endl;
            }
        }
        else {
            cout << "\033[1;31mCommande invalide !" << endl
                << "\033[0;37mPour afficher les commandes disponibles, tapez help" << endl;;
        }
    }
}

void JeuConsole::afficheJoueur(size_t joueur, Tuile &tuileSelected, Vector2& positionSelectionne) {
    cout << "\033[0;36m-------------------------------------------" << endl
         << "\033[0;97m"<<joueurs[joueur]->getNomJoueur()<<", Où voulez vous placer cette tuile:" << endl;
    affichage->affiche_container(tuileSelected, Vector2(0,0));
    cout << endl
         << "\033[0;97mSur votre plateau:" << endl;
    affichage->affiche_joueur(*joueurs[joueur], positionSelectionne);
}

void JeuConsole::afficheTourAutomatique(size_t joueur) {
    cout << "\033[0;36m-------------------------------------------" << endl
        << "\033[0;97mVoici le plateau de l'Illustre Architechte:" << endl;
    affichage->affiche_joueur(*joueurs[joueur]);

}

void JeuConsole::finDePartie(multimap<int, size_t> scores) {
    cout << "\033[1;93mPartie Finie, voici les gagnants :" << endl << endl;

    size_t i = 0;

    for (auto scoreIterator = scores.rbegin(); scoreIterator != scores.rend(); scoreIterator++) {
        i++;
        string placeSuffixe = i == 1 ? "er" : "ème";
        if (modeDeJeu == GameMode::MULTIJOUEUR) {
            cout << "En " << i << placeSuffixe << ", le joueur " << scoreIterator->second + 1
                << " avec " << scoreIterator->first << " points !" << endl;
        }
        else {
            string nom = scoreIterator->second == 0 ? "vous" : "l'Illustre Architechte";
            cout << "En " << i << placeSuffixe << "," << nom
                << " avec " << scoreIterator->first << " points !" << endl;
        }
    }
}

Jeu *JeuConsole::getJeu() {
    if (jeu == nullptr) jeu = new JeuConsole();
    return jeu;
}

bool JeuConsole::selectChargerPartie() {
    string reponse;
    cout << "\033[0;97mVoulez-vous recharger la dernière partie ?" << endl
         << "Yes ( y ) / No ( n )"
         << endl << "\033[0;37m-> \033[0;97m";
    cin >> reponse;

    return reponse == "y" || reponse == "yes" || reponse == "Yes";
}

void JeuConsole::titleScreen() {
    cout <<
         "    _______ __  __ ______ _______ ______ _______ _____   _______ _______ \n"
         "   |   _   |  |/  |   __ \\       |   __ \\       |     |_|_     _|     __|\n"
         "   |       |     <|      <   -   |    __/   -   |       |_|   |_|__     |\n"
         "   |___|___|__|\\__|___|__|_______|___|  |_______|_______|_______|_______|\n";
}

// JEU GUI //

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
    QWidget::connect(window->getEcranTitre(), SIGNAL(startGame()), &SignalWaitLoop, SLOT(quit()));
    SignalWaitLoop.exec();

}


bool JeuGUI::selectChargerPartie() {
    window->showEcran(window->getEcranSelectionSauvegarde());

    // Connecter le signal de séléction à une lambda expression qui changera la valeure
    bool resultat = false;
    QObject::connect(window->getEcranSelectionSauvegarde(),
                     &EcranSelectionSauvegarde::selectionFinished,
                     [&](bool chargeSauvegarde){resultat = chargeSauvegarde;});

    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;
    QWidget::connect(window->getEcranSelectionSauvegarde(),
                     SIGNAL(selectionFinished(bool))
                     , &SignalWaitLoop, SLOT(quit()));
    SignalWaitLoop.exec();

    // Retourner la réponse de l'utilisateur
    return resultat;
}

void JeuGUI::selectGameMode() {
    window->showEcran(window->getEcranSelectionModeDeJeu());
    // Connecter le signal de séléction à une lambda expression qui changera la valeure
    QObject::connect(window->getEcranSelectionModeDeJeu(),
                     &EcranSelectionModeDeJeu::selectionFinished,
                     [this](GameMode modeDeJeuSelected){modeDeJeu = modeDeJeuSelected;});

    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;
    QWidget::connect(window->getEcranSelectionModeDeJeu(),
                     SIGNAL(selectionFinished(GameMode)),
                     &SignalWaitLoop, SLOT(quit()));
    SignalWaitLoop.exec();
    if (modeDeJeu == GameMode::SOLO) qDebug() << "Mode de jeu: SOLO";
    else qDebug() << "Mode de jeu: MULTIJOUEUR";
}

void JeuGUI::selectJoueurs() {

    window->showEcran(window->getEcranSelectionNombreJoueurs());
    // Connecter le signal de séléction à une lambda expression qui changera la valeure
    QObject::connect(window->getEcranSelectionNombreJoueurs(),
                     &EcranSelectionNombreJoueurs::selectionFinished,
                     [this](int nb){
                         this ->nombreJoueurs = nb;
                     });

    //Attendre que le signal pour quitter l'écran soit émis
    QEventLoop SignalWaitLoop;
    QWidget::connect(window->getEcranSelectionNombreJoueurs(),
                     SIGNAL(selectionFinished()),
                     &SignalWaitLoop, SLOT(quit()));
    SignalWaitLoop.exec();
    qDebug() << "Partie comptant " << nombreJoueurs << "joueurs.";
}

/*
void JeuGUI::selectNomsJoueurs() {

}*/

/*
void JeuGUI::selectReglesScore() {
}*/

void JeuGUI::afficheTourAutomatique(size_t joueurIndex) {
    //recupere joueur actuelle
    Joueur* j = joueurs[joueurIndex];

    // mise à jour des labels
    //fenetre->jeu->labelNom->setText("Joueur: " + QString::fromStdString(j->getNomJoueur()));
    //fenetre->jeu->labelPierre->setText("Pierres: " + QString::number(j->get_pierre()));
    //fenetre->jeu->labelScore->setText("Score: " + QString::number(j->get_score()));

    // mise à jour de la map
    //fenetre->mettreAJourPlateau(j->get_plateau());

    // mise à jour du CHANTIER
    // TODO

    //QApplication::processEvents();
}
