#include "geometry.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <cassert>
#define vec std::vector<Point>
#define pi 3.1415926535

//todo indenation
    Point::Point() //конструктор со значениями по умолчанию
    {
        x=0;
        y=0;
    }

    Point::Point(double x1, double y1) //конструктор с заданными значениями
    {
        x=x1;
        y=y1;
    }

    Point::Point(const Point &point1) //конструктор копирования
    {
        x=point1.x;
        y=point1.y;
    }
    Point& Point::operator=(const Point &point){ //оператор присваивания
        if (this!= &point) {
            x = point.x;
            y = point.y;
        }
        return *this;
    }
    void Point::get()
    {
        std::cout<<"x: "<<x<<"\ny: "<<y<<std::endl;
    }
    double Point::getX() const {
        return x;
    }
    double Point::getY() const {
        return y;
    }
    void Point::set(double x1, double y1)
    {
        x=x1;
        y=y1;
    }


//todo S P A C E S
PolygonalChain::PolygonalChain(int n,Point* fig) //конструктор
    {
        number_of_points=n;
        for (int i=0;i<n;i++){
            points.push_back(fig[i]);
        }
    }

PolygonalChain&PolygonalChain:: operator=(const PolygonalChain &chain){ //оператор присваивания
    //todo vector has =, u dont need clear
    if (this!= &chain) {
        points.clear();
        number_of_points = chain.number_of_points;
        for (int i = 0; i < chain.number_of_points; i++) {
            points.push_back(chain.points[i]);
        }
    }
    return *this;
    }

PolygonalChain::PolygonalChain(const PolygonalChain &chain) //конструктор копирования
//todo remove it
    {
        points.clear();
        number_of_points=chain.number_of_points;
        for (int i=0;i<chain.number_of_points;i++){
            points.push_back(chain.points[i]);
        }
    }

    void PolygonalChain::get()
    {
        std::cout<<"number: "<<number_of_points<<std::endl;
        for (int i=0;i<number_of_points;i++){
            std::cout<<"point "<<i<<": "<<points[i].getX()<<" "<<points[i].getY()<<std::endl;
        }
    }

    Point PolygonalChain::getPoint(int n) const { //возвращает точку по номеру
        return points[n];
    }

    int PolygonalChain::getN() const {
    return number_of_points;
    }

    float PolygonalChain::perimeter() const {
        float per=0;
        for (int i=1;i<number_of_points;i++){
            per=per+hypotenuse(points[i-1],points[i]);
        }
        return per;
    }

float PolygonalChain::hypotenuse(Point first, Point second) const {
    return sqrt(pow((first.getX()-second.getX()),2)+pow((first.getY()-second.getY()),2));
}

//todo enormous amount of copy-paste
ClosedPolygonalChain::ClosedPolygonalChain(int n,Point* fig):PolygonalChain(n,fig) //конструктор
    {
        number_of_points=n;
        for (int i=0;i<n;i++){
            points.push_back(fig[i]);
        }
    }

ClosedPolygonalChain&ClosedPolygonalChain:: operator=(const ClosedPolygonalChain &chain){ //оператор присваивания
    if (this!= &chain) {
        points.clear();
        number_of_points = chain.number_of_points;
        for (int i = 0; i < chain.number_of_points; i++) {
            points.push_back(chain.points[i]);
        }
    }
        return *this;
    }

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &chain):PolygonalChain(chain) //конструктор копирования
    {
        points.clear();
        number_of_points=chain.number_of_points;
        for (int i=0;i<chain.number_of_points;i++){
            points.push_back(chain.points[i]);
        }
    }


    float ClosedPolygonalChain::perimeter() const {
        //copy-paster perimeter
        float per=0;
        for (int i=1;i<number_of_points;i++){
            per=per+hypotenuse(points[i-1],points[i]);
        }
        per=per+hypotenuse(points[0],points[number_of_points-1]);
        return per;
    }


Polygon::Polygon(int n,Point* fig):ClosedPolygonalChain(n,fig){
        number_of_points=n;
        for (int i=0;i<n;i++){
            points.push_back(fig[i]);
        }
    }


Polygon::Polygon(const Polygon &fig):ClosedPolygonalChain(fig){ //копирование
        points.clear();
        number_of_points=fig.number_of_points;
        for (int i=0;i<fig.number_of_points;i++){
            points.push_back(fig.points[i]);
        }
    }

Polygon&Polygon:: operator=(const Polygon &fig){ //присваивание
    if (this!= &fig) {
        points.clear();
        number_of_points = fig.number_of_points;
        for (int i = 0; i < fig.number_of_points; i++) {
            points.push_back(fig.points[i]);
        }
    }
    return *this;
    }

    void Polygon::get()
    {
        std::cout<<"number: "<<number_of_points<<std::endl;
        for (int i=0;i<number_of_points;i++){
            std::cout<<"point "<<i<<": "<<points[i].getX()<<" "<<points[i].getY()<<std::endl;
        }
    }

    Point Polygon::getPoint(int n){ //возвращает точку по номеру
        return points[n];
    }

    float Polygon::perimeter(){
        float per=0;
        for (int i=1;i<number_of_points;i++){
            per=per+hypotenuse(points[i-1],points[i]);
        }
        per=per+hypotenuse(points[0],points[number_of_points-1]);
        return per;
    }

    float Polygon::area() const {
        float sq=0;
        for (int i=0;i<number_of_points-1;i++){
            sq+=points[i].getX()*points[i+1].getY()-points[i].getY()*points[i+1].getX();
        }
        sq+=points[number_of_points-1].getX()*points[0].getY()-points[number_of_points-1].getY()*points[0].getX();
        return abs(sq/2);
    }

