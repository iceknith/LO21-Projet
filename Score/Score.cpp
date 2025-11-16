#include "Score.hpp"

using namespace ScoreUtils;

map<Vector2, Hexagone*> ScoreUtils::get_hexagone_filtres(Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur ){
    std::map<Vector2, Hexagone*> result;
    for (auto iterateur = plateau->get_iterateur_debut(); iterateur != plateau->get_iterateur_fin(); ++iterateur) {
        Hexagone* h = iterateur->second;
        if (h->get_type() == type && h->get_couleur() == couleur) {
            result.emplace(iterateur->first, h);
        }
    }
    return result;
}

int ScoreUtils::get_iteration_filtres(Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    int result = 0;
    for (auto iterateur = plateau->get_iterateur_debut(); iterateur != plateau->get_iterateur_fin(); ++iterateur) {
        Hexagone* h = iterateur->second;
        if (h->get_type() == type && h->get_couleur() == couleur) {
            result++;
        }
    }
    return result;
}

int ScoreUtils::get_iteration_with_hauteur_filtres ( Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) {
    int iteration = 0;
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, type, couleur);
    for (auto& [pos,hex] : Hex) {
        iteration+= hex->get_hauteur();
    }
    return iteration;
}

map<Vector2, Hexagone*> ScoreUtils::get_hexagone_voisins( Plateau* plateau, Vector2 position) {
    std::map<Vector2, Hexagone*> voisins;
    for (int i = 0; i < GameConstants::HEXAGON_DIRECTIONS; ++i) {
        Vector2 npos = position + adjascenceHex[i];
        if (plateau->hexagone_existe(npos))
            voisins.emplace(npos, plateau->obtenir_hexagone(npos));
    }
    return voisins;
}

std::map<Vector2, Hexagone*> ScoreUtils::flood_fill_collect(const std::map<Vector2, Hexagone*>& selection,std::set<Vector2>& visite,const Vector2& positionDepart)
{
    std::map<Vector2, Hexagone*> voisinnage;
    //  Si cette position a déjà été visitée, on retourne un groupe vide (evite boucle infinie)
    if (visite.find(positionDepart) != visite.end()) {
        return voisinnage;
    }
    visite.insert(positionDepart); //Marque cette position comme visitée
    voisinnage[positionDepart] = selection.at(positionDepart);

    // Explore recursivement les directions autour
    for (int d = 0; d < GameConstants::MAX_HEXAGON_NEIGHBORS; ++d) {
        Vector2 npos = positionDepart + adjascenceHex[d];
        if (selection.find(npos) != selection.end() && visite.find(npos) == visite.end()) {
            auto recursion = flood_fill_collect(selection, visite, npos);
            voisinnage.insert(recursion.begin(), recursion.end());
        }
    }
    return voisinnage;
}

std::map<Vector2, Hexagone*> ScoreUtils::get_largest_hexagone_voisinnage_filtres( Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur)
{
    auto selection = get_hexagone_filtres(plateau, type, couleur);
    std::set<Vector2> visite;

    //On suit les positions déjà visitées
    std::map<Vector2, Hexagone*> meilleurVoisinnage;

    for (const auto& [pos, hex] : selection) {
        // Si cette position a déjà été visitée
        if (visite.find(pos) == visite.end()) {
            // Sur chaque hexagone qui n'est pas deja visité, on va calculer la taille de son voisinnage
            auto test = flood_fill_collect(selection, visite, pos);
            if (test.size() > meilleurVoisinnage.size()) {
                meilleurVoisinnage = std::move(test);
            }
        }
    }
    return meilleurVoisinnage;
}

int ScoreUtils::sum_heights( std::map<Vector2, Hexagone*> m) {
    int resultat=0;
    for (const auto& [pos, hex]:m) {
        resultat+= hex->get_hauteur();
    }
    return resultat;
}

StatsCouleursSoloArchitecte ScoreUtils::compteur_couleur(Plateau* plateau) {
    StatsCouleursSoloArchitecte stats;

    for (auto iterateur = plateau->get_iterateur_debut(); iterateur != plateau->get_iterateur_fin(); ++iterateur) {
        Hexagone* h = iterateur->second;
        int c = static_cast<int>(h->get_couleur());
        if (h->get_type()==TypeHexagone::Quartier) stats.quartiers[c]++;
        if (h->get_type()==TypeHexagone::Place ) {
            if (c == static_cast<int>(CouleursAkropolis::BLANC))stats.places[c]++;
            else if (c == static_cast<int>(CouleursAkropolis::VERT))stats.places[c]+=3;
            else stats.places[c]+=2;
        }
    }
    return stats;
}
// =======================
// Illustre architecte - FACILE - NORMALE - DIFFICILE

