#include "Jeu.hpp"

void print_title() {
    cout <<
"    _______ __  __ ______ _______ ______ _______ _____   _______ _______ \n"
"   |   _   |  |/  |   __ \\       |   __ \\       |     |_|_     _|     __|\n"
"   |       |     <|      <   -   |    __/   -   |       |_|   |_|__     |\n"
"   |___|___|__|\\__|___|__|_______|___|  |_______|_______|_______|_______|\n";
}

// Jeu //

void Jeu::gameLoop() {
    selectGameMode();
    size_t joueurActuel;
    if (modeDeJeu == GameMode::MULTIJOUEUR){
        selectJoueurs();
        srand(time(NULL));
        joueurActuel = rand()%nombreJoueurs;
    }
    // Le joueur 0 sera arbitrairement l'utilisateur et le joueur 1 sera l'illustre architecte.
    else {
        nombreJoueurs = 2;
        joueurs[0] = new JoueurSimple();
        joueurs[1] = new IllustreArchitecte(selectNiveauIllustreArchitechte());
        joueurActuel = 0;
        initialisePlateau();
    }

    // Initialisation de la règle de score
    selectReglesScore();

    // Initialisation du nombre de pierres
    for (size_t i = 0; i<nombreJoueurs; i++) {
        joueurs[(joueurActuel+i)%nombreJoueurs]->set_pierre(i+1);
    }

    deck = new Deck(modeDeJeu == GameMode::SOLO ? 1 : nombreJoueurs);
    chantier.set_nombre_joueurs(nombreJoueurs);

    nombre_tours = 1;
    max_nombre_tours = deck->get_taille()/(chantier.get_taille()-1);

    int diff = chantier.get_taille()-chantier.get_nombre_tuiles();

    if (diff > 0 && deck->get_nombre_tuiles() >= diff) {
        chantier.ajouter_tuile(deck->tirer_tuile(diff), diff);
    }

    while (chantier.get_nombre_tuiles() > 1) {
        // Joueur manuel
        if (!joueurs[joueurActuel]->get_joue_tout_seul())
        {
            Tuile* tuileSelected = selectTuile(joueurActuel);
            placeTuile(joueurActuel, tuileSelected);
        }

        // Illustre architechte
        else {
            joueurs[joueurActuel]->jouer(chantier);
            afficheTourAutomatique(joueurActuel);
        }
        //___________
        joueurActuel = (joueurActuel + 1)%nombreJoueurs;
        nombre_tours += joueurActuel == 0;

        if (joueurActuel == 0) {
            diff = chantier.get_taille()-chantier.get_nombre_tuiles();

            if (diff > 0 && deck->get_nombre_tuiles() >= diff) {
                chantier.ajouter_tuile(deck->tirer_tuile(diff), diff);
            }
        }
    }

    finDePartie(calculerScores());
}

void Jeu::initialisePlateau() {
    Vector2 positionNulle{0,0};
    for (size_t i = 0; i < nombreJoueurs; i++) {
        joueurs[i]->place_tuile(new TuileDepart(), positionNulle, true);
    }
}

multimap<int, size_t> Jeu::calculerScores() {
    multimap<int, size_t> scores{};
    for (size_t i = 0; i < nombreJoueurs; i++) scores.insert(make_pair(joueurs[i]->get_score(), i));
    return scores;
}

// Jeu console //

JeuConsole::JeuConsole() {
    affichage = new AffichageConsole();
}

void JeuConsole::selectGameMode()  {
    print_title();

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
    initialisePlateau();
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
    Difficulte difficulte = static_cast<Difficulte>(choix-1);
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

    if (modeDeJeu == GameMode::SOLO) joueurs[0]->set_score(score);
    else for (size_t i = 0; i < nombreJoueurs; i++) joueurs[i]->set_score(score);

    initialisePlateau();
}

