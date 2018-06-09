//
// Created by Lukas Bischof on 09.06.18.
//

#ifndef LAUNCHR_CONFIGURATION_H
#define LAUNCHR_CONFIGURATION_H


namespace launchr {
  class Configuration {
  private:
      const char *confpath;
  public:
      Configuration(const char *path);
      bool parse();
  };
};


#endif //LAUNCHR_CONFIGURATION_H
