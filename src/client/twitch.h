#include <ixwebsocket/IXWebSocket.h>
#include <string>
#include <vector>

class TwitchIRCClient {
public:
  TwitchIRCClient(std::string username, std::string password);
  void connect();
  void join(std::string channelName);
  void say(std::string channelName, std::string message);

private:
  std::string username;
  std::string password;
  std::string host;
  ix::WebSocket ws;

  std::vector<std::string> pool;
  std::vector<std::string> joinedChannels;

  void run();
};
