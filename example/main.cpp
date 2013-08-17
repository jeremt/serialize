
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
  settings.serialize(settingsStream);
  // message
  serialize::out msgStream("messages.bin");
  Message next(42, "Hi guys!");
  Message msg(21, "Hello ;)", &next);
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