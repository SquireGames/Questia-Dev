#ifndef BOUNDS_H
#define BOUNDS_H

#include <vector>

#include "QuestiaEng/Utl/Type/Vector2.h"

struct Circ
{
    Circ(float radius):radius(radius){}
    float radius;
};
struct Rect
{
    Rect(utl::Vector2f dims, utl::Vector2f origin):dims(dims), origin(origin){}
    utl::Vector2f dims;
    utl::Vector2f origin;
};
struct Poly
{
    Poly(utl::Vector2f origin, float angle, utl::Vector2f* points, int len): origin(origin), angle(angle), points(points), len(len){}
    utl::Vector2f origin;
    float angle;
	//c style storage of points
    utl::Vector2f* points;
	unsigned int len;
};
struct Dot
{
    Dot(utl::Vector2f point):point(point){}
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

    Shape getShape() const;

    utl::Vector2f rel_coords = utl::Vector2f(0,0);
    float maxRadius = -1;
   // boost::variant<Circ, Rect, Poly, Dot, None> area;
private:
    Shape coll_shape;
};
#endif // BOUNDS_H
