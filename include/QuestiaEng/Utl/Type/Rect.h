#ifndef RECT_H
#define RECT_H

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/Type/Vector2.h"

namespace utl
{
struct IntRect
{
    IntRect() = default;
    IntRect(int _x, int _y, int _width, int _height): x(_x), y(_y), width(_width), height(_height) {}
    int x, y, width, height;

    utl::Direction getCollision(const IntRect& other);
    bool isColliding(const IntRect& other);
    utl::Vector2i distanceTo(const IntRect& other, utl::Direction& direction);
};
struct FloatRect
{
    FloatRect() = default;
    FloatRect(float _x, float _y, float _width, float _height): x(_x), y(_y), width(_width), height(_height) {}
    float x, y, width, height;

    utl::Direction getCollision(const FloatRect& other);
    bool isColliding(const FloatRect& other);
    utl::Vector2f distanceTo(const FloatRect& other, utl::Direction& direction);
};
}

#endif // RECT_H
