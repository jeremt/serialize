
#include <iostream>
#include "Settings.hpp"
#include "Message.hpp"

/**
 * Test deserialisation feature.
 */
static void testSerialize()
{
  // settings
  serialize::out settingsStream("settings.bin");
  Settings settings;
  settings.size = 5;
  settings.isOnline = true;
  settings.percent = 42.21f;
  settings.addresses["titi "].num = 21;
  settings.addresses["titi"].street = "rue des tulipes";

  settings.serialize(settingsStream);
  // message
  serialize::out msgStream("messages.bin");
  Message next("titi", "Hi guys!");
  Message msg("bob", "Hello ;)", &next);
  msg.serialize(msgStream);


  // addresses
  serialize::out addrStream("test.bin");
  Address addr = {50, "rue des fleurs"};
  addrStream.serialize(addr); // addr.serialize() should be called.
  addr.print();
}

static void testDeserialize()
{
  // settings
  serialize::in settingsStream("settings.bin");
  Settings settings;
  settings.deserialize(settingsStream);
  settings.print();
  // message
  serialize::in msgStream("messages.bin");
  Message next;
  Message msg(&next);
  msg.deserialize(msgStream);
  msg.print();
  std::cout << std::endl;

  // serialize::in addrStream;
  // std::list<Address> addrList;
  // addrStream.deserialize(addrList);
  // for (auto addr : addrList)
  //   std::cout << addr.num << " " << addr.street << std::endl;


}

/**
 * Entry point.
 */
int main()
{
  testSerialize();
  testDeserialize();
}