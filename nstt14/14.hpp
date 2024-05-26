#include <iostream>
#include <type_traits>

template<typename... Types>
constexpr bool check_size(int size) {
    return size >= (sizeof(Types) + ...);
}

template<typename... Types>
constexpr bool is_good = (std::is_copy_constructible_v<Types> && ...);

template<typename T>
char* allocate_one(char* ptr, T&& arg) {
    using T_WITH_OUT_REF = std::remove_reference_t<T>;
    new(ptr) T_WITH_OUT_REF(std::forward<T>(arg));
    ptr += sizeof(T);
    return ptr;
}

template<int SIZE, typename... Types>
void allocate(void* memory, Types&&... types) requires (is_good<Types...> && check_size<Types...>(SIZE)) {
    char* current_ptr = static_cast<char*>(memory);
    ((current_ptr = allocate_one(current_ptr, std::forward<Types>(types))), ...);
}
