#ifndef LO21_PROJET_PLAYERS_HPP
#define LO21_PROJET_PLAYERS_HPP

#include "../Score/Score.hpp"
#include "../HexagoneContainer/Tuile.hpp"
#include "../Utils.hpp"
#include "../Chantier/Chantier.hpp"

//! La classe abstraite Joueur, qui implémente n'importe quel Joueur
/*!
  La classe qui va représenter à la fois
  chaque joueur humain, mais à la fois chaque joueur non humain (dont l'IllustreArchitechte)
*/
class Joueur {
protected:
    //! Le nombre de pierres du Joueur
    int pierre = 0;
    //! Le Plateau du joueur
    Plateau plateauJoueur;
    //! Le Score du joueur, va être utilisé pour calculer le score du joueur à la fin de la partie
    Score* scoreJoueur = nullptr;

public:
    //! Constructeur du joueur
    Joueur() : plateauJoueur() {}
    //! Si le joueur joue tout seul
    /*!
      Si le joueur joue tout seul. \n
      Cette méthode indique au moteur de jeu, si il as à attendre des inputs de la part du joueur
    */
    virtual bool get_joue_tout_seul() const = 0;
    //! Retourne le Score calculé du Joueur
    int get_score() {return scoreJoueur->score(&plateauJoueur);}
    //! Set le score du joueur
    void set_score(Score* score);
    //! Retourne la quantité de pierres du Joueur
    int get_pierre() {return pierre;}
    //! Set la quantité de pierres du Joueur
    void set_pierre(int pierre) {this->pierre = max(0, pierre);}
    //! Ajoute des pierres au Joueur
    void ajouter_pierre(int pierre) {this->pierre += pierre;}
    //! Retourne le plateau du Joueur
    Plateau& get_plateau() {return plateauJoueur;}
    //! Tente de placer une tuile aux coordonées indiquées.
    /*!
     * @param tuile la Tuile à placer
     * @param coordonées le Vector2 qui donne la position de la Tuile
     * @return Si la tuile as été placé ou non
     */
    bool place_tuile(Tuile* tuile, Vector2& coordonees, bool forcePlacement = false) {return plateauJoueur.placer(tuile, coordonees, forcePlacement, this);}
    //! La fonction appelée lorsque le joueur joueToutSeul
    /*!
     *
     * @param chantier un tableau de Tuile, représentant le chantier
     */
    virtual void jouer(Chantier &chantier) {}
};

//! Une impléméntation concrète d'un Joueur humain
/*!
  Représente un Joueur humain
*/
class JoueurSimple : public Joueur {
protected:
    //! Le joueur, étant humain, ne joue pas tout seul.
    bool joueToutSeul = false;
public:
    bool get_joue_tout_seul() const override {return false;}
};

namespace IllustreArchitechteConsts {
    const int board_max_width = 15;
}

class IllustreArchitecte : public Joueur {
protected:
    //! Le niveau de l'Architechte (va influencer les règles de score)
    Difficulte difficulte = Difficulte::NORMALE;
    //! Choisit une tuile à partir du chantier
    Tuile* choisir_tuile(Chantier &chantier);
    //! Trouve un emplacement vide et valide pour placer une tuile
    Vector2 trouver_emplacement_tuile(Tuile &tuile);
public:
    IllustreArchitecte(Difficulte difficulte);
    //! Supprime la fonction setScore de l'illustre architechte, car il gère sa méthode de score totu seul
    void set_score() = delete;
    //! Le setteur du niveau
    void set_niveau(int niveau);
    //! Le getteur du niveau
    Difficulte get_difficulte() const {return difficulte;}
    //! La fonction appelée pour faire jouer l'Illustre Architechte
    void jouer(Chantier &chantier) override;
    bool get_joue_tout_seul() const override {return true;}
};

#endif //LO21_PROJET_PLAYERS_HPP