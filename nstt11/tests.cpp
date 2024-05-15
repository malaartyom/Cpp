#include <iostream>

template<int N, int div>
struct is_prime_rec {
    static const bool val = (N % div != 0) && is_prime_rec<N, div-1>::val;
};

template<int N>
struct is_prime_rec<N, 1> {
    static const bool val = true;
};

template<int N>
struct is_prime_rec<N, 0> {
    static const bool val = true;
};

template<int N>
struct prime {
    static const bool val = is_prime_rec<N, N-1>::val;
};

template<int N, bool cond>
struct next_prime_if {
    static const int val = N + 1;
};

template<int N>
struct next_prime {
    static const int val = next_prime_if<N, prime<N + 1>::val>::val;
};


template<int N>
struct next_prime_if<N, false> {
    static const int val = next_prime<N + 1>::val;
};

template<int N>
struct nth_prime {
    static const int val = next_prime<nth_prime<N - 1>::val>::val;
};

template<>
struct nth_prime<0> {
    static const int val = 2;
};


int main() {
    std::cout << prime<6>::val << std::endl;
    std::cout << next_prime<2>::val << std::endl;
    std::cout << nth_prime<200>::val << std::endl;

    return 0;
}