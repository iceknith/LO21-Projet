//
// Created by Ethann Pencole on 27/09/2025.
//

#ifndef LO21_PROJET_PLAYERS_HPP
#define LO21_PROJET_PLAYERS_HPP

#include "../Score/Score.hpp"
#include "../Tuile/Tuile.hpp"
#include "../Utils.hpp"

class Joueur {
protected:
    int pierre = 0;
    Plateau& plateauJoueur;
    bool joueToutSeul;

public:
    int get_score();
    int get_pierre();
    void set_pierre(int pierre);
    void ajouter_pierre(int pierre);
    Plateau& get_plateau();

    bool place_tuile(Tuile tuile, Vector2 coordonées);
};

class JoueurSimple : Joueur {
protected:
    Score* scoreJoueur;
    bool joueToutSeul = false;
public:
    void set_niveau(int niveau);
    int get_niveau();
    void jouer(Tuile chantier);
};

class IllustreArchitecte : Joueur {
protected:
    int niveau = 0;
    bool joueToutSeul = true;
    Tuile choisir_tuile(Tuile* chantier);
    Vector2 trouver_emplacement_tuile();
public:
    void set_niveau(int niveau);
    int get_niveau();
    void jouer(Tuile chantier);

};

#endif //LO21_PROJET_PLAYERS_HPP