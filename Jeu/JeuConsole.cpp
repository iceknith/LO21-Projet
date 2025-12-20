#include "Jeu.hpp"

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

    bool variantesCouleursScores[5]{};

    for (int i = 0; i < 5; i++) {
        string choixRegles;
        cout << "\033[0;97mAvec quelles règles de score voulez-vous jouer pour la couleur " << GameConstants::nomScoresInOrder[i] << " ?" << endl
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

        if (choixRegles == "v")
            cout << "\033[0;36mCette partie se déroulera avec les règles de score de la variante pour la couleur " << GameConstants::nomScoresInOrder[i] << endl;
        else
            cout << "\033[0;36mCette partie se déroulera avec les règles de score simples pour la couleur " << GameConstants::nomScoresInOrder[i] << endl;

        variantesCouleursScores[i] = choixRegles == "v";
    }

    Score* score = getScore(variantesCouleursScores);

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
