#pragma once

#include "Command.h"
#include "client/twitch_message.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

class CommandLoader {
public:
  CommandLoader();
  void registerCommand(std::shared_ptr<Command> command);
  std::optional<std::vector<std::string>>
  run(std::string commandId,
      const IRCMessage<IRCMessageType::PrivmsgMessage> &message);

private:
  std::vector<std::shared_ptr<Command>> _commands;
};
