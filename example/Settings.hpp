
#ifndef SETTINGS_HPP_
# define SETTINGS_HPP_

# include "serialize/in.hpp"
# include "serialize/out.hpp"

/**
 * Simple
 */
struct Address {
  size_t num;
  std::string street;
  void serialize(serialize::out &out);
  void deserialize(serialize::in &in);
  void print();
};

/**
 * @struct Settings
 * Simple data structure to try to serialize differents types
 * of data.
 */
struct Settings {
  static const size_t MAX_ID_NUMBER = 10;
  size_t ids[MAX_ID_NUMBER];
  std::list<std::pair<size_t, std::string>> pseudos;
  size_t size;
  bool isOnline;
  float percent;
  std::vector<std::vector<char>> square;
  std::map<std::string, Address> addresses;
  Settings();
  void serialize(serialize::out &out);
  void deserialize(serialize::in &in);
  void print();
};

#endif // !SETTINGS_HPP_