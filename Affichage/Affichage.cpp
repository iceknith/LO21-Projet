#include "Affichage.hpp"
using namespace constAffichageConsoleHex;

// Création de l'instance d'affichage
AffichageConsole* AffichageConsole::instance = nullptr;


// Affichage console //

// L'affichage se fera sous la forme
//  /1 1 1\
// /1 Mar-1\
// \1-ché 1/3 3 3\
//  \1 1 1/3Carr-3\
//  /2 2 2\3-iere3/
// /2Place2\3 3 3/
// \2     2/
//  \2 2 2/

// Ou (si dans une tuile unie)
//  /1 1 1\
// /1 Mar-1\
// \1-ché   1 1 1\
//  \1      Carr-1\
//  /1      -iere1/
// /1Place  1 1 1/
// \1     1/
//  \1 1 1/

void AffichageConsole::affiche_container(HexagoneContainer& container, bool selectHexagone, Vector2 selectedHexagone) {
    Vector2 posInit = axialToScreen(selectHexagone ? selectedHexagone : container.begin()->first);
    Vector2 posFin = posInit;
    float highestVectX = posInit.x;

    for (auto iter : container) {
        Vector2 pos = axialToScreen(iter.first);

        if (pos.x < posInit.x) posInit.x = pos.x;
        else if (pos.x > posFin.x) posFin.x = pos.x;

        if (pos.y < posInit.y) {
            posInit.y = pos.y;
            highestVectX = pos.x;
        }
        else if (pos.y > posFin.y) posFin.y = pos.y;
    }

    // tableau "canvas" de caractères (assez grand pour plusieurs hex)
    size_t largeur = (posFin.x - posInit.x) + largeurHex;
    size_t hauteur = (posFin.y - posInit.y) + hauteurHex;
    vector<string> canvas(hauteur);

    // Initialisation des valeurs du tableau, et insertion de balises de couleurs, pour assurer un alignement
    string emptyLineB{};
    string emptyLineS{" "};
    for (int i = 0; i < largeur/emptyHexLineB.size(); i++) {
        emptyLineB += emptyHexLineB;
        emptyLineS += emptyHexLineS;
    }
    emptyLineS += " ";
    emptyLineB += " ";

    //Optention de la parité de l'affichage
    int parite = static_cast<int>(2 * (highestVectX - posInit.x) / largeurHex) % 2;
    for (int i = 0; i < hauteur; i += 1) {
        // Si la parite est à 0, alors les petites lignes sont aux indices 0 et 3, sinon ils sont aux indices 1 et 2.
        if (i%4 == parite || i%4 == 3 - parite) canvas[i] = emptyLineS;
        else canvas[i] = emptyLineB;
    }

    // Affichage de chaque carreau
    bool selectedHexEstAffiche = false;
    for (auto iter : container) {
        Vector2 pos = axialToScreen(iter.first) - posInit;
        bool highlighted = selectHexagone && selectedHexagone == iter.first;
        if (highlighted) selectedHexEstAffiche = true;
        vector<string> affichageHex = iter.second->affiche_console(highlighted);

        /*
        canvas[pos.y].replace(pos.x+decalagePetiteLigne, affichageHex[0].size(), affichageHex[0]);
        canvas[pos.y+1].replace(pos.x, affichageHex[1].size(), affichageHex[1]);
        canvas[pos.y+2].replace(pos.x, affichageHex[2].size(), affichageHex[2]);
        canvas[pos.y+3].replace(pos.x+decalagePetiteLigne, affichageHex[3].size(), affichageHex[3]);
         */
        replace_sauf_charactere(canvas[pos.y], pos.x+decalagePetiteLigne, affichageHex[0].size(), affichageHex[0], ' ');
        replace_sauf_charactere(canvas[pos.y+1], pos.x, affichageHex[1].size(), affichageHex[1], ' ');
        replace_sauf_charactere(canvas[pos.y+2], pos.x, affichageHex[2].size(), affichageHex[2], ' ');
        replace_sauf_charactere(canvas[pos.y+3], pos.x+decalagePetiteLigne, affichageHex[3].size(), affichageHex[3], ' ');
    }

    //Affichage de l'hexagone séléctionné, si il n'as pas encore été affiché
    if (selectHexagone && !selectedHexEstAffiche) {
        Vector2 pos = axialToScreen(selectedHexagone) - posInit;
        canvas[pos.y].replace(pos.x+decalagePetiteLigne, emptySelectedHex[0].size(), emptySelectedHex[0]);
        canvas[pos.y+1].replace(pos.x, emptySelectedHex[1].size(), emptySelectedHex[1]);
        canvas[pos.y+2].replace(pos.x, emptySelectedHex[2].size(), emptySelectedHex[2]);
        canvas[pos.y+3].replace(pos.x+decalagePetiteLigne, emptySelectedHex[3].size(), emptySelectedHex[3]);
    }

    // Affichage final
    for (auto &line : canvas) {
        cout << couleurConsoleOutline; // On mets la console à la bonne couleur
        cout << line << endl;
    }
}

