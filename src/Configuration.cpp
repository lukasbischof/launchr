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

Configuration::Configuration(const char *path) : confpath(path) {
  commands = std::vector<LaunchCommand>();
};

static ConfigurationError *handle_conf_statement(string line, LaunchCommand *current_command) {
  current_command->name = string("hi");

  return NULL;
}

void Configuration::parse(ConfigurationError **configurationError) {
  ifstream ifstream(confpath);
  string line;
  LaunchCommand *current_command = NULL;
  unsigned int current_line_number = 0;

  while (getline(ifstream, line)) {
    current_line_number++;
    ltrim(line);

    if (regex_search(line, REGEX("^\\#.*")))
      continue;

    bool is_block_start = regex_search(line, REGEX("\\{\\s*"));
    if (is_block_start) {
      // Beginning of a new command block

      if (current_command != NULL) {
        ConfigurationError error("Unexpected start of new block", kConfigurationErrorTypeSyntaxError, current_line_number);
        *configurationError = &error;
        goto closing;
      }

      LaunchCommand mycommand;
      current_command = &mycommand;
    } else {
      bool is_block_end = regex_search(line, REGEX("\\}\\s*"));
      if (is_block_end) {
        // End of a new command block

        commands.push_back(*current_command);
        current_command = NULL;
      } else {
        // Handle statement inside a command block

        ConfigurationError *error = handle_conf_statement(line, current_command);
        if (error != NULL) {
          *configurationError = error;
          goto closing;
        }
      }
    }
  }

closing:
  ifstream.close();
  return;
}
