#ifndef LO21_PROJET_CHANTIER_HPP
#define LO21_PROJET_CHANTIER_HPP

#include "../HexagoneContainer/Tuile.hpp"

const int max_tuiles_par_chantier = 5;

//! La classe implémentant le Chantier, permettant aux Joueur de piocher des Tuile
class Chantier {
private:
    //! La taille maximale du Chantier (est dépendante du nombre de joueurs)
    int taille = 0;
    //! le nombre de tuiles actuellement dans le Chantier
    int nombreTuiles = 0;
    //! Le tableau enregistrant toutes les tuiles sur tout le Chantier
    Tuile* tuiles[max_tuiles_par_chantier];
public:
    //! Calcule la taille du chantier selon le nombre de joueurs
    void set_nombre_joueurs(int nombre_joueurs){
        if (nombre_joueurs == 1) {
            this->set_taille(2);
        }
        else if (nombre_joueurs == 2) {
            this->set_taille(3);
        }
        else if (nombre_joueurs == 3) {
            this->set_taille(4);
        }
        else{
            this->set_taille(5);
        }
    };
    //! Setteur de la taille du chantier
    void set_taille(int tailles) {this->taille = min(max(tailles, 0), max_tuiles_par_chantier);} // Clamp entre 0 et max_tuiles_par_chantier
    //! Getteur de la taille du chantier
    int get_taille() {return taille;}
    //! Getteur du nombres de tuiles dans le chantier
    int get_nombre_tuiles() {return nombreTuiles;}
    //! Si le chantier est vide
    bool est_vide() {return nombreTuiles <= 0;}
    //! Getteur des tuiles du chantier
    Tuile** get_tuiles() {return tuiles;}
    //! Retire la tuile, à l'index indiqué, du chantier
    /*!
     * Retire la tuile, à l'index indiqué, du chantier
     * Les tuiles d'index supérieur vons "descendre" le chantier
     * comme un mechanisme de rivière.
     * @param index l'index de la tuile à prendre
     * @return La Tuile selectionée
     */
    Tuile* prendre_tuile(int index);
    //! Ajoute une Tuile à la fin du chantier
    void ajouter_tuile(Tuile* tuile);
    //! Ajoute des Tuile à la fin du chantier
    void ajouter_tuile(Tuile* tuile, int nombre);
};


#endif //LO21_PROJET_CHANTIER_HPP
