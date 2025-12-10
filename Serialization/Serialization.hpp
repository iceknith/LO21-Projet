#ifndef LO21_PROJET_SERIALIZATION_HPP
#define LO21_PROJET_SERIALIZATION_HPP

#include "../Players/Players.hpp"
#include "../Chantier/Chantier.hpp"
#include "../Chantier/Deck.hpp"
#include <QVariant>

//! Context de sérialisation, qui permet de sérialiser tout objets sérializables (dont ceux avec des pointeurs)
class SerializationContext {
public:
    // Serialize un pointeur
    size_t serialize(Serializable* object );
    Serializable* deserialize(const size_t index);

    friend QDataStream& operator<<(QDataStream& stream, const SerializationContext& context);
    friend QDataStream& operator>>(QDataStream& stream, SerializationContext& context);

private:
    struct Record
    {
        Serializable* object;
        string type;
        QVariantMap serializedData;

    };
    friend QDataStream& operator<<(QDataStream& stream, const Record& record);
    friend QDataStream& operator>>(QDataStream& stream, Record& record);

    //! La liste des pointeurs enregistrés
    QList<Record> recordList;
    //! Une hashmap associant le pointeur d'un serializable à son index dans le record
    QHash<Serializable*, size_t> recordMap;
};


//! Factory chargée de créer des objets serialisables
class SerializableFactory {
public:
    static Serializable* createSerializable(string type);
};

#endif //LO21_PROJET_SERIALIZATION_HPP
