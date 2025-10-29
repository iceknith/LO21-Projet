#ifndef LO21_PROJET_SCORE_HPP
#define LO21_PROJET_SCORE_HPP

#include "../Players/Plateau.hpp"

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
ScoreVert(Score* s) : Score(s) {}

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

    int get_iteration_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur);

    int get_iteration_with_hauteur_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur);

    //std::vector<Hexagone*> get_hexagones_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur);

    int get_largest_voisinnage_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur) ;

    //std::vector<Vector2> get_hexagones_coordonates_filtres (Plateau* plateau, TypeHexagone type, CouleursAkropolis couleur)



    //int plusLongVolume(plateau)

    //hex** verifi contour(map et coordones)

    //entouré?




};


#endif //LO21_PROJET_SCORE_HPP