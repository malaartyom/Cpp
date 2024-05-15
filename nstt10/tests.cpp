#include "10.hpp"
#include <stdlib.h> 
class Foo: Counter<Foo, 2> {
    int x;
    public:
    Foo(int val): x(val) {}
    Foo() {Foo(0);}
    ~Foo() = default;
};
int main() {
    try {
        Foo f1 = Foo();
        Foo f2 = Foo();
        Foo f3 = Foo();
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}