//
// Created by Lukas Bischof on 09.06.18.
//

#include "Configuration.h"
#include "LaunchCommand.h"
#include <fstream>
#include <iostream>
#include <regex>

#define REGEX(matcher) regex(matcher, regex::ECMAScript | regex::icase)

using namespace launchr;
using namespace std;

static inline void ltrim(std::string &string) {
  string.erase(string.begin(), std::find_if(string.begin(), string.end(), [](int ch) {
    return !isspace(ch);
  }));
}

Configuration::Configuration(const char *path) : confpath(path) { };

void Configuration::parse(ConfigurationError **configurationError) {
  ifstream ifstream(confpath);
  string line;
  LaunchCommand *current_command = NULL;
  unsigned int current_line_number = 0;

  while (getline(ifstream, line)) {
    current_line_number++;
    ltrim(line);

    if (regex_search(line, REGEX("$\\#.*")))
      continue;

    bool is_block_start = regex_search(line, REGEX("\\{\\s*"));
    if (is_block_start) {
      if (current_command != NULL) {
        ConfigurationError error(string("Unexpected start of new block"), kConfigurationErrorTypeSyntaxError, current_line_number);
        *configurationError = &error;
        goto closing;
      }

      LaunchCommand mycommand;
      current_command = &mycommand;
    }
  }

closing:
  ifstream.close();
  return;
}
