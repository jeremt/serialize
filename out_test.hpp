
#ifndef OUT_TEST_HPP_
# define OUT_TEST_HPP_

# include <type_traits>

namespace serialize {

# include "detail.inl"

class out {
  template<typename ObjType>
  auto _serialize(out& os, ObjType const& obj)
      -> decltype(detail::_serialize(os, obj, 0), void()) {
    detail::_serialize(os, obj, 0);
  }
public:
  int buffer;
public:

  template<typename ObjType>
  void basicSerialize(ObjType const &obj) {
    std::cout << "basic serialization of "
              << &obj << " in " << buffer
              << std::endl;
  }

  template<typename ObjType>
  void serialize(ObjType const &obj) {
    _serialize(*this, obj);
  }

  void serialize(std::string const &s) {
    std::cout << "special case: " << s << std::endl;
  }
};

}

#endif // !OUT_TEST_HPP_