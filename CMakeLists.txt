cmake_minimum_required(VERSION 3.27)
project(LO21-Projet)

set(CMAKE_CXX_STANDARD 17)

# Fichier indispensables pour utiliser qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# Trouve les paquets qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(LO21-Projet main.cpp
        Tests/Tests.cpp
        Tuile/Tuile.cpp
        Tuile/Hexagone.cpp
        Players/Players.hpp
        Players/Plateau.cpp
        Score/Score.cpp
        Affichage/Affichage.cpp
        Chantier/Chantier.cpp
        Chantier/Chantier.hpp
        Chantier/Deck.cpp
        Chantier/Deck.hpp
        Players/Players.cpp
        Jeu.cpp
        Jeu.hpp
)

# Lier executable aux bibliothèques qt
target_link_libraries(LO21-Projet PRIVATE Qt6::Widgets)