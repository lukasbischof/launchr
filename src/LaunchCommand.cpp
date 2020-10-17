//
// Created by Lukas Bischof on 09.06.18.
//

#include "LaunchCommand.h"
#include <vector>

namespace launchr {
  static const char *kLaunchCommandKeywordName = "name";
  static const char *kLaunchCommandKeywordTest = "test";
  static const char *kLaunchCommandKeywordCommand = "command";

  static const std::vector<const char *> kLaunchCommandRequiredKeywords = {
      kLaunchCommandKeywordName,
      kLaunchCommandKeywordTest,
      kLaunchCommandKeywordCommand
  };

  LaunchCommand::LaunchCommand() {
    statements = std::map<std::string, std::string>();
  }

  void LaunchCommand::add_statement(const std::string &key, const std::string &value) {
    statements.insert(std::pair<std::string, std::string>(key, value));
  }

  const char *LaunchCommand::get_statement(const std::string &key) const {
    if (statements.find(key) == statements.end()) {
      return nullptr;
    } else {
      return statements.at(key).c_str();
    }
  }

  bool LaunchCommand::validate() const {
    for (auto key : kLaunchCommandRequiredKeywords) {
      if (statements.find(string(key)) == statements.end())
        return false;
    }

    return true;
  }

  const char *LaunchCommand::name() const {
    return get_statement("name");
  }

  const char *LaunchCommand::test() const {
    return get_statement("test");
  }
}
