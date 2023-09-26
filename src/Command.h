#pragma once

#include "client/twitch_message.h"
#include <functional>
#include <string>
#include <vector>

class Command {
public:
  virtual std::string getName() = 0;
  virtual std::vector<std::string>
  run(const IRCMessage<IRCMessageType::PrivmsgMessage> &message) = 0;

  Command() {}
  virtual ~Command() {}
};
