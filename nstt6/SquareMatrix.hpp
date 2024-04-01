#include <iostream>
#include <vector>
#include <cmath>

class SquareMatrix {
private:
    double* data;
    int size;

public:
    SquareMatrix() : data(nullptr), size(0) {}
    SquareMatrix(int size) : size(size) {
        data = new double[size * size];
    }

    SquareMatrix(std::vector<double> vec) {
        size = static_cast<int> (std::sqrt(vec.size()));
        data = new double[size * size];
        
        for (int i = 0; i < size; i++) {
            data[i + size * i] = vec[i];
        }
    }
    SquareMatrix(SquareMatrix&& other) {
        size = other.size;
        data = other.data;
        other.data = nullptr;
    }
    SquareMatrix(const SquareMatrix& other) {
        size = other.size;
        data = new double[size * size];
        
        for (int i = 0; i < size * size; ++i) {
            data[i] = other.data[i];
        }
    }
    SquareMatrix& operator=(const SquareMatrix& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new double[size * size];

            for (int i = 0; i < size * size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    SquareMatrix& operator=(SquareMatrix&& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
    explicit operator double() const {
        double sum = 0;
        for (int i = 0; i < size * size; i++) {
            sum+=data[i];
        }
        return sum;
    }
    friend SquareMatrix operator+ (const SquareMatrix& left,const SquareMatrix& right);

    friend SquareMatrix& operator+= (SquareMatrix& left, SquareMatrix& right);

    friend SquareMatrix operator* (const SquareMatrix& left,const SquareMatrix& right);

    friend SquareMatrix& operator*= (SquareMatrix& left, SquareMatrix& right);

    friend SquareMatrix operator* (const int left, const SquareMatrix& right);

    friend SquareMatrix& operator*= (int left, SquareMatrix& right);

    friend bool operator==(SquareMatrix& left, SquareMatrix& right);

    friend bool operator!=(SquareMatrix& left, SquareMatrix& right);

    class Row {
        double * row;
    public:
        Row(double * row): row(row) {}
        double& operator[] (size_t i) {
            return row[i];
        }
    };

    Row operator[] (size_t i) {
        return Row(data + i * size);
    }
 
    ~SquareMatrix() {
        delete[] data;
    }
    void display_matrix() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << data[i * size + j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

SquareMatrix operator+ (const SquareMatrix& left, const SquareMatrix& right) {
    if (left.size == right.size) {
        auto size = left.size; 
        SquareMatrix* result = new SquareMatrix(size);
        for (int i = 0; i < size * size; i++) {
            result->data[i] = left.data[i] + right.data[i];
        }
        return *result;
    }
    else {
        throw "You can't add matrcies with different size";
    }

}
SquareMatrix operator* (const SquareMatrix& left,const SquareMatrix& right) {
    if (left.size == right.size) {
        auto size = left.size; 
        SquareMatrix* result = new SquareMatrix(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    result->data[i + size * j] = left.data[i + size * k] + left.data[k + size * j];
                }
            }
        }
        return *result;
    }
    else {
        throw "You can't multiply matrcies with different size";
    }
}
SquareMatrix& operator+= (SquareMatrix& left, SquareMatrix& right) {
        if (left.size == right.size){
            auto size = left.size; 
            for (int i = 0; i < size * size; i++) {
                left.data[i] += right.data[i];
            }
        }
        else {
            throw "You can't add matrcies with different size";
        }
        return left;

    }
SquareMatrix& operator*= (SquareMatrix& left, SquareMatrix& right) {
    if (left.size == right.size) {
        auto size = left.size; 
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    left.data[i + size * j] = left.data[i + size * k] + left.data[k + size * j];
                }
            }
        }
        return left;
    }
    else {
        throw "You can't multiply matrcies with different size";
    }
}
SquareMatrix operator* (const int left, const SquareMatrix& right) {
    auto size = right.size; 
    SquareMatrix* result = new SquareMatrix(size);
    for (auto i = 0; i < size * size; i++) {
        result->data[i] = left * right.data[i];
    }
    return *result;
}

SquareMatrix& operator*= (int left, SquareMatrix& right){
    auto size = right.size; 
    for (auto i = 0; i < size * size; i++) {
        right.data[i] *= left;
    }
    return right;
}

bool operator==(SquareMatrix& left, SquareMatrix& right) {
    if (left.size == right.size) {
        auto size = right.size; 
        for (auto i = 0; i < size * size; i++) {
            if (left.data[i] != right.data[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }

}

bool operator!=(SquareMatrix& left, SquareMatrix& right) {
    if (left.size == right.size) {
        auto size = right.size; 
        for (auto i = 0; i < size * size; i++) {
            if (left.data[i] != right.data[i]) {
                return true;
            }
        }
        return false;
    } else {
        return true;
    }
}
int main() {
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0}; 

    SquareMatrix matrix(vec);
    matrix.display_matrix();

    return 0;
}