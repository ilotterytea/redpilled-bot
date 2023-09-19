#include "../utils/string.h"
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

enum IRCMessageType { PrivmsgMessage, NoticeMessage };

template <IRCMessageType T> struct MessageHandler;

template <> struct MessageHandler<IRCMessageType::PrivmsgMessage> {
  using fn = std::function<void(std::string msg)>;
};

std::optional<IRCMessageType> define_message_type(const std::string &msg);

struct MessageSender {
  bool isSubscriber;
  bool isTurbo;
  bool isReturningChatter;
  bool isFirstMessage;
  bool isMod;

  std::string id;
  std::string name;
  std::string displayName;

  std::string color;

  std::map<std::string, int> badgeInfo;
};

struct MessageSource {
  std::string id;
  std::string name;
};

template <IRCMessageType T> struct IRCMessage;

template <> struct IRCMessage<IRCMessageType::PrivmsgMessage> {
  MessageSender sender;
  MessageSource source;
  std::string message;
  std::string messageId;
};

template <IRCMessageType T>
std::optional<IRCMessage<T>> parse_message(const std::string &msg) {
  std::vector<std::string> vec = split(msg, " ");

  if (T == IRCMessageType::PrivmsgMessage) {
    MessageSender sender;
    MessageSource source;
    IRCMessage<IRCMessageType::PrivmsgMessage> message;

    // getting message
    vec[4] = vec[4].substr(1, vec[4].length());

    for (int i = 4; i < vec.size(); i++) {
      message.message += vec[i] + " ";
    }

    int mStart = message.message.find_first_not_of(" \t\n\r\f\v");
    if (mStart != std::string::npos) {
      message.message = message.message.substr(mStart);
    }

    int mEnd = message.message.find_last_not_of(" \t\n\r\f\v");
    if (mEnd != std::string::npos) {
      message.message = message.message.substr(0, mEnd + 1);
    }

    // getting channel name
    source.name = vec[vec.size() - 2].substr(1, vec[vec.size() - 2].length());

    // getting user name
    std::vector<std::string> userNameSplit = split(vec[1], "!");
    sender.name = userNameSplit[0].substr(1, userNameSplit[0].length());

    // parsing user info
    std::vector<std::string> userInfo = split(vec[0], ";");

    for (std::string str : userInfo) {
      std::vector<std::string> strSplit = split(str, "=");
      std::string key = strSplit[0];
      std::string value = strSplit[1];

      // this is dumb
      if (key == "user-id") {
        sender.id = value;
      } else if (key == "turbo") {
        sender.isTurbo = std::stoi(value);
      } else if (key == "subscriber") {
        sender.isSubscriber = std::stoi(value);
      } else if (key == "room-id") {
        source.id = value;
      } else if (key == "returning-chatter") {
        sender.isReturningChatter = std::stoi(value);
      } else if (key == "mod") {
        sender.isMod = std::stoi(value);
      } else if (key == "id") {
        message.messageId = value;
      } else if (key == "first-msg") {
        sender.isFirstMessage = std::stoi(value);
      } else if (key == "display-name") {
        sender.displayName = value;
      } else if (key == "color") {
        sender.color = value;
      } else {
        std::cout << "\"" << key << "\" key is not defined!" << std::endl;
      }
    }

    message.source = source;
    message.sender = sender;

    return message;
  }

  return std::nullopt;
}
