#include "twitch.h"
#include "../utils/string.h"
#include <algorithm>
#include <ios>
#include <iostream>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>
#include <optional>
#include <string>
#include <vector>

TwitchIRCClient::TwitchIRCClient(std::string username, std::string password) {
  this->username = username;
  this->password = password;

  this->host = "wss://irc-ws.chat.twitch.tv";
}

void TwitchIRCClient::connect() {
  // Required on Windows
  ix::initNetSystem();

  this->ws.setUrl(this->host);

  std::cout << "Connecting to " << this->host << "..." << std::endl;

  this->ws.setOnMessageCallback([this](const ix::WebSocketMessagePtr &msg) {
    if (msg->type == ix::WebSocketMessageType::Message) {
      std::cout << "received message: " << msg->str << std::endl;

      std::vector<std::string> vec = split(msg->str, "\n");

      for (std::string m : vec) {
        m.erase(std::remove_if(
                    m.begin(), m.end(),
                    [](char c) { return c == '\n' || c == '\r' || c == '\t'; }),
                m.end());

        std::optional<IRCMessageType> type = define_message_type(m);
        IRCMessageType mType;

        if (!type.has_value()) {
          continue;
        } else {
          mType = type.value();
        }
        if (mType == IRCMessageType::PrivmsgMessage) {
          std::optional<IRCMessage<IRCMessageType::PrivmsgMessage>> message =
              parse_message<IRCMessageType::PrivmsgMessage>(m);

          if (!message.has_value()) {
            std::cout << "this shit has no value" << std::endl;
            continue;
          }

          this->_onPrivmsgMessage(message.value());
        }
      }

    } else if (msg->type == ix::WebSocketMessageType::Open) {
      std::cout << "Connection established" << std::endl;

      // Authenticating
      this->ws.send(std::string("PASS ") + std::string(this->password));
      this->ws.send(std::string("NICK ") + std::string(this->username));
      this->ws.send("CAP REQ :twitch.tv/membership");
      this->ws.send("CAP REQ :twitch.tv/commands");
      this->ws.send("CAP REQ :twitch.tv/tags");

      if (!this->pool.empty()) {
        std::cout << "Sending messages from pool..." << std::endl;

        for (std::string msg : this->pool) {
          this->ws.send(msg);
        }

        this->pool.clear();
        std::cout << "Sent all messages from pool!" << std::endl;
      }

      for (std::string channel : this->joinedChannels) {
        this->join(channel);
      }

    } else if (msg->type == ix::WebSocketMessageType::Error) {
      std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
    }
  });

  this->ws.start();
}

void TwitchIRCClient::join(std::string channelName) {
  std::string str = "JOIN #" + channelName;

  if (this->ws.getReadyState() != ix::ReadyState::Open) {
    this->pool.push_back(str);
  } else {
    this->ws.send(str);
    this->joinedChannels.push_back(channelName);
  }
}

void TwitchIRCClient::say(std::string channelName, std::string message) {
  this->ws.send(std::string("PRIVMSG #") + channelName + std::string(" :") +
                message);
}
