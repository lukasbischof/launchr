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

const char *getconfpath() {
  const char *sysconf = "/etc/launchr.conf";
  boolean_t sysconf_exists = fexists(sysconf);
  
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
