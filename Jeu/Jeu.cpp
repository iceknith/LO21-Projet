#include "Jeu.hpp"
#include "../Serialization/Serialization.hpp"

// Jeu //

Jeu* Jeu::jeu = nullptr;

void Jeu::gameLoop(int argc, char *argv[]) {
    bool Charger = false;
    bool BackPressed2 = false;
    bool StartJeu = true;

    titleScreen();

    // Si on charge une partie existante
    QFileInfo saveFileInfo{constJeu::saveFilePath};

    do {
        BackPressed = false;

        if (saveFileInfo.exists() && saveFileInfo.isFile()&&selectChargerPartie()) {
            BackPressed = false;
            chargerPartie();
        }
        else {
            do {
                BackPressed = false;
                selectGameMode();

                if (!BackPressed) {
                    do {
                        BackPressed = false;

                        if (modeDeJeu == GameMode::MULTIJOUEUR) {
                            selectJoueurs();
                            BackPressed2 = BackPressed;
                            BackPressed = false;

                            if (!BackPressed2) {
                                srand(time(NULL));
                                premierJoueur = rand() % nombreJoueurs;
                            }
                        }
                        else {
                            nombreJoueurs = 2;
                            joueurs[0] = new JoueurSimple();
                            joueurs[1] = new IllustreArchitecte(selectNiveauIllustreArchitechte());
                            BackPressed2 = BackPressed;
                            BackPressed = false;
                            if (!BackPressed2) {
                                premierJoueur = 0;
                            }
                        }

                        if (BackPressed2 == false) {

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

                            BackPressed2 = true;
                            BackPressed = true;
                            StartJeu = false;
                        }

                    } while (!BackPressed2);
                }

            } while (!BackPressed);
        }

    } while (BackPressed && StartJeu);

    afficheSceneJeu();
    while (chantier.get_nombre_tuiles() > 1) {
        sauvegarderPartie();
        string s;
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
    else throw AkropolisException("Cannot open the file");
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
    else throw AkropolisException("Cannot open the file");
}