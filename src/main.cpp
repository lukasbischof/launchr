#include <iostream>
#include <zconf.h>
#include "utilities.h"
#include "confloader.h"

using namespace std;

int main() {
  char cwd[1024];

  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    errprintlnf("Can't retrieve current workdir!");
    return EXIT_FAILURE;
  } else {
    cout << cwd << endl;
  }

  load_conf();

  return EXIT_SUCCESS;
}