int ScoreSoloArchitecteHippodamos::score_solo_architechte_hippodamos(Plateau* plateau) {
    // Règle FACILE :pour chaque couleur: score = nombre quartiers * nombre de places
    // exeption : la couleur blanche (car il s'agit de carrières) ne compte pas.
    // Tous les hexagones partagent la meme hauteur = 1
    auto stats = compteur_couleur(plateau);
    int resultat = 0;
    for (int i =0;i< GameConstants::MAX_COULEUR;i++) {
        if (static_cast<CouleursAkropolis>(i) != CouleursAkropolis::BLANC) {
            resultat += stats.quartiers[i]*stats.places[i];
        }
    }
    return resultat;
}

int ScoreSoloArchitecteMetagenes::score_solo_architechte_metagenes(Plateau* plateau) {
    // Règle NORMALE :pour chaque couleur: score = nombre quartiers * nombre de places + nombre de carrières * 2
    // Tous les hexagones partagent la meme hauteur = 1
    auto stats = compteur_couleur(plateau);
    int resultat = 0;
    for (int i =0;i< GameConstants::MAX_COULEUR;i++) {
        if (static_cast<CouleursAkropolis>(i) != CouleursAkropolis::BLANC) {
            resultat += stats.quartiers[i]*stats.places[i];
        }
        else {
            resultat += stats.quartiers[i]*2;
        }
    }
    return resultat;
}

int ScoreSoloArchitecteBleuCallicrates::score_solo_architechte_callicrates(Plateau* plateau) {
    // Règle NORMALE :pour chaque couleur: score = nombre quartiers * nombre de places
    // Tous les hexagones partagent la meme hauteur = 2
    auto stats = compteur_couleur(plateau);
    int resultat = 0;
    for (int i =0;i< GameConstants::MAX_COULEUR;i++) {
        if (static_cast<CouleursAkropolis>(i) != CouleursAkropolis::BLANC) {
            resultat += stats.quartiers[i]*stats.places[i]*2;
        }
    }
    return resultat;
}

// =======================
// ScoreBleu

