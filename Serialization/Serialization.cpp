#include "Serialization.hpp"
#include "../Jeu.hpp"

QVariant SerializationContext::serialize(Serializable *object) {
    // Si on donne un pointeur nul, retourner une valeur infinie
    if (object == nullptr) return {};

    // On regarde si le pointeur existe déjà dans la liste
    auto it = recordMap.find(object);

    // Si le pointeur existe deja dans la liste, on renvoie l'indice de son pointeur
    if (it != recordMap.end()) return {it.value()};

    // Sinon, on sérialize l'objet, et on le rajoute dans un record
    qsizetype index = recordList.count();

    // On crée un lien entre le pointeur et l'index
    recordMap.insert(object, index);

    Record record;
    QVariantMap data;
    recordList.append(record); // Ajout du record pour réserver cet indice

    // Création du record
    record.object = object;
    record.type = object->className();
    object->serialize(data, this);
    record.serializedData = data;

    // Enregistrement du record dans la liste
    recordList[index] = record;


    // On retourne l'index de l'objet, histoire qu'on puisse le retrouver lors de la désérialisation
    return {index};
}

Serializable *SerializationContext::deserialize(const QVariant& objectIndex) {
    // Si on as une valeur infinie, alors on as eu un pointeur nul
    if (objectIndex == QVariant()) return nullptr;
    auto index = qvariant_cast<qsizetype>(objectIndex);
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
    QByteArray type;
    stream >> type;
    record.type = static_cast<string>(type);
    stream >> record.serializedData;
    return stream;
}

Serializable *SerializableFactory::createSerializable(string type) {
    if (type == "Vector2") return new Vector2();

    if (type == "Place") return new Place();
    if (type == "Quartier") return new Quartier();
    if (type == "Carriere") return new Carriere();
    if (type == "Plateau") return new Plateau();

    if (type == "TuileDepart") return new TuileDepart();
    if (type == "TuileJeu") return new TuileJeu();

    if (type == "Deck") return new Deck();
    if (type == "Chantier") return new Chantier();

    if (type == "JoueurSimple") return new JoueurSimple();
    if (type == "IllustreArchitecte") return new IllustreArchitecte();

    if (type == "Jeu") return Jeu::getJeu();

    if (type == "ScoreSoloArchitecteCallicrates") return new ScoreSoloArchitecteCallicrates();
    if (type == "ScoreSoloArchitecteMetagenes") return new ScoreSoloArchitecteMetagenes();
    if (type == "ScoreSoloArchitecteHippodamos") return new ScoreSoloArchitecteHippodamos();
    if (type == "ScoreBleu") return new ScoreBleu();
    if (type == "ScoreRouge") return new ScoreRouge();
    if (type == "ScoreVert") return new ScoreVert();
    if (type == "ScoreViolet") return new ScoreViolet();
    if (type == "ScoreJaune") return new ScoreJaune();
    if (type == "ScoreBleuVariante") return new ScoreBleuVariante();
    if (type == "ScoreRougeVariante") return new ScoreRougeVariante();
    if (type == "ScoreVertVariante") return new ScoreVertVariante();
    if (type == "ScoreVioletVariante") return new ScoreVioletVariante();
    if (type == "ScoreJauneVariante") return new ScoreJauneVariante();

    return nullptr;
}
