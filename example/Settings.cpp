
#include <iostream>
#include "Settings.hpp"

Settings::Settings()
: ids{1, 2, 3, 4, 5, 6, 7, 8, 9}
, size(0)
, isOnline(false)
, percent(0.0f)
{}

void Settings::serialize(serialize::out &out) {
  out << size << ids << isOnline << percent;
}

void Settings::deserialize(serialize::in &in) {
  in >> size >> ids >> isOnline >> percent;
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
    std::cout << "      "      << ids[i]    << std::endl;
  std::cout << std::endl;
}