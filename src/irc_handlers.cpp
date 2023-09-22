#include "irc_handlers.h"
#include "client/twitch.h"
#include "client/twitch_message.h"

void handle_chat_message(TwitchIRCClient *client,
                         IRCMessage<IRCMessageType::PrivmsgMessage> message) {
  if (message.message == "juuuuuuuuuuuuuuuuuuuustrl") {
    client->say(message.source.name, "juuuuuuuuuuuuuuuuuuuustrl ");
  }
}
