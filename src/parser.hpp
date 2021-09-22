#pragma once

#include "defs.hpp"

namespace Parser {
  bool mainblock;
  std::vector<Token> toks;
  long long tokpos = 0;
  Node basictypecatch() {
    Node ret;
    if(toks[tokpos].name == "int") {
      ret.name = "int";
      ret.int_ = toks[tokpos].val.int_;
    }
    else if(toks[tokpos].name == "dec") {
      ret.name = "dec";
      ret.dec = toks[tokpos].val.dec;
    }
    else if(toks[tokpos].name == "str") {
      ret.name = "str";
      ret.str = toks[tokpos].val.str;
    }
    return ret;
  }
  Node keys() {
    Node ret = basictypecatch();
    if(toks[tokpos].name == "key") {
      if(toks[tokpos + 1].name == "lparen") {
        ret.name = "func";
        Node name;
        name.name = "name";
        name.str = toks[tokpos].val.str;
        ret.nodes.push_back(name);
        tokpos += 2;
        while(toks[tokpos].name != "rparen") {
          Node temp = keys();
          ret.nodes.push_back(temp);
          tokpos++;
          if(toks[tokpos].name != "rparen" && toks[tokpos].name != "comma") {
            throw GenericException("Got unexpected token");
          }
          else if(toks[tokpos].name == "comma") {
            tokpos++;
          }
        }
        tokpos++;
        if(toks[tokpos].val.str == "end") {
          return ret;
        }
        else {
          tokpos++;
          Node temp = keys();
          ret.next = &temp;
        }
      }
      else if(toks[tokpos].val.str == "begin") {
        mainblock = true;
        tokpos++;
        Node contents = keys();
        if(toks[tokpos].val.str != "end") {
          throw GenericException("Expected end!");
        }
        tokpos++;
        if(toks[tokpos].name == "lineend") {
          mainblock = false;
          ret.name = "block";
        }
        else if(toks[tokpos].name == "stop") {
          ret.name = "mainblock";
        }
        else {
          throw GenericException("Must have line end or stop at end!");
        }
        ret.nodes.push_back(contents);
      }
      else if(toks[tokpos].val.str == "program") {
        if(toks[tokpos].name != "key") {
          throw GenericException("Program name must be a stringthat doesn't start with a digit and only contains a-z, A-Z, 0-9, or _");
        }
        tokpos++;
        ret.name = "program";
        while(toks[tokpos].name != "lineend") {
          ret.str += toks[tokpos].val.str;
          ret.str += " ";
          tokpos++;
        }
        tokpos++;
        ret.str += "\b";
        Node next = keys();
        ret.linepos = ret.nodes.size();
        ret.nodes.push_back(next);
        tokpos++;
      }
    }
    return ret;
  }
  Node parse(std::vector<Token> toks_) {
    toks = toks_;
    return keys();
  }
}