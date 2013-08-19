
#ifndef SERIALIZE_OUT_HPP_
# define SERIALIZE_OUT_HPP_

# include <vector>
# include <list>
# include <map>
# include <string>
# include <fstream>
# include <cstring>

namespace serialize {

# include "detail.inl"

/**
 * @class out
 * Used to serialize data and save it into a binary file.
 */
class out {
public:
  /**
   * Default constructor.
   */
  out()
  : _buffer(new char[DEFAULT_CAPACITY])
  , _capacity(DEFAULT_CAPACITY)
  , _size(0)
  {}

  /**
   * Construct and open file.
   */
  out(std::string const &path)
  : _buffer(new char[DEFAULT_CAPACITY])
  , _capacity(DEFAULT_CAPACITY)
  , _size(0) {
    save(path);
  }

  /**
   * Destructor.
   */
  ~out() {
    save();
    if (isOpen())
      _file.close();
  }

  bool isOpen() const {
    return _file.is_open();
  }

  /**
   * Save the buffer content to the file.
   */
  void save() {
    if (isOpen())
      _file.write(_buffer, _size);
  }

  /**
   * Save the stream content into the given file.
   * @param path The path to the file.
   * @param inFile True if you want to update the file content.
   */
  bool save(std::string const &path, bool inFile = true) {
    if (isOpen())
      _file.close();
    _file.open(path, std::ios::out | std::ios::binary);
    if (inFile)
      save();
    return isOpen();
  }

  /**
   * Basicaly serialize the given data.
   */
  template<typename FieldType>
  void basicSerialize(FieldType const &field) {
    unsigned int size = sizeof(FieldType);
    if(_size + size >= _capacity)
      _resize();
    std::memcpy(_buffer + _size, (char*)&field, size);
    _size += size;
  }

  /**
   * Serialize the given data.
   */
  template<typename FieldType>
  void serialize(FieldType const &field) {
    _serialize(*this, field);
  }

  /**
   * Serialize the given string field.
   */
  void serialize(std::string const &field) {
    std::string tmp = field + '\0';
    unsigned int size = sizeof(char) * tmp.length();
    if (_size + size >= _capacity)
      _resize();
    std::memcpy(_buffer + _size, tmp.c_str(), size);
    _size += size;
  }

  /**
   * Serialize the given vector field.
   */
  template<typename T>
  void serialize(std::vector<T> const &field) {
    if (_size + sizeof(size_t) >= _capacity)
      _resize();
    size_t size = field.size();
    std::memcpy(_buffer + _size, &size, sizeof(size_t));
    _size += sizeof(size_t);
    for (auto f : field)
      serialize(f);
  }

  /**
   * Serialize the given list field.
   */
  template<typename T>
  void serialize(std::list<T> const &field) {
    if (_size + sizeof(size_t) >= _capacity)
      _resize();
    size_t size = field.size();
    std::memcpy(_buffer + _size, &size, sizeof(size_t));
    _size += sizeof(size_t);
    for (auto f : field)
      serialize(f);
  }

  /**
   * Serialize the given pair field.
   */
  template<typename Key, typename Value>
  void serialize(std::pair<Key, Value> const &field) {
    serialize(field.first);
    serialize(field.second);
  }

  /**
   * Serialize the given map field.
   */
  template<typename Key, typename Value>
  void serialize(std::map<Key, Value> const &field) {
    if (_size + sizeof(size_t) >= _capacity)
      _resize();
    size_t size = field.size();
    std::memcpy(_buffer + _size, &size, sizeof(size_t));
    _size += sizeof(size_t);
    for (auto f : field)
      serialize(f);
  }

  /**
   * Use stream operator the serialize field.
   */
  template<typename FieldType>
  out &operator<<(FieldType const &field) {
    serialize(field);
    return *this;
  }

private:

  /**
   * Resize the buffer.
   */
  void _resize() {
    _capacity += DEFAULT_CAPACITY;
    char *newBuffer = new char[_capacity];
    std::memcpy(newBuffer, _buffer, sizeof(char) * _size);
    delete[] _buffer;
    _buffer = newBuffer;
  }

  /**
   * Choose the serialize function to use.
   */
  template<typename FieldType>
  auto _serialize(out& os, FieldType const &field)
      -> decltype(detail::_serialize(os, field, 0), void()) {
    detail::_serialize(os, field, 0);
  }
private:
  static const unsigned int DEFAULT_CAPACITY = 128;
  std::ofstream _file;
  char *_buffer;
  size_t _capacity;
  size_t _size;
};

} // !serialize::

#endif // !SERIALIZE_OUT_HPP_