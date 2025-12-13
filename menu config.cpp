#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *fenetre0 = new QWidget;
    QLabel* choix = new QLabel("Que souhaitez-vous faire ?");
    QPushButton *NewGame = new QPushButton("Nouvelle partie");
    QPushButton *LoadGame = new QPushButton("Charger une partie");

    QVBoxLayout *layoutfenetre0 = new QVBoxLayout(fenetre0);
    layoutfenetre0->addWidget(choix);
    layoutfenetre0->addWidget(NewGame);
    layoutfenetre0->addWidget(LoadGame);

    //Fenêtre 1 : Choix nombre de Joueurs
    QWidget *fenetre1 = new QWidget;
    //fenetre1->setFixedSize(1200, 750);
    QLabel *NbJoueurs = new QLabel("Nombre de Joueurs");
    QPushButton *buttonPlayers1 = new QPushButton("Un");
    QPushButton *buttonPlayers2 = new QPushButton("Deux");
    QPushButton *buttonPlayers3 = new QPushButton("Trois");
    QPushButton *buttonPlayers4 = new QPushButton("Quatre");

    //En vertical
    QVBoxLayout *layoutfenetre1 = new QVBoxLayout(fenetre1);
    layoutfenetre1->addWidget(NbJoueurs);
    layoutfenetre1->addWidget(buttonPlayers1);
    layoutfenetre1->addWidget(buttonPlayers2);
    layoutfenetre1->addWidget(buttonPlayers3);
    layoutfenetre1->addWidget(buttonPlayers4);




    //Signal pour ouvrir la fenêtre du nb de joueurs
    QObject::connect(NewGame, &QPushButton::clicked, fenetre1, &QWidget::show);
    //Signal pour fermer la fenêtre du chargement de partie
    QObject::connect(NewGame, &QPushButton::clicked, fenetre0, &QWidget::close);
    QObject::connect(LoadGame, &QPushButton::clicked, fenetre0, &QWidget::close);

    //Fenêtre 1.5 : Choix nv Illustre Architecte si le joueur est seul
    QWidget *fenetre1_5 = new QWidget;
    QLabel *NvIllustre = new QLabel("Niveau de l'Illustre Architecte");
    QPushButton *buttonNvIll1 = new QPushButton("1");
    QPushButton *buttonNvIll2 = new QPushButton("2");
    QPushButton *buttonNvIll3 = new QPushButton("3");




    //Signal pour ouvrir la fenêtre de l'Illustre Architecte
    QObject::connect(buttonPlayers1, &QPushButton::clicked, fenetre1_5, &QWidget::show);
    //Signal pour fermer la fenêtre du choix du nombre de joueurs
    QObject::connect(buttonPlayers1, &QPushButton::clicked, fenetre1, &QWidget::close);

    QVBoxLayout *layoutfenetre1_5 = new QVBoxLayout(fenetre1_5);
    layoutfenetre1_5->addWidget(NvIllustre);
    layoutfenetre1_5->addWidget(buttonNvIll1);
    layoutfenetre1_5->addWidget(buttonNvIll2);
    layoutfenetre1_5->addWidget(buttonNvIll3);

    //Fenêtre 2.1 à 2.4 : nom des joueurs
    //Joueur 4
    QWidget *fenetre2_4 = new QWidget;
    QLabel *NomJoueur4 = new QLabel("Entrez le nom du quatrième joueur");
    QLineEdit *Nom4 = new QLineEdit;

    QVBoxLayout *layoutfenetre2_4 = new QVBoxLayout(fenetre2_4);
    layoutfenetre2_4->addWidget(NomJoueur4);
    layoutfenetre2_4->addWidget(Nom4);



    QObject::connect(buttonPlayers4, &QPushButton::clicked, fenetre2_4, &QWidget::show);
    //Signal pour fermer la fenêtre du choix du nombre de joueurs
    QObject::connect(buttonPlayers4, &QPushButton::clicked, fenetre1, &QWidget::close);

    //Joueur 3
    QWidget *fenetre2_3= new QWidget;
    QLabel *NomJoueur3 = new QLabel("Entrez le nom du troisième joueur");
    QLineEdit *Nom3 = new QLineEdit;

    QVBoxLayout *layoutfenetre2_3 = new QVBoxLayout(fenetre2_3);
    layoutfenetre2_3->addWidget(NomJoueur3);
    layoutfenetre2_3->addWidget(Nom3);



    QObject::connect(buttonPlayers3, &QPushButton::clicked, fenetre2_3, &QWidget::show);
        //Signal pour fermer la fenêtre du choix du nombre de joueurs
    QObject::connect(buttonPlayers3, &QPushButton::clicked, fenetre1, &QWidget::close);
    QObject::connect(Nom4, &QLineEdit::returnPressed, fenetre2_3, &QWidget::show);
    QObject::connect(Nom4, &QLineEdit::returnPressed, fenetre2_4, &QWidget::close);

    //Joueur 2
    QWidget *fenetre2_2= new QWidget;
    QLabel *NomJoueur2 = new QLabel("Entrez le nom du deuxième joueur");
    QLineEdit *Nom2 = new QLineEdit;

    QVBoxLayout *layoutfenetre2_2 = new QVBoxLayout(fenetre2_2);
    layoutfenetre2_2->addWidget(NomJoueur2);
    layoutfenetre2_2->addWidget(Nom2);



    QObject::connect(buttonPlayers2, &QPushButton::clicked, fenetre2_2, &QWidget::show);
        //Signal pour fermer la fenêtre du choix du nombre de joueurs
    QObject::connect(buttonPlayers2, &QPushButton::clicked, fenetre1, &QWidget::close);
    QObject::connect(Nom3, &QLineEdit::returnPressed, fenetre2_2, &QWidget::show);
    QObject::connect(Nom3, &QLineEdit::returnPressed, fenetre2_3, &QWidget::close);

    //Joueur 1
    QWidget *fenetre2_1= new QWidget;
    QLabel *NomJoueur1 = new QLabel("Entrez le nom du premier joueur");
    QLineEdit *Nom1 = new QLineEdit;

    QVBoxLayout *layoutfenetre2_1 = new QVBoxLayout(fenetre2_1);
    layoutfenetre2_1->addWidget(NomJoueur1);
    layoutfenetre2_1->addWidget(Nom1);



    QObject::connect(buttonNvIll1, &QPushButton::clicked, fenetre2_1, &QWidget::show);
        //Signal pour fermer la fenêtre de l'Illustre Architecte
    QObject::connect(buttonNvIll1, &QPushButton::clicked, fenetre1_5, &QWidget::close);
    QObject::connect(buttonNvIll2, &QPushButton::clicked, fenetre2_1, &QWidget::show);
    //Signal pour fermer la fenêtre de l'Illustre Architecte
    QObject::connect(buttonNvIll2, &QPushButton::clicked, fenetre1_5, &QWidget::close);
    QObject::connect(buttonNvIll3, &QPushButton::clicked, fenetre2_1, &QWidget::show);
    //Signal pour fermer la fenêtre de l'Illustre Architecte
    QObject::connect(buttonNvIll3, &QPushButton::clicked, fenetre1_5, &QWidget::close);
    QObject::connect(Nom2, &QLineEdit::returnPressed, fenetre2_1, &QWidget::show);
        //Signal pour fermer la fenêtre du choix du nombre de joueurs
    QObject::connect(Nom2, &QLineEdit::returnPressed, fenetre2_2, &QWidget::close);

    //Fenêtre 3 : Scoring
    QWidget *fenetre3 = new QWidget;
    QLabel* choixscore = new QLabel("Souhaitez-vous un score avec ou sans les variants ?");
    QPushButton *Simple = new QPushButton("Score sans les variantes");
    QPushButton *Var = new QPushButton("Score avec les variantes");

    QVBoxLayout *layoutfenetre3 = new QVBoxLayout(fenetre3);
    layoutfenetre3->addWidget(choixscore);
    layoutfenetre3->addWidget(Simple);
    layoutfenetre3->addWidget(Var);


    QObject::connect(Nom1, &QLineEdit::returnPressed, fenetre3, &QWidget::show);
    QObject::connect(Nom1, &QLineEdit::returnPressed, fenetre2_1, &QWidget::close);

    fenetre0->show();
    return app.exec();
}
