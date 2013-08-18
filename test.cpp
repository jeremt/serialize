
#include <type_traits>
#include <iostream>

class out;

// namespace detail {
  template<typename T>
  auto _serialize(out& os, T const& obj, long)
      -> decltype(obj, void()) {
    std::cout << "no method, address is: " << &obj << std::endl;
  }
   
  template<typename T>
  auto _serialize(out& os, T const& obj, int)
      -> decltype(obj.serialize(os), void()) {
    obj.serialize(os);
  }
// }

class out {
  template<typename T>
  auto _serialize(out& os, T const& obj)
      -> decltype(_serialize(os, obj, 0), void()) {
    ::_serialize(os, obj, 0);
  }
public:
  int buffer;
public:

  template<typename T>
  void serialize(T const &obj) {
    _serialize(*this, obj);
  }

  void serialize(std::string const &s) {
    std::cout << "special case: " << s << std::endl;
  }
};

struct Success {
  void serialize(out &os) const{
    std::cout << "serialize, buffer is: " << os.buffer << std::endl;
  }
};

struct Fail {};
 
int main(){
  out os;
  Success success;
  Fail fail;
  std::string s = "hello";

  os.buffer = 42;
  std::cout << "---" << std::endl; os.serialize(5);
  std::cout << "---" << std::endl; os.serialize(success);
  std::cout << "---" << std::endl; os.serialize(fail);
  std::cout << "---" << std::endl; os.serialize(s);
  std::cout << "---" << std::endl;
}