#pragma once
#include "enviroment.cpp"
#include <string>

#ifdef ENV_PROD
  std::string api = "https://api.bytecube.tk";
#else
  #ifdef ENV_DEV
    std::string api = "http://localhost:" + "3000";
  #endif
#endif
