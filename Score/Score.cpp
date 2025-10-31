#include "Score.hpp"

#include <vector>
using namespace ScoreUtils;

map<Vector2, Hexagone*> ScoreUtils::get_hexagone_filtres(Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur ){
    map<Vector2, Hexagone*> Hex ;
    auto iterateur = plateau->get_iterateur_debut();
    auto iterateur_fin = plateau->get_iterateur_fin();
    do {
        const auto *h=iterateur->second;
        if (h->get_couleur() == couleur && h->get_type()== type) {
            Hex.insert({iterateur->first,iterateur->second});
        }
    } while (++iterateur != iterateur_fin);
    return Hex;
}

int ScoreUtils::get_iteration_filtres(Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    return get_hexagone_filtres(plateau, type, couleur).size();
}

int ScoreUtils::get_iteration_with_hauteur_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    int iteration = 0;
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, type, couleur);
    for (auto& [pos,hex] : Hex) {
        iteration+= hex->get_hauteur();
    }
    return iteration;
}

/*
void get_hexagones_coordonates_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    vector<Vector2> resultat;
    auto iterateur = plateau->get_iterateur_debut();
    auto iterateur_fin = plateau->get_iterateur_fin();
    do {
        auto *h=iterateur->second;
        if (h->get_couleur() == couleur && h->get_type()== type) {
        }
    } while (++iterateur != iterateur_fin);
    // DEBUG - Afficher le contenu du vecteur
    cout << "DEBUG - Nombre d'hexagones trouvés: " << resultat.size() << endl;
    for (int i = 0; i < resultat.size(); i++) {
        cout << "Hexagone " << i << ": (" << resultat[i].x << ", " << resultat[i].y << ")" << endl;
    }

}
*/

bool find_vector (vector<Vector2> v, Vector2 elem) {
    for (int i =0; i< v.size();i++) {
        if (v[i] == elem) {
            return true;
        }
    }
    return false;

}




//map<Vector2, Hexagone*>



/*
vector<Vector2> ScoreUtils::get_hexagone_voisins(Plateau* plateau, Vector2 position) {
    vector<Vector2> voisins ;
    auto iterateur = plateau->get_iterateur_debut();
    auto iterateur_fin = plateau->get_iterateur_fin();
    do {
        if (iterateur->first == position) {
            for (int i=0;i<6;i++) {
                if (plateau->hexagone_existe(iterateur->first+PositionContourHexagone[i])) {
                    voisins.push_back( iterateur->first+PositionContourHexagone[i] );
                }
            }
            return voisins;
        }
    } while (++iterateur != iterateur_fin);
    return voisins;
}*/

map<Vector2, Hexagone*> ScoreUtils::get_hexagone_voisins(Plateau* plateau, Vector2 position) {
    map<Vector2, Hexagone*> voisins ;
    auto iterateur = plateau->get_iterateur_debut();
    auto iterateur_fin = plateau->get_iterateur_fin();
    do {
        if (iterateur->first == position) {
            for (int i=0;i<6;i++) {
                if (plateau->hexagone_existe(iterateur->first+PositionContourHexagone[i])) {
                    voisins.insert( {iterateur->first+PositionContourHexagone[i],plateau->obtenir_hexagone(iterateur->first+PositionContourHexagone[i])} );
                }
            }
            return voisins;
        }
    } while (++iterateur != iterateur_fin);
    return voisins;
}



