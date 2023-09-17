#include "twitch.h"
#include <iostream>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>
#include <string>

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
    } else if (msg->type == ix::WebSocketMessageType::Open) {
      std::cout << "Connection established" << std::endl;

      // Authenticating
      this->ws.send(std::string("PASS ") + std::string(this->password));
      this->ws.send(std::string("NICK ") + std::string(this->username));
      this->ws.send("CAP REQ :twitch.tv/membership");
      this->ws.send("CAP REQ :twitch.tv/commands");
      this->ws.send("CAP REQ :twitch.tv/tags");
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
