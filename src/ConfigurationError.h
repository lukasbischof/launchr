//
// Created by Lukas Bischof on 09.06.18.
//

#ifndef LAUNCHR_CONFIGURATIONERROR_H
#define LAUNCHR_CONFIGURATIONERROR_H

#include <cstdlib>
#include <string>

using namespace std;

namespace launchr {
  typedef const char *ConfigurationErrorType;
  static ConfigurationErrorType kConfigurationErrorTypeSyntaxError = "SyntaxError";
  static ConfigurationErrorType kConfigurationErrorTypeStatementError = "StatementError";
  static ConfigurationErrorType kConfigurationErrorTypeNone = "NoError";

  class ConfigurationError {
  public:
    const char *message;
    ConfigurationErrorType type;
    const unsigned int line;

    ConfigurationError(const char *message, ConfigurationErrorType type, unsigned int line)
        : message(message), type(type), line(line) {};

    static ConfigurationError no_error();
    
    bool is_no_error() const;
    const char *description();
  };
};


#endif //LAUNCHR_CONFIGURATIONERROR_H
