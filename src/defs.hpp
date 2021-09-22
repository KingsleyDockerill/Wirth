#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "error.hpp"

typedef struct {
  std::string str;
  long long int_;
  double dec;
} lexervalue;

class Token {
  public:
    std::string name, type;
    lexervalue val;
    Token() { }
    Token(std::string name, std::string type, lexervalue val) {
      this->name = name;
      this->type = type;
      this->val = val;
    }
};

class Node {
  public:
    std::string name;
    std::string str;
    long long int_;
    double dec;
    long long linepos;
    std::vector<Node> nodes;
    Node* next;
};

class Var {
  public:
    std::string name;
    std::string str;
    long long int_;
    double dec;
};

std::string total_output;

typedef std::vector<Var> wirthargs;
void wirth_println(wirthargs args) {
  for(Var a: args) {
    if(a.name == "str") {
      std::puts(a.str.c_str());
    }
    else if(a.name == "dec") {
      std::cout << a.dec << "\n";
    }
    else if(a.name == "int") {
      std::cout << a.int_ << "\n";
    }
    else {
      throw GenericException("println got non-basic type");
    }
  }
}