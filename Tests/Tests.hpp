/**
\file Tests.hpp
\date 17/09/2025
\author Dimitri Maréchal
\version 1
\brief  Test & Assertion function definition

 This file defines the different test/assertion functions.\n
 To disable those tests & assertions, uncomment the `// #define NDEBUG` at the beginning of the `main.cpp` file
**/

#ifndef LO21_PROJET_TESTS_HPP
#define LO21_PROJET_TESTS_HPP

#include <cassert>

//! \brief The main test function
void assertTests();

// Tests pour le système de Score
void test_ScoreUtils();
void test_ScoreBleu();
void test_ScoreRouge();
void test_ScoreVert();
void test_ScoreViolet();
void test_ScoreJaune();

#endif