#include <iostream>
#include <stdio.h>
#include <optional>
// struct
using namespace std;
struct Point
{
    double x;
    double y;

};

struct Line
{
    double A;
    double B;
    Line(double A, double B) {
        this->A = A;
        this->B = B;
    }
    Line(Point first, Point second) {
        double x0 = first.x;
        double y0 = first.y;
        double x1 = second.x;
        double y1 = second.y;
        this->A = (y0 - y1) / (x0 - x1);
        this->B = (y1 * x0 - y0 * x1) / (x0 - x1);
    }
    // std::optional
    optional<Point> get_intersection(Line line) {
        if (this->A == line.A) {
            cout << "Lines are paralell" << endl;
            return {};
        } 
        else
        {
            double A0 = this->A;
            double B0 = this->B;
            double A1 = line.A;
            double B1 = line.B;
            return Point{(B1 - B0) / (A0 - A1), (A0 * B1 - A1 * B0) / (A0 - A1)};
        }        
    }
    // std::optinal if A == 0
    optional<Line> get_perpendicular_line(Point point) {
        if (!A) {
            std::cout << "There is a bunch of perpendicular lines, because line is parallel to Ox" << std::endl;
        }
        double A1 = -1 / this->A;
        double B1 = point.y - A1 * point.x;
        return Line(A1, B1);
    }
};


