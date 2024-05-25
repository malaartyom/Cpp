#include <iostream>
#include <type_traits>

template<typename... Types>
constexpr bool check_size(int size, Types&&... types){
    return size >= (sizeof(types) + ...);
}
template<typename... Types>
constexpr bool is_good = (std::is_copy_constructible<Types>:: value && ...);

template<typename T>
char* allocate_one(char* ptr, T&& arg) {
    new(ptr) T(arg);
    ptr += sizeof(arg);
    return ptr;
}

template<int SIZE, typename... Types> 
void allocate(void* memory, Types&&... types) requires(is_good<Types...>, check_size<Types...>(SIZE, types...))
{ 
   (memory = ((char*) memory, types) ...); 
}

