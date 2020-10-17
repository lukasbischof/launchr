//
// Created by Lukas Bischof on 09.06.18.
//

#ifndef LAUNCHR_CONFIGURATION_H
#define LAUNCHR_CONFIGURATION_H


#include <vector>
#include "ConfigurationError.h"
#include "LaunchCommand.h"

namespace launchr {
  class Configuration {
  private:
    const char *confpath;
  public:
    explicit Configuration(const char *path);

    std::vector<LaunchCommand> commands;

    void parse(ConfigurationError **configurationError);
  };
};


#endif //LAUNCHR_CONFIGURATION_H
