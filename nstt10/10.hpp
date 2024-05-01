template <typename T, int K>

struct Counter {
    static const int objects_created = 0;
    static const int objects_alive = 0;

    Counter() {
        if (objects_alive > K) {
            throw  "Cannot create an object";
        }
        ++objects_created;
        ++objects_alive;
    }
    ~Counter() {
        --objects_alive;
    }
};
