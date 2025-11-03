#include "Tests.hpp"
#include <iostream>
#include "../Players/Plateau.hpp"
void assertTests(){
    /*
     * Insérer des asserts sous la forme suivante :
     *
     *  // --- Nom de classe --- //
     *  // - Nom de fonction - //
     *  // Objectif du test
     *  assert(test);
     *
     * OU
     * (pour les classes qui ont déjà une batterie de tests inclue)
     * // --- Nom de classe --- //
     * NomDeClasse.fonctionBatterieDeTest()
     */
}


void test_ScoreBleu() {
    std::cout << "=== Test ScoreBleu ===" << std::endl;
    std::cout << "Calcul du score bleu, test plateau vide et test avec exemple:" << std::endl;


    // Test avec plateau vide
    //int scoreVide = scoreBleu.score(plateau);
    //assert(scoreVide == 0);

    // Test avec un quartier bleu simple


    std::cout << "ScoreBleu tests passed" << std::endl;
}

void test_ScoreRouge() {
    std::cout << "=== Test ScoreRouge ===" << std::endl;

}

void test_ScoreVert() {
    std::cout << "=== Test ScoreVert ===" << std::endl;

}


void assertTestsScore(){
    std::cout << "Début des tests:" << std::endl;

    try {
        test_ScoreBleu();
        test_ScoreRouge();
        test_ScoreVert();

        std::cout << "Tous les tests sont passés avec succès" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test échoué: " << e.what() << std::endl;
        throw;
    }
}