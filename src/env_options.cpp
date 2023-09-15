#include "env_options.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

std::optional<env_options> parse_from_file(std::string file_name) {
  std::ifstream file(file_name);
  env_options options;

  if (file.is_open()) {
    std::string line;

    while (std::getline(file, line)) {
      std::istringstream lineStream(line);
      std::string key;
      std::string value;

      if (std::getline(lineStream, key, '=') &&
          std::getline(lineStream, value)) {
        if (key == "username") {
          options.username = value;
        } else if (key == "password") {
          options.password = value;
        } else {
          std::cout << "Failed to define " << key << " in \"" << file_name
                    << "\" file!" << std::endl;
        }
      }
    }

    return options;
  }

  return std::nullopt;
}
