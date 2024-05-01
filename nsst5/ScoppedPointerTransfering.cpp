#include <iostream>

template<typename T>
class ScoppedPointerTransfer {
    T* pointer;

public:
    ScoppedPointerTransfer(T* raw): pointer(raw) {}
    ScoppedPointerTransfer(const ScoppedPointerTransfer& other) = delete;
    ScoppedPointerTransfer& operator=(const ScoppedPointerTransfer& other) = delete;
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