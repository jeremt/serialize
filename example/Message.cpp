
#include <iostream>
#include "Message.hpp"

Message::Message()
: name("anonymous")
, text("")
, next(0)
{}

Message::Message(Message *ne)
: name("anonymous")
, text("")
, next(ne)
{}

Message::Message(
  std::string const &n,
  std::string const &t,
  Message *ne
)
: name(n)
, text(t)
, next(ne)
{}

void Message::serialize(serialize::out &out)
{
  out << name << text;
  if (next)
    next->serialize(out);
}

void Message::deserialize(serialize::in &in)
{
  in >> name >> text;
  if (next)
    next->deserialize(in);
}

void Message::print()
{
  std::cout << "  " << name << "> " << text << std::endl;
  if (next)
    next->print();
}