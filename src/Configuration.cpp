//
// Created by Lukas Bischof on 09.06.18.
//

#include "Configuration.h"
#include "LaunchCommand.h"
#include <fstream>
#include <iostream>
#include <regex>

#define REGEX(matcher) regex((matcher), regex::ECMAScript | regex::icase)
#define TEST(string, regex_string) regex_search((string), REGEX(regex_string))

using namespace launchr;
using namespace std;

static inline void ltrim(string &string) {
  string.erase(string.begin(), find_if(string.begin(), string.end(), [](int ch) {
    return !isspace(ch);
  }));
}

Configuration::Configuration(const char *path) : confpath(path) {
  commands = std::vector<LaunchCommand>();
};

static ConfigurationError
parse_statement(string &content, string &keyword, const string &line, unsigned int current_line) {
  auto delemiter_index = line.find(string(":"));
  if (delemiter_index == string::npos) {
    return {"No delemiter found", kConfigurationErrorTypeSyntaxError, current_line};
  }

  keyword = line.substr(0, delemiter_index);
  content = line.substr(delemiter_index + 1, line.length());

  if (content.length() == 0) {
    return {"statement is empty", kConfigurationErrorTypeStatementError, current_line};
  }

  ltrim(content);

  return ConfigurationError::no_error();
}

static ConfigurationError
handle_conf_statement(string &line, LaunchCommand *current_command, unsigned int current_line) {
  string keyword;
  string content;
  ConfigurationError error = parse_statement(content, keyword, line, current_line);
  if (!error.is_no_error())
    return error;

  current_command->add_statement(keyword, content);

  return ConfigurationError::no_error();
}

static void process_line(std::string &line) {
  ltrim(line);

  if (line.find('#') != string::npos) {
    line = regex_replace(line, REGEX("#.*$"), "");
  }
}

static bool is_invalid_line(const string &line) {
  return TEST(line, "^\\s*$");
}

void Configuration::parse(ConfigurationError **configurationError) {
  ifstream ifstream(confpath);
  string line;
  LaunchCommand *current_command = nullptr;
  unsigned int current_line_number = 0;

  while (getline(ifstream, line)) {
    current_line_number++;

    process_line(line);

    if (is_invalid_line(line))
      continue;

    cout << line << endl;

    bool is_block_start = TEST(line, "\\{\\s*");
    if (is_block_start) {
      // Beginning of a new command block

      if (current_command != nullptr) {
        ConfigurationError error("Unexpected start of new block", kConfigurationErrorTypeSyntaxError,
                                 current_line_number);
        *configurationError = &error;
        goto closing;
      }

      LaunchCommand mycommand;
      current_command = &mycommand;
    } else {
      bool is_block_end = TEST(line, "\\}\\s*");
      if (is_block_end) {
        // End of a new command block

        if (!current_command->validate()) {
          ConfigurationError error("Block is missing required keywords", kConfigurationErrorTypeStatementError,
                                   current_line_number);
          *configurationError = &error;
          goto closing;
        }

        commands.push_back(*current_command);
        current_command = nullptr;
      } else {
        // Handle statement inside a command block

        ConfigurationError error = handle_conf_statement(line, current_command, current_line_number);
        if (!error.is_no_error()) {
          *configurationError = &error;
          goto closing;
        }
      }
    }
  }

closing:
  ifstream.close();
}
