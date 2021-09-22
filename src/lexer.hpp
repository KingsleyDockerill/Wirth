#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "defs.hpp"
#include "error.hpp"

long long count(std::string str, char chr) {
  long long counter = 0;
  for(auto a: str) {
    if(a == chr) {
      counter++;
    }
  }
  return counter;
}

std::vector<Token> generate(std::string input) {
  std::vector<Token> toks;
  for(int i = 0; i < input.size(); i++) {
    switch(input[i]) {
      case '{' :
        while(input[i] != '}') {
          i++;
        }
        break;
      case ' ' :
        break;
      case '\t' :
        break;
      case '(' : {
        lexervalue val;
        val.str = "(";
        toks.push_back(Token("lparen", "str", val));
        break;
      }
      case ')' : {
        lexervalue val;
        val.str = ")";
        toks.push_back(Token("rparen", "str", val));
        break;
      }
      case '"' : {
        std::string str;
        while(input[++i] != '"') {
          str += input[i];
        }
        lexervalue val;
        val.str = str;
        toks.push_back(Token("str", "str", val));
        break;
      }
      case '\'' : {
        std::string str;
        while(input[++i] != '\'') {
          str += input[i];
        }
        lexervalue val;
        val.str = str;
        toks.push_back(Token("str", "str", val));
        break;
      }
      case ',' : {
        lexervalue val;
        val.str = ",";
        toks.push_back(Token("comma", "str", val));
      }
      case ';' : {
        lexervalue val;
        val.str = ".";
        toks.push_back(Token("lineend", "str", val));
        break;
      }
      case '.' : {
        lexervalue val;
        val.str = ".";
        toks.push_back(Token("stop", "str", val));
        break;
      }
      default : {
        std::string num;
        if(std::isdigit(input[i]) || input[i] == '.') {
          while(std::isdigit(input[i]) || input[i] == '.') {
            num += input[i];
            i++;
          }
          std::string name, type;
          lexervalue val;
          if(count(num, '.') == 1 && num.size() > 1) {
            name = "dec";
            type = "dec";
            val.dec = std::stod(num);
          }
          else if(count(num, '.') > 0) {
            // Implement later... func or var name
          }
          else {
            name = "int";
            name = "int";
            try {
              val.int_ = std::stoll(num);
            }
            catch(std::out_of_range) {
              throw GenericException("Num too large for int");
            }
          }
          toks.push_back(Token(name, type, val));
        }
        else if(std::isalpha(input[i]) || input[i] == '_') {
          std::string key;
          while((std::isalpha(input[i]) || input[i] == '_' || std::isdigit(input[i])) && !std::isspace(input[i])) {
            key += input[i];
            i++;
          }
          std::string name, type;
          lexervalue val;
          name = "key";
          type = "str";
          val.str = key;
          toks.push_back(Token(name, type, val));
        }
        else {
          throw GenericException(std::string("Illegal char ") + input[i] + "!");
        }
        i--;
        break;
      }
    }
  }
  return toks;
}