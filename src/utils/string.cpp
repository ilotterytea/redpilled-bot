#include "string.h"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string string, std::string delimiter) {
  int pos_start = 0;
  int pos_end;
  int delim_len = delimiter.length();

  std::string token;
  std::vector<std::string> vec;

  while ((pos_end = string.find(delimiter, pos_start)) != std::string::npos) {
    token = string.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;

    vec.push_back(token);
  }

  vec.push_back(string.substr(pos_start));

  return vec;
}
