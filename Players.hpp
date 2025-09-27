//
// Created by Ethann Pencole on 27/09/2025.
//

#ifndef LO21_PROJET_PLAYERS_HPP
#define LO21_PROJET_PLAYERS_HPP

#include "Score.hpp"

class Tuile{};

class Vector2 {
    float x ;
    float y;
    Vector2() : x(0), y(0){};
};

class IllustreArchitecte {
protected:
    int niveau = 0;
    Tuile choisir_tuile(Tuile* chantier);
    Vector2 trouver_emplacement_tuile();
public:
    void set_niveau(int niveau);
    int get_niveau();
    void jouer(Tuile chantier);

};

class Joueur {
protected:
    int pierre = 0;
    Score* ScoreJoueur = nullptr;
    Plateau PlateauJoueur;

public:
    bool place_tuile(Tuile tuile, Vector2 coordonées);
    int get_score();
    int get_pierre();
    void set_pierre(int pierre);
    void ajouter_pierre(int pierre);
};

#endif //LO21_PROJET_PLAYERS_HPP