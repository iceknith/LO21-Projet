#include "Jeu.hpp"

void Jeu::gameLoop() {
    selectJoueurs();

    srand(time(NULL));
    size_t joueurActuel = rand()%nombreJoueurs;

    chantier.set_nombre_joueurs(nombreJoueurs);

    deck = new Deck(nombreJoueurs);

    // Vector2 positionNulle{0,0};
    // for (size_t i = 0; i<deck->get_taille(); i++) {
    //     // Définition du plateau pour la tuile
    //     Plateau plateauTuileSelected;
    //     plateauTuileSelected.placer(deck->tirer_tuile(), positionNulle);
    //     affichage->affiche_plateau_actuel(plateauTuileSelected, Vector2(0,0));
    // }

    //! TODO ajouter la logique de pioche du deck dans le chantier

    // À décommenter dès que le chantier est implémenté
    //while (!chantier.est_vide()) {
    while (true) {
        joueurActuel = (joueurActuel + 1)%nombreJoueurs;

        Tuile* tuileSelected = selectTuile(joueurActuel);
        placeTuile(joueurActuel, tuileSelected);
    }
    finDePartie();
}

JeuConsole::JeuConsole() {
    affichage = new AffichageConsole();
}

void JeuConsole::selectJoueurs() {
    cout << "\033[0;97mCombien de joueurs joueront à cette partie ?"
        << endl << "\033[0;37m-> \033[0;97m";
    cin >> nombreJoueurs;

    while (cin.fail() || nombreJoueurs <= 0 || nombreJoueurs > 4) {
        cout << "\033[1;31mLe nombre de joueur doit être un entier entre 1 et 4 !"
            << endl << "\033[0;37m-> \033[0;97m";
        // Enlève l'état d'erreur
        cin.clear();
        // Ignore les "mauvais" charactères
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> nombreJoueurs;
    }

    cout << "\033[0;36mCette partie se déroulera à " << nombreJoueurs << " joueurs" << endl;

    // Initialisation des plateaux des joueurs
    Vector2 positionNulle{0,0};
    for (size_t i = 0; i < nombreJoueurs; i++) {
        joueurs[i].place_tuile(new TuileDepart(i+1), positionNulle);
    }
}

Tuile* JeuConsole::selectTuile(size_t joueur) {
    //! TODO implémenter une vraie méthode de séléction de tuile
    // Actuellement ça leak de la mémoire, mais on changera ça plus tard, tkt ^^

    int diff = chantier.get_taille()-chantier.get_nombre_tuiles();

    if (chantier.get_nombre_tuiles()<chantier.get_taille()) {
        for (size_t i = 0; i<diff; i++) {
            chantier.ajouter_tuile(deck->tirer_tuile());
        }
    }

    int output;
    Vector2 positionNulle{0,0};
    Tuile ** ch = chantier.get_tuiles();


    int nb_tuilles = chantier.get_nombre_tuiles();
    for (size_t i = 0; i<nb_tuilles; i++) {
        // Définition du plateau pour la tuile
        Plateau plateauTuileSelected;
        plateauTuileSelected.placer(*(ch+i), positionNulle);
        cout<<"\033[0;97mTuile n°"<<i+1<< " (cout en pierre = "<< i << ") : "<<endl;
        affichage->affiche_plateau_actuel(plateauTuileSelected);

    }
    cout<<"\033[0;97mVotre plateau :" <<endl;
    affichage->affiche_joueur_actuel(joueurs[joueur]);

    cout << "\033[0;97mQuelle tuile voulez vous selectionner ?" << endl;
    cout << "\033[0;37m-> \033[0;97m";
    cin >> output;

    while (output <= 0 || output > chantier.get_taille()) {
        cout << "La valeur doit etre entre "<< 1 <<" et " << chantier.get_taille() << endl;
        cout << "\033[0;37m-> \033[0;97m";
        cin >> output;
    }

    Tuile* ret = chantier.prendre_tuile(output-1);

    return ret;
}

void JeuConsole::placeTuile(size_t joueur, Tuile* tuileSelected) {
    Vector2 positionSelectionne{0,0};

    // Définition du plateau pour la tuile
    Vector2 positionNulle{0,0};
    Plateau plateauTuileSelected;
    plateauTuileSelected.placer(tuileSelected, positionNulle);

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
            plateauTuileSelected.placer(tuileSelected, positionNulle);
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
            if (joueurs[joueur].get_plateau().peut_placer(*tuileSelected, positionSelectionne)) {
                cout << "\033[1;32mPosition valide :" << endl;

                Joueur tempJoueur = joueurs[joueur];
                tempJoueur.place_tuile(tuileSelected, positionSelectionne);
                affichage->affiche_joueur_actuel(tempJoueur);

                cout << "\033[0;97mTapez \033[1;32my\033[0;97m pour confirmer ce placement !" << endl
                    << "\033[0;37m-> \033[0;97m";
                cin >> output;
                if (output == "y") {
                    cout << "\033[1;32mPlacement validé !" << endl;
                    joueurs[joueur].place_tuile(tuileSelected, positionSelectionne);
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
         << "\033[0;97mOù voulez vous placer cette tuile:" << endl;
    affichage->affiche_plateau_actuel(tuileSelected, Vector2(0,0));
    cout << endl
         << "\033[0;97mSur votre plateau:" << endl;
    affichage->affiche_joueur_actuel(joueurs[joueur], positionSelectionne);
}

void JeuConsole::finDePartie() {
    cout << "\033[1;93mPartie Finie !";
}


