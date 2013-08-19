
#include <iostream>
#include "out_test.hpp"

// template<class T> struct has_serialize
// {
//     typedef char (&Yes)[1];
//     typedef char (&No)[2];

//     template<class U>
//     static Yes test(U * data, MyClass* arg1 = 0,
//                     typename std::enable_if<std::is_void<
//                              decltype(data->serialize(*arg1, 1u))
//                     >::value>::type * = 0) {
//       std::cout << "Has" << std::Endl;
//     }

//     static No test(...) {
//       std::cout << "Default" << std::endl;
//     }
//     static const bool value = sizeof(Yes) == sizeof(has_serialize::test((typename std::remove_reference<T>::type*)0));
// };

struct Success {
  void serialize(serialize::out &os) const{
    std::cout << "serialize from method" << std::endl;
  }
};

struct Fail {};
 
int main(){
  serialize::out os;
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