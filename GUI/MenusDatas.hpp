#ifndef LO21_PROJET_MENUSDATAS_HPP
#define LO21_PROJET_MENUSDATAS_HPP

#include "../Serialization/Serializable.hpp"
#include "../Utils.hpp"

namespace MenuData {
    // Infos pour chacun des menus du jeu, à utiliser avec la class abstraite AbstractEcran.

    struct MENU_SELECTION_SAUVEGARDE {
        bool signalData;   // La valeur du signal
        QString btnTexte;   // Ce qui est écrit sur le bouton
        QString couleur; // La couleur du bouton
    };
    // La liste des options
    static const std::vector<MENU_SELECTION_SAUVEGARDE> getSeletionSauvegarde() {
        return {
                {false, "NOUVELLE PARTIE", "red"},
                {true, "CHARGER DERNIERE PARTIE", "red"}
        };
    }

    // ================================

    struct MENU_MODE_DE_JEU {
        GameMode signalData;
        QString btnTexte;
        QString couleur;
    };
    static const std::vector<MENU_MODE_DE_JEU> getModesDeJeu() {
        return {
                {GameMode::SOLO, "SOLO", "gray"},
                {GameMode::MULTIJOUEUR, "MULTIJOUEUR", "gray"}
        };
    }

    // ================================

    struct MENU_DIFFICULTE {
        Difficulte signalData;
        QString btnTexte;
        QString couleur;
    };

    static const std::vector<MENU_DIFFICULTE> getDifficultes() {
        return {
                {Difficulte::FACILE, "Hippodamos (Facile)", "green"},
                {Difficulte::NORMALE, "Metagenes (Moyen)", "orange"},
                {Difficulte::DIFFICILE, "Callicrates (Difficile)", "red"}
        };
    }

    // ================================

    struct MENU_NB_JOUEURS {
        int signalData;
        QString btnTexte;
        QString couleur;
    };

    static const std::vector<MENU_NB_JOUEURS> getNbJoueurs() {
        return {
                {2, "2", "orange"},
                {3, "3", "orange"},
                {4, "4", "orange"}
        };
    }

    // ================================

    struct MENU_NB_TOURS {
        VITESSE signalData;
        QString btnTexte;
        QString couleur;
    };
    static const std::vector<MENU_NB_TOURS> getNbTours() {
        return {
                {VITESSE::RAPIDE, "RAPIDE", "green"},
                {VITESSE::NORMALE, "NORMAL", "orange"},
                {VITESSE::LENT, "LENT", "red"}
        };
    }

}

#endif //LO21_PROJET_MENUSDATAS_HPP
