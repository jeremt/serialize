
#ifndef SETTINGS_HPP_
# define SETTINGS_HPP_

# include "serialize/in.hpp"
# include "serialize/out.hpp"

/**
 * @struct Settings
 * Simple data structure to try to serialize differents types
 * of data.
 */
struct Settings {
  static const size_t MAX_ID_NUMBER = 10;
  size_t ids[MAX_ID_NUMBER];
  size_t size;
  bool isOnline;
  float percent;
  Settings();
  void serialize(serialize::out &out);
  void deserialize(serialize::in &in);
  void print();
};

#endif // !SETTINGS_HPP_