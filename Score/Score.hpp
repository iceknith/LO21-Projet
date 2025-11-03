#ifndef LO21_PROJET_SCORE_HPP
#define LO21_PROJET_SCORE_HPP

#include "../Players/Plateau.hpp"
#include <set>

//! Classe de Score, utilisée pour calculer le score d'un joueur à partir d'un plateau
/*!
 * Classe de Score, utilisée pour calculer le score d'un joueur à partir d'un plateau
 * Est une classe abstraite, mais également un décorateur.
 */
class Score {
protected:
    //! Le score décoré
    Score * scoreDecore = nullptr;
public:
    Score() = default;
    Score(Score* scoreDecore) : scoreDecore(scoreDecore) {}
    virtual ~Score() = default;
    //! La fonction de calcul de Score
    virtual int score(Plateau* plateau) {return 0;}
};

//! Classe de Score de l'Illustre Architechte, utilisée pour calculer le score de l'Illustre Architechte à partir d'un plateau
/*!
 * Classe de Score de l'Illustre Architechte, utilisée pour calculer le score de l'Illustre Architechte à partir d'un plateau
 * Est une classe abstraite, mais également un décorateur.
 */
class ScoreSoloArchitechte : public Score {
protected:
    //! Le niveau de l'Illustre Architechte, sera utilisé pour calculer son score
    int niveau = 0;
public:
    //! Le setteur de niveau de l'Illustre Architechte
    virtual void set_niveau(int niveau);
    //! Le getteur de niveau de l'Illustre Architechte
    int get_niveau();
};

//! Décorateur qui implémente le scoring pour les points Bleus de l'Illustre Architechte
class ScoreSoloArchitechteBleu : public ScoreSoloArchitechte {
    int score_bleu(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Rouges de l'Illustre Architechte
class ScoreSoloArchitechteRouge : public ScoreSoloArchitechte {
    int score_rouge(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Jaunes de l'Illustre Architechte
class ScoreSoloArchitechteJaune : public ScoreSoloArchitechte {
    int score_jaune(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Verts de l'Illustre Architechte
class ScoreSoloArchitechteVert : public ScoreSoloArchitechte {
    int score_vert(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Violets de l'Illustre Architechte
class ScoreSoloArchitechteViolet : public ScoreSoloArchitechte {
    int score_violet(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Bleus d'un joueur normal
class ScoreBleu : public Score{
    int score_bleu(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Rouges d'un joueur normal
class ScoreRouge : public Score{
    int score_rouge(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Verts d'un joueur normal
class ScoreVert : public Score{
    int score_vert(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Violets d'un joueur normal
class ScoreViolet : public Score{
    int score_violet(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Jaunes d'un joueur normal
class ScoreJaune : public Score{
    int score_jaune(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};


//! Décorateur qui implémente le scoring pour les points Bleus d'un joueur avec variante
class ScoreBleuVariante : public Score{
    int score_bleu_variante(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Rouges d'un joueur avec variante
class ScoreRougeVariante : public Score{
    int score_rouge_variante(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Verts d'un joueur avec variante
class ScoreVertVariante : public Score{
    int score_vert_variante(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Violets d'un joueur avec variante
class ScoreVioletVariante : public Score{
    int score_violet_variante(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

//! Décorateur qui implémente le scoring pour les points Jaunes d'un joueur avec variante
class ScoreJauneVariante : public Score{
    int score_jaune_variante(Plateau* plateau);
public:
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
    //! Retourne la somme des hauteurs d'une map d'hexagones
    /*!
     * @param m map associant Vector2 (position) et Hexagone* sur lequel on va iterer
     * @return Un entier, la somme des hauteurs de tous les hexagones
     */
    int sum_heights( std::map<Vector2, Hexagone*> m);

    std::map<Vector2, Hexagone*> flood_fill_collect(const std::map<Vector2, Hexagone*>& selection,set<Vector2>& visite,const Vector2& positionDepart);
};


#endif //LO21_PROJET_SCORE_HPP