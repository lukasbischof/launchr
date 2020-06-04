//
// Created by Lukas Bischof on 09.06.18.
//

#include "ConfigurationError.h"

const char *launchr::ConfigurationError::description() {
  char *output = static_cast<char *>(malloc(512));
  sprintf(output, "%s: %s at line %u", type, message, line);

  return output;
}

launchr::ConfigurationError launchr::ConfigurationError::no_error() {
  return ConfigurationError(nullptr, kConfigurationErrorTypeNone, -1);
}

bool launchr::ConfigurationError::is_no_error() const {
  return type == kConfigurationErrorTypeNone;
}
