//
// Created by Lukas Bischof on 09.06.18.
//

#ifndef LAUNCHR_LAUNCHCOMMAND_H
#define LAUNCHR_LAUNCHCOMMAND_H


#include <string>
#include <map>

using namespace std;

namespace launchr {
  class LaunchCommand {
  public:
    const char *name() const;

    const char *command() const;

    const char *test() const;

    LaunchCommand();

    void add_statement(const string &key, const string &value);

    bool validate() const;

  protected:
    map<string, string> statements;

  private:
    const char *get_statement(const std::string &key) const;
  };
}


#endif //LAUNCHR_LAUNCHCOMMAND_H