float Polygon::hypotenuse(Point first, Point second) const {
    return sqrt(pow((first.getX()-second.getX()),2)+pow((first.getY()-second.getY()),2));
}

Polygon::~Polygon() = default;


RegularPolygon::RegularPolygon(int n,Point* fig):Polygon(n,fig){
        number_of_points=n;
        for (int i=0;i<n;i++){
            points.push_back(fig[i]);
        }
    }

RegularPolygon::RegularPolygon(const RegularPolygon &fig):Polygon(fig){ //копирование
        points.clear();
        number_of_points=fig.number_of_points;
        for (int i=0;i<fig.number_of_points;i++){
            points.push_back(fig.points[i]);
        }
    }

RegularPolygon&RegularPolygon:: operator=(const RegularPolygon &fig){ //присваивание
    if (this!= &fig) {
        points.clear();
        number_of_points = fig.number_of_points;
        for (int i = 0; i < fig.number_of_points; i++) {
            points.push_back(fig.points[i]);
        }
    }
    return *this;
    }


    bool RegularPolygon::regular(){
        float first=abs(hypotenuse(points[0],points[1]));
        for (int i=2;i<number_of_points;i++) {
            if (abs(hypotenuse(points[i-1],points[i]))!=first)
                return false;
        }
        if (abs(hypotenuse(points[number_of_points-1],points[0]))!=first)
            return false;
        return true;
    }

float RegularPolygon::perimeter(){
    float per=0;
    per=per+hypotenuse(points[number_of_points-1],points[0]);
    per = per*float(number_of_points);
    return per;
}

float RegularPolygon::area() {
    float a=hypotenuse(points[number_of_points-1],points[0]);
    float sq=number_of_points*a*a/(4*tan(pi/number_of_points));
    return sq;
}


Triangle::Triangle(int n,Point* fig):Polygon(n,fig){
        assert(n==3);
        for (int i=0;i<n;i++){
            points.push_back(fig[i]);
        }
    }

Triangle::Triangle(const Triangle &fig):Polygon(fig){ //копирование
        points.clear();
        for (int i=0;i<fig.number_of_points;i++){
            points.push_back(fig.points[i]);
        }
    }

Triangle&Triangle:: operator=(const Triangle &fig){ //присваивание
    if (this!= &fig) {
        points.clear();
        for (int i = 0; i < fig.number_of_points; i++) {
            points.push_back(fig.points[i]);
        }
    }
    return *this;
    }


    
    float Triangle::height()
    {
        float a=abs(hypotenuse(points[1],points[2]));
        float b=abs(hypotenuse(points[0],points[1]));
        float c=abs(hypotenuse(points[0],points[2]));
        float p=(a+b+c)/2;
        float h=(2/a)*sqrt(p*(p-a)*(p-b)*(p-c));
        return h;
    }

    float Triangle::area()
    {
        float a=abs(hypotenuse(points[1],points[2]));
        float b=abs(hypotenuse(points[0],points[1]));
        float c=abs(hypotenuse(points[0],points[2]));
        float p=(a+b+c)/2;
        float area=sqrt(p*(p-a)*(p-b)*(p-c));
        return area;
    }

    bool Triangle::hasRightAngle() const {
       //todo return expression
        if (((points[0].getX()-points[1].getX())*(points[1].getX()-points[2].getX())+(points[0].getY()-points[1].getY())*(points[1].getY()-points[2].getY())==0) or ((points[0].getX()-points[1].getX())*(points[0].getX()-points[2].getX())+(points[0].getY()-points[1].getY())*(points[0].getY()-points[2].getY())==0) or ((points[0].getX()-points[2].getX())*(points[1].getX()-points[2].getX())+(points[0].getY()-points[2].getY())*(points[1].getY()-points[2].getY())==0))
            return true;
        else
            return false;
    }


Trapezoid::Trapezoid (int n,Point* fig):Polygon(n,fig){
        assert(n==4);
        for (int i=0;i<n;i++){
            points.push_back(fig[i]);
        }
    }

Trapezoid::Trapezoid (const Trapezoid &fig):Polygon(fig){ //копирование
        points.clear();
        for (int i=0;i<fig.number_of_points;i++){
            points.push_back(fig.points[i]);
        }
    }

Trapezoid&Trapezoid:: operator=(const Trapezoid &fig){ //присваивание
    if (this!= &fig) {
        points.clear();
        for (int i = 0; i < fig.number_of_points; i++) {
            points.push_back(fig.points[i]);
        }
    }
    return *this ;
    }

    float Trapezoid::height() const {
        float higher=abs(hypotenuse(points[1],points[2]));
        float lower=abs(hypotenuse(points[0],points[3]));
        float h=area()/(0.5*higher+0.5*lower);
        return h;
    }

    float Trapezoid::area() const {
        float sq=0;
        for (int i=0;i<number_of_points-1;i++){
            sq+=points[i].getX()*points[i+1].getY()-points[i].getY()*points[i+1].getX();
        }
        sq+=points[number_of_points-1].getX()*points[0].getY()-points[number_of_points-1].getY()*points[0].getX();
        return abs(sq/2);
    }

