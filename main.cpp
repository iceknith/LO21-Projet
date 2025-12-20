// Décommenter cette ligne pour la release (pour que les tests ne s'executent pas)
// #define NDEBUG

#include "main.hpp"
#include "Tests/Tests.hpp"
using namespace std;


int main(int argc, char *argv[]) {
    try{
        string versionProgramme;
        cout << "\033[0;97mQuel version du programme voulez-vous lancer ? " << endl
             << "CONSOLE ( c ) / GRAPHIQUE ( g )" << endl
             << "\033[0;37m-> \033[0;97m";
        cin >> versionProgramme;

        while (cin.fail() || (versionProgramme != "c" && versionProgramme != "g")) {
            cout << "\033[1;31mIl n'y as que deux versions du programme: CONSOLE ( c ) / GRAPHIQUE ( g ) !"
                 << endl << "\033[0;37m-> \033[0;97m";
            // Enlève l'état d'erreur
            cin.clear();
            // Ignore les "mauvais" charactères
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> versionProgramme;
        }

        if (versionProgramme == "c")
            JeuConsole::getJeu()->gameLoop(argc, argv);
        else if (versionProgramme == "g")
            JeuGUI::getJeu()->gameLoop(argc, argv);
    } catch (AkropolisException e) {
        cout << "\033[1;31mUne erreure inconnue est survenue, veuillez réessayer !";
        //cout << e.get_info() << "\n";
    }
}