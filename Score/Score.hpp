#ifndef LO21_PROJET_SCORE_HPP
#define LO21_PROJET_SCORE_HPP

#include "../HexagoneContainer/Plateau.hpp"
#include <set>

//! Classe de Score, utilisée pour calculer le score d'un joueur à partir d'un plateau
/*!
 * Classe de Score, utilisée pour calculer le score d'un joueur à partir d'un plateau
 * Est une classe abstraite, mais également un décorateur.
 */
class Score {
protected:
    //! Le score décoré
    Score* scoreDecore = nullptr;
public:
    Score() {};
    Score(Score* scoreDecore) : scoreDecore(scoreDecore) {}
    virtual ~Score() { free(scoreDecore);}
    //! La fonction de calcul de Score
    virtual int score(Plateau* plateau) {return 0;}
    int owo() {return 1;}
};

//! Décorateur qui implémente le scoring pour l’Illustre architecte Hippodamos (MODE FACILE)
class ScoreSoloArchitecteHippodamos : public Score {
    int score_solo_architechte_hippodamos(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour l’Illustre architecte Metagenes (MODE NORMALE)
class ScoreSoloArchitecteMetagenes : public Score {
    int score_solo_architechte_metagenes(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour l’Illustre architecte Callicrates (MODE DIFFICILE)
class ScoreSoloArchitecteCallicrates : public Score {
    int score_solo_architechte_callicrates(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};


//! Décorateur qui implémente le scoring pour les points Bleus d'un joueur normal
class ScoreBleu : public Score{
    int score_bleu(Plateau* plateau);
public:
    ScoreBleu() : Score() {}
    explicit ScoreBleu(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Rouges d'un joueur normal
class ScoreRouge : public Score {
    int score_rouge(Plateau* plateau);
public:
    ScoreRouge() : Score() {}
    explicit ScoreRouge(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Verts d'un joueur normal
class ScoreVert : public Score{
    int score_vert(Plateau* plateau);
public:
    ScoreVert() : Score() {}
    explicit ScoreVert(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Violets d'un joueur normal
class ScoreViolet : public Score{
    int score_violet(Plateau* plateau);
public:
    ScoreViolet() : Score() {}
    explicit ScoreViolet(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Jaunes d'un joueur normal
class ScoreJaune : public Score{
    int score_jaune(Plateau* plateau);
public:
    ScoreJaune() : Score() {}
    explicit ScoreJaune(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};


//! Décorateur qui implémente le scoring pour les points Bleus d'un joueur avec variante
class ScoreBleuVariante : public Score{
    int score_bleu_variante(Plateau* plateau);
public:
    ScoreBleuVariante() : Score() {}
    explicit ScoreBleuVariante(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Rouges d'un joueur avec variante
class ScoreRougeVariante : public Score{
    int score_rouge_variante(Plateau* plateau);
public:
    ScoreRougeVariante() : Score() {}
    explicit ScoreRougeVariante(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Verts d'un joueur avec variante
class ScoreVertVariante : public Score{
    int score_vert_variante(Plateau* plateau);
public:
    ScoreVertVariante() : Score() {}
    explicit ScoreVertVariante(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Violets d'un joueur avec variante
class ScoreVioletVariante : public Score{
    int score_violet_variante(Plateau* plateau);
public:
    ScoreVioletVariante() : Score() {}
    explicit ScoreVioletVariante(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Jaunes d'un joueur avec variante
class ScoreJauneVariante : public Score{
    int score_jaune_variante(Plateau* plateau);
public:
    ScoreJauneVariante() : Score() {}
    explicit ScoreJauneVariante(Score* scoreDecore) : Score(scoreDecore) {}
    int score (Plateau* plateau) override;
};

//! Ensemble de fonctions utiles au calcul du score
namespace ScoreUtils {
    //! Retourne tous les hexagones dont le type et la couleur correspondent aux critères donnés
    /*!
     * @param plateau Plateau sur lequel effectuer la recherche
     * @param type Type d'hexagone à filtrer
     * @param couleur Couleur d'hexagone à filtrer
     * @return Une map associant la position aux Hexagones filtrées
     */
    map<Vector2, Hexagone*> get_hexagone_filtres(Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur );
    //! Retourne le nombre hexagones dont le type et la couleur correspondent aux critères donnés
    /*!
     * @param plateau Plateau sur lequel effectuer la recherche
     * @param type Type d'hexagone à filtrer
     * @param couleur Couleur d'hexagone à filtrer
     * @return Le nombre d'hexagones filtrées
     */
    int get_iteration_filtres ( Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur);
    //! Retourne l'addition des hauteurs de tous les hexagones dont le type et la couleur correspondent aux critères donnés
    /*!
     * @param plateau Plateau sur lequel effectuer la recherche
     * @param type Type d'hexagone à filtrer
     * @param couleur Couleur d'hexagone à filtrer
     * @return Addition des hauteurs de tous les hexagones filtrées
     */
    int get_iteration_with_hauteur_filtres ( Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur);
    //! Retourne tous les hexagones voisins autour d'une position donnée sur le plateau
    /*!
     * @param plateau Plateau sur lequel effectuer la recherche
     * @param position Position de l'hexagone dont on veut obtenir les voisins
     * @return Une map associant chaque position voisine à un pointeur vers l'hexagone correspondant.
     */
    map<Vector2, Hexagone*> get_hexagone_voisins(Plateau* plateau, Vector2 position) ;
    //! Retourne tous les hexagones composant le plus grand voisinnage sur le plateau
    /*!
     * @param plateau Plateau sur lequel effectuer la recherche
     * @param type Type d'hexagone à filtrer
     * @param couleur Couleur d'hexagone à filtrer
     * @return Une map des hexagones du plus grand voisinnage
     */
    std::map<Vector2, Hexagone*> get_largest_hexagone_voisinnage_filtres( Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur);
    //! Retourne tous les hexagones voisinage en partant d'un hexagone (recursivement)
    /*!
    * @param selection Les hexagones sur lequels on effectue la recherche
     * @param visite Positions déjà visitées
     * @param positionDepart Point de départ de l'exploration
     * @return Groupe connecté d'hexagones
     */
    std::map<Vector2, Hexagone*> flood_fill_collect(const std::map<Vector2, Hexagone*>& selection,set<Vector2>& visite,const Vector2& positionDepart);
    //! Retourne la somme des hauteurs d'une map d'hexagones
    /*!
     * @param m map associant Vector2 (position) et Hexagone* sur lequel on va iterer
     * @return Un entier, la somme des hauteurs de tous les hexagones
     */
    int sum_heights( std::map<Vector2, Hexagone*> m);
    //! Colcule le nombre de Quartiers et de Places par couleur
    /*!
     * @param plateau Pointeur vers le plateau à analyser.
     * @return Une structure StatsCouleursSoloArchitecte composée des compteur de quartiers et de place pour chque couleur
     */
    StatsCouleursSoloArchitecte compteur_couleur(Plateau* plateau);

};

//! Responsable de la création du score simple pour les joueurs
Score* getScoreSimple();

//! Responsable de la création du score avancé pour les joueurs
Score* getScoreVariante();

#endif //LO21_PROJET_SCORE_HPP