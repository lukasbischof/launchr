#include <iostream>
#include <zconf.h>
#include "utilities.h"
#include "confloader.h"
#include "Configuration.h"

using namespace std;
using namespace launchr;

int main() {
  char cwd[1024];

  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    errprintlnf("Can't retrieve current workdir!");
    return EXIT_FAILURE;
  } else {
    cout << cwd << endl;
  }

  const char *confpath = getconfpath();
  if (confpath == NULL) {
      errprintlnf("Cannot load configuration");
      return EXIT_FAILURE;
  } else {
      debugprintlnf("loading configuration %s", confpath);
  }

  Configuration configuration(confpath);
  ConfigurationError *error;
  configuration.parse(&error);
  if (error != NULL) {
    errprintlnf("Can't read configuration file: %s", error->description());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
