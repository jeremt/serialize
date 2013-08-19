
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
}

/**
 * Entry point.
 */
int main()
{
  testSerialize();
  testDeserialize();
}