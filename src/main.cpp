#include "CommandLoader.h"
#include "client/twitch.h"
#include "client/twitch_message.h"
#include "env_options.h"
#include "irc_handlers.h"
#include <iostream>
#include <optional>

int main(int argc, char *argv[]) {
  std::cout << "yo world!" << std::endl;

  std::optional<env_options> options = parse_from_file(".env");

  if (!options.has_value()) {
    std::cerr << "No options file!" << std::endl;
    return 1;
  }

  TwitchIRCClient ircClient(options->username, options->password);
  CommandLoader commandLoader;

  ircClient.on<IRCMessageType::PrivmsgMessage>(
      [&ircClient](IRCMessage<IRCMessageType::PrivmsgMessage> message) {
        handle_chat_message(&ircClient, message);
      });

  ircClient.connect();
  ircClient.join("ilotterytea");

  while (true) {
  }

  return 0;
}
