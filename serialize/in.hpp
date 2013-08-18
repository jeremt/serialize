
#ifndef SERIALIZE_IN_HPP_
# define SERIALIZE_IN_HPP_

# include <string>
# include <vector>
# include <list>
# include <map>
# include <cstring>
# include <fstream>
# include <stdexcept>

#include <iostream>
namespace serialize {

/**
 * @class in
 * Used to load binary data from file and serialize the class.
 */
class in {
public:
  /**
   * Default constructor (need to load data after).
   */
  in()
  : _counter(0)
  {}

  /**
   * Create a serialize input stream.
   * @param size The buffer size.
   */
  in(std::string const &path)
  : _counter(0) {
    load(path);
  }

  /**
   * Destruct the input stream all free all allocated memory.
   */
  ~in() {
    delete[] _buffer;
    _file.close();
  }

  /**
   * Check if the file is open.
   */
  bool isOpen() const {
    return _file.is_open();
  }

  /**
   * Load data from file.
   * @param path The path to the file.
   */
  bool load(std::string const &path) {
    _file.open(path.c_str(), std::ios::in | std::ios::binary);
    if (!isOpen())
      return false;
    _file.seekg(0, std::ios::end);
    _size = _file.tellg();
    _file.seekg(0, std::ios::beg);
    _buffer = new char[_size];
    _file.read(_buffer, _size);
    return true;
  }

  /**
   * Deserialize the next data.
   * @param field The data field to fill.
   */
  template<typename T>
  void deserialize(T &field) {
    size_t size = sizeof(field);
    if (_counter + size > _size)
      throw std::out_of_range("Cannot read data.");
    std::memcpy(
      reinterpret_cast<char *>(&field),
      _buffer + _counter,
      size
    );
    _increaseCounter(size);
  }

  /**
   * Deserialize the next string.
   * @param field The string field to fill.
   */
  void deserialize(std::string &field) {
    field.clear();
    while (_getCurrentByte() != '\0') {
      field += _getCurrentByte();
      _increaseCounter(1);
    }
    _increaseCounter(1);
  }

  /**
   * Deserialize the next vector.
   * @param field The string field to fill.
   */
  template<typename T>
  void deserialize(std::vector<T> &field) {
    if (_counter + sizeof(size_t) > _size)
      throw std::out_of_range("Cannot read data.");
    size_t size;
    std::memcpy(&size, _buffer + _counter, sizeof(size_t));
    _increaseCounter(sizeof(size_t));
    field.clear();
    T f;
    for (size_t i = 0; i < size; ++i) {
      deserialize(f);
      field.push_back(std::move(f));
    }
  }

  /**
   * Deserialize the next list.
   * @param field The string field to fill.
   */
  template<typename T>
  void deserialize(std::list<T> &field) {
    if (_counter + sizeof(size_t) > _size)
      throw std::out_of_range("Cannot read data.");
    size_t size;
    std::memcpy(&size, _buffer + _counter, sizeof(size_t));
    _increaseCounter(sizeof(size_t));
    field.clear();
    T f;
    for (size_t i = 0; i < size; ++i) {
      deserialize(f);
      field.push_back(std::move(f));
    }
  }

  /**
   * Deserialize the next pair.
   * @param field The string field to fill.
   */
  template<typename Key, typename Value>
  void deserialize(std::pair<Key, Value> &field) {
    deserialize(field.first);
    deserialize(field.second);
  }

  /**
   * Deserialize the next map.
   * @param field The string field to fill.
   */
  template<typename Key, typename Value>
  void deserialize(std::map<Key, Value> &field) {
    if (_counter + sizeof(size_t) > _size)
      throw std::out_of_range("Cannot read data.");
    size_t size;
    std::memcpy(&size, _buffer + _counter, sizeof(size_t));
    _increaseCounter(sizeof(size_t));
    field.clear();
    std::pair<Key, Value> f;
    for (size_t i = 0; i < size; ++i) {
      deserialize(f);
      field[f.first] = f.second;
    }
  }

  /**
   * Simple stream operator to deserialize.
   */
  template<typename T>
  in &operator>>(T &field) {
    deserialize(field);
    return *this;
  }

private:

  /**
   * Increate buffer offset.
   */
  void _increaseCounter(size_t size) {
    if (_counter + size > _size)
      throw std::out_of_range("Cannot increase offset.");
    _counter += size;
  }

  /**
   * Return current byte of the buffer.
   */
  char _getCurrentByte() {
    return (_buffer + _counter)[0];
  }
private:
  std::ifstream _file;
  char* _buffer;
  size_t _size;
  size_t _counter;
};

}

#endif // !SERIALIZE_IN_HPP_