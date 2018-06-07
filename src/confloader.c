//
// Created by Lukas Bischof on 07.06.18.
//

#include <zconf.h>
#include <stdlib.h>
#include "confloader.h"
#include "utilities.h"

static boolean_t create_local_conf(const char *localconf) {
  FILE *fp;
  if ((fp = fopen(localconf, "w")) == NULL) {
    return FALSE;
  }

  if (fprintf(fp, "{}") < 0) {
    fclose(fp);
    return FALSE;
  }

  fclose(fp);
  return TRUE;
}

static inline boolean_t fexists(const char *f) {
  return access(f, F_OK) != -1;
}

static const char *getconfpath() {
  const char *homedir;
  if ((homedir = getenv("HOME")) != NULL) {
    char *localconf = malloc(1024);
    sprintf(localconf, "%s/.launchr.conf", homedir);
    if (fexists(localconf)) {
      return localconf;
    } else {
      const char *sysconf = "/etc/launchr.conf";
      if (fexists(sysconf)) {
        return sysconf;
      } else {
        debugprintlnf("No config file found. Creating one...");

        if (create_local_conf(localconf)) {
          return localconf;
        }
      }
    }
  }

  return NULL;
}

boolean_t load_conf() {
  debugprintlnf("loading configuration...");

  const char *path = getconfpath();
  if (path == NULL) {
    debugprintlnf("Can't retrieve configuration file path");
  }

  debugprintlnf("Using configuration %s", path);

  return TRUE;
}
