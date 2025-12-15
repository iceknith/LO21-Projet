#include "HexagoneContainer.hpp"
#include "../Serialization/Serialization.hpp"

void HexagoneContainer::tourne(bool sens_horaire, const Vector2 &centre_rotation) {
    cout << "heyyy" << endl;
    map<Vector2, Hexagone*> newContainer;
    Vector2 pos;

    // Changer la position locale de toutes les tuiles
    for (auto iter : *this) {
        // Convertir les coordinates axiales en coordonées cubiques
        pos = iter.first - centre_rotation;
        float q = pos.x;
        float r = pos.y;
        float s = -q-r;

        // Tourner les coordonées et reconvertir en axial
        pos =  (sens_horaire ? Vector2(-r, -s) : Vector2(-s, -q)) + centre_rotation;
        newContainer[pos] = iter.second;
        iter.second->set_local_position(pos);
    }

    container.clear();
    container.merge(newContainer);

    // Change la rotation
    rotation += (sens_horaire ? 1.0f : -1.0f) * 30;
    if (rotation < 0) rotation += 360;
    else if (rotation > 360) rotation -= 360;
}

void HexagoneContainer::serialize(QVariantMap &data, SerializationContext *context) const {
    data["rotation"] = rotation;
    int key = 1;

    for (const auto& it : container) {
        QVariantMap hexVecMap;
        QVariantMap vecData;
        it.first.serialize(vecData, context);
        hexVecMap["key"] = vecData;
        hexVecMap["value"] = context->serialize(it.second);
        data[QString::number(key++)] = hexVecMap;
    }
}

void HexagoneContainer::deserialize(const QVariantMap &data, SerializationContext *context) {
    // Enlever tout les hexagones qui pourraient exister.
    container.clear();
    rotation = data["rotation"].value<float>();
    for (auto it = data.begin(); it != data.end(); it++) {
        // Si l'info décrit un couple Vecteur/Hexagone de la map
        if (it.key().toInt() != 0) {
            auto hexVecMap = it->value<QVariantMap>();
            Vector2 vec{};
            vec.deserialize(hexVecMap["key"].value<QVariantMap>(), context);
            auto* hex = dynamic_cast<Hexagone *>(context->deserialize(hexVecMap["value"]));
            container[vec] = hex;
        }
    }
}
