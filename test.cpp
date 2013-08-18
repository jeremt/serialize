#include <iostream>

namespace detail {

  // SFINAE test
  template<typename Obj>
  class has_serialize {
    typedef char true_t;
    typedef int false_t;
    template <typename C> static true_t test(typeof(&C::serialize));
    template <typename C> static false_t test(...);
  public:
    enum {value = sizeof(test<Obj>(0)) == sizeof(true_t)};
  };

  template<typename Obj>
  class try_serialize {
    // TODO
  };

}

// http://stackoverflow.com/questions/10957924/is-there-any-way-to-detect-whether-a-function-exists-and-can-be-used-at-compile
// http://stackoverflow.com/questions/10957924/is-there-any-way-to-detect-whether-a-function-exists-and-can-be-used-at-compile

template<typename Type>
void serialize(Type const &field)  {
  if (detail::has_serialize<Type>::value)
    std::cout << "From method" << std::endl;
  else
    std::cout << "Basic" << std::endl;
}

class B {
public:
  void serialize() {
    std::cout << "serialize !!!" << std::endl;
  }
};

// TODO - Find a way to call field.serialize();
// (template specification from has_serialize::value)

int main()
{
  int a;
  B b;

  serialize(a);
  serialize(b);
  return 0;
}
