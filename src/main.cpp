#include "lexer.h"
#include "parser.h"

#include <iostream>
#include <string>

int main() {
	std::cout << "Starting parsing\n";
	Lexer l("(+ 9 (+ 5 5)) (+ 9 10) (print \"Hello world!\")");
	AST_Node ast(AST_ROOT);
	ast.createAST(&l);
	ast.printAST();
	return 0;
}

