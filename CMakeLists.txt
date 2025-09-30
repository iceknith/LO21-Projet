cmake_minimum_required(VERSION 3.27)
project(LO21-Projet)

set(CMAKE_CXX_STANDARD 17)

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
)
