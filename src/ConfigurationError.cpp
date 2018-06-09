//
// Created by Lukas Bischof on 09.06.18.
//

#include "ConfigurationError.h"

const char *launchr::ConfigurationError::description() {
  char *output = static_cast<char *>(malloc(512));
  sprintf(output, "%s: %s at line %u", type, message, line);

  return output;
}
