#include "10.hpp"
class Foo: Counter<Foo, 3> {};
class Bar: Counter<Bar, 2> {};
int main() {
    Foo f1 = Foo();
    Foo f2 = Foo();
    Foo f3 = Foo();
    Foo f4 = Foo();
}