//
// Created by Lukas Bischof on 09.06.18.
//

#ifndef LAUNCHR_CONFIGURATION_H
#define LAUNCHR_CONFIGURATION_H


#include "ConfigurationError.h"

namespace launchr {
  class Configuration {
  private:
      const char *confpath;
  public:
      Configuration(const char *path);
      void parse(ConfigurationError **configurationError);
  };
};


#endif //LAUNCHR_CONFIGURATION_H
