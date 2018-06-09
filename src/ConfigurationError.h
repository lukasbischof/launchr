//
// Created by Lukas Bischof on 09.06.18.
//

#ifndef LAUNCHR_CONFIGURATIONERROR_H
#define LAUNCHR_CONFIGURATIONERROR_H

#include <stdlib.h>
#include <string>

using namespace std;

namespace launchr {
  typedef const char *ConfigurationErrorType;
  static ConfigurationErrorType kConfigurationErrorTypeSyntaxError = "SyntaxError";

  class ConfigurationError {
  public:
    const char *message;
    ConfigurationErrorType type;
    const unsigned int line;

    ConfigurationError(const char *message, ConfigurationErrorType type, unsigned int line)
        : message(message), type(type), line(line) {};

    const char *description();
  };
};


#endif //LAUNCHR_CONFIGURATIONERROR_H
