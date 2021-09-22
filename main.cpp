#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "src/lexer.hpp"
#include "src/parser.hpp"
#include "src/interpreter.hpp"
#include "src/error.hpp"

int main() {
  try {
    std::string filename;
    std::cout << "Enter file name to run: ";
    getline(std::cin, filename);
    std::ifstream file{filename};
    if(!file) {
      throw GenericException("Could not open file!");
    }
    std::string input;
    while(file) {
      std::string temp;
      file >> temp;
      input += temp;
      input += ' ';
    }
    std::vector<Token> toks = generate(input);
    Node node = Parser::parse(toks);
    interpret(node);
  }
  catch (GenericException &e) {
    std::cerr << e.what() << std::endl;
  }
}