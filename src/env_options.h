#include <optional>
#include <string>

struct env_options {
  std::string username;
  std::string password;
};

std::optional<env_options> parse_from_file(std::string file_name);
