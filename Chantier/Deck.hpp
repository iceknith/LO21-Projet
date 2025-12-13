#ifndef LO21_PROJET_DECK_HPP
#define LO21_PROJET_DECK_HPP

#include "../HexagoneContainer/Tuile.hpp"
#include "../Serialization/Serializable.hpp"

class Deck : public Serializable{
private:
    //! La taille maximale du Deck (est dépendante du nombre de joueurs)
    size_t taille;
    //! le nombre de tuiles actuellement dans le Deck
    size_t nombreTuiles;
    //! Le tableau enregistrant toutes les tuiles sur tout le Deck
    TuileJeu** tuiles;
public:
    //! Initialiseur du Deck par défaut
    Deck() : taille(0), nombreTuiles(0), tuiles(nullptr) {}
    //! Initialise le Deck selon le nombre de joueurs.
    Deck(int nombre_joueurs);
    //! Libère toutes les tuiles au sein du deck
    ~Deck();

    //! Remplis le Deck selon le nombre de joueurs
    void setNombreJoueurs(int nombre_joueurs);

    //! Getteur de la taille maximale du Deck
    int get_taille() {return taille;};
    //! Getteur du nombre de tuiles
    int get_nombre_tuiles(){return nombreTuiles;};
    //! Tire la tuile la plus en haut du deck
    TuileJeu* tirer_tuile();
    //! Tire les x tuiles les plus en haut du deck
    TuileJeu** tirer_tuiles(size_t nombre_tuiles);

    //! Implémentation concrète de la sérialisation
    void serialize(QVariantMap& data, SerializationContext* context) const override;
    //! Implémentation concrète de la désérialisation
    void deserialize(const QVariantMap& data, SerializationContext* context) override;
    //! Implémentation concrète de ClassName
    string className() override {return "Deck";}

};


#endif
