//
// Created by Ethann Pencole on 27/09/2025.
//

#ifndef LO21_PROJET_SCORE_HPP
#define LO21_PROJET_SCORE_HPP

class Plateau{};

class Score {
protected:
    Score * scoreDecore = nullptr;
public:
    virtual ~Score() = default;
    virtual int score (Plateau* plateau) = 0;
};

class ScoreSoloArchitechte : public Score {
protected:
    int niveau = 0;
public:
    virtual void set_niveau(int niveau);
    int get_niveau();
};


class ScoreSoloArchitechteBleu : public ScoreSoloArchitechte {
    int score_bleu(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

class ScoreSoloArchitechteRouge : public ScoreSoloArchitechte {
    int score_rouge(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

class ScoreSoloArchitechteJaune : public ScoreSoloArchitechte {
    int score_jaune(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

class ScoreSoloArchitechteVert : public ScoreSoloArchitechte {
    int score_vert(Plateau* plateau);
public:
    int score(Plateau* plateau) override;
};

class ScoreBleu : public Score{
    int score_bleu(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

class ScoreRouge : public Score{
    int score_rouge(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

class ScoreVert : public Score{
    int score_vert(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

class ScoreJaune : public Score{
    int score_jaune(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};


class ScoreBleuVariante : public Score{
    int score_bleu_variante(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

class ScoreRougeVariante : public Score{
    int score_rouge_variante(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

class ScoreVertVariante : public Score{
    int score_vert_variante(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};

class ScoreJauneVariante : public Score{
    int score_jaune_variante(Plateau* plateau);
public:
    int score (Plateau* plateau) override;
};


#endif //LO21_PROJET_SCORE_HPP