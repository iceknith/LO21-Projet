// Décommenter cette ligne pour la release (pour que les tests ne s'executent pas)
// #define NDEBUG

#include "main.hpp"
#include "Tests/Tests.hpp"
using namespace std;


int main(int argc, char *argv[]) {
    try{
        JeuConsole::getJeu()->gameLoop(argc, argv);
        //JeuGUI::getJeu()->gameLoop(argc, argv);
    } catch (AkropolisException e) {
        cout << e.get_info() << "\n";
    }
}
    /*
int main() {
    assertTests();
*/

    /*
    Deck d{3};
    Affichage* a = new AffichageConsole();
    for(size_t i = 0; i < d.get_taille(); i++) a->affiche_container(*d.getTuiles()[i]);



    cout << "------------------------------";

    SerializationContext s2{};
    QFile file2{"output.dat"};
    if (file2.open(QIODevice::ReadOnly)) {
        QDataStream in(&file2);
        in >> s2;
        file2.close();
    }

    Deck d2 = *dynamic_cast<Deck*>(s2.deserialize(0));
    for(size_t i = 0; i < d.get_taille(); i++) a->affiche_container(*d2.getTuiles()[i]);

    return 0;*/
