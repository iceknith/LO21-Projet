#ifndef LO21_PROJET_AFFICHAGE_HPP
#define LO21_PROJET_AFFICHAGE_HPP

#include "../Utils.hpp"
#include "../Players/Players.hpp"
#include "../GUI/GUI.hpp"
#include <vector>

// Affichage //

class Affichage {
protected:
    virtual void affiche_joueur(Joueur& joueur, bool selectHexagone, Vector2 selectedHexagone) = 0;
    virtual void affiche_container(HexagoneContainer& container, bool selectHexagone, Vector2 selectedHexagone) = 0;

public:
    void affiche_container(HexagoneContainer& container) { affiche_container(container, false, Vector2());};
    void affiche_container(HexagoneContainer& container, Vector2 selectedHexagone) {affiche_container(container, true, selectedHexagone);};
    void affiche_joueur(Joueur& joueur) { affiche_joueur(joueur, false, Vector2());};
    void affiche_joueur(Joueur& joueur, Vector2 selectedHexagone) { affiche_joueur(joueur, true, selectedHexagone);};

    virtual ~Affichage() = default;

};

// Affichage console //

class AffichageConsole : public Affichage{
    AffichageConsole() = default;
    static AffichageConsole* instance;

protected:
    void affiche_joueur(Joueur& joueur, bool selectHexagone, Vector2 selectedHexagone) override;
    void affiche_container(HexagoneContainer& hexagoneContainer, bool selectHexagone, Vector2 selectedHexagone) override;

public:
    static AffichageConsole* getInstance() {
        if (instance == nullptr) instance = new AffichageConsole();
        return instance;
    }
};

//! Ensemble de fonctions utiles à l'affichage console
namespace constAffichageConsoleHex {
    //! Implémente replace, sauf qu'il 'skip' les charactères identiques à charactere_non_remplace
    /*!
     *
     * @param text_original Le texte d'où on va remplacer des choses
     * @param pos La position du remplacement
     * @param len La taille du remplacement
     * @param text_nouveau Le texte avec lequel on remplace
     * @param charactere_non_remplace Le charactère qui ne remplacera pas le texte_original
     */
    void replace_sauf_charactere(string& text_original, size_t pos, size_t len,
                                 const string& text_nouveau, char charactere_non_remplace);

    const int hexH = 5; // lignes
    const int hexW = 9; // colonnes

    //! Convertion entre les coordonées axiales et les coordonées de l'écran
    Vector2 axialToScreen (Vector2 v);
}

// Affichage graphique //

class AffichageGUI : public Affichage {
private:
    QGraphicsScene* sceneMap = nullptr;
    QLabel* labelNom = nullptr;
    QLabel* labelScore = nullptr;
    QLabel* labelPierre = nullptr;

protected:
    void affiche_joueur(Joueur& joueur, bool selectHexagone, Vector2 selectedHexagone) override;
    void affiche_container(HexagoneContainer& container, bool selectHexagone, Vector2 selectedHexagone) override;

public:
    AffichageGUI() = default;
    AffichageGUI(QGraphicsScene* newSceneMap) : sceneMap(newSceneMap) {};
    AffichageGUI(QGraphicsScene* sceneMap, QLabel* labelNom, QLabel* labelScore, QLabel* labelPierre)
        : sceneMap(sceneMap), labelScore(labelScore), labelNom(labelNom), labelPierre(labelPierre) {};
    QGraphicsItemGroup* getContainerGraphicsItem(HexagoneContainer& container);

    void clearAffichage() {if (sceneMap) sceneMap->clear();}

    void setSceneMap(QGraphicsScene* newSceneMap) {sceneMap = newSceneMap;}
    void setLabelNom(QLabel* newlabelNom) {labelNom = newlabelNom;}
    void setLabelScore(QLabel* newlabelScore) {labelScore = newlabelScore;}
    void setLabelPierre(QLabel* newlabelPierre) {labelPierre = newlabelPierre;}
};

//! Ensemble de fonctions utiles à l'affichage console
namespace constAffichageGraphiqueHex {
    //! Convertion entre les coordonées axiales et les coordonées de l'écran
    QPointF axialToScreen (Vector2 v);
    Vector2 screenToAxial (QPointF pos);
}

#endif //LO21_PROJET_AFFICHAGE_HPP
