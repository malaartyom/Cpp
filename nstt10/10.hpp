#include <iostream>

template <typename T, int K>
struct Counter {
    static int objects;

    Counter() {
        if (objects >= K) {
            throw std::runtime_error("\033[1;31mCannot create an object!!!\033[0m");
        }
        ++objects;
    }
    Counter(const Counter& other) {
        std::cout << "Copy " << K << std::endl;
        if (objects >= K) {
            throw std::runtime_error("\033[1;31mCannot create an object!!!\033[0m");
        }
        ++objects;
    }
    ~Counter() {
        --objects;
    }
};

template<typename T, int K>
int Counter<T , K>::objects = 0;




