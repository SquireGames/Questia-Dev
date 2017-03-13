#ifndef VECTOR2_H
#define VECTOR2_H

#include <SFML/System/Vector2.hpp> //conversions

namespace utl
{
struct Vector2i
{
    Vector2i() : x(0), y(0) {}
    Vector2i(int _x, int _y): x(_x), y(_y) {}
    int x, y;

    //conversion
    sf::Vector2i sf()
    {
        return sf::Vector2i(x, y);
    }

    //operator overloading
    Vector2i operator+(const Vector2i& other)
    {
        return Vector2i(other.x + x, other.y + y);
    }
    Vector2i& operator+=(const Vector2i& other)
    {
        x+=other.x;
        y+=other.y;
        return *this;
    }
};
struct Vector2ui
{
    Vector2ui() : x(0), y(0) {}
    Vector2ui(unsigned int _x, unsigned int _y): x(_x), y(_y) {}
    unsigned int x, y;

    //conversion
    sf::Vector2u sf()
    {
        return sf::Vector2u(x, y);
    }

    //operator overloading
    Vector2ui operator+(const Vector2ui& other)
    {
        return Vector2ui(other.x + x, other.y + y);
    }
    Vector2ui& operator+=(const Vector2ui& other)
    {
        x+=other.x;
        y+=other.y;
        return *this;
    }
};
struct Vector2f
{
    Vector2f() : x(0), y(0) {}
    Vector2f(float _x, float _y): x(_x), y(_y) {}
    Vector2f(sf::Vector2f other): x(other.x), y(other.y) {}
    float x, y;

    //conversion
    sf::Vector2f sf()
    {
        return sf::Vector2f(x, y);
    }

    //operator overloading
    Vector2f operator+(const Vector2f& other)
    {
        return Vector2f(other.x + x, other.y + y);
    }
    Vector2f operator-(const Vector2f& other)
    {
        //TODO test if right order
        return Vector2f(x - other.x, y - other.y);
    }
    Vector2f& operator+=(const Vector2f& other)
    {
        x+=other.x;
        y+=other.y;
        return *this;
    }
    Vector2f operator/(const float& other)
    {
        return Vector2f(x / other, y / other);
    }
    Vector2f operator*(const float& other)
    {
        return Vector2f(x * other, y * other);
    }
};
}
#endif // VECTOR2_H
