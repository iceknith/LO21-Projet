// Décommenter cette ligne pour la release (pour que les tests ne s'executent pas)
// #define NDEBUG

#include "main.hpp"
#include "Tests/Tests.hpp"
using namespace std;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 1. Création de la fenêtre
    MainWindow window;
    window.resize(1200, 800);
    window.show();
    return app.exec();
    // 2. Initialisation du Jeu avec la fenêtre
    Jeu* jeu = JeuGUI::getJeu(&window);

    // 3. Lancement de la GameLoop APRÈS le démarrage de l'app
    QTimer::singleShot(100, [jeu](){
        jeu->gameLoop(); // Ceci va appeler titleScreen() -> attendre le clic -> lancer le jeu
    });

    return app.exec();
    /*
    QApplication app(argc, argv);
    // MA SCENE
    QGraphicsScene scene;


    constGUI::backgroundMap(10,&scene);

    //---------------------
    // MA VUE = camera
    CameraMap VUE(&scene);
    VUE.resize(800,800);
    VUE.show();

    return app.exec();*/
}



    /*
int main() {
    assertTests();
    JeuConsole::getJeu()->gameLoop();
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
