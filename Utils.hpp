#ifndef LO21_PROJET_UTILS_HPP
#define LO21_PROJET_UTILS_HPP

class Vector2 {
public:
    float x;
    float y;

    Vector2() : x(0), y(0) {};
    Vector2(float x) : x(x), y(0) {};
    Vector2(float x, float y) : x(x), y(y) {};
};

#endif
