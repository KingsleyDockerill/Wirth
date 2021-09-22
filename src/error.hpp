#pragma once

#include <string>

class GenericException {
  public :
    std::string msg;
    GenericException(std::string msg) {
      this->msg = msg;
    }
    const char* what() {
      return msg.c_str();
    }
};