#include "twitch_message.h"
#include "../utils/string.h"
#include <optional>
#include <string>
#include <vector>

std::optional<IRCMessageType> define_message_type(const std::string &msg) {
  std::vector<std::string> vec = split(msg, " ");
  std::string stringType;
  IRCMessageType type;

  if (vec[0][0] == '@') {
    stringType = vec[2];
  } else if (vec[0][0] == ':') {
    stringType = vec[1];
  } else {
    return std::nullopt;
  }

  if (stringType == "PRIVMSG") {
    return IRCMessageType::PrivmsgMessage;
  } else {
    return std::nullopt;
  }

  return std::nullopt;
}
