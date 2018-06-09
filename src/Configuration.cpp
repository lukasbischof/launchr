//
// Created by Lukas Bischof on 09.06.18.
//

#include "Configuration.h"
#include <fstream>
#include <iostream>

using namespace launchr;

static inline void ltrim(std::string &string) {
  string.erase(string.begin(), std::find_if(string.begin(), string.end(), [](int ch) {
    return !std::isspace(ch);
  }));
}

Configuration::Configuration(const char *path) : confpath(path) { };

bool Configuration::parse() {
  std::ifstream ifstream(confpath);
  std::string line;
  while (std::getline(ifstream, line)) {
    ltrim(line);
    std::cout << line << std::endl;
  }

  ifstream.close();

  return true;
}
