
#include <type_traits>

namespace detail{
  template<class T, class A0>
  static auto test_serialize(A0&& a0, int) -> decltype(std::declval<T>().serialize(a0), void());
  template<class, class A0>
  static char test_serialize(A0&&, long);
}

template<class T, class Arg>
struct has_serialize : std::is_void<decltype(detail::test_serialize<T>(std::declval<Arg>(), 0))>{};

struct X{ void serialize(int){} };
struct Y{};

#include <iostream>

int main(){
  if (has_serialize<X, int>())
    std::cout << "X" << std::endl;
  if (has_serialize<Y, int>())
    std::cout << "Y" << std::endl;
}
