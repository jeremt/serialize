
#include <iostream>
#include "Settings.hpp"

void Address::serialize(serialize::out &out) {
  out << num << street;
  std::cout << "Serialize address, num: " << num << std::endl;
}

void Address::deserialize(serialize::in &in) {
  in >> num >> street;
  std::cout << "Deserialize address, num: " << num << std::endl;
}

Settings::Settings()
: ids{1, 2, 3, 4, 5, 6, 7, 8, 9}
, pseudos{{1, "bob"}, {2, "titi"}, {3, "toto"}}
, size(0)
, isOnline(false)
, percent(0.0f)
, square({
    {'x', 'x', 'x'},
    {'x', ' ', 'x'},
    {'x', 'x', 'x'}
  })
, addresses({
    {"bob  ", {42, "rue des lilas"}},
    {"toto ", {1337, "rue des lavandes"}}
  })
{}

void Settings::serialize(serialize::out &out) {
  out << size << ids << pseudos << isOnline
      << percent << square << addresses;
}

void Settings::deserialize(serialize::in &in) {
  in >> size >> ids >> pseudos >> isOnline
     >> percent >> square >> addresses;
}

void Settings::print() {
  std::cout << std::boolalpha << std::endl;
  std::cout << "  Settings"                 << std::endl;
  std::cout << std::endl;
  std::cout << "    size     " << size      << std::endl;
  std::cout << "    isOnline " << isOnline  << std::endl;
  std::cout << "    percent  " << percent   << std::endl;
  std::cout << "    ids"                    << std::endl;
  for (size_t i = 0; i < size; ++i)
    std::cout << "             " <<  ids[i] << std::endl;
  std::cout << "    pseudos"                << std::endl;
  for (auto p : pseudos)
    std::cout << "             "
              << p.first << " "
              << p.second                   << std::endl;
  std::cout << "    square"                 << std::endl; 
  for (auto line : square) {
    std::cout << "             ";
    for (auto point : line)
      std::cout << point;
    std::cout << std::endl;
  }
  std::cout << "    addresses"              << std::endl;
  for (auto addr : addresses)
    std::cout << "             "
              << addr.first << " "
              << addr.second.num << " "
              << addr.second.street           << std::endl;
  std::cout << std::endl;
}