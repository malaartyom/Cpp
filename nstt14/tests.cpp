#include "14.hpp"

int main() {
    int i = 0;
    double d = 9.0;
    char c = 'A';

    constexpr int size = sizeof(int) + sizeof(double) + sizeof(char);
    char buff[size];
    allocate<size>(buff, i, d, c);

    int* i_ptr =(int*) (buff);
    double* d_ptr = (double*) (buff + sizeof(int));
    char* c_ptr = (char*) (buff + sizeof(int) + sizeof(double));

    assert(*i_ptr == 0); 
    assert(*d_ptr == 9.0);  
    assert(*c_ptr == 'A');

    return 0;
}