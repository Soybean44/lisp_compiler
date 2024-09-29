#include "lexer.h"
#include "parser.h"
#include "compiler.h"

#include <iostream>
#include <string>

int main() {
	std::cout << "Starting parsing\n";
	Lexer l("(println \"Hello\" \"World!\") (println \"Hello world 2!\")");
	AST_Node ast(AST_ROOT);
	ast.createAST(&l);
	interpretAST(&ast);
	return 0;
}

