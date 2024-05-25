#include <iostream>
#include <functional>

// Old version
template<typename Checker>
int get_index(Checker check, int index) {
    return -1;
}

template<typename Checker, typename T, typename... Rest>
int get_index(Checker check, int index, T&& first, Rest&&... rest) {
    if (check(std::forward<T>(first))) return index;
    else return get_index(check, index + 1, std::forward<Rest>(rest)...);
}

// New version 
template<typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker checker, Args&&... args) {
        int index = 0;
    int result = 0;
    bool found = ((checker(std::forward<Args>(args)) ? (result = index, true) : (index++, false)) || ...);
    if (found) {
        return result;
    } else {
        return -1;
    }

}