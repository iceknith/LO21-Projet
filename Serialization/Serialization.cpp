#include "Serialization.hpp"

size_t SerializationContext::serialize(Serializable *object) {
    // Si on donne un pointeur nul, retourner une valeur infinie
    if (object == nullptr) return numeric_limits<size_t>::infinity();

    // On regarde si le pointeur existe déjà dans la liste
    auto it = recordMap.find(object);

    // Si le pointeur existe deja dans la liste, on renvoie son pointeur
    if (it != recordMap.end()) return it.value();

    // Sinon, on sérialize l'objet, et on le rajoute dans un record
    size_t index = recordList.count();

    QVariantMap data;
    Record record;
    record.object = object;
    record.type = object->className();
    object->serialize(data, this);
    record.serializedData = data;
    recordList.append(record);

    recordMap.insert(object, index);

    // On retourne l'index de l'objet, histoire qu'on puisse le retrouver lors de la désérialisation
    return index;
}

Serializable *SerializationContext::deserialize(const size_t index) {
    // Si on as une valeur infinie, alors on as eu un pointeur nul
    if (index == numeric_limits<size_t>::infinity()) return nullptr;
    Record& r = recordList[index];

    // Si l'objet existe déjà dans la nouvelle liste
    if (r.object) return r.object;

    // Si l'objet n'existe pas, nous devons alors le créer
    Serializable* object = SerializableFactory::createSerializable(r.type);
    r.object = object;
    object->deserialize(r.serializedData, this);
    return object;
}

QDataStream &operator<<(QDataStream &stream, const SerializationContext &context) {
    stream << context.recordList;
    return stream;
}

QDataStream &operator<<(QDataStream &stream, const SerializationContext::Record &record) {
    stream << static_cast<QByteArray>(record.type) << record.serializedData;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, SerializationContext &context) {
    stream >> context.recordList;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, SerializationContext::Record &record) {
    QByteArray typeOtherFormat;
    stream >> typeOtherFormat;
    record.type = static_cast<string>(typeOtherFormat);
    stream >> record.serializedData;
    return stream;
}
