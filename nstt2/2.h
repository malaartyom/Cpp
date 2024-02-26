#include <iostream>
#include <stdio.h>
using namespace std;
class Point
{
private:
    double x;
    double y;
public:
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    };
    double get_x( ){
         return this->x;
    }
    double get_y(){
        return this->y;   
    }
};

class Line
{
private:
    double A;
    double B;
public: 
    Line(double A, double B) {
        this->A = A;
        this->B = B;
    }
    Line(Point first, Point second) {
        double x0 = first.get_x();
        double y0 = first.get_y();
        double x1 = second.get_x();
        double y1 = second.get_y();
        this->A = (y0 - y1) / (x0 - x1);
        this->B = (y1 * x0 - y0 * x1) / (x0 - x1);
    }
    double get_A() {
        return this->A;
    }
    double get_B() {
        return this->B;
    }

    Point get_intersection(Line line) {
        if (this->A == line.get_A()) {
            cout << "Lines are paralell" << endl;
        } 
        else
        {
            double A0 = this->A;
            double B0 = this->B;
            double A1 = line.get_A();
            double B1 = line.get_B();
            return Point((B1 - B0) / (A0 - A1), (A0 * B1 - A1 * B0) / (A0 - A1));
        }        
    }

    Line get_perpendicular_line(Point point) {
        double A1 = -1 / this->A;
        double B1 = point.get_y() - A1 * point.get_x();
        return Line(A1, B1);
    }
};


