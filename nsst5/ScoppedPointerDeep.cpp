#include <iostream>

template<typename T>
class ScoppedPointerTransfer {
    T* pointer;

public:
    ScoppedPointerTransfer(T* raw): pointer(raw) {}
    ScoppedPointerTransfer(const ScoppedPointerTransfer& other) {
        if (other.pointer) {
            pointer = new T(*(other.pointer))
        } else {
            pointer = nullptr;
        }
    }
    ScoppedPointerTransfer& operator=(const ScoppedPointerTransfer& other) {
        if (this != &other) {
            delete pointer;
            if (other.pointer) {
                pointer = new T(*(other.pointer))
            } else {
                pointer = nullptr;
            }
        }
        return *this;
    }
    ScoppedPointerTransfer(ScoppedPointerTransfer&& other) {
        pointer = other.pointer;
        other.pointer = nullptr;
    }
    ScoppedPointerTransfer& operator=(ScoppedPointerTransfer&& other) {
        if (this != &other) {
            delete pointer;
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        return *this;
    }
    

    T& get() {return *pointer};
    const T& get() {return *pointer}

    ~ScoppedPointerTransfer() {delete pointer};
};