#include "irc_handlers.h"
#include "CommandLoader.h"
#include "SharedVariables.h"
#include "client/twitch.h"
#include "client/twitch_message.h"
#include <optional>
#include <string>
#include <vector>

void handle_chat_message(TwitchIRCClient *client, CommandLoader *commandLoader,
                         IRCMessage<IRCMessageType::PrivmsgMessage> message) {
  if (message.message == "juuuuuuuuuuuuuuuuuuuustrl") {
    client->say(message.source.name, "juuuuuuuuuuuuuuuuuuuustrl ");
  }

  std::optional<std::vector<std::string>> response =
      commandLoader->run(message.message, message);

  if (response.has_value()) {
    for (std::string msg : response.value()) {
      client->say(message.source.name, msg);
    }
  }
}
