// Décommenter cette ligne pour la release (pour que les tests ne s'executent pas)
// #define NDEBUG

#include <iostream>
#include "main.hpp"
#include "Tests/Tests.hpp"
using namespace std;

int main() {
    assertTests();

    return 0;
}