
#include <iostream>
#include "Message.hpp"

Message::Message()
: id(0)
, text("")
, next(0)
{}

Message::Message(Message *ne)
: id(0)
, text("")
, next(ne)
{}

Message::Message(size_t id, std::string const &txt, Message *ne)
: id(id)
, text(txt)
, next(ne)
{}

void Message::serialize(serialize::out &out)
{
  out << id << text;
  if (next)
    next->serialize(out);
}

void Message::deserialize(serialize::in &in)
{
  in >> id >> text;
  if (next)
    next->deserialize(in);
}

void Message::print()
{
  std::cout << "  " << id << "> " << text << std::endl;
  if (next)
    next->print();
}