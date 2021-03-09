#include "geometry.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <cassert>
#define pi 3.1415926535

//fixed indenation
Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(double x1, double y1)
{
    x = x1;
    y = y1;
}

Point::Point(const Point &point1)
{
    x = point1.x;
    y = point1.y;
}
Point& Point::operator=(const Point &point)
{
    if (this != &point) {
        x = point.x;
        y = point.y;
    }
    return *this;
}
void Point::get()
{
    std::cout << "x: " << x << "\ny: " << y << std::endl;
}
double Point::getX() const
{
    return x;
}
double Point::getY() const
{
    return y;
}
void Point::set(double x1, double y1)
{
    x = x1;
    y = y1;
}


//fixed S P A C E S
PolygonalChain::PolygonalChain (int n, Point* fig)
{
    for ( int i = 0 ; i < n ; i++ ){
        points.push_back(fig[i]);
    }
}

PolygonalChain&PolygonalChain::operator= (const PolygonalChain &chain)=default;

PolygonalChain::PolygonalChain(const PolygonalChain &chain)
//fixed remove it
{
    points=chain.points;
}

void PolygonalChain::get()
{
    std::cout << "number: " << points.size() << std::endl;
    for (unsigned int i = 0; i < points.size(); i++){
        std::cout << "point " << i << ": " << points[i].getX() << " " << points[i].getY() << std::endl;
    }
}

PolygonalChain::~PolygonalChain() = default;

Point PolygonalChain::getPoint(int n) const
{
    return points[n];
}

int PolygonalChain::getN() const
{
    return points.size();
}

float PolygonalChain::perimeter() const
{
    float per = 0;
    for (unsigned int i = 1; i < points.size(); i++){
        per = per + hypotenuse(points[i-1], points[i]);
    }
    return per;
}

float PolygonalChain::hypotenuse(Point first, Point second) const
{
    return sqrt(pow((first.getX() - second.getX()), 2) + pow((first.getY() - second.getY()), 2));
}

//fixed enormous amount of copy-paste
ClosedPolygonalChain::ClosedPolygonalChain(int n, Point* fig):PolygonalChain(n, fig)
{
}


ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &chain):PolygonalChain(chain)
{
}


float ClosedPolygonalChain::perimeter() const
{
    float per = PolygonalChain::perimeter();
    per = per + hypotenuse(points[0], points[points.size() - 1]);
    return per;
}


Polygon::Polygon(int n, Point* fig):ClosedPolygonalChain(n, fig)
{
}


Polygon::Polygon(const Polygon &fig):ClosedPolygonalChain(fig)
{
}
//fixed one = default

void Polygon::get()
{
    std::cout << "number: " << points.size() << std::endl;
    for (unsigned int i = 0; i < points.size(); i++){
        std::cout << "point " << i << ": " << points[i].getX() << " " << points[i].getY() << std::endl;
    }
}

Point Polygon::getPoint(int n)
{
    return points[n];
}

float Polygon::area() const
{
    float sq=0;
    for (int i = 0; i < points.size() - 1; i++){
        sq += points[i].getX() * points[i + 1].getY() - points[i].getY() * points[i + 1].getX();
    }
    sq += points[points.size() - 1].getX() * points[0].getY() - points[points.size() - 1].getY() * points[0].getX();
    return abs(sq / 2);
}

RegularPolygon::RegularPolygon(int n,Point* fig):Polygon(n,fig)
{
}

RegularPolygon::RegularPolygon(const RegularPolygon &fig):Polygon(fig)
{
}




bool RegularPolygon::regular()
{
    float first = abs(hypotenuse(points[0], points[1]));
    for (unsigned int i = 2; i < points.size(); i++) {
        if (abs(hypotenuse(points[i - 1], points[i])) != first)
            return false;
    }
    if (abs(hypotenuse(points[points.size() - 1], points[0])) != first)
        return false;
    return true;
}

float RegularPolygon::area()
{
    float a = hypotenuse(points[points.size() - 1],points[0]);
    float sq = points.size() * a * a / (4 * tan(pi / points.size()));
    return sq;
}


Triangle::Triangle(int n, Point* fig):Polygon(n, fig)
{
    assert(n == 3);
}

Triangle::Triangle(const Triangle &fig):Polygon(fig)
{
}




float Triangle::height()
{
    float a = abs(hypotenuse(points[1], points[2]));
    float b = abs(hypotenuse(points[0], points[1]));
    float c = abs(hypotenuse(points[0], points[2]));
    float p = (a + b + c) / 2;
    float h = (2 / a) * sqrt(p * (p - a) * (p - b) * (p - c));
    return h;
}

float Triangle::area()
{
    float a = abs(hypotenuse(points[1],points[2]));
    float b = abs(hypotenuse(points[0],points[1]));
    float c = abs(hypotenuse(points[0],points[2]));
    float p = (a + b + c) / 2;
    float area = sqrt(p * (p - a) * (p - b) * (p - c));
    area=floor(area * 100) / 100;
    return area;
}

bool Triangle::hasRightAngle() const
{
    //fixed return expression
    return (((points[0].getX() - points[1].getX()) * (points[1].getX() - points[2].getX()) + (points[0].getY() - points[1].getY()) * (points[1].getY() - points[2].getY()) == 0) or ((points[0].getX() - points[1].getX()) * (points[0].getX() - points[2].getX()) + (points[0].getY() - points[1].getY()) * (points[0].getY() - points[2].getY()) == 0) or ((points[0].getX() - points[2].getX()) * (points[1].getX() - points[2].getX()) + (points[0].getY() - points[2].getY()) * (points[1].getY() - points[2].getY()) == 0));
}


Trapezoid::Trapezoid (int n,Point* fig):Polygon(n,fig)
{
    assert(n == 4);
}

Trapezoid::Trapezoid (const Trapezoid &fig):Polygon(fig)
{
}


float Trapezoid::height() const
{
    float higher = abs(hypotenuse(points[1], points[2]));
    float lower = abs(hypotenuse(points[0], points[3]));
    float h = area() / (0.5 * higher + 0.5 * lower);
    return h;
}

float Trapezoid::area() const
{
    float sq = 0;
    for (unsigned int i = 0; i < points.size() - 1; i++){
        sq+=points[i].getX() * points[i + 1].getY() - points[i].getY() * points[i + 1].getX();
    }
    sq+=points[points.size() - 1].getX() * points[0].getY() - points[points.size() - 1].getY() * points[0].getX();
    return abs(sq / 2);
}
