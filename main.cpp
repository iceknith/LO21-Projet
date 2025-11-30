// Décommenter cette ligne pour la release (pour que les tests ne s'executent pas)
// #define NDEBUG

#include "main.hpp"
#include "Tests/Tests.hpp"
#include "GUI/GUI.hpp"

int main(int argc, char *argv[]) {


    QApplication app(argc, argv);

    Application game;



    game.resize(1024, 768);


    game.show();
    return app.exec();


    JeuConsole::getJeu()->gameLoop();
    assertTests();

    return 0;


}