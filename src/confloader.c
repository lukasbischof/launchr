//
// Created by Lukas Bischof on 07.06.18.
//

#include <zconf.h>
#include <stdlib.h>
#include "confloader.h"

static bool create_local_conf(const char *localconf) {
  FILE *fp;
  if ((fp = fopen(localconf, "w")) == NULL) {
    return true;
  }

  if (fprintf(fp, "{}") < 0) {
    fclose(fp);
    return false;
  }

  fclose(fp);
  return true;
}

static inline bool fexists(const char *f) {
  return access(f, F_OK) != -1;
}

const char *getconfpath() {
  const char *sysconf = "/etc/launchr.conf";
  bool sysconf_exists = fexists(sysconf);

  const char *homedir;
  if ((homedir = getenv("HOME")) != NULL) {
    char *localconf = malloc(512);
    sprintf(localconf, "%s/.launchr.conf", homedir);
    if (fexists(localconf)) {
      return localconf;
    } else if (!sysconf_exists) {
      debugprintlnf("No config file found. Creating one...");

      if (create_local_conf(localconf)) {
        return localconf;
      }
    }
  }

  return (sysconf_exists) ? sysconf : NULL;
}