Tuile* JeuConsole::selectTuile(size_t joueur) {
    int output;
    Vector2 positionNulle{0,0};
    Tuile ** ch = chantier.get_tuiles();

    cout << "\033[0;36m------------------" << endl
        << "--- Tour " << (nombre_tours < 10 ? "0" : "") << nombre_tours << "/" << max_nombre_tours << " ---" << endl
        << "------------------" << endl << endl;

    int nb_tuilles = chantier.get_nombre_tuiles();
    for (size_t i = 0; i<nb_tuilles; i++) {
        // Définition du plateau pour la tuile
        Plateau plateauTuileSelected;
        plateauTuileSelected.placer(*(ch+i), positionNulle, true);
        cout<<"\033[0;97mTuile n°"<<i+1<< " (cout en pierre = "<< i << ") : "<<endl;
        affichage->affiche_plateau_actuel(plateauTuileSelected);

    }
    cout<<"\033[0;97m\n Votre plateau :" <<endl;
    affichage->affiche_joueur_actuel(*joueurs[joueur]);

    cout << "\033[0;97m Joueur "<< joueur+1 <<" quelle tuile voulez vous selectionner ?" << endl;
    cout << "\033[0;37m-> \033[0;97m";
    cin >> output;

    while (output <= 0 || output > chantier.get_nombre_tuiles() || (output-1 > joueurs[joueur]->get_pierre()) || cin.fail()) {
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

    joueurs[joueur]->set_pierre(joueurs[joueur]->get_pierre()-output+1);
    Tuile* ret = chantier.prendre_tuile(output-1);
    cout << output-1;
    return ret;
}

void JeuConsole::placeTuile(size_t joueur, Tuile* tuileSelected) {
    cout << "\033[0;36m------------------" << endl
         << "--- Tour " << (nombre_tours < 10 ? "0" : "") << nombre_tours << "/" << max_nombre_tours << " ---" << endl
         << "------------------" << endl;

    Vector2 positionSelectionne{0,0};

    // Définition du plateau pour la tuile
    Vector2 positionNulle{0,0};
    Plateau plateauTuileSelected;
    plateauTuileSelected.placer(tuileSelected, positionNulle, true);

    afficheJoueur(joueur, plateauTuileSelected, positionSelectionne);
    cout << "\033[0;37mPour afficher les commandes disponibles, tapez help" << endl;

    bool valide = false;
    string output;
    while (!valide) {
        cout << "\033[0;37m-> \033[0;97m";
        cin >> output;

        if (output == "help") {
            cout << "\033[0;97mActuellement, vous devez séléctionner une case où placer votre tuile." << endl
                << "Vous avez un curseur, qui séléctionne un emplacement pour palcer votre tuile." << endl
                << endl
                << "Voici la liste des commandes disponibles:" << endl
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
        else if (output == "tg" || output == "td") {
            tuileSelected->tourne_tuile(output == "tg");
            plateauTuileSelected = Plateau();
            plateauTuileSelected.placer(tuileSelected, positionNulle, true);
            afficheJoueur(joueur, plateauTuileSelected, positionSelectionne);
        }
        else if (output == "mh") {
            positionSelectionne.y += -1;
            afficheJoueur(joueur, plateauTuileSelected, positionSelectionne);
        }
        else if (output == "mhg") {
            positionSelectionne.x += -1;
            afficheJoueur(joueur, plateauTuileSelected, positionSelectionne);
        }
        else if (output == "mhd") {
            positionSelectionne.x += 1;
            positionSelectionne.y += -1;
            afficheJoueur(joueur, plateauTuileSelected, positionSelectionne);
        }
        else if (output == "mb") {
            positionSelectionne.y += 1;
            afficheJoueur(joueur, plateauTuileSelected, positionSelectionne);
        }
        else if (output == "mbg") {
            positionSelectionne.x += -1;
            positionSelectionne.y += 1;
            afficheJoueur(joueur, plateauTuileSelected, positionSelectionne);
        }
        else if (output == "mbd") {
            positionSelectionne.x += 1;
            afficheJoueur(joueur, plateauTuileSelected, positionSelectionne);
        }
        else if (output == "p") {
            if (joueurs[joueur]->get_plateau().peut_placer(*tuileSelected, positionSelectionne)) {
                cout << "\033[1;32mPosition valide :" << endl;

                Joueur *tempJoueur = joueurs[joueur];
                tempJoueur->place_tuile(tuileSelected, positionSelectionne);
                affichage->affiche_joueur_actuel(*tempJoueur);

                cout << "\033[0;97mTapez \033[1;32my\033[0;97m pour confirmer ce placement !" << endl
                    << "\033[0;37m-> \033[0;97m";
                cin >> output;
                if (output == "y") {
                    cout << "\033[1;32mPlacement validé !" << endl;
                    joueurs[joueur]->place_tuile(tuileSelected, positionSelectionne);
                    valide = true;
                }
                else {
                    cout << "\033[0;37mPlacement annulé" << endl;
                    afficheJoueur(joueur, plateauTuileSelected, positionSelectionne);
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

void JeuConsole::afficheJoueur(size_t joueur, Plateau &tuileSelected, Vector2& positionSelectionne) {
    cout << "\033[0;36m-------------------------------------------" << endl
         << "\033[0;97mJoueur "<< joueur+1<<",Où voulez vous placer cette tuile:" << endl;
    affichage->affiche_plateau_actuel(tuileSelected, Vector2(0,0));
    cout << endl
         << "\033[0;97mSur votre plateau:" << endl;
    affichage->affiche_joueur_actuel(*joueurs[joueur], positionSelectionne);
}

void JeuConsole::afficheTourAutomatique(size_t joueur) {
    cout << "\033[0;36m-------------------------------------------" << endl
        << "\033[0;97mVoici le plateau de l'Illustre Architechte:" << endl;
    affichage->affiche_joueur_actuel(*joueurs[joueur]);

}

void JeuConsole::finDePartie(multimap<int, size_t> scores) {
    cout << "\033[1;93mPartie Finie, voici les gagnants :" << endl << endl;

    size_t i = 0;

    for (auto scoreIterator = scores.rbegin(); scoreIterator != scores.rend(); scoreIterator++) {
        i++;
        string placeSuffixe = i == 1 ? "er" : "ième";
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
