#include <ixwebsocket/IXWebSocket.h>
#include <string>

class TwitchIRCClient {
public:
  TwitchIRCClient(std::string username, std::string password);
  void connect();

private:
  std::string username;
  std::string password;
  std::string host;
  ix::WebSocket ws;

  void run();
};
