//
// Created by Lukas Bischof on 09.06.18.
//

#ifndef LAUNCHR_LAUNCHCOMMAND_H
#define LAUNCHR_LAUNCHCOMMAND_H


#include <string>

namespace launchr {
  class LaunchCommand {
  public:
    std::string name;
    std::string command;
    std::string test;
  };
}


#endif //LAUNCHR_LAUNCHCOMMAND_H
