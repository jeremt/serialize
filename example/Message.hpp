
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
  std::string name;
  std::string text;
  Message *next;
  Message();
  Message(Message *ne);
  Message(
    std::string const &n,
    std::string const &t,
    Message *ne = NULL
  );
  void serialize(serialize::out &out);
  void deserialize(serialize::in &in);
  void print();

};

#endif // !MESSAGE_HPP_