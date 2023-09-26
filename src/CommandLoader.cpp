#include "CommandLoader.h"
#include "Command.h"
#include "client/twitch_message.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

// TODO: Do some reflection shit (if possible)
CommandLoader::CommandLoader() {}

void CommandLoader::registerCommand(std::shared_ptr<Command> command) {
  this->_commands.push_back(command);
}

std::optional<std::vector<std::string>>
CommandLoader::run(std::string commandId,
                   const IRCMessage<IRCMessageType::PrivmsgMessage> &message) {
  for (std::shared_ptr<Command> cmd : this->_commands) {
    if (cmd->getName() == commandId) {
      return cmd->run(message);
    }
  }

  return std::nullopt;
}
