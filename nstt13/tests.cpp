#include "13.hpp"

struct Point {
    int x, y;
    Point(int x, int y): x(x), y(y) {std::cout << "Constructor was called" << std::endl; }
    Point(const Point& other): x(other.x), y(other.y) { std::cout << "Copy costructor was called" << std::endl; };
    Point(const Point&& other): x(other.x), y(other.y) { std::cout << "Move costructor was called" << std::endl; };
    Point& operator=(const Point& other) {
        std::cout << "Assignment operator was called" << std::endl;
        x = other.x;
        y = other.y;
        return *this;
    };
    
    ~Point() { std::cout << "Destructor was called" << std::endl;};
};

bool isEven(int n) {
    return n % 2 == 0;
}

int main() {
    int index = getIndexOfFirstMatch(isEven, 1, 3, 4, 7, 10, 11);
    std::cout << "First even number is at index: " << index << std::endl;
    int index0 = getIndexOfFirstMatch(isEven, 1, 3, 7);
    std::cout << "First even number is at index: " << index0 << std::endl;
    int index1 = getIndexOfFirstMatch([](Point p){ return p.x % 2 == 0;}, Point(1, 2), Point(3, 3), Point(5, 4), Point(6, 7));
    std::cout << "First Point with even x: " << index1 << std::endl;
    return 0;
}
