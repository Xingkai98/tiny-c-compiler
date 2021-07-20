#include <iostream>
#include "lexer.h"
#include "Parser.h"

int main(int, char**) {
    std::string input;
    std::getline(std::cin, input);
    Parser p(input);
	p.parse();
}
