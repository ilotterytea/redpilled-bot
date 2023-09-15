#include "env_options.h"
#include <iostream>
#include <optional>

int main(int argc, char *argv[]) {
  std::cout << "yo world!" << std::endl;

  std::optional<env_options> options = parse_from_file(".env");

  if (!options.has_value()) {
    std::cerr << "No options file!" << std::endl;
    return 1;
  }

  return 0;
}
