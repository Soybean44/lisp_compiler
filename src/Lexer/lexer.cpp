#include "lexer.h"
#include <iostream>

Lexer::Lexer() {
	name = "bob";
}

void Lexer::greet() {
	std::cout << "Hello " << name << "!\n";
}
