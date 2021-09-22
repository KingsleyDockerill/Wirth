#include <iostream>
#include <string>
#include <vector>
#include "defs.hpp"

std::string programname = "main";

Var interpret(Node node) {
  Var ret;
  if(node.name == "program") {
    programname = node.str;
    ret = interpret(node.nodes[0]);
  }
  else if(node.name == "mainblock") {
    ret = interpret(node.nodes[0]);
  }
  else if(node.name == "func") {
    std::string funcname;
    funcname = node.nodes[0].str;
    node.nodes.erase(node.nodes.begin());
    std::vector<Var> args;
    int i;
    for(i = 0; i <= node.linepos; i++) {
      args.push_back(interpret(node.nodes[i]));
    }
    if(funcname == "println") {
      wirth_println(args);
    }
    if(node.next != NULL) {
      ret = interpret(*node.next);
    }
  }
  else if(node.name == "int") {
    ret.name = "int";
    ret.int_ = node.int_;
  }
  else if(node.name == "str") {
    ret.name = "str";
    ret.str = node.str;
  }
  else if(node.name == "dec") {
    ret.name = "dec";
    ret.str = node.dec;
  }
  return ret;
}