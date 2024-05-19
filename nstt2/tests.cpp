#include <iostream>
#include <cassert>
#include "2.hpp"

void testProgram() {
    Point p1{2.0, 3.0};
    assert(p1.x == 2.0);
    assert(p1.y == 3.0);
    
    Point start{1.0, 1.0};
    Point end{2.0, 2.0};
    Line line(start, end);
    assert(line.A == 1.0);
    assert(line.B == 0.0);

    
    optional<Point> intersectionPoint = line.get_intersection(Line(Point{3.0, 1.0}, Point{1.5, 2.5}));
    assert(intersectionPoint.has_value());
    assert(intersectionPoint.value().x == 2.0);
    assert(intersectionPoint.value().y == 2.0);

    optional<Line> perpendicular = line.get_perpendicular_line(Point{2.0, 3.0});
    assert(intersectionPoint.has_value());
    assert(perpendicular.value().A == -1.0);
    assert(perpendicular.value().B == 5.0);

    std::cout << "All tests passed successfully!" << std::endl;
}

int main() {
    testProgram();
    return 0;
}
