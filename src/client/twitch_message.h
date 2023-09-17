#include <functional>
#include <optional>
#include <string>

enum IRCMessageType { PrivmsgMessage, NoticeMessage };

template <IRCMessageType T> struct MessageHandler;

template <> struct MessageHandler<IRCMessageType::PrivmsgMessage> {
  using fn = std::function<void(std::string msg)>;
};

std::optional<IRCMessageType> define_message_type(const std::string &msg);
