#include "HexagoneContainer.hpp"

void HexagoneContainer::tourne(bool sens_horaire, const Vector2 &centre_rotation) {
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