
#ifndef MESSAGE_HPP_
# define MESSAGE_HPP_

# include <string>
# include "serialize/in.hpp"
# include "serialize/out.hpp"

/**
 * @struct Message
 * Simple structure to test chainable serialization.
 */
struct Message {
  size_t id;
  std::string text;
  Message *next;
  Message();
  Message(Message *ne);
  Message(size_t id, std::string const &message, Message *ne = NULL);
  void serialize(serialize::out &out);
  void deserialize(serialize::in &in);
  void print();

};

#endif // !MESSAGE_HPP_