int ScoreUtils::get_largest_voisinnage_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    int compteur=0;
    int tmp=0;
    vector<Vector2> marque;
    auto iterateur = plateau->get_iterateur_debut();
    auto iterateur_fin = plateau->get_iterateur_fin();
    do {
        const auto *h=iterateur->second;
        if (h->get_couleur() == couleur && h->get_type()== type && !find_vector(marque,iterateur->first)) {
            // si c'est le bon hexagone bleu et qu'on est pas deja passé dessus
            tmp+=1;
            marque.push_back(iterateur->first);
            // si element bleu trouvé autour -> on le
            compteur++;
        }
    } while (++iterateur != iterateur_fin);
    for (int i =0;i < marque.size(); i++ ) {
        cout << "x" << to_string( marque[i].x)<< "y" << to_string( marque[i].y)<<endl;
    }
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
    int tmp=0;
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,ROUGE);
    auto quartier_bleu = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, ROUGE);
    for (auto & [pos,hex]:quartier_bleu) {
        //tmp=ScoreUtils::flodd_fill();
        if (tmp>quartier) {quartier=tmp;}
        //flood fill
    }
    return quartier*place;
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
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,ROUGE);
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, ROUGE);
    for (const auto& [pos, hex]:Hex) {
        if (ScoreUtils::get_hexagone_voisins(plateau,pos).size() < 6) {
            quartier+= hex->get_hauteur();
        }
    }
    return quartier*place;
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
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,VIOLET);
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, VIOLET);
    for (const auto& [pos, hex]:Hex) {
        if (ScoreUtils::get_hexagone_voisins(plateau,pos).size() == 6) {
            quartier+= hex->get_hauteur();
        }
    }
    return quartier*place;
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
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,JAUNE);
    bool voisin_jaune = false;
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, JAUNE);
    for (const auto& [pos, hex]:Hex) {
        voisin_jaune = false;
        for (int d=0;d<6;d++) {
            Vector2 position_contour = pos+PositionContourHexagone[d];
            if (plateau->hexagone_existe(position_contour) ) {
                if ((plateau->obtenir_hexagone(position_contour)->get_couleur() == JAUNE) && plateau->obtenir_hexagone(position_contour)->get_type() == TypeHexagone::Quartier) {
                    voisin_jaune = true;
                }
            }
        }
        if (!voisin_jaune) quartier+= hex->get_hauteur();
    }
    return quartier*place;
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
    int tmp=0;
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,ROUGE);
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, ROUGE);
    for (const auto& [pos, hex]:Hex) {
        tmp= 6- ScoreUtils::get_hexagone_voisins(plateau,pos).size();
        if (tmp ==3||tmp==4) {
            quartier+= hex->get_hauteur()*2;
        }
        else if (tmp){
            quartier+= hex->get_hauteur();
        }
    }
    return quartier*place;
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
    int place = get_iteration_filtres(plateau,TypeHexagone::Place,VERT)*3; 
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
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,VIOLET);
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, VIOLET);
    for (const auto& [pos, hex]:Hex) {
        if (ScoreUtils::get_hexagone_voisins(plateau,pos).size() == 6) {
            if (hex->get_hauteur()>1) {
                quartier+= hex->get_hauteur()*2;
            }
            else {
                quartier+= hex->get_hauteur();
            }
        }
    }
    return quartier*place;
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
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,JAUNE);
    bool quartier_voisin_jaune = false;
    bool place_voisin_jaune = false;
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, JAUNE);
    for (const auto& [pos, hex]:Hex) {
        quartier_voisin_jaune = false;
        place_voisin_jaune = false;
        for (int d=0;d<6;d++) {
            Vector2 position_contour = pos+PositionContourHexagone[d];
            if (plateau->hexagone_existe(position_contour) ) {
                if (plateau->obtenir_hexagone(position_contour)->get_couleur() == JAUNE)
                {
                    if ( plateau->obtenir_hexagone(position_contour)->get_type() == TypeHexagone::Quartier) quartier_voisin_jaune = true;
                    else if ( plateau->obtenir_hexagone(position_contour)->get_type() == TypeHexagone::Place) place_voisin_jaune = true;
                }
            }
        }
        if (!quartier_voisin_jaune && place_voisin_jaune ) quartier+= hex->get_hauteur()*2;
        else if (!quartier_voisin_jaune ) quartier+= hex->get_hauteur();
    }
    return quartier*place;
}

int ScoreJauneVariante::score(Plateau* plateau) {
    int s = 0;
    if (scoreDecore) s += scoreDecore->score(plateau);
    s += score_jaune_variante(plateau);
    return s;
}