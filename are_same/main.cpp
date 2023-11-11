#include <type_traits>
#include <cstdint>

template <typename... Ts>
struct are_same;

template <typename T, typename... Ts>
struct are_same<T, Ts...> : std::integral_constant<bool, (std::is_same_v<T, Ts> && ...)> {};

template <>
struct are_same<> : std::true_type {};

template <typename... Ts>
constexpr bool are_same_v = are_same<Ts...>::value;

int main() {
    static_assert(are_same_v<int, int32_t, signed int>, "compile assert");
    static_assert(!are_same_v<int, float, double>, "compile assert");
    return 0;
}