void AffichageConsole::affiche_joueur(Joueur &joueur, bool selectHexagone, Vector2 selectedHexagone) {
    cout << "\033[0;97mPlateau de " << joueur.getNomJoueur() << endl;
    affiche_container(joueur.get_plateau(), selectHexagone, selectedHexagone);
    cout << "\033[0;37m " << joueur.get_pierre() << " pierre(s)" << endl;
}

Vector2 constAffichageConsoleHex::axialToScreen(Vector2 v) {
    float col = v.x / 2 * largeurHex;
    float ligne = (v.y + v.x / 2) * hauteurHex;
    return Vector2{col, ligne};
}

void constAffichageConsoleHex::replace_sauf_charactere(string &text_original, size_t pos, size_t len,
                                                    const std::string &text_nouveau, char charactere_non_remplace)  {
    size_t endSize = min(text_original.length(), pos + min(len, text_nouveau.size()));
    for (size_t i = pos; i < endSize; i++){
        if (text_nouveau[i - pos] != charactere_non_remplace){
            text_original[i] = text_nouveau[i - pos];
        }
    }
}

// Affichage graphique //

void AffichageGUI::affiche_joueur(Joueur &joueur, bool selectHexagone, Vector2 selectedHexagone) {
    affiche_container(joueur.get_plateau(), false, Vector2());
    if (labelNom) labelNom->setText("Plateau de: " + QString::fromStdString(joueur.getNomJoueur()));
    if (labelScore) labelScore->setText("Score Actuel: " + QString::number(joueur.get_score()));
    if (labelPierre) labelPierre->setText("Pierre(s): " + QString::number(joueur.get_pierre()));
}

void AffichageGUI::affiche_container(HexagoneContainer &container, bool selectHexagone, Vector2 selectedHexagone) {
    // On ne peut rien afficher si la map de scene est nulle
    if (sceneMap == nullptr) return;
    sceneMap->clear(); // On efface tout l'ancien affichage

    //boucle de dessin
    for (const auto& iter : container) {
        QPointF pos = constAffichageGraphiqueeHex::axialToScreen(iter.first);
        HexagoneGUIObjet* guiHex = iter.second->affiche_gui();
        guiHex->setPos(pos);
        sceneMap->addItem(guiHex);
    }
}

QPointF constAffichageGraphiqueeHex::axialToScreen (Vector2 v) {
    float largeurGUI = GUIConstants::HEX_SIZE * 3;
    float hauteurGUI = GUIConstants::HEX_SIZE * 2 * 0.866; // Car le ratio rayon/hauteur est de 0.866 * 2

    float x = v.x / 2 * largeurGUI;
    float y = (v.y + v.x / 2) * hauteurGUI;
    return QPointF{x, y};
}