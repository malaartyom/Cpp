#include "13.hpp"

bool isEven(int n) {
    return n % 2 == 0;
}

int main() {
    int index = getIndexOfFirstMatch(isEven, 1, 3, 4, 7, 10, 11);
    std::cout << "First even number is at index: " << index << std::endl;
    int index0 = getIndexOfFirstMatch(isEven, 1, 3, 7);
    std::cout << "First even number is at index: " << index0 << std::endl;
    return 0;
}
