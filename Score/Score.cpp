#include "Score.hpp"

#include <vector>
using namespace ScoreUtils;


int ScoreUtils::get_iteration_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    int compteur=0;
    auto iterateur = plateau->get_iterateur_debut();
    auto iterateur_fin = plateau->get_iterateur_fin();
    do {
        const auto *h=iterateur->second;
        if (h->get_couleur() == couleur && h->get_type()== type) {
            compteur++;
            //cout<<compteur<<endl;
        }
    } while (++iterateur != iterateur_fin);
    cout<<compteur<<endl;
    return compteur;
}

int ScoreUtils::get_iteration_with_hauteur_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    int compteur=0;
    auto iterateur = plateau->get_iterateur_debut();
    auto iterateur_fin = plateau->get_iterateur_fin();
    do {
        const auto *h=iterateur->second;
        if (h->get_couleur() == couleur && h->get_type()== type) {
            compteur+= h->get_hauteur();
        }
    } while (++iterateur != iterateur_fin);
    cout<<compteur<<endl;
    return compteur;
}

void get_hexagones_coordonates_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    vector<Vector2> resultat;
    auto iterateur = plateau->get_iterateur_debut();
    auto iterateur_fin = plateau->get_iterateur_fin();
    do {
        auto *h=iterateur->second;
        if (h->get_couleur() == couleur && h->get_type()== type) {
            int q = (int) iterateur->first.x;
            int r = (int) iterateur->first.y;
            resultat.push_back( Vector2{static_cast<float>(q),static_cast<float>(r)});
        }
    } while (++iterateur != iterateur_fin);
    // DEBUG - Afficher le contenu du vecteur
    cout << "DEBUG - Nombre d'hexagones trouvés: " << resultat.size() << endl;
    for (int i = 0; i < resultat.size(); i++) {
        cout << "Hexagone " << i << ": (" << resultat[i].x << ", " << resultat[i].y << ")" << endl;
    }

}

int ScoreUtils::get_largest_voisinnage_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    int compteur=0;
    auto iterateur = plateau->get_iterateur_debut();
    auto iterateur_fin = plateau->get_iterateur_fin();
    do {
        const auto *h=iterateur->second;
        if (h->get_couleur() == couleur && h->get_type()== type) {

            compteur++;
        }
    } while (++iterateur != iterateur_fin);
    return compteur;
}
/*
bool est_entoure (Plateau* plateau, Hexagone* hexagone) {
    plateau->obtenir_hexagone(hexagone.)
}
*/
// =======================
// ScoreBleu

int ScoreBleu::score_bleu(Plateau* plateau) {
    // TODO: logique de score BLEU pour joueur normal
    //methode speciale qui conte le voisinage le plus grand
    return 0;
}

int ScoreBleu::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_bleu(plateau);
    return s;
}

// =======================
// ScoreRouge

int ScoreRouge::score_rouge(Plateau* plateau) {

    // TODO
    return 0;
}

int ScoreRouge::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_rouge(plateau);
    return s;
}

// =======================
// ScoreVert

int ScoreVert::score_vert(Plateau* plateau) {
    get_hexagones_coordonates_filtres(plateau,TypeHexagone::Place,VERT);
    int place = get_iteration_filtres(plateau,TypeHexagone::Place,VERT)*3;
    int quartier = get_iteration_with_hauteur_filtres(plateau,TypeHexagone::Quartier,VERT);
    return place*quartier;
}

int ScoreVert::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_vert(plateau);
    return s;
}

// =======================
// ScoreViolet

int ScoreViolet::score_violet(Plateau* plateau) {
    // TODO
    return 0;
}

int ScoreViolet::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_violet(plateau);
    return s;
}

// =======================
// ScoreJaune

int ScoreJaune::score_jaune(Plateau* plateau) {
    // TODO
    return 0;
}

int ScoreJaune::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_jaune(plateau);
    return s;
}

// =======================
// Variante: ScoreBleuVariante

int ScoreBleuVariante::score_bleu_variante(Plateau* plateau) {
    // TODO
    return 0;
}

int ScoreBleuVariante::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_bleu_variante(plateau);
    return s;
}

// =======================
// Variante: ScoreRougeVariante

int ScoreRougeVariante::score_rouge_variante(Plateau* plateau) {
    // TODO
    return 0;
}

int ScoreRougeVariante::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_rouge_variante(plateau);
    return s;
}

// =======================
// Variante: ScoreVertVariante

int ScoreVertVariante::score_vert_variante(Plateau* plateau) {
    int place = get_iteration_filtres(plateau,TypeHexagone::Place,VERT)*3; // get_iteration_filtres qui regarde les lacs
    int quartier = get_iteration_with_hauteur_filtres(plateau,TypeHexagone::Quartier,VERT);
    return place*quartier;
}

int ScoreVertVariante::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_vert_variante(plateau);
    return s;
}

// =======================
// Variante: ScoreVioletVariante

int ScoreVioletVariante::score_violet_variante(Plateau* plateau) {
    // TODO
    return 0;
}

int ScoreVioletVariante::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_violet_variante(plateau);
    return s;
}

// =======================
// Variante: ScoreJauneVariante

int ScoreJauneVariante::score_jaune_variante(Plateau* plateau) {
    // TODO
    return 0;
}

int ScoreJauneVariante::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_jaune_variante(plateau);
    return s;
}