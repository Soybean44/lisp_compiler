#include "lexer.h"
#include <iostream>

int main() {
	Lexer lex_freedman("(+ 12 21)");
	Token tok = lex_freedman.next();
	while (tok.type != T_EOF) {
		std::cout << tok.contents << "\n";
		tok = lex_freedman.next();
	}
	return 0;
}
