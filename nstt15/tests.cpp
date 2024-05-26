#include "15.hpp"

int main() {
    int i = 0;
    double d = 9.0;
    char c = 'A';
    Point p(1, 2);

    Container<int, double, char, Point> container(i, d, c, p);

    std::cout << container.getElement<int>(0) << std::endl;
    std::cout << container.getElement<double>(1) << std::endl;
    std::cout << container.getElement<char>(2) << std::endl;
    Point& p_ref = container.getElement<Point>(3);
    std::cout << "Point: (" << p_ref.x << ", " << p_ref.y << ")" << std::endl;

    return 0;
}