int ScoreBleu::score_bleu(Plateau* plateau) {
    // Règle bleue : (somme des hauteurs du plus grand groupe de quartiers bleus) * (nombre de places bleues)
    int quartier = ScoreUtils::sum_heights(ScoreUtils::get_largest_hexagone_voisinnage_filtres(plateau,TypeHexagone::Quartier,CouleursAkropolis::BLEU));
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::BLEU);
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
    // Règle rouge : (somme des hauteurs des quartiers rouges adjacents au vide) * (nombre de places rouges)
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::ROUGE);
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, CouleursAkropolis::ROUGE);
    for (const auto& [pos, hex]:Hex) {
        if (ScoreUtils::get_hexagone_voisins(plateau,pos).size() < GameConstants::MAX_HEXAGON_NEIGHBORS) {
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
    // Règle vert : (somme des hauteurs des quartiers verts) * (nombre de places vertes * 3)
    int place = ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::VERT)*GameConstants::VERT_PLACE_MULTIPLIER;
    int quartier = ScoreUtils::get_iteration_with_hauteur_filtres(plateau,TypeHexagone::Quartier,CouleursAkropolis::VERT);
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
    // Règle violet : (somme des hauteurs des quartiers violets non adjacents au vide) * (nombre de places violets)
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::VIOLET);
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, CouleursAkropolis::VIOLET);
    for (const auto& [pos, hex]:Hex) {
        if (ScoreUtils::get_hexagone_voisins(plateau,pos).size() == GameConstants::MAX_HEXAGON_NEIGHBORS) {
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
    // Règle jaune : (somme des hauteurs des quartiers jaunes non adjacents à un autre quartier jaune) * (nombre de places jaunes)
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::JAUNE);
    bool voisin_jaune = false;
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, CouleursAkropolis::JAUNE);
    for (const auto& [pos, hex]:Hex) {
        voisin_jaune = false;
        for(int d=0;d<GameConstants::MAX_HEXAGON_NEIGHBORS;d++) {
            Vector2 position_contour = pos+adjascenceHex[d];
            if (plateau->hexagone_existe(position_contour) ) {
                if ((plateau->obtenir_hexagone(position_contour)->get_couleur() == CouleursAkropolis::JAUNE) && plateau->obtenir_hexagone(position_contour)->get_type() == TypeHexagone::Quartier) {
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
    // Règle bleueVariante : (somme des hauteurs du plus grand groupe de quartiers bleus) * (nombre de places bleues) * (2 si ce plus grand groupe de quartiers bleus >= 10)
    int quartier =0;
    auto voisinnage = ScoreUtils::get_largest_hexagone_voisinnage_filtres(plateau,TypeHexagone::Quartier,CouleursAkropolis::BLEU);
    quartier = sum_heights(voisinnage);
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::BLEU);
    if (voisinnage.size() >=GameConstants::BLEU_VARIANTE_BONUS_THRESHOLD){return quartier*place*GameConstants::BLEU_VARIANTE_BONUS_MULTIPLIER;}
    return quartier*place;
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
    // Règle rougeVariante : (somme des hauteurs des quartiers rouges adjacents au vide (*2 sur hauteur si le quartier rouge est adjacent à 3 ou 4 vide ) ) * (nombre de places rouges)
    int tmp=0;
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::ROUGE);
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, CouleursAkropolis::ROUGE);
    for (const auto& [pos, hex]:Hex) {
        //tmp correspond au nombre de place vide (place vide = 6 - place occupés)
        tmp= GameConstants::MAX_HEXAGON_NEIGHBORS- ScoreUtils::get_hexagone_voisins(plateau,pos).size();
        //si 3 ou 4 places vides: bonus *2 sinon calcul score normale
        if (tmp ==GameConstants::ROUGE_VARIANTE_BONUS_MIN_EDGES||tmp==GameConstants::ROUGE_VARIANTE_BONUS_MAX_EDGES) {
            quartier+= hex->get_hauteur()*GameConstants::ROUGE_VARIANTE_BONUS_MULTIPLIER;
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
    // Règle vertVariante : (somme des hauteurs des quartiers verts (*2 si quartier vert est adjacent à un espace vide entouré ) ) * (nombre de places vertes * 3)
    // TODO : implementer regle vert variante
    // en attendant: uniquement regle de base
    int place = get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::VERT)*GameConstants::VERT_PLACE_MULTIPLIER;
    int quartier = get_iteration_with_hauteur_filtres(plateau,TypeHexagone::Quartier,CouleursAkropolis::VERT);
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
    // Règle violetVariante : (somme des hauteurs des quartiers violets non adjacents au vide (*2 si le quartier à une hauteur > 1 ) ) * (nombre de places violets)
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::VIOLET);
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, CouleursAkropolis::VIOLET);
    for (const auto& [pos, hex]:Hex) {
        if (ScoreUtils::get_hexagone_voisins(plateau,pos).size() == GameConstants::MAX_HEXAGON_NEIGHBORS) {
            // Si hauteur du quartier >1, bonus *2 sinon calcul normale
            if (hex->get_hauteur()>GameConstants::VIOLET_VARIANTE_HAUTEUR_THRESHOLD) {
                quartier+= hex->get_hauteur()*GameConstants::VIOLET_VARIANTE_BONUS_MULTIPLIER;
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
    // Règle jauneVariante : (somme des hauteurs des quartiers jaunes non adjacents à un autre quartier jaune (*2 si le quartier est adjacent à une place jaune) ) * (nombre de places jaunes)
    int quartier = 0;
    int place =  ScoreUtils::get_iteration_filtres(plateau,TypeHexagone::Place,CouleursAkropolis::JAUNE);
    bool quartier_voisin_jaune,place_voisin_jaune = false;
    auto Hex = ScoreUtils::get_hexagone_filtres(plateau, TypeHexagone::Quartier, CouleursAkropolis::JAUNE);
    for (const auto& [pos, hex]:Hex) {
        quartier_voisin_jaune = false;
        place_voisin_jaune = false;
        for (int d=0;d<GameConstants::MAX_HEXAGON_NEIGHBORS;d++) {
            Vector2 position_contour = pos+adjascenceHex[d];
            if (plateau->hexagone_existe(position_contour)) {
                if (plateau->obtenir_hexagone(position_contour)->get_couleur() == CouleursAkropolis::JAUNE)
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