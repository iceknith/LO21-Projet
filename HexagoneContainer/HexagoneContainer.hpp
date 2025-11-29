#ifndef LO21_PROJET_HEXAGONECONTAINER_HPP
#define LO21_PROJET_HEXAGONECONTAINER_HPP


#include <map>
#include "../Utils.hpp"
#include "../Hexagone/Hexagone.hpp"

class HexagoneContainer {
private:
protected:
    //! La map associant une coordonée vectorielle à un hexagone.
    map<Vector2, Hexagone*> container;
    float rotation;
public:
    HexagoneContainer() = default;
    virtual ~HexagoneContainer() = default;
    // TODO faire le destructeur de HexagoneContainer

    //! Retourne si il existe un hexagone aux coordonées entreées
    /*!
     * Retourne si il existe un hexagone aux coordonées entreées
     * @param coordonees les coordonées du potentiel hexagone
     * @return un booléen qui indique si l'hexagone existe ou non
     */
    bool hasHexagone(const Vector2& coordonees) {return container.find(coordonees) != container.end();}
    //! Retourne l'hexagone aux coordonées du Vector2
    /*!
     * @param coordonees le Vector2 des coordonées de l'hexagone recherché
     * @return l'hexagone à ces coordonées
     */
    Hexagone* getHexagone(const Vector2& coordonees) {return container.at(coordonees);}
    //! Retourne le nombre d'hexagones dans le container
    size_t getSize() const {return container.size();}

    //! Tourne le containeur de l'hexagone de 30 degre autour du centre de rotation, dans le sens indiqué.
    void tourne(bool sens_horaire=true, const Vector2& centre_rotation = Vector2());

    //! Retourne la position initiale de l'itérateur du container
    auto begin()  {return container.begin();}
    //! Retourne la position fianle de l'itérateur du container
    auto end()  {return container.end();}

    //! Retourne la position initiale de l'itérateur const du container
    auto begin() const {return container.begin();}
    //! Retourne la position fianle de l'itérateur const du container
    auto end() const {return container.end();}
    //! Retourne la position initiale de l'itérateur const du container
    auto cbegin() const {return container.begin();}
    //! Retourne la position fianle de l'itérateur const du container
    auto cend() const {return container.end();}
};


#endif //LO21_PROJET_HEXAGONECONTAINER_HPP
