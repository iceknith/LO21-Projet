#ifndef LO21_PROJET_CHANTIER_HPP
#define LO21_PROJET_CHANTIER_HPP

#include "../HexagoneContainer/Tuile.hpp"
#include "../Serialization/Serializable.hpp"

const size_t max_tuiles_par_chantier = 5;

//! La classe implémentant le Chantier, permettant aux Joueur de piocher des Tuile
class Chantier : public Serializable{
private:
    //! La taille maximale du Chantier (est dépendante du nombre de joueurs)
    size_t taille = 0;
    //! le nombre de tuiles actuellement dans le Chantier
    size_t nombreTuiles = 0;
    //! Le tableau enregistrant toutes les tuiles sur tout le Chantier
    TuileJeu* tuiles[max_tuiles_par_chantier]{};

    //! Setteur de la taille du chantier
    void set_taille(size_t newTaille) {taille = min(max(newTaille, (size_t) 0), max_tuiles_par_chantier);} // Clamp entre 0 et max_tuiles_par_chantier
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
    //! Getteur de la taille du chantier
    size_t get_taille() const {return taille;}
    //! Getteur du nombres de tuiles dans le chantier
    size_t get_nombre_tuiles() const {return nombreTuiles;}
    //! Si le chantier est vide
    bool est_vide() const {return nombreTuiles <= 0;}
    //! Retire la tuile, à l'index indiqué, du chantier
    /*!
     * Retire la tuile, à l'index indiqué, du chantier
     * Les tuiles d'index supérieur vons "descendre" le chantier
     * comme un mechanisme de rivière.
     * @param index l'index de la tuile à prendre
     * @return La Tuile selectionée
     */
    Tuile* prendre_tuile(size_t index);
    //! Ajoute une Tuile à la fin du chantier
    void ajouter_tuile(TuileJeu* tuile);
    //! Ajoute des Tuile à la fin du chantier
    void ajouter_tuile(TuileJeu** tuile, size_t nombre);



    //! Iterateur de Chantier
    class iterator {
        size_t indx = 0;
        const Chantier& c;
        iterator(size_t index, const Chantier& chantier) : indx(index), c{chantier} {};
        friend Chantier;
    public:
        iterator& operator++() {++indx; return *this;}
        iterator& operator--() {--indx; return *this;}
        [[nodiscard]] Tuile* operator*() const {return c.tuiles[indx];}
        [[nodiscard]] bool operator !=(iterator other) const {return indx != other.indx;}
    };

    [[nodiscard]] iterator begin() {return iterator{0, *this};}
    [[nodiscard]] iterator end() {return iterator{taille, *this};}
    // Itérateur const
    [[nodiscard]] iterator begin() const {return iterator{0, *this};}
    [[nodiscard]] iterator end() const {return iterator{taille, *this};}
    [[nodiscard]] iterator cbegin() const {return iterator{0, *this};}
    [[nodiscard]] iterator cend() const {return iterator{taille, *this};}


    //! Implémentation concrète de la sérialisation
    void serialize(QVariantMap& data, SerializationContext* context) const override;
    //! Implémentation concrète de la désérialisation
    void deserialize(const QVariantMap& data, SerializationContext* context) override;
    //! Implémentation concrète de class name
    std::string className() override {return "Chantier";};
};


#endif //LO21_PROJET_CHANTIER_HPP
