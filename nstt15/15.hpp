#include "../nstt14/14.hpp"
#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>  

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) { std::cout << "Constructor was called" << std::endl; }
    Point(const Point& other) : x(other.x), y(other.y) { std::cout << "Copy constructor was called" << std::endl; }
    Point(Point&& other) : x(other.x), y(other.y) { std::cout << "Move constructor was called" << std::endl; }
    Point& operator=(const Point& other) {
        std::cout << "Assignment operator was called" << std::endl;
        x = other.x;
        y = other.y;
        return *this;
    }
    ~Point() { std::cout << "Destructor was called" << std::endl; }
};

template<typename... Types>
constexpr size_t get_size = (sizeof(Types) + ...);

template<typename... Types>
class Container {
    char* pointer;
    std::vector<size_t> shifts;

    template<typename T>
    void add_shift(size_t& counter) {
        shifts.push_back(counter);
        counter += sizeof(T);
    }

    template<typename T>
    void free_memory(size_t& idx) {
        
        reinterpret_cast<T*>(pointer + shifts[idx])->~T();
        idx++;
    }

public:
    Container(Types... types) {
        pointer = new char[get_size<Types...>];
        allocate<get_size<Types...>>(pointer, std::forward<Types>(types)...);
        
        size_t counter = 0;
        (add_shift<Types>(counter), ...);
    }

    template<typename T>
    T& getElement(size_t idx) {
        return *reinterpret_cast<T*>(pointer + shifts[idx]);
    }

    ~Container() {
        size_t idx = 0;
        (free_memory<Types>(idx), ...);
        delete[] pointer;  
    }
};
