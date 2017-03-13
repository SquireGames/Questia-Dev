#ifndef BOUNDS_H
#define BOUNDS_H

#include <vector>

#include "QuestiaEng/Utl/Type/Vector2.h"

struct Circ
{
    Circ(float _radius):radius(_radius){}
    float radius;
};
struct Rect
{
    Rect(utl::Vector2f _dims, utl::Vector2f _origin):dims(_dims), origin(_origin){}
    utl::Vector2f dims;
    utl::Vector2f origin;
};
struct Poly
{
    Poly(utl::Vector2f _origin, float _angle, std::vector<utl::Vector2f> _points): origin(_origin), angle(_angle), points(_points){}
    utl::Vector2f origin;
    float angle;
    std::vector<utl::Vector2f> points;
};
struct Dot
{
    Dot(utl::Vector2f _point):point(_point){}
    utl::Vector2f point;
};
struct None {};

class Bounds
{
public:
    Bounds(Circ circ);
    Bounds(Rect rect);
    Bounds(Poly poly);
    Bounds(Dot dot);
    Bounds();

    enum class Shape{circ, rect, poly, dot, none};

    Shape getShape();

    utl::Vector2f rel_coords = utl::Vector2f(0,0);
    float maxRadius = -1;
   // boost::variant<Circ, Rect, Poly, Dot, None> area;
private:
    Shape coll_shape;
};
#endif // BOUNDS_H
