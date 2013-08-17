
#ifndef SERIALIZE_OUT_HPP_
# define SERIALIZE_OUT_HPP_

# include <string>
# include <fstream>
# include <cstring>

namespace serialize {

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
   * Serialize the given string field.
   */
  void serialize(std::string const &field) {
    std::string tmp = field + '\0';
    unsigned int size = sizeof(char) * tmp.length();
    if (_size + size >= _capacity)
      _resize();
    memcpy(_buffer + _size, tmp.c_str(), size);
    _size += size;
  }

  /**
   * Serialize the given data.
   */
  template<typename T>
  void serialize(T const &value) {
    unsigned int size = sizeof(T);
    if(_size + size >= _capacity)
      _resize();
    memcpy(_buffer + _size, (char*)&value, size);
    _size += size;
  }

  /**
   * Use stream operator the serialize field.
   */
  template<typename T>
  out &operator<<(T const &field) {
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
private:
  static const unsigned int DEFAULT_CAPACITY = 128;
  std::ofstream _file;
  char *_buffer;
  size_t _capacity;
  size_t _size;
};

}

#endif // !SERIALIZE_OUT_HPP_