#ifndef C___LAB_2_SEMESTER_GEOMETRY_H
#define C___LAB_2_SEMESTER_GEOMETRY_H
#include <vector>
#define vec std::vector<Point>

class Point
{
private:
    double x;
    double y;
public:
    Point();
    Point(double x, double y);
    Point(const Point &point1);
    Point& operator=(const Point &point);
    void get();
    double getX() const;
    double getY() const;
    void set(double x, double y);

};

class PolygonalChain
{
protected:
    vec points;
public:
    PolygonalChain(int n,Point* fig);

    virtual PolygonalChain& operator=(const PolygonalChain &chain);

    PolygonalChain(const PolygonalChain &chain);

    void get();
    int getN() const;
    Point getPoint(int n) const;

    virtual ~PolygonalChain();

    virtual float perimeter() const;

    float hypotenuse(Point first, Point second) const;
};

class ClosedPolygonalChain:public PolygonalChain
{
//fixed inherit fields
public:
    ClosedPolygonalChain(int n,Point* fig);

    ClosedPolygonalChain& operator=(const ClosedPolygonalChain &chain);

    ClosedPolygonalChain(const ClosedPolygonalChain &chain);

    float perimeter() const;
};

class Polygon:public ClosedPolygonalChain
{
public:

    Polygon(int n,Point* fig);

    Polygon(const Polygon &fig);

    Polygon& operator=(const Polygon &fig);

    void get();

    Point getPoint(int n);

    virtual float area() const;
};

class RegularPolygon:public Polygon
{
public:
    RegularPolygon(int n,Point* fig);

    RegularPolygon(const RegularPolygon &fig);

    RegularPolygon& operator=(const RegularPolygon &fig);

    float area();

    bool regular();

};

class Triangle:public Polygon
{
public:
    Triangle(int n,Point* fig);

    Triangle(const Triangle &fig);

    Triangle& operator=(const Triangle &fig);

    float height();

    float area();

    bool hasRightAngle() const;

};

class Trapezoid:public Polygon
{
public:
    Trapezoid (int n,Point* fig);
    Trapezoid (const Trapezoid &fig);
    Trapezoid& operator=(const Trapezoid &fig);
    float height() const;
    float area() const;
};


#endif //C___LAB_2_SEMESTER_GEOMETRY